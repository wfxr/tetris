#pragma once

struct Position {
	Position(int x, int y) : X(x), Y(y) {}
	Position() : Position(0, 0) {}
	int X;
	int Y;
};