#ifndef CANVAS_H
#define CANVAS_H

#include "Widget.h"

#include <vector>

class Canvas : public Widget
{
public:
	Canvas(sf::FloatRect _drawingDimensions, float _maxScrollY);

	void handleEvents(sf::Event e, const sf::RenderWindow& window, sf::Vector2f displacement) override;

	void update(const sf::Time& deltaTime) override;

	void draw(sf::RenderTarget& target) override;

	void addWidget(std::unique_ptr<Widget> _widget);
private:
	float m_scrollY = 0.f;
	float m_scrollYActual = 0.f;
	float m_deltaScroll = 0.f;
	float m_maxScrollY;
	sf::FloatRect m_drawingDimensions;

	sf::RenderTexture m_texture;
	sf::Sprite m_sprite;

	std::vector<std::unique_ptr<Widget>> m_widgets;

	float lerp(float a, float b, float t);
};

inline std::unique_ptr<Canvas> makeCanvas(sf::FloatRect _drawingDimensions, int _maxScrollX)
{
	return std::make_unique<Canvas>(_drawingDimensions, _maxScrollX);
}

#endif