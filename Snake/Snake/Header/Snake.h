#pragma once

#include <vector>
#include <SFML/Graphics.hpp>


class Food;
class Snake
{
private:
	std::vector<sf::Vector2f> _bodies;
	sf::Vector2f _direction;
	sf::CircleShape _circle;

public:

	sf::Vector2f getBody(int i) const { return _bodies[i]; }
	void setBody(int i, sf::Vector2f pos) { _bodies[i] = pos; }

	sf::Vector2f getDirection() const { return _direction; }
	void setDirection(sf::Vector2f direction) { _direction = direction; }


	void init(sf::Vector2f startPos);
	void move(sf::Vector2f direction);
	void draw(sf::RenderWindow& window);

	void eatFood(std::vector<Food>& foods);
};