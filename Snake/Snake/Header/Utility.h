#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include "Data.h"

class Utility
{
public:
	static void gotoxy(int x, int y)
	{
		COORD posXY = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
	}

	static void printStringOnPos(std::string part, Pos pos)
	{
		gotoxy(pos.x * 2, pos.y);
		std::cout << part;
	}


};