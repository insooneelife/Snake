#include "Food.h"


Food::Food(sf::Vector2f pos)
{
	_pos = pos;
	_shape.setRadius(10);

	Utils::setCirclePos(_shape, pos);
	_shape.setFillColor(sf::Color::Red);
}


void Food::draw(sf::RenderWindow& window)
{
	window.draw(_shape);
}