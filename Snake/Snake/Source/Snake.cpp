#include "Snake.h"
#include "Utils.h"
#include "Food.h"
#include <iostream>
using namespace sf;

void Snake::init(Vector2f startPos)
{
	_direction = Vector2f(1, 0);

	_bodies.push_back(startPos);
	_bodies.push_back(startPos + Vector2f(0, 20));
	_bodies.push_back(startPos + Vector2f(0, 40));
	_bodies.push_back(startPos + Vector2f(0, 60));

	float radius = 10;
	_circle.setRadius(radius);
	_circle.setFillColor(Color::Black);
}

void Snake::move(Vector2f direction)
{
	Vector2f tailPos = getBody(_bodies.size() - 1);

	for (int i = _bodies.size() - 1; i >= 1; --i)
	{
		setBody(i, getBody(i - 1));
	}

	if (Utils::getVectorSizeSQ(direction) < 0.00001f)
	{

	}
	else
	{
		setDirection(direction);
	}
	Vector2f curPos = getBody(0);
	setBody(0, curPos + _direction * 10.0f);
}

void Snake::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < _bodies.size(); ++i)
	{
		Utils::setCirclePos(_circle, _bodies[i]);

		window.draw(_circle);
	}
}

void Snake::eatFood(std::vector<Food>& foods)
{
	Vector2f head = getBody(0);
	
	int foodIdx = -1;

	for (int i = 0; i < foods.size(); ++i)
	{
		Vector2f foodPos = foods[i].getPos();

		// this circle is for check collision
		CircleShape shape;
		shape.setRadius(_circle.getRadius());
		Utils::setCirclePos(shape, head);

		// check collision
		if (Utils::intersects(foods[i].getShape(), shape))
		{
			foodIdx = i;
			break;
		}
	}

	// no food found
	if (foodIdx == -1)
	{
	}
	// found food
	else
	{
		foods.erase(foods.begin() + foodIdx);
		_bodies.push_back(getBody(_bodies.size() - 1));
	}
}