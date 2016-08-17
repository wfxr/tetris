#include "ConsoleTetris.h"

int main() {
    auto game = ConsoleTetris::Create(20, 10);
    game->run();
}