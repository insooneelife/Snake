#include "Snake.h"
#include "Food.h"
#include "Globals.h"

typedef sf::Vector2f Vec;

void Snake::init(int startX, int startY)
{
	_direction = sf::Vector2f(1, 0);

	_bodies.push_back(Vec(startX, startY));
	_bodies.push_back(Vec(startX, startY + 10));
	_bodies.push_back(Vec(startX, startY + 20));
	_bodies.push_back(Vec(startX, startY + 30));

	Utility::setCircle(_shape, 10.0f);
	_shape.setFillColor(sf::Color::Black);
}

void Snake::moveBodies(sf::Vector2f direction)
{
	Vec tailPos = getBody(getBodySize() - 1);

	for (int i = getBodySize() - 1; i >= 1; --i)
	{
		setBody(i, getBody(i - 1));
	}

	setDirection(direction);
	Vec curPos = getBody(0);
	setBody(0, curPos + direction * 10.0f);
}

void Snake::eatFoot(std::vector<Food>& foods)
{
	Vec head = getBody(0);

	int tryNum = foods.size();

	while (tryNum-- >= 0)
	{
		int foodIdx = -1;
		for (int i = 0; i < foods.size(); ++i)
		{
			Vec foodPos = foods[i].getPos();

			
			sf::CircleShape headShape;
			Utility::setCircle(headShape, _shape.getRadius(), head);

			if (Utility::intersects(headShape, foods[i].getShape()))
			{
				foodIdx = i;
				break;
			}
			
		}
		if (foodIdx == -1)
		{
			break;
		}
		else
		{
			foods.erase(foods.begin() + foodIdx);
			addBody(getBody(getBodySize() - 1));
		}
	}
}

bool Snake::checkDead(const sf::CircleShape& boundingCircle)
{
	Vec head = getBody(0);
	int x = head.x;
	int y = head.y;


	sf::CircleShape headShape;
	Utility::setCircle(headShape, _shape.getRadius(), head);

	if (Utility::intersects(headShape, boundingCircle))
	{
		return true;
	}

	return false;
}

void Snake::render(sf::RenderWindow& window)
{
	for (int i = 0; i < getBodySize(); ++i)
	{
		Vec pos = _bodies[i];
		
		Utility::setCirclePos(_shape, pos);

		window.draw(_shape);
	}
}