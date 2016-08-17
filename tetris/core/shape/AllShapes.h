#pragma once

#include "Shape.h"
#include "Bulge.h"
#include "Stick.h"
#include "Square.h"
#include "LShape.h"
#include "JShape.h"
#include "ZShape.h"
#include "SShape.h"

enum class ShapeCategory {
	Square,
	Stick,
	Bulge,
	LShape,
	ZShape,
	JShape,
	SShape,

	// Count of all categories
	Count
};