#include "Options.h"

Options::Options(sf::Vector2f pos, sf::Vector2f size) :
	m_width(size.x), m_height(size.y)
{
	setPosition(pos);

	m_selectedOption = std::make_unique<Option>();

	m_selectedOption->shape.setPosition(getPosition());
	m_selectedOption->shape.setFillColor(sf::Color(200, 200, 200));
	m_selectedOption->shape.setSize(sf::Vector2f(m_width, m_height - 1));
}

void Options::handleEvents(sf::Event e, const sf::RenderWindow& window, sf::Vector2f displacement)
{
	switch (e.type) {
		case sf::Event::MouseButtonPressed:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (m_clicked)
				{
					for (int i = 0; i < m_options.size(); i++)
						if (isHovering(m_options[i].shape, window, displacement))
						{
							m_selectedOption = std::make_unique<Option>(m_options[i]);
							m_selectedOption->shape.setFillColor(sf::Color(200, 200, 200));
							m_selectedOption->text->setPosition(m_selectedOption->text->getPosition() - sf::Vector2f(0, (i + 1) * m_height));
							m_selectedOption->shape.setPosition(sf::Vector2f(m_x + m_width / 2.f, m_y + m_height / 2.f));

							m_index = i;
							m_selectedStringOption = m_selectedOption->text->getString();
						}
				}

				if (isHovering(sf::IntRect(m_x + m_width / 2, m_y + m_height / 2, m_width, m_height), window, displacement))
					m_clicked = !m_clicked;
			}
		} break;
		case sf::Event::MouseWheelScrolled:
		case sf::Event::MouseMoved:
		{
			for (auto& option : m_options)
			{
				if (isHovering(option.shape, window, displacement))
					option.shape.setFillColor(sf::Color(150, 150, 150));
				else
					option.shape.setFillColor(sf::Color(200, 200, 200));
			}
			if (isHovering(sf::IntRect(m_x + m_width / 2, m_y + m_height / 2, m_width, m_height), window, displacement))
				m_selectedOption->shape.setFillColor(sf::Color(150, 150, 150));
			else
				m_selectedOption->shape.setFillColor(sf::Color(200, 200, 200));
		}
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

sf::Vector2f Options::getMouseWorldPos(const sf::RenderWindow& window, sf::Vector2f displacement)
{
	auto pixelPos = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(pixelPos) + displacement;
}

bool Options::isHovering(sf::IntRect rect, const sf::RenderWindow& window, sf::Vector2f displacement)
{
	auto worldPos = getMouseWorldPos(window, displacement);
	return rect.contains(worldPos.x, worldPos.y);
}

bool Options::isHovering(const sf::RectangleShape& _rect, const sf::RenderWindow& window, sf::Vector2f displacement)
{
	auto worldPos = getMouseWorldPos(window, displacement);
	return _rect.getGlobalBounds().contains(worldPos);
}

const std::string* Options::getPtrToString()
{
	return &m_selectedStringOption;
}

const int* Options::getPtrToIndex()
{
	return &m_index;
}