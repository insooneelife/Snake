#pragma once


struct Pos
{
	int x, y;

	Pos() {}

	Pos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

const int W = 30;
const int H = 50;
enum
{
	Left, Right, Up, Down
};

const Pos moveXY[4] = { Pos(-1, 0), Pos(1, 0), Pos(0, -1), Pos(0, 1) };
const int oppositeDir[4] = { Right, Left, Down, Up };