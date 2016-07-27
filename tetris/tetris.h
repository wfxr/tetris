#pragma once
#include <thread>
#include <chrono>
#include <conio.h>
#include <random>
#include <cctype>
#include <memory>
#include <iostream>

#include "Block.h"
#include "Board.h"

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
	shared_ptr<Block> _currBlock;
	system_clock::time_point time;
	static const int BlockShapesCount = static_cast<int>(ShapeCategory::Count);

	static Board intersection(const Board& board, const Block& block) {
		auto ret = board;
		for (int h = 0; h < block.width(); ++h) {
			for (int v = 0; v < block.height(); ++v)
				if (block.get(v, h))
					ret.set(block.posV() + v, block.posH() + h);
		}
		return ret;
	}

	bool isOverlap() const {
		for (int h = 0; h < _currBlock->width(); ++h) {
			for (int v = 0; v < _currBlock->height(); ++v)
				if (_currBlock->get(v, h) && _board.get(v + _currBlock->posV(), h + _currBlock->posH()))
					return true;
		}
		return false;
	}

	bool topOversetp() const { return _currBlock->posV() < 0; }
	bool leftOverstep() const { return _currBlock->posH() < 0; }
	bool bottomOverstep() const { return _currBlock->posV() + _currBlock->height() > _board.height(); }
	bool rightOverstep() const { return _currBlock->posH() + _currBlock->width() > _board.width(); }

	void rotate() { 
		_currBlock->rotate();
		if (bottomOverstep() || rightOverstep() || leftOverstep() || isOverlap())
			_currBlock->contrarotate();
		repaint();
	}

	void stackBlock() { _board = intersection(_board, *_currBlock); }

	bool shiftDown() { 
		_currBlock->shiftDown();
		if (bottomOverstep() || isOverlap()) {
			_currBlock->shiftUp();
			return false;
		}
		repaint();
		return true;
	}

	bool shiftLeft() {
		_currBlock->shiftLeft();
		if (leftOverstep() || isOverlap()) {
			_currBlock->shiftRight();
			return false;
		}
		repaint();
		return true;
	}

	bool shiftRight() {
		_currBlock->shiftRight();
		if (rightOverstep() || isOverlap()) {
			_currBlock->shiftLeft();
			return false;
		}
		repaint();
		return true;
	}

	void repaint() const {
		auto board = intersection(_board, *_currBlock);
		board.paint();
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
		}
	}

	bool isGameOver() { return isOverlap(); }

	int eliminateBlocks() {
		auto rows = _board.eliminateRows();
		repaint();
		return rows * rows;
	}
public:
	Tetris(int row = 20, int col = 10) : _board(row, col), _currBlock(randomBlock()) { }

	void run() {
		time = system_clock::now();

		while (!isGameOver()) {
			repaint();
			do {
				readOpeartion();
			} while (shiftDown());
			stackBlock();
			eliminateBlocks();
			_currBlock = randomBlock();
		}
	}
};