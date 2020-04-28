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

public:

	std::vector<Food>& getFoods() { return _foods; }

	void init();

	void printBoard();

	bool update(int inputDir);

	void render(sf::RenderWindow& window);

	void genFood();

	void printFoods();
};