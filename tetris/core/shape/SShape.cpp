#include "SShape.h"

const shared_ptr<SShape::Canvas> SShape::Forms[FormsCount]{
	shared_ptr<SShape::Canvas>(new Canvas({ { 0,1,1 },{ 1,1,0 } })),
	shared_ptr<SShape::Canvas>(new Canvas({ { 1,0 },{ 1,1 },{ 0,1 } })),
};
