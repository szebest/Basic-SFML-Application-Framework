#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "State\MenuState.h"

class Game
{
public:
	Game(std::string&&, unsigned int, unsigned int);

	const sf::RenderWindow& getWindow() const;

	int run();

	void pushState(std::unique_ptr<BaseState> _ptr);

	void popState();

	BaseState& getCurrentState();
private:
	void handleEvent();

	sf::RenderWindow m_window;

	std::vector<std::unique_ptr<BaseState>> m_states;
};

#endif
