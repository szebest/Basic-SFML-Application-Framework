#ifndef WIDGET_H
#define WIDGET_H

#include "../Resources/Holder.h"

#include <SFML/Graphics.hpp>

class Widget
{
public:
	Widget() = default;

	virtual void handleEvents(sf::Event e, const sf::RenderWindow& window) = 0;

	virtual void update(const sf::Time& deltaTime) = 0;

	virtual void draw(sf::RenderTarget& target) = 0;
private:
};

#endif