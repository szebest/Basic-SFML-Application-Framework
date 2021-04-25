#include "MenuState.h"


#include <iostream>

MenuState::MenuState(Game& _game)
	: BaseState(_game)
{
	
}

void MenuState::handleEvents(sf::Event e)
{
	
}

void MenuState::update()
{

}

void MenuState::draw(sf::RenderTarget& target)
{
	sf::CircleShape shape;
	shape.setPosition(100, 100);
	shape.setRadius(50);
	shape.setFillColor(sf::Color::Blue);

	target.draw(shape);
}
