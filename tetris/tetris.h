#pragma once
#include <thread>

#include "block.h"
#include "board.h"

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

class Tetris {
private:
	Block _currBlock;
	Board _board;

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
public:
	Tetris() : _currBlock(Shape::ofSquare()), _board() { }

	void run() {
		int speed = 20;
		do {
			sleep_for(milliseconds(speed));
			rotate();
		} while (shiftDown());
		stackBlock();

		_currBlock = Shape::ofBulge();
		do {
			sleep_for(milliseconds(speed));
			rotate();
		} while (shiftDown());
		stackBlock();

		_currBlock = Shape::ofStick();
		do {
			sleep_for(milliseconds(speed));
			rotate();
		} while (shiftDown());
		stackBlock();

		_currBlock = Shape::ofZ();
		do {
			sleep_for(milliseconds(speed));
			rotate();
		} while (shiftDown());
		stackBlock();
	}
};