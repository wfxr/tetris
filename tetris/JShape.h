#pragma once

#include <memory>

#include "shape.h"

using std::shared_ptr;
using std::make_shared;

class JShape : public Shape {
public:
	JShape(int form = 0) { 
		_currentForm = form % formCount();
		setCanvas(Forms[_currentForm]);
	}

	virtual int formCount() override { return FormsCount; }
	virtual	void updateForm() override { setCanvas(Forms[_currentForm]); }
	virtual shared_ptr<Shape> clone() const {
		auto ret = make_shared<JShape>();
		ret->_currentForm = _currentForm;
		ret->_canvas = make_shared<Canvas>(*_canvas);
		return ret;
	}
private:
	static const int FormsCount = 4;
	static const shared_ptr<Canvas> Forms[FormsCount];
};
