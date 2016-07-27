#include "LShape.h"

const shared_ptr<LShape::Canvas> LShape::Forms[FormsCount]{
	shared_ptr<LShape::Canvas>(new Canvas({{1,0},{1,0},{1,1}})),
	shared_ptr<LShape::Canvas>(new Canvas({{1,1,1},{1,0,0}})),
	shared_ptr<LShape::Canvas>(new Canvas({{1,1},{0,1},{0,1}})),
	shared_ptr<LShape::Canvas>(new Canvas({{0,0,1},{1,1,1}})),
};
