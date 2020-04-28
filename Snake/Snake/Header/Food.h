#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Utility.h"

class Snake;

class Food
{
private:
	Pos _pos;
	std::string _shape;

public:

	Food(Pos pos);
	Pos getPos() const { return _pos; }
	void printBody();

	void render(sf::RenderWindow& window);
};
