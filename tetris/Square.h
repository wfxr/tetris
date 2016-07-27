#pragma once

#include "shape.h"

class Square : public Shape {
public:
	Square(int a = 2) : Shape(2, 2) { setAll(); }
};