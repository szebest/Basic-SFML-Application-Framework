#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"

class MenuState : public BaseState
{
public:
	MenuState();

	void handleEvents() override;

	void update() override;

	void draw(sf::RenderTarget& target) override;
private:
};

#endif

