#pragma once

#include <memory>

#include "shape.h"

using std::shared_ptr;
using std::make_shared;

class Stick : public Shape {
public:
	Stick(int form = 0) { 
		_currentForm = form % FormsCount;
		setCanvas(Forms[_currentForm]);
	}

	virtual int formCount() override { return FormsCount; }
	virtual	void updateForm() override { setCanvas(Forms[_currentForm]); }
	virtual shared_ptr<Shape> clone() const {
		auto ret = make_shared<Stick>();
		ret->_currentForm = _currentForm;
		ret->_canvas = make_shared<Canvas>(*_canvas);
		return ret;
	}
private:
	static const int FormsCount = 2;
	static const shared_ptr<Canvas> Forms[FormsCount];
};