#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Utility.h"

class Food;
class Snake
{
private:
	int _direction;
	std::vector<sf::Vector2f> _bodies;
	std::string _cshape;

	sf::CircleShape _shape;

public:
	int getDirection() const { return _direction; }
	void setDirection(int dir) { _direction = dir; }

	int getBodySize() const { return _bodies.size(); }
	sf::Vector2f getBody(int i) const { return _bodies[i]; }

	void setBody(int i, sf::Vector2f pos) { _bodies[i] = pos; }
	void addBody(sf::Vector2f pos) { _bodies.push_back(pos); }

	void init(int startX, int startY);

	void printBodies();

	void moveBodies(int direction);

	void eatFoot(std::vector<Food>& foods);

	bool checkDead();


	void render(sf::RenderWindow& window);
};