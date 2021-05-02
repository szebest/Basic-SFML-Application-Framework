#include <SFML/Graphics.hpp>

sf::Vector2f operator/(const sf::Vector2f& vec, const float& number)
{
	return sf::Vector2f(vec.x / number, vec.y / number);
}

sf::Vector2f operator*(const sf::Vector2f& vec, const float& number)
{
	return sf::Vector2f(vec.x * number, vec.y * number);
}

sf::Vector2f operator-(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return sf::Vector2f(vec1.x - vec2.x, vec1.y - vec2.y);
}

sf::Vector2f operator+(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return sf::Vector2f(vec1.x + vec2.x, vec1.y + vec2.y);
}