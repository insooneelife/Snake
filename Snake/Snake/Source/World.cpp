#include "World.h"


void World::init()
{
	printBoard();

	_snake.init(15, 30);
}

void World::printBoard()
{
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			if (y == 0 || x == 0 || y == H - 1 || x == W - 1)
				std::cout << "бр";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

bool World::update(int inputDir)
{
	if (_snake.checkDead())
	{
		std::cout << "Game Over!" << std::endl;
		return false;
	}

	genFood();
	if (inputDir == -1)
	{
		_snake.moveBodies(_snake.getDirection());
	}
	else
	{
		_snake.moveBodies(inputDir);
	}

	_snake.eatFoot(_foods);
	_snake.printBodies();
	printFoods();

	return true;
}

void World::render(sf::RenderWindow& window)
{
	_snake.render(window);

	for (int i = 0; i < _foods.size(); ++i)
	{
		_foods[i].render(window);
	}
}

void World::genFood()
{
	if (rand() % 10 == 0)
	{
		int x = rand() % (W - 2) + 1;
		int y = rand() % (H - 2) + 1;

		Food food(Pos(x, y));
		_foods.push_back(food);
	}
}

void World::printFoods()
{
	for (int i = 0; i < _foods.size(); ++i)
	{
		_foods[i].printBody();
	}
}