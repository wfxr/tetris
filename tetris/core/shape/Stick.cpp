#include "Stick.h"

const shared_ptr<Stick::Canvas> Stick::Forms[FormsCount]{
	shared_ptr<Stick::Canvas>(new Canvas({{1,1,1,1}})),
	shared_ptr<Stick::Canvas>(new Canvas({{1},{1},{1},{1}})),
};