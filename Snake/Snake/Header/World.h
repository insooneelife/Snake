#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"


class World
{
private:
	std::vector<Food> _foods;
	Snake _snake;

	sf::Vector2f _targetViewPos;
	sf::CircleShape _boundingCircle;


public:

	std::vector<Food>& getFoods() { return _foods; }
	sf::Vector2f getTargetViewPos() const { return _targetViewPos; }

	void init();

	bool update(sf::Vector2f inputDir);

	void render(sf::RenderWindow& window);

	void genFood();
};