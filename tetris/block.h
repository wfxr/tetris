#pragma once

#include <vector>

#include "shape.h"

using std::vector;

class Block {
private:
	int _posV;
	int _posH;
	Shape _shape;
public:
	Block(const Shape& shape, int posH = 0, int posV = 0) : 
		_posH(posH), _posV(posV), _shape(shape) { }

	int width() const { return _shape.width(); }
	int height() const { return _shape.height(); }
	int posH() const { return _posH; }
	int posH(int h) { _posH = h; }
	int posV() const { return _posV; }
	int posV(int v) { _posV = v; }
	void shiftUp() { --_posV; }
	void shiftDown() { ++_posV; }
	void shiftLeft() { --_posH; }
	void shiftRight() { ++_posH; }
	void rotate() { _shape.rotate(); }

	int get(int row, int col) const {
		return _shape.get(row, col);
	}
};