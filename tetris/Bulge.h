#pragma once

#include <memory>

#include "shape.h"

using std::shared_ptr;
using std::make_shared;

class Bulge : public Shape {
public:
	Bulge() { updateForm(); }

	virtual int getFormCount() override { return FormsCount; }
	virtual shared_ptr<Canvas> currentCanvas() override { return Forms[_currentForm]; }
private:
	static const int FormsCount = 4;

	static const shared_ptr<Canvas> Forms[FormsCount];
};