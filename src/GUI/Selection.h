#ifndef SELECTION_H
#define SELECTION_H

#include "Widget.h"

class Selection : public Widget
{
public:
	Selection(sf::Vector2f pos);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

	void draw(sf::RenderTarget& target) override;

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void setSelected(bool _selected);

	bool getSelected();

	void setPointerToSelected(const bool*& _ptr);

private:
	sf::CircleShape m_outerShape;
	sf::CircleShape m_innerShape;

	bool m_selected;

	bool isHovering(const sf::RenderWindow& window);
};

inline std::unique_ptr<Selection> makeSelection(sf::Vector2f pos)
{
	return std::make_unique<Selection>(pos);
}

inline std::unique_ptr<Selection> makeSelection(std::unique_ptr<Selection>& other)
{
	return std::make_unique<Selection>(*other);
}

#endif