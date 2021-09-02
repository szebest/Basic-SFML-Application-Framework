#include "Canvas.h"

#include <iostream>

Canvas::Canvas(sf::FloatRect _drawingDimensions, float _maxScrollY) :
	m_drawingDimensions(_drawingDimensions), m_maxScrollY(_maxScrollY)
{
	m_texture.create(m_drawingDimensions.width, m_drawingDimensions.height, false);
}

void Canvas::handleEvents(sf::Event e, const sf::RenderWindow& window, sf::Vector2f displacement)
{
	switch (e.type) {
		case sf::Event::MouseWheelScrolled:
		{
			m_deltaScroll -= e.mouseWheelScroll.delta;

			m_scrollY = std::max(0.f, m_scrollY);
			m_scrollY = std::min(m_maxScrollY, m_scrollY);
		} break;
		default:
			break;
	}

	for (const auto& widget : m_widgets)
		widget->handleEvents(e, window, sf::Vector2f(0.f, m_scrollY));
}

void Canvas::update(const sf::Time& deltaTime)
{
	m_scrollY += m_deltaScroll * deltaTime.asSeconds() * 2500;
	m_scrollY = std::max(0.f, m_scrollY);
	m_scrollY = std::min(m_maxScrollY, m_scrollY);
	m_deltaScroll = 0.f;

	for (const auto& widget : m_widgets)
		widget->update(deltaTime);
}

void Canvas::draw(sf::RenderTarget& target)
{
	sf::View view(sf::FloatRect(0.f, m_scrollY, m_drawingDimensions.width, m_drawingDimensions.height));
	m_texture.setView(view);

	m_texture.clear(sf::Color::Transparent);

	for (const auto& widget : m_widgets)
		widget->draw(m_texture);

	m_texture.display();

	m_sprite.setTexture(m_texture.getTexture());

	m_sprite.setPosition(sf::Vector2f(m_drawingDimensions.left, m_drawingDimensions.top));

	target.draw(m_sprite);
}

void Canvas::addWidget(std::unique_ptr<Widget> _widget)
{
	m_widgets.push_back(std::move(_widget));
}