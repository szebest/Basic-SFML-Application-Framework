#include "Game.h"
#include "Util/Random.h"
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<Game> game(new Game("Test", 1280, 720));
    return game->run();
}