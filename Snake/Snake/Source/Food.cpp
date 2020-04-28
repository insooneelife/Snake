#include "Food.h"
#include "Snake.h"

using namespace sf;

Food::Food(Vector2f pos)
{
	_pos = pos;

	int r = rand();
	if (r % 3 == 0)
	{
		_cshape = "¡Ý";
	}
	else if (r % 3 == 1)
	{
		_cshape = "¡Ü";
	}
	else
	{
		_cshape = "¡Ù";
	}

	_shape.setRadius(10.0f);
	_shape.setFillColor(sf::Color::Red);
}

void Food::printBody()
{
	Utility::printStringOnPos(_cshape, _pos);
}

void Food::render(sf::RenderWindow& window)
{
	int MoveScale = 20;

	_shape.setPosition(sf::Vector2f(_pos.x * Globals::MoveScale, _pos.y * MoveScale));

	window.draw(_shape);
}