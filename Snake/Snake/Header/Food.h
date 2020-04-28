#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "Globals.h"

class Snake;

class Food
{
private:
	sf::Vector2f _pos;
	sf::CircleShape _shape;

public:

	Food(sf::Vector2f pos);
	sf::Vector2f getPos() const { return _pos; }
	const sf::CircleShape& getShape() const { return _shape; }

	void render(sf::RenderWindow& window);
};
