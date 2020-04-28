#pragma once

#include <SFML/Graphics.hpp>

class Globals
{
public:
	constexpr static float MoveScale = 20;

	constexpr static int W = 30;
	constexpr static int H = 50;
	enum
	{
		Left, Right, Up, Down
	};

	const static sf::Vector2f moveXY[4];
	const static int oppositeDir[4];
};