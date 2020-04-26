#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>

using namespace std;

struct Pos
{
	int x, y;

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

Pos moveXY[4] = { Pos(-1, 0), Pos(1, 0), Pos(0, -1), Pos(0, 1) };
int oppositeDir[4] = { Right, Left, Down, Up };

int curDir;
vector<Pos> bodies;
vector<Pos> foods;

void gotoxy(int x, int y)
{
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}

void printBody(string part, Pos pos)
{
	gotoxy(pos.x * 2, pos.y);
	cout << part;
}

void printBodies()
{
	for (int i = 0; i < bodies.size(); ++i)
	{
		Pos pos = bodies[i];
		printBody("бс", pos);
	}
}

void moveBodies(int direction)
{
	if (oppositeDir[direction] == curDir)
	{
		direction = curDir;
	}

	Pos tailPos = bodies[bodies.size() - 1];
	printBody("  ", tailPos);

	for (int i = bodies.size() - 1; i >= 1; --i)
	{
		bodies[i] = bodies[i - 1];
	}

	curDir = direction;
	Pos curPos = bodies[0];
	int x = curPos.x + moveXY[curDir].x;
	int y = curPos.y + moveXY[curDir].y;
	bodies[0] = Pos(x, y);
}

void eatFoot()
{
	Pos head = bodies[0];

	int tryNum = foods.size();

	while (tryNum-- >= 0)
	{
		int foodIdx = -1;
		for (int i = 0; i < foods.size(); ++i)
		{
			if (head.x == foods[i].x && head.y == foods[i].y)
			{
				foodIdx = i;
				break;
			}
		}
		if (foodIdx == -1)
		{
			break;
		}
		else
		{
			foods.erase(foods.begin() + foodIdx);
			bodies.push_back(bodies[bodies.size() - 1]);
		}
	}

}

bool checkDead()
{
	Pos curPos = bodies[0];
	int x = curPos.x;
	int y = curPos.y;

	if (y == 0 || x == 0 || y == H - 1 || x == W - 1)
	{
		return true;
	}

	for (int i = 1; i < bodies.size(); ++i)
	{
		if (bodies[i].x == curPos.x && bodies[i].y == curPos.y)
		{
			return true;
		}
	}

	return false;
}

void genFood()
{
	if (rand() % 10 == 0)
	{
		int x = rand() % (W - 2) + 1;
		int y = rand() % (H - 2) + 1;


		foods.push_back(Pos(x, y));
	}
}

void printFoods()
{
	for (int i = 0; i < foods.size(); ++i)
	{
		Pos pos = foods[i];
		printBody("б▌", pos);
	}
}

int main()
{
	srand((unsigned int)time(0));

	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			if (y == 0 || x == 0 || y == H - 1 || x == W - 1)
				cout << "бр";
			else
				cout << "  ";
		}
		cout << endl;
	}

	int startX = 10;
	int startY = 10;
	bodies.push_back(Pos(startX, startY));
	bodies.push_back(Pos(startX, startY + 1));
	bodies.push_back(Pos(startX, startY + 2));
	bodies.push_back(Pos(startX, startY + 3));

	int stepCnt = 0;
	while (true)
	{
		int inputDir = -1;
		if (GetAsyncKeyState(VK_LEFT))
		{
			inputDir = Left;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			inputDir = Right;
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			inputDir = Up;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			inputDir = Down;
		}

		if (stepCnt % 50 == 0)
		{
			if (checkDead())
			{
				cout << "Game Over!" << endl;
				break;
			}

			genFood();
			if (inputDir == -1)
			{
				moveBodies(curDir);
			}
			else
			{
				moveBodies(inputDir);
			}

			eatFoot();
			printBodies();
			printFoods();
		}


		stepCnt++;
		Sleep(1);
	}




	return 0;
}