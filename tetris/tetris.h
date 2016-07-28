#pragma once
#include <thread>
#include <chrono>
#include <conio.h>
#include <random>
#include <cctype>
#include <memory>
#include <iostream>
#include <thread>

#include "Block.h"
#include "Board.h"
#include "ConsoleUtility.h"

using std::this_thread::sleep_for;
using std::shared_ptr;
using std::make_shared;
using std::toupper;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::cout;
using std::endl;
using namespace std::chrono_literals;

class Tetris {
private:
	Board _board;
	shared_ptr<Block> _curr;
	system_clock::time_point time;
	static const int BlockShapesCount = static_cast<int>(ShapeCategory::Count);

	bool isOverlap() const { return isOverlap(*_curr); }
	bool isOverlap(const Block& block) const {
		for (int h = block.left(); h < block.right(); ++h)
			for (int v = block.top(); v < block.bottom(); ++v)
				if (block.at(h, v) && _board.at(h, v))
					return true;
		return false;
	}

	bool reachLeftBorder() const { return _curr->left() == 0; }
	bool reachRightBorder() const { return _curr->right() == _board.width(); }
	bool reachBottomBorder() const { return _curr->bottom() == _board.height(); }

	void stackBlock() { 
		for (int h = _curr->left(); h < _curr->right(); ++h)
			for (int v = _curr->top(); v < _curr->bottom(); ++v)
				if (_curr->at(h, v)) _board.set(h, v);
	}

	bool rotate() { 
		if (!canRotate()) return false;

		erase();
		_curr->rotate();
		repaint();
		return true;
	}

	bool canRotate() {
		Block block(*_curr);
		block.rotate();

		if (block.right() > _board.width() || block.bottom() > _board.height())
			return false;

		return !isOverlap(block);
	}

	bool canShiftLeft() {
		if (reachLeftBorder())
			return false;
		for (int h = _curr->left(); h < _curr->right(); ++h)
			for (int v = _curr->top(); v < _curr->bottom(); ++v)
				if (_curr->at(h, v) && _board.at(h - 1, v))
					return false;
		return true;
	}

	bool canShiftRight() {
		if (reachRightBorder())
			return false;
		for (int h = _curr->left(); h < _curr->right(); ++h)
			for (int v = _curr->top(); v < _curr->bottom(); ++v)
				if (_curr->at(h, v) && _board.at(h + 1, v))
					return false;
		return true;
	}

	bool canShiftDown() {
		if (reachBottomBorder())
			return false;
		for (int h = _curr->left(); h < _curr->right(); ++h)
			for (int v = _curr->top(); v < _curr->bottom(); ++v)
				if (_curr->at(h, v) && _board.at(h, v + 1))
					return false;
		return true;
	}

	bool shiftDown() { 
		if (!canShiftDown()) return false;

		erase();
		_curr->shiftDown();
		repaint();
		return true;
	}

	bool shiftLeft() {
		if (!canShiftLeft()) return false;

		erase();
		_curr->shiftLeft();
		repaint();
		return true;
	}

	bool shiftRight() {
		if (!canShiftRight()) return false;

		erase();
		_curr->shiftRight();
		repaint();
		return true;
	}

	void erase() const {
		repaint("  ");
	}

	void repaint(char* brush = "¨~") const {
		for (int v = _curr->top(); v < _curr->bottom(); ++v) {
			CursorGoto(1 + _curr->left() * 2, 1 + v);
			for (int h = _curr->left(); h < _curr->right(); ++h) {
				if (_curr->at(h, v))
					cout << brush;
				else
					CursorRight(2);
			}
		}
	}

	shared_ptr<Block> randomBlock() {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, BlockShapesCount - 1);

		int horizontalCenter = _board.width() / 2 - 1;
		auto type = static_cast<ShapeCategory>(dis(gen));
		return Block::CreateBlock(type, horizontalCenter);
	}

	void readOpeartion() {
		time = system_clock::now();
		while (system_clock::now() - time < 300ms) {
			if (_kbhit()) {
				switch (toupper(_getch())) {
				case 'S':
					while(shiftDown());
					readOpeartion();
					break;
				case 'A': 
					shiftLeft();
					break;
				case 'D':
					shiftRight();
					break;
				case 'W':
					rotate();
					break;
				default:
					break;
				}
			}
			sleep_for(50ms);
		}
	}

	bool isGameOver() { return isOverlap(); }

	int eliminateBlocks() {
		auto rows = _board.eliminateRows();
		if (rows)
			_board.paint();
		return rows * rows;
	}
public:
	Tetris(int row = 20, int col = 10) : _board(row, col), _curr(randomBlock()) {
		HideCursor();
	}

	void run() {
		_board.paint();

		time = system_clock::now();
		while (!isGameOver()) {
			repaint();
			do {
				readOpeartion();
			} while (shiftDown());
			stackBlock();
			eliminateBlocks();
			_curr = randomBlock();
		}
	}
};