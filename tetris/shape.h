#pragma once

#include <vector>
using std::vector;
using std::swap;

class Shape {
public:
	Shape(int height, int width) :_height(height), _width(width),
		_canvas(height, vector<int>(width)) { }

	int width() const { return _width; }
	int height() const { return _height; }
	int get(int row, int col) const { return _canvas[row][col]; }

	void rotate() {
		vector<vector<int>> new_canvas(width(), vector<int>(height()));
		for (int r = 0; r < height(); ++r)
			for (int c = 0; c < width(); ++c)
				new_canvas[c][r] = _canvas[r][c];
		swap(_height, _width);
		_canvas = new_canvas;
	}

	static Shape ofZ() {
		Shape shape(2, 3);
		shape.setAll();
		shape.unset(1, 0);
		shape.unset(0, 2);
		return shape;
	}

	static Shape ofSquare() {
		Shape shape(2, 2);
		shape.setAll();
		return shape;
	}

	static Shape ofStick() {
		Shape shape(4, 1);
		shape.setAll();
		return shape;
	}

	static Shape ofBulge() {
		Shape shape(2, 3);
		shape.setAll(false);
		shape.setTopLeftCorner();
		shape.setTopRightCorner();
		shape.flip();
		return shape;
	}

	void flip() {
		for (auto& row : _canvas)
			for (auto& e : row)
				e = (e == 1) ? 0 : 1;
	}
private:
	vector<vector<int>> _canvas;
	int _height;
	int _width;

	void set(int row, int col) { _canvas[row][col] = 1; }
	void unset(int row, int col) { _canvas[row][col] = 0; }
	void setAll(int value = 1) {
		for (auto& row : _canvas)
			for (auto& cell : row)
				cell = value;
	}

	void setTopLeftCorner(bool value = true) { _canvas.front().front() = value; }
	void setTopRightCorner(bool value = true) { _canvas.front().back() = value; }
	void setTottomLeftCorner(bool value = true) { _canvas.back().front() = value; }
	void setTottomRightCorner(bool value = true) { _canvas.back().back() = value; }
};