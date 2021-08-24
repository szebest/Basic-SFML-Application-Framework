#ifndef INPUTFORM_H
#define INPUTFORM_H

#include "Widget.h"

#include <windows.h>

class InputForm : public Widget
{
public:
	InputForm(sf::Vector2f pos, sf::Vector2f size, std::string* ptrToString);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

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

	sf::RectangleShape m_select;
	
	sf::Text m_text;

	sf::Text m_underline;

	std::string* m_modifiedStringPtr;

	bool m_active;

	bool m_selected;

	sf::Clock m_clock;

	bool isHovering(const sf::RenderWindow& window);

	void toClipboard(const std::string& s);
};

inline std::unique_ptr<InputForm> makeInputForm(sf::Vector2f pos, sf::Vector2f size, std::string* ptrToString)
{
	return std::make_unique<InputForm>(pos, size, ptrToString);
}

inline std::unique_ptr<InputForm> makeInputForm(std::unique_ptr<InputForm>& other)
{
	return std::make_unique<InputForm>(*other);
}

#endif