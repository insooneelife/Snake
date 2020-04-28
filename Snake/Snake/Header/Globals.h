#pragma once

#include <SFML/Graphics.hpp>

class Globals
{
public:
	enum
	{
		Left, Right, Up, Down
	};

	const static sf::Vector2f moveXY[4];
	const static int oppositeDir[4];

	constexpr static float PI = 3.14159265358979323846f;
};