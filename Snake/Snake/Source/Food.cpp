#include "Food.h"
#include "Snake.h"

using namespace sf;

Food::Food(Vector2f pos)
{
	_pos = pos;
	
	Utility::setCircle(_shape, 10.0f);
	_shape.setFillColor(sf::Color::Red);
}

void Food::render(sf::RenderWindow& window)
{
	_shape.setPosition(sf::Vector2f(_pos.x, _pos.y));

	window.draw(_shape);
}