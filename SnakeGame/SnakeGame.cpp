#include "Game.h"
#include <iostream>

int main()
{
    Game game;
    if (!game.Init()) {
        std::cerr << "GAME START FAILED!"<< std::endl;
        return -1;
    }
    game.Run();
    return 0;
}
