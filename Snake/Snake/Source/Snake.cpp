#include "Snake.h"
#include "Food.h"

void Snake::init(int startX, int startY)
{
	// 벽을 뚫을 위험이 있음
	_bodies.push_back(Pos(startX, startY));
	_bodies.push_back(Pos(startX, startY + 1));
	_bodies.push_back(Pos(startX, startY + 2));
	_bodies.push_back(Pos(startX, startY + 3));

	int r = rand();
	if (r % 2 == 0)
	{
		_shape = "■";
	}
	else if (r % 2 == 1)
	{
		_shape = "◆";
	}
}

void Snake::printBodies()
{
	for (int i = 0; i < getBodySize(); ++i)
	{
		Pos pos = _bodies[i];
		Utility::printStringOnPos(_shape, pos);
	}
}

void Snake::moveBodies(int direction)
{
	if (oppositeDir[direction] == getDirection())
	{
		// read
		direction = getDirection();
	}

	Pos tailPos = getBody(getBodySize() - 1);
	Utility::printStringOnPos("  ", tailPos);

	for (int i = getBodySize() - 1; i >= 1; --i)
	{
		setBody(i, getBody(i - 1));
	}

	setDirection(direction);
	Pos curPos = getBody(0);
	int x = curPos.x + moveXY[getDirection()].x;
	int y = curPos.y + moveXY[getDirection()].y;
	setBody(0, Pos(x, y));
}

void Snake::eatFoot(std::vector<Food>& foods)
{
	Pos head = getBody(0);

	int tryNum = foods.size();

	while (tryNum-- >= 0)
	{
		int foodIdx = -1;
		for (int i = 0; i < foods.size(); ++i)
		{
			Pos foodPos = foods[i].getPos();
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
	Pos curPos = getBody(0);
	int x = curPos.x;
	int y = curPos.y;

	if (y == 0 || x == 0 || y == H - 1 || x == W - 1)
	{
		return true;
	}

	for (int i = 1; i < getBodySize(); ++i)
	{
		Pos body = getBody(i);
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
		Pos pos = _bodies[i];
		//Utility::printStringOnPos(_shape, pos);

		sf::CircleShape shape(10.f);
		shape.setFillColor(sf::Color::Black);
		shape.setPosition(sf::Vector2f(pos.x * MoveScale, pos.y * MoveScale));

		window.draw(shape);
	}
}