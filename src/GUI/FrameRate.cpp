#include "FrameRate.h"

FrameRate::FrameRate(sf::Vector2f pos) :
	Text(pos, "FPS: -%")
{
	setArgs(&m_fps);
	setColor(sf::Color::Red);
	setCharSize(32);
	setOutlineColor(sf::Color::White);

	setFixedPos(true);
}

void FrameRate::handleEvents(sf::Event e, const sf::RenderWindow& window, sf::Vector2f displacement)
{

}

void FrameRate::update(const sf::Time& deltaTime)
{
	m_fps = 1 / deltaTime.asSeconds();

	Text::update(deltaTime);
}

void FrameRate::draw(sf::RenderTarget& target)
{
	Text::draw(target);
}

const float* FrameRate::getFpsPointer()
{
	return &m_fps;
}