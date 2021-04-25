#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "../Game.h"

class MenuState : public BaseState
{
public:
	MenuState(Game& _game);

	void handleEvents(sf::Event e) override;

	void update() override;

	void draw(sf::RenderTarget& target) override;
private:
	bool m_draw = false;
};

#endif

