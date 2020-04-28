#include "Snake.h"
#include "Food.h"
#include "Globals.h"

typedef sf::Vector2f Vec;

void Snake::init(int startX, int startY)
{
	// 벽을 뚫을 위험이 있음
	_bodies.push_back(Vec(startX, startY));
	_bodies.push_back(Vec(startX, startY + 1));
	_bodies.push_back(Vec(startX, startY + 2));
	_bodies.push_back(Vec(startX, startY + 3));

	int r = rand();
	if (r % 2 == 0)
	{
		_cshape = "■";
	}
	else if (r % 2 == 1)
	{
		_cshape = "◆";
	}

	_shape.setRadius(10.0f);
	_shape.setFillColor(sf::Color::Black);
}

void Snake::printBodies()
{
	for (int i = 0; i < getBodySize(); ++i)
	{
		Vec pos = _bodies[i];
		Utility::printStringOnPos(_cshape, pos);
	}
}

void Snake::moveBodies(int direction)
{
	if (Globals::oppositeDir[direction] == getDirection())
	{
		// read
		direction = getDirection();
	}

	Vec tailPos = getBody(getBodySize() - 1);
	Utility::printStringOnPos("  ", tailPos);

	for (int i = getBodySize() - 1; i >= 1; --i)
	{
		setBody(i, getBody(i - 1));
	}

	setDirection(direction);
	Vec curPos = getBody(0);
	int x = curPos.x + Globals::moveXY[getDirection()].x;
	int y = curPos.y + Globals::moveXY[getDirection()].y;
	setBody(0, Vec(x, y));
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
			if (head.x == foodPos.x && head.y == foodPos.y)
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

bool Snake::checkDead()
{
	Vec curPos = getBody(0);
	int x = curPos.x;
	int y = curPos.y;

	if (y == 0 || x == 0 || y == Globals::H - 1 || x == Globals::W - 1)
	{
		return true;
	}

	for (int i = 1; i < getBodySize(); ++i)
	{
		Vec body = getBody(i);
		if (body.x == curPos.x && body.y == curPos.y)
		{
			return true;
		}
	}

	return false;
}

void Snake::render(sf::RenderWindow& window)
{
	int MoveScale = 20;

	for (int i = 0; i < getBodySize(); ++i)
	{
		Vec pos = _bodies[i];
		
		_shape.setPosition(pos * (float)MoveScale);

		window.draw(_shape);
	}
}