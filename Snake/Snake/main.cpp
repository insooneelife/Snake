#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include "Globals.h"
#include "World.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 640), "SFML works!");
	sf::View view(sf::FloatRect(0.f, 0.f, 960.f, 640.f));
	window.setView(view);

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


		sf::Vector2f inputDir;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			inputDir += sf::Vector2f(-1, 0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			inputDir += sf::Vector2f(1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			inputDir += sf::Vector2f(0, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			inputDir += sf::Vector2f(0, 1);
		}

		inputDir = Utility::getVectorSafeNorm(inputDir);

		if (!world.update(inputDir))
		{
			break;
		}
		

		window.clear(sf::Color::White);

		view.setCenter(world.getTargetViewPos());
		window.setView(view);
		world.render(window);

		
		window.display();

		Sleep(5);
	}

	return 0;
}