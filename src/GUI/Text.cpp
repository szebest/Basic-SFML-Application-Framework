#include "Text.h"

Text::Text(sf::Vector2f pos, const std::string& text) :
	m_pattern(text), m_pos(pos)
{
	setFont(holder::get().fonts.get("arial"));
	setText(text);
	setColor(sf::Color::White);
	setCharSize(32);
	setPosition(pos);
}

void Text::handleEvents(sf::Event e, const sf::RenderWindow& window)
{

}

void Text::update()
{
	m_ss.clear();

	m_func();

	std::string tmp = "";

	bool special = false;

	for (int i = 0; i < m_pattern.size(); i++)
	{
		bool wasSpecial = special;

		if (m_pattern[i] == '-')
			special = true;
		else
			special = false;

		if (m_pattern[i] == '%' && wasSpecial)
		{
			std::string val = "";

			getline(m_ss, val);

			if (val.size() > 0)
				tmp += val;
		}
		else if (!special)
		{
			if (wasSpecial)
				tmp = tmp + "-" + m_pattern[i];
			else
				tmp += m_pattern[i];
		}
	}

	setText(tmp);

	setPosition(m_pos);
}

void Text::draw(sf::RenderTarget& target)
{
	target.draw(m_text);
}

void Text::setPosition(sf::Vector2f pos)
{
	m_text.setPosition(pos - sf::Vector2f(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f + getCharSize() / 2.f));
}

sf::Vector2f Text::getPosition()
{
	return m_text.getPosition() + sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height - getCharSize() / 2.f);
}

void Text::setCharSize(int size)
{
	m_text.setCharacterSize(size);
}

int Text::getCharSize()
{
	return m_text.getCharacterSize();
}

void Text::setText(const std::string& text)
{
	m_text.setString(text);
}

void Text::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void Text::setColor(sf::Color color)
{
	m_text.setFillColor(color);
}

void Text::setOutlineColor(sf::Color color)
{
	m_text.setOutlineColor(color);
}

void Text::setOutlineThickness(int thickness)
{
	m_text.setOutlineThickness(thickness);
}