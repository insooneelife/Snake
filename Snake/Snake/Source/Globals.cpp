#include "Globals.h"

const sf::Vector2f Globals::moveXY[4] =
	{ sf::Vector2f(-1, 0), sf::Vector2f(1, 0), sf::Vector2f(0, -1), sf::Vector2f(0, 1) };

const int Globals::oppositeDir[4] = { Globals::Right, Globals::Left, Globals::Down, Globals::Up };