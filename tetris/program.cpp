#include <iostream>

#include "block.h"
#include "board.h"
#include "tetris.h"

int main() {
	Tetris game(20, 10);
	game.run();
}