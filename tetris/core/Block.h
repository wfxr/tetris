#pragma once

#include <vector>
#include <memory>
#include <random>

#include "Position.h"
#include "shape/AllShapes.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

class Block {
public:
    static const int ShapesCount = static_cast<int>(ShapeCategory::Count);

    explicit Block(shared_ptr<Shape> shape, Position pos = { 0,0 }) : _pos(pos), _shape(shape) { }
    Block(const Block& block) : _pos(block._pos) , _shape(block._shape->clone()) { }

    static shared_ptr<Block> CreateBlock(ShapeCategory type, int form = 0, Position pos = { 0, 0}) {
        switch (type) {
        case ShapeCategory::Square:
                return make_shared<Block>(make_shared<Square>(form), pos);
        case ShapeCategory::Stick:
                return make_shared<Block>(make_shared<Stick>(form), pos);
        case ShapeCategory::Bulge:
                return make_shared<Block>(make_shared<Bulge>(form), pos);
        case ShapeCategory::LShape:
                return make_shared<Block>(make_shared<LShape>(form), pos);
        case ShapeCategory::JShape:
                return make_shared<Block>(make_shared<JShape>(form), pos);
        case ShapeCategory::ZShape:
                return make_shared<Block>(make_shared<ZShape>(form), pos);
        case ShapeCategory::SShape:
                return make_shared<Block>(make_shared<SShape>(form), pos);
        default:
                return make_shared<Block>(make_shared<Square>(form), pos);
        }
    }

    static shared_ptr<Block> RandomBlock() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> typeRand(0, ShapesCount - 1);
        uniform_int_distribution<> formRand;

        auto type = static_cast<ShapeCategory>(typeRand(gen));
        auto form = formRand(gen);
        return CreateBlock(type, form);
    }

    int width() const { return _shape->width(); }
    int height() const { return _shape->height(); }

    int left() const { return _pos.X; }
    int top() const { return _pos.Y; }
    int right() const { return _pos.X + width(); }
    int bottom() const { return _pos.Y + height(); }

    void shiftUp() { --_pos.Y; }
    void shiftDown() { ++_pos.Y; }
    void shiftLeft() { --_pos.X; }
    void shiftRight() { ++_pos.X; }
    void rotate() const { _shape->rotate(); }
    void contrarotate() const { _shape->contrarotate(); }

    int at(int x, int y) const { return _shape->at(x - left(), y - top()); }
    void setPosition(int x, int y) { 
        _pos.X = x;
        _pos.Y = y;
    }
private:
    Position _pos;
    shared_ptr<Shape> _shape;
};