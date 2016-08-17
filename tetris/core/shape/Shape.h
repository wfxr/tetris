#pragma once

#include <vector>
#include <memory>
using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::swap;

class Square;
class Stick;

class Shape {
public:
	using Canvas = vector<vector<int>>;

	Shape(int height, int width);
	Shape(const Shape& shape) 
		: _canvas(make_shared<Canvas>(*shape._canvas)), _currentForm(shape._currentForm) { }

	int width() const;
	int height() const;
	int at(int h, int v) const;

	void rotate() { nextForm(); }
	void contrarotate() { prevForm(); }

	virtual shared_ptr<Shape> clone() const { return make_shared<Shape>(*this); }

protected:
	Shape();
	void setCanvas(shared_ptr<Canvas> canvas);
	void setAll(int value = 1);

	virtual int formCount() { return 1; }
	virtual shared_ptr<Canvas> currentCanvas() { return _canvas; }

	virtual void updateForm() {}

	void nextForm() {
		++_currentForm;
		if (_currentForm == formCount())
			_currentForm = 0;
		updateForm();
	}

	void prevForm() {
		--_currentForm;
		if (_currentForm == -1)
			_currentForm = formCount() - 1;
		updateForm();
	}

	int _currentForm = 0;
	shared_ptr<Canvas> _canvas;
};