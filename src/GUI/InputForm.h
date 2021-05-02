#ifndef INPUTFORM_H
#define INPUTFORM_H

#include "Widget.h"

class InputForm : public Widget
{
public:
	InputForm(sf::Vector2f pos, sf::Vector2f size, std::string* ptrToString);

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

private:
	sf::RectangleShape m_shape;
	
	sf::Text m_text;

	std::string* m_modifiedStringPtr;

	bool m_active;

	bool isHovering(const sf::RenderWindow& window);
};

inline std::unique_ptr<InputForm> makeInputForm(sf::Vector2f pos, sf::Vector2f size, std::string* ptrToString)
{
	return std::make_unique<InputForm>(pos, size, ptrToString);
}

#endif