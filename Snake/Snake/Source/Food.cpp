#include "Food.h"
#include "Snake.h"

Food::Food(Pos pos)
{
	_pos = pos;

	int r = rand();
	if (r % 3 == 0)
	{
		_shape = "¡Ý";
	}
	else if (r % 3 == 1)
	{
		_shape = "¡Ü";
	}
	else
	{
		_shape = "¡Ù";
	}
}

void Food::printBody()
{
	Utility::printStringOnPos(_shape, _pos);
}

void Food::render(sf::RenderWindow& window)
{
	int MoveScale = 20;

	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(sf::Vector2f(_pos.x * MoveScale, _pos.y * MoveScale));

	window.draw(shape);
}