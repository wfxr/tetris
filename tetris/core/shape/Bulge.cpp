#include "Bulge.h"

const shared_ptr<Bulge::Canvas> Bulge::Forms[FormsCount]{
	shared_ptr<Bulge::Canvas>(new Canvas({{0,1,0},{1,1,1}})),
	shared_ptr<Bulge::Canvas>(new Canvas({{1,0},{1,1},{1,0}})),
	shared_ptr<Bulge::Canvas>(new Canvas({{1,1,1},{0,1,0}})),
	shared_ptr<Bulge::Canvas>(new Canvas({{0,1},{1,1},{0,1}})),
};
