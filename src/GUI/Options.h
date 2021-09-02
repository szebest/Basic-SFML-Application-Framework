#ifndef OPTIONS_H
#define OPTIONS_H

#include "Widget.h"
#include "Text.h"

class Options : public Widget
{
public:
	Options(sf::Vector2f pos, sf::Vector2f size);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

	void draw(sf::RenderTarget& target) override;

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void addOption(std::string _option);

	const std::string* getPtrToString();

	const int* getPtrToIndex();

private:
	int m_height;
	int m_width;
	int m_x;
	int m_y;
	int m_index = -1;
	bool m_clicked = false;
	std::string m_selectedStringOption = "";

	struct Option {
		sf::RectangleShape shape;
		std::unique_ptr<Text> text = nullptr;

		Option()
		{

		}

		Option(sf::Vector2f _pos, sf::Vector2f _size, std::string _text)
		{
			text = makeText(_pos - sf::Vector2f(0, 8), _text);
			shape.setSize(_size);
			shape.setPosition(_pos - _size / 2.f);
			shape.setFillColor(sf::Color(200, 200, 200));
		}

		Option(const Option& _other)
		{
			shape = _other.shape;
			text = makeText(_other.text);
		}
	};

	std::unique_ptr<Option> m_selectedOption;

	std::vector<Option> m_options;

	sf::Vector2f getMouseWorldPos(const sf::RenderWindow& window);

	bool isHovering(sf::IntRect rect, const sf::RenderWindow& window);

	bool isHovering(const sf::RectangleShape& _rect, const sf::RenderWindow& window);
};

inline std::unique_ptr<Options> makeOptions(sf::Vector2f pos, sf::Vector2f size)
{
	return std::make_unique<Options>(pos, size);
}

#endif