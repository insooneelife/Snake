#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include "World.h"

using namespace std;


int main()
{
	srand((unsigned int)time(0));
	World world;

	world.init();
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

		if(stepCnt % 50 == 0)
		{
			if (!world.update(inputDir))
			{
				break;
			}
		}
		
		stepCnt++;
		Sleep(1);
	}

	return 0;
}