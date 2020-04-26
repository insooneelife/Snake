#pragma once
#include <iostream>
#include <vector>
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

	void genFood();

	void printFoods();
};