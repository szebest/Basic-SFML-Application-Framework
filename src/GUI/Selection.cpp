#include "Selection.h"

Selection::Selection(sf::Vector2f pos) :
	m_selected(false)
{
	m_outerShape.setRadius(12);
	m_innerShape.setRadius(10);
	m_innerShape.setFillColor(sf::Color::Blue);
	setPosition(pos);
}

void Selection::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type) {
	case sf::Event::MouseButtonPressed:
	{
		if (e.mouseButton.button == sf::Mouse::Left)
			if (isHovering(window))
				m_selected = !m_selected;
	} break;
	default:
		break;
	}
}

void Selection::update(const sf::Time& deltaTime)
{
	
}

void Selection::draw(sf::RenderTarget& target)
{
	target.draw(m_outerShape);
	if (m_selected)
		target.draw(m_innerShape);
}

void Selection::setPosition(sf::Vector2f pos)
{
	float outerRadius = m_outerShape.getRadius();
	float innerRadius = m_innerShape.getRadius();
	m_outerShape.setPosition(pos - sf::Vector2f(outerRadius, outerRadius));
	m_innerShape.setPosition(pos - sf::Vector2f(innerRadius, innerRadius));
}

sf::Vector2f Selection::getPosition()
{
	float radius = m_outerShape.getRadius();
	return m_outerShape.getPosition() + sf::Vector2f(radius, radius) / 2.f;
}

bool Selection::isHovering(const sf::RenderWindow& window)
{
	auto pixelPos = sf::Mouse::getPosition(window);
	auto worldPos = window.mapPixelToCoords(pixelPos);
	return m_outerShape.getGlobalBounds().contains(worldPos.x, worldPos.y);
}

void Selection::setSelected(bool _selected)
{
	m_selected = _selected;
}

bool Selection::getSelected()
{
	return m_selected;
}

const bool* Selection::getPointerToSelected()
{
	return &m_selected;
}