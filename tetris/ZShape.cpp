#include "ZShape.h"

const shared_ptr<ZShape::Canvas> ZShape::Forms[FormsCount]{
	shared_ptr<ZShape::Canvas>(new Canvas({ { 1,1,0 },{0,1,1} })),
	shared_ptr<ZShape::Canvas>(new Canvas({ { 0,1 },{ 1,1 },{ 1,0 } })),
};
