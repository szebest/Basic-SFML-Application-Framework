#include "MenuState.h"

#include <iostream>

MenuState::MenuState(Game& _game)
	: BaseState(_game)
{
	auto m_button1 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f, sf::Vector2f(200, 100), "Button 1");

	m_button1->setFunction([&]()
		{
			std::cout << "Button 1 was pressed\n";
			m_active = &m_widgetsAfterClick;
		}
	);

	auto m_button2 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f + sf::Vector2f(0, 150), sf::Vector2f(200, 100), "Exit");

	m_button2->setFunction([&]()
		{
			std::cout << "Exit\n";
			m_game->popState();
		}
	);

	auto m_button11 = makeButton((sf::Vector2f)_game.getWindow().getSize() / 2.f, sf::Vector2f(200, 100), "Button 1.1");

	m_button11->setFunction([&]()
		{
			std::cout << "Button 1.1 was pressed: " + m_input + '\n';
			m_active = &m_widgets;
		}
	);

	auto m_inputForm = makeInputForm((sf::Vector2f)_game.getWindow().getSize() / 2.f - sf::Vector2f(0, 150), sf::Vector2f(400, 50), &m_input);

	auto m_text1 = makeText((sf::Vector2f)_game.getWindow().getSize() / 2.f - sf::Vector2f(0, 250), "-%: -%");

	m_text1->setArgs(&m_input, &m_value);
	m_text1->setColor(sf::Color::Red);
	m_text1->setCharSize(64);
	m_text1->setOutlineThickness(5);
	m_text1->setOutlineColor(sf::Color::White);

	m_widgets.push_back(std::move(m_button1));
	m_widgets.push_back(std::move(m_button2));
	m_widgets.push_back(std::move(m_inputForm));
	m_widgets.push_back(std::move(m_text1));

	m_widgetsAfterClick.push_back(std::move(m_button11));
	//m_widgetsAfterClick.push_back(std::move(m_text1));
}

void MenuState::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	for (auto& widget : *m_active)
		widget->handleEvents(e, window);
}

void MenuState::update()
{
	for (auto& widget : *m_active)
		widget->update();
}

void MenuState::draw(sf::RenderTarget& target)
{
	for (auto& widget : *m_active)
		widget->draw(target);
}
