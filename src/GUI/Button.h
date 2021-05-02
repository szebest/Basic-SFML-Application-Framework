#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

#include <functional>

class Button : public Widget
{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, const std::string& text);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update() override;

	void draw(sf::RenderTarget& target) override;

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void setSize(sf::Vector2f size);

	sf::Vector2f getSize();

	void setText(const std::string& text);

	void setFont(const sf::Font& font);

	void setColor(sf::Color color);

	void setFunction(std::function<void()> function);

private:
	std::function<void()> m_function = []() {};

	sf::RectangleShape m_shape;

	sf::Text m_text;

	bool isHovering(const sf::RenderWindow& window);
};

inline std::unique_ptr<Button> makeButton(sf::Vector2f pos, sf::Vector2f size, const std::string& text)
{
	return std::make_unique<Button>(pos, size, text);
}

#endif