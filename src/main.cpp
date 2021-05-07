#include "Game.h"
#include "Util/Random.h"
#include "Util/util.h"
#include <iostream>

int main()
{
	std::unique_ptr<Game> game(new Game("Test", 1280, 720));
	return game->run();
}