#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "../GUI/Button.h"
#include "../Game.h"

class MenuState : public BaseState
{
public:
	MenuState(Game& _game);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update() override;

	void draw(sf::RenderTarget& target) override;
private:
	std::vector<std::unique_ptr<Widget>> m_widgets;
};

#endif

