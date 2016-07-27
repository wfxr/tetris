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
public:
	Shape(int height, int width);
	int width() const;
	int height() const;
	int get(int row, int col) const;

	void rotate() { nextForm(); }
	void contrarotate() { prevForm(); }

protected:
	Shape();
	void setCanvas(shared_ptr<Canvas> canvas);
	void set(int row, int col);
	void unset(int row, int col);
	void setAll(int value = 1);
	void setTopLeftCorner(int value = 1);
	void setTopRightCorner(int value = 1);
	void setTottomLeftCorner(int value = 1);
	void setTottomRightCorner(int value = 1);

	virtual int getFormCount() { return 1; }
	virtual shared_ptr<Canvas> currentCanvas() { return _canvas; }

	void updateForm() { setCanvas(currentCanvas()); }

	void nextForm() {
		++_currentForm;
		if (_currentForm == getFormCount())
			_currentForm = 0;
		updateForm();
	}

	void prevForm() {
		--_currentForm;
		if (_currentForm == -1)
			_currentForm = getFormCount() - 1;
		updateForm();
	}

	int _currentForm = 0;
private:
	shared_ptr<Canvas> _canvas;
};