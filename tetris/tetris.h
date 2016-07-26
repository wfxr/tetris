#pragma once
#include <thread>
#include <chrono>
#include <conio.h>
#include <random>
#include <cctype>

#include "block.h"
#include "board.h"

using std::toupper;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std::chrono_literals;

class Tetris {
private:
	Block _currBlock;
	Board _board;
	system_clock::time_point time;

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
		for (int h = 0; h < _currBlock.width(); ++h) {
			for (int v = 0; v < _currBlock.height(); ++v)
				if (_currBlock.get(v, h) && _board.get(v + _currBlock.posV(), h + _currBlock.posH()))
					return true;
		}
		return false;
	}

	bool topOversetp() const { return _currBlock.posV() < 0; }
	bool leftOverstep() const { return _currBlock.posH() < 0; }
	bool bottomOverstep() const { return _currBlock.posV() + _currBlock.height() > _board.height(); }
	bool rightOverstep() const { return _currBlock.posH() + _currBlock.width() > _board.width(); }

	void rotate() { 
		_currBlock.rotate();
		if (bottomOverstep() || rightOverstep() || leftOverstep() || isOverlap())
			rotate();
		repaint();
	}

	void stackBlock() { _board = intersection(_board, _currBlock); }

	bool shiftDown() { 
		_currBlock.shiftDown();
		if (bottomOverstep() || isOverlap()) {
			_currBlock.shiftUp();
			return false;
		}
		repaint();
		return true;
	}

	bool shiftLeft() {
		_currBlock.shiftLeft();
		if (leftOverstep() || isOverlap()) {
			_currBlock.shiftRight();
			return false;
		}
		repaint();
		return true;
	}

	bool shiftRight() {
		_currBlock.shiftRight();
		if (rightOverstep() || isOverlap()) {
			_currBlock.shiftLeft();
			return false;
		}
		repaint();
		return true;
	}

	void repaint() const {
		auto board = intersection(_board, _currBlock);
		board.paint();
	}

	Block randomBlock() {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(1, 5);

		switch (dis(gen)) {
		case 1:
			return Block(Shape::ofSquare(), 4);
		case 2:
			return Block(Shape::ofStick(), 4);
		case 3:
			return Block(Shape::ofBulge(), 4);
		case 4:
			return Block(Shape::ofZ(), 4);
		case 5:
			return Block(Shape::ofL(), 4);
		}
	}

	void readOpeartion() {
		for (;;) {
			auto current = system_clock::now();
			if (current - time > 300ms) {
				time = current;
				return;
			}

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
public:
	Tetris() : _currBlock(randomBlock()), _board() { }

	void run() {
		time = system_clock::now();

		for (;;) {
			repaint();
			do {
				readOpeartion();
			} while (shiftDown());
			stackBlock();
			_currBlock = randomBlock();
		}
	}
};