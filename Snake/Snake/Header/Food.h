#pragma once


#include "Utils.h"
#include <SFML/Graphics.hpp>

class Food
{

private:
	sf::Vector2f _pos;
	sf::CircleShape _shape;

public:
	Food(sf::Vector2f pos);
	sf::Vector2f getPos() const { return _pos; }

	const sf::CircleShape& getShape() const { return _shape; }

	void draw(sf::RenderWindow& window);
};