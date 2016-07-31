#pragma once

#include <vector>
#include <memory>
#include <random>

#include "AllShapes.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

class Block {
private:
	int _v;
	int _h;
	shared_ptr<Shape> _shape;
public:
	static const int ShapesCount = static_cast<int>(ShapeCategory::Count);

	Block(shared_ptr<Shape> shape, int h = 0, int v = 0) : 
		_h(h), _v(v), _shape(shape) { }
	Block(const Block& block) :
		_h(block._h), _v(block._v) , _shape(block._shape->clone()) { }

	static shared_ptr<Block> CreateBlock(ShapeCategory type, int posH = 0, int posV = 0, int form = 0) {
		switch (type) {
		case ShapeCategory::Square:
				return make_shared<Block>(make_shared<Square>(form), posH, posV);
		case ShapeCategory::Stick:
				return make_shared<Block>(make_shared<Stick>(form), posH, posV);
		case ShapeCategory::Bulge:
				return make_shared<Block>(make_shared<Bulge>(form), posH, posV);
		case ShapeCategory::LShape:
				return make_shared<Block>(make_shared<LShape>(form), posH, posV);
		case ShapeCategory::JShape:
				return make_shared<Block>(make_shared<JShape>(form), posH, posV);
		case ShapeCategory::ZShape:
				return make_shared<Block>(make_shared<ZShape>(form), posH, posV);
		case ShapeCategory::SShape:
				return make_shared<Block>(make_shared<SShape>(form), posH, posV);
		default:
				return make_shared<Block>(make_shared<Square>(form), posH, posV);
		}
	}

	static shared_ptr<Block> RandomBlock() {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> typeRand(0, ShapesCount - 1);
		uniform_int_distribution<> formRand;

		auto type = static_cast<ShapeCategory>(typeRand(gen));
		auto form = formRand(gen);
		return Block::CreateBlock(type, 0, 0, form);
	}

	int width() const { return _shape->width(); }
	int height() const { return _shape->height(); }

	int left() const { return _h; }
	int top() const { return _v; }
	int right() const { return _h + width(); }
	int bottom() const { return _v + height(); }

	void shiftUp() { --_v; }
	void shiftDown() { ++_v; }
	void shiftLeft() { --_h; }
	void shiftRight() { ++_h; }
	void rotate() { _shape->rotate(); }
	void contrarotate() { _shape->contrarotate(); }

	int at(int h, int v) const { return _shape->at(h - left(), v - top()); }
	void setPosition(int x, int y) { 
		_h = x;
		_v = y;
	}
};