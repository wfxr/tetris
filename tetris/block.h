#pragma once

#include <vector>
#include <memory>

#include "AllShapes.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

class Block {
private:
	int _posV;
	int _posH;
	shared_ptr<Shape> _shape;
public:
	Block(shared_ptr<Shape> shape, int posH = 0, int posV = 0) : 
		_posH(posH), _posV(posV), _shape(shape) { }

	static shared_ptr<Block> CreateBlock(ShapeCategory type, int posH = 0, int posV = 0, int form = 0) {
		switch (type) {
		case ShapeCategory::Square:
				return make_shared<Block>(make_shared<Square>(), posH, posV);
		case ShapeCategory::Stick:
				return make_shared<Block>(make_shared<Stick>(), posH, posV);
		case ShapeCategory::Bulge:
				return make_shared<Block>(make_shared<Bulge>(), posH, posV);
		case ShapeCategory::LShape:
				return make_shared<Block>(make_shared<LShape>(), posH, posV);
		case ShapeCategory::JShape:
				return make_shared<Block>(make_shared<JShape>(), posH, posV);
		case ShapeCategory::ZShape:
				return make_shared<Block>(make_shared<ZShape>(), posH, posV);
		case ShapeCategory::SShape:
				return make_shared<Block>(make_shared<SShape>(), posH, posV);
		default:
				return make_shared<Block>(make_shared<Square>(), posH, posV);
		}
	}

	int width() const { return _shape->width(); }
	int height() const { return _shape->height(); }
	int posH() const { return _posH; }
	int posH(int h) { _posH = h; }
	int posV() const { return _posV; }
	int posV(int v) { _posV = v; }
	void shiftUp() { --_posV; }
	void shiftDown() { ++_posV; }
	void shiftLeft() { --_posH; }
	void shiftRight() { ++_posH; }
	void rotate() { _shape->rotate(); }
	void contrarotate() { _shape->contrarotate(); }
	int get(int row, int col) const { return _shape->get(row, col); }
};