#pragma once

#include "shape.h"

class Square : public Shape {
public:
	Square(int form = 0) : Shape(2, 2) { setAll(); }
};