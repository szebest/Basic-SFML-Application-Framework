#include "MenuState.h"

#include <iostream>

MenuState::MenuState(Game& _game)
	: BaseState(_game)
{
	auto m_button1 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f, sf::Vector2f(200, 100), "Button 1");

	m_button1->setFunction([]()
		{
			std::cout << "Button 1 was pressed\n";
		}
	);

	auto m_button2 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f + sf::Vector2f(0, 150), sf::Vector2f(200, 100), "Button 2");

	m_button2->setFunction([]()
		{
			std::cout << "Button 2 was pressed\n";
		}
	);

	m_widgets.push_back(std::move(m_button1));
	m_widgets.push_back(std::move(m_button2));
}

void MenuState::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	for (auto& widget : m_widgets)
		widget->handleEvents(e, window);
}

void MenuState::update()
{
	for (auto& widget : m_widgets)
		widget->update();
}

void MenuState::draw(sf::RenderTarget& target)
{
	for (auto& widget : m_widgets)
		widget->draw(target);
}
