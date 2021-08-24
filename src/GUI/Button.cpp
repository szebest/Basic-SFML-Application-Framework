#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, const std::string& text) :
	m_shouldCall(false)
{
	setColor(sf::Color::White);
	setSize(size);
	setPosition(pos);

	m_text.setCharacterSize(32);
	m_text.setFillColor(sf::Color::Black);
	setFont(holder::get().fonts.get("arial"));
	setText(text);
}

void Button::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type) {
		case sf::Event::MouseButtonPressed:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
				if (isHovering(window))
					m_shouldCall = true;
		} break;
		default:
			break;
	}
}

void Button::update(const sf::Time& deltaTime)
{
	if (m_shouldCall)
	{
		m_shouldCall = false;
		m_function();
	}
}

void Button::draw(sf::RenderTarget& target)
{
	target.draw(m_shape);
	target.draw(m_text);
}

void Button::setPosition(sf::Vector2f pos)
{
	m_shape.setPosition(pos - m_shape.getSize() / 2.f);
}

sf::Vector2f Button::getPosition()
{
	return m_shape.getPosition() + m_shape.getSize() / 2.f;
}

void Button::setSize(sf::Vector2f size)
{
	m_shape.setSize(size);
}

sf::Vector2f Button::getSize()
{
	return m_shape.getSize();
}

void Button::setText(const std::string& text)
{
	m_text.setString(text);

	m_text.setPosition(getPosition() - sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height + m_text.getCharacterSize()) / 2.f);
}

void Button::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void Button::setColor(sf::Color color)
{
	m_shape.setFillColor(color);
}

void Button::setFunction(std::function<void()> function)
{
	m_function = function;
}

bool Button::isHovering(const sf::RenderWindow& window)
{
	auto pixelPos = sf::Mouse::getPosition(window);
	auto worldPos = window.mapPixelToCoords(pixelPos);
	return m_shape.getGlobalBounds().contains(worldPos.x, worldPos.y);
}