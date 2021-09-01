#include "Options.h"

Options::Options(sf::Vector2f pos)
{
	setPosition(pos);

	m_selectedOption = std::make_unique<Option>();

	m_selectedOption->shape.setPosition(getPosition());
	m_selectedOption->shape.setFillColor(sf::Color(200, 200, 200));
	m_selectedOption->shape.setSize(sf::Vector2f(m_width, m_height - 1));
}

void Options::handleEvents(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type) {
	case sf::Event::MouseButtonPressed:
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			for (int i = 0; i < m_options.size(); i++)
				if (isHovering(m_options[i].shape, window))
				{
					m_selectedOption = std::make_unique<Option>(m_options[i]);
					m_selectedOption->text->setPosition(m_selectedOption->text->getPosition() - sf::Vector2f(0, (i + 1) * m_height));
					m_selectedOption->shape.setPosition(sf::Vector2f(m_x + m_width / 2.f, m_y + m_height / 2.f));
				}

			if (isHovering(sf::IntRect(m_x + m_width / 2, m_y + m_height / 2, m_width, m_height), window))
				m_clicked = !m_clicked;
		}
	} break;
	default:
		break;
	}
}

void Options::update(const sf::Time& deltaTime)
{

}

void Options::draw(sf::RenderTarget& target)
{
	target.draw(m_selectedOption->shape);
	if (m_selectedOption->text)
		m_selectedOption->text->draw(target);

	if (m_clicked)
	{
		for (const auto& option : m_options)
		{
			target.draw(option.shape);
			option.text->draw(target);
		}
	}
}

void Options::setPosition(sf::Vector2f pos)
{
	m_x = pos.x - m_width / 2;
	m_y = pos.y - m_height / 2;
}

sf::Vector2f Options::getPosition()
{
	return sf::Vector2f(m_x + m_width / 2, m_y + m_height / 2);
}

void Options::addOption(std::string _option)
{
	int size = m_options.size();
	Option o(sf::Vector2f(m_x + m_width, m_y + (size + 2) * m_height), sf::Vector2f(m_width, m_height - 1), _option);

	m_options.push_back(o);
}

sf::Vector2f Options::getMouseWorldPos(const sf::RenderWindow& window)
{
	auto pixelPos = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(pixelPos);
}

bool Options::isHovering(sf::IntRect rect, const sf::RenderWindow& window)
{
	auto worldPos = getMouseWorldPos(window);
	return rect.contains(worldPos.x, worldPos.y);
}

bool Options::isHovering(const sf::RectangleShape& _rect, const sf::RenderWindow& window)
{
	auto worldPos = getMouseWorldPos(window);
	return _rect.getGlobalBounds().contains(worldPos);
}