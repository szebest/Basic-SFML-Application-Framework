#ifndef FRAMERATE_H
#define FRAMERATE_H

#include "Text.h"

class FrameRate : public Text
{
public:
	FrameRate(sf::Vector2f pos);

	void handleEvents(sf::Event e, const sf::RenderWindow& window) override;

	void update(const sf::Time& deltaTime) override;

	void draw(sf::RenderTarget& target) override;

	const float* getFpsPointer();
private:
	float m_fps;
};

inline std::unique_ptr<FrameRate> makeFrameRate(sf::Vector2f pos)
{
	return std::make_unique<FrameRate>(pos);
}

inline std::unique_ptr<FrameRate> makeFrameRate(std::unique_ptr<FrameRate>& other)
{
	return std::make_unique<FrameRate>(*other);
}

#endif