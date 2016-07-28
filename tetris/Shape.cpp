#include "Shape.h"

Shape::Shape(int height, int width) : _canvas(make_shared<Canvas>(height, vector<int>(width))) { }

int Shape::at(int h, int v) const { return (*_canvas)[v][h]; }

int Shape::width() const { return _canvas->front().size(); }

int Shape::height() const { return _canvas->size(); }

Shape::Shape() {}

void Shape::setCanvas(shared_ptr<Canvas> canvas) { _canvas = canvas; }

void Shape::setAll(int value) {
	for (auto& row : (*_canvas))
		for (auto& cell : row)
			cell = value;
}

void Shape::setTopLeftCorner(int value /*= 1*/) { _canvas->front().front() = value; }

void Shape::setTopRightCorner(int value /*= 1*/) { _canvas->front().back() = value; }

void Shape::setTottomLeftCorner(int value /*= 1*/) { _canvas->back().front() = value; }

void Shape::setTottomRightCorner(int value /*= 1*/) { _canvas->back().back() = value; }
