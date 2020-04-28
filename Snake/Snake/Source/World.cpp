#include "World.h"

using namespace sf;

void World::init()
{
	_snake.init(15, 30);
	float radius = 2000;

	Utility::setCircle(_boundingCircle, radius);
	_boundingCircle.setOutlineThickness(5);
	_boundingCircle.setOutlineColor(sf::Color::Red);
	_boundingCircle.setFillColor(sf::Color::Transparent);
	_boundingCircle.setPointCount(100);
}

bool World::update(sf::Vector2f inputDir)
{
	if (_snake.checkDead(_boundingCircle))
	{
		std::cout << "Game Over!" << std::endl;
		return false;
	}

	genFood();
	if (Utility::getVectorSizeSQ(inputDir) < 0.0001f)
	{
		_snake.moveBodies(_snake.getDirection());
	}
	else
	{
		_snake.moveBodies(inputDir);
	}

	_snake.eatFoot(_foods);

	_targetViewPos = _snake.getBody(0);

	
	return true;
}

void World::render(RenderWindow& window)
{
	_snake.render(window);

	for (int i = 0; i < _foods.size(); ++i)
	{
		_foods[i].render(window);
	}

	window.draw(_boundingCircle);
}

void World::genFood()
{
	{
		sf::Vector2f pos = Utility::randomPosInCircle(
			Utility::getCenter(_boundingCircle), _boundingCircle.getRadius());

		Food food(pos);
		_foods.push_back(food);
	}
}