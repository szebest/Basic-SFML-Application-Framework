#ifndef TEXT_H
#define TEXT_H

#include "Widget.h"

class Text : public Widget
{
public:
	Text(sf::Vector2f pos, const std::string& text);


	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update() override;

	void draw(sf::RenderTarget& target) override;

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void setCharSize(const int size);

	int getCharSize();

	void setText(const std::string& text);

	void setFont(const sf::Font& font);

	void setColor(sf::Color color);

	void setOutlineColor(sf::Color color);

	void setOutlineThickness(int thickness);
private:
	sf::Text m_text;
};

inline std::unique_ptr<Text> makeText(sf::Vector2f pos, const std::string& text)
{
	return std::make_unique<Text>(pos, text);
}

inline std::unique_ptr<Text> makeText(std::unique_ptr<Text>& other)
{
	return std::make_unique<Text>(*other);
}

#endif