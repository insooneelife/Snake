#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Utility.h"

class Food;
class Snake
{
private:
	int _direction;
	std::vector<Pos> _bodies;
	std::string _shape;

public:
	int getDirection() const { return _direction; }
	void setDirection(int dir) { _direction = dir; }

	int getBodySize() const { return _bodies.size(); }
	Pos getBody(int i) const { return _bodies[i]; }

	void setBody(int i, Pos pos) { _bodies[i] = pos; }
	void addBody(Pos pos) { _bodies.push_back(pos); }

	void init(int startX, int startY);

	void printBodies();

	void moveBodies(int direction);

	void eatFoot(std::vector<Food>& foods);

	bool checkDead();
};