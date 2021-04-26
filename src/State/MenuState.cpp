#include "MenuState.h"


#include <iostream>

MenuState::MenuState(Game& _game)
	: BaseState(_game)
{
	text.setPosition(m_game->getWindow().getSize().x / 2.f, m_game->getWindow().getSize().y / 2.f);
	text.setFont(holder::get().fonts.get("arial"));
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::White);

	cooldown.restart();
}

void MenuState::handleEvents(sf::Event e)
{
	
}

void MenuState::update()
{
	if (cooldown.getElapsedTime().asSeconds() >= 4)
	{
		m_game->popAndPushState(std::unique_ptr<MenuState>(new MenuState(*m_game)));
	}
}

void MenuState::draw(sf::RenderTarget& target)
{
	text.setString("Test");

	if (cooldown.getElapsedTime().asSeconds() >= 2)
		target.draw(text);
}
