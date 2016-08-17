#include "JShape.h"

const shared_ptr<JShape::Canvas> JShape::Forms[FormsCount]{
	shared_ptr<JShape::Canvas>(new Canvas({ { 0,1 },{ 0,1 },{ 1,1 } })),
	shared_ptr<JShape::Canvas>(new Canvas({ { 1,0,0 },{ 1,1,1 } })),
	shared_ptr<JShape::Canvas>(new Canvas({ { 1,1 },{ 1,0 },{ 1,0 } })),
	shared_ptr<JShape::Canvas>(new Canvas({ { 1,1,1 },{ 0,0,1 } })),
};
