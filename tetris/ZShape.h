#pragma once

#include <memory>

#include "shape.h"

using std::shared_ptr;
using std::make_shared;

class ZShape : public Shape {
public:
	ZShape() { updateForm(); }

	virtual int getFormCount() override { return FormsCount; }
	virtual shared_ptr<Canvas> currentCanvas() override { return Forms[_currentForm]; }
private:
	static const int FormsCount = 2;
	static const shared_ptr<Canvas> Forms[FormsCount];
};
