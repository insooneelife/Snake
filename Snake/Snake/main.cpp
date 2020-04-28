#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include "World.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "SFML works!");
	

	srand((unsigned int)time(0));
	World world;

	world.init();
	int stepCnt = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		int inputDir = -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			inputDir = Left;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			inputDir = Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			inputDir = Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			inputDir = Down;
		}

		if (!world.update(inputDir))
		{
			break;
		}


		window.clear(sf::Color::White);

		world.render(window);

		window.display();

		Sleep(50);
	}

	return 0;
}