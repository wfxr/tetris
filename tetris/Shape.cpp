#include "Shape.h"

Shape::Shape(int height, int width) : _canvas(make_shared<Canvas>(height, vector<int>(width))) { }

int Shape::get(int row, int col) const { return (*_canvas)[row][col]; }

int Shape::width() const { return _canvas->front().size(); }

int Shape::height() const { return _canvas->size(); }

Shape::Shape() {}

void Shape::setCanvas(shared_ptr<Canvas> canvas) { _canvas = canvas; }

inline void Shape::set(int row, int col) { (*_canvas)[row][col] = 1; }

inline void Shape::unset(int row, int col) { (*_canvas)[row][col] = 0; }

void Shape::setAll(int value) {
	for (auto& row : (*_canvas))
		for (auto& cell : row)
			cell = value;
}

void Shape::setTopLeftCorner(int value /*= 1*/) { _canvas->front().front() = value; }

void Shape::setTopRightCorner(int value /*= 1*/) { _canvas->front().back() = value; }

void Shape::setTottomLeftCorner(int value /*= 1*/) { _canvas->back().front() = value; }

void Shape::setTottomRightCorner(int value /*= 1*/) { _canvas->back().back() = value; }
