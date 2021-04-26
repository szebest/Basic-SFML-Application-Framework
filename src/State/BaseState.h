#ifndef BASESTATE_H
#define BASESTATE_H

#include <SFML/Graphics.hpp>
#include "../Resources/Holder.h"

class Game;

class BaseState
{
public:
	BaseState(Game& _game)
		: m_game(&_game)
	{

	}

	virtual ~BaseState() = default;

	virtual void handleEvents(sf::Event e) = 0;

	virtual void update() = 0;

	virtual void draw(sf::RenderTarget& target) = 0;

protected:
	Game* m_game = nullptr;
};

#endif

