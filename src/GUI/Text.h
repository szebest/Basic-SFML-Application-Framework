#ifndef TEXT_H
#define TEXT_H

#include "Widget.h"
#include <sstream>
#include <functional>
#include <iostream>
#include <iomanip>

class Text : public Widget
{
public:
	Text(sf::Vector2f pos, const std::string& text);

	Text(const Text& other);

	template<typename... Args>
	void setArgs(Args... args)
	{
		m_func = [this, args...]() { this->m_print(args...); };
	}

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

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

	void setFixedPos(bool fixedPos);
private:
	sf::Text m_text;

	std::string m_pattern;

	std::stringstream m_ss;

	sf::Vector2f m_pos;

	sf::Vector2f m_fPos;

	std::function<void()> m_func = []() {};

	bool m_fixedPos;

	template<typename T>
	void m_print(T value)
	{

	}

	template<typename... Args, typename T>
	void m_print(T value, Args... args)
	{
		m_print(args...);
	}

	template<typename... Args>
	void m_print(std::string* value)
	{
		m_ss << *value + '\n';
	}

	template<typename... Args>
	void m_print(std::string* value, Args... args)
	{
		m_ss << *value + '\n';

		m_print(args...);
	}

	template<typename... Args, typename T>
	void m_print(T* value)
	{
		m_ss << std::to_string(*value) + '\n';
	}

	template<typename... Args, typename T>
	void m_print(T* value, Args... args)
	{
		m_ss << std::to_string(*value) + '\n';

		m_print(args...);
	}
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