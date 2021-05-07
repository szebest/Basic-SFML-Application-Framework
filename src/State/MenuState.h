#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
#include "../GUI/Button.h"
#include "../GUI/InputForm.h"
#include "../GUI/Text.h"
#include "../Game.h"

class MenuState : public BaseState
{
public:
	MenuState(Game& _game);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update() override;

	void draw(sf::RenderTarget& target) override;
private:
	std::string m_input = "";

	int m_value = 5;

	std::vector<std::unique_ptr<Widget>> m_widgets;
	std::vector<std::unique_ptr<Widget>> m_widgetsAfterClick;

	std::vector<std::unique_ptr<Widget>>* m_active = &m_widgets;
};

#endif

