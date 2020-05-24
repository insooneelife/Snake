#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Header/Snake.h"
#include "Header/Utils.h"
#include "Header/Food.h"

using namespace std;
using namespace sf;

const float GameWidth = 960;
const float GameHeight = 640;



int main()
{
	RenderWindow window(VideoMode(GameWidth, GameHeight), "snake");
	View view(FloatRect(0, 0, GameWidth, GameHeight));
	window.setView(view);

	srand((unsigned int)time(0));

	Snake snake;
	snake.init(Vector2f(300, 300));

	std::vector<Food> foods;

	for (int i = 0; i < 50; ++i)
	{
		Food food(Vector2f(
			Utils::randomFloat() * GameWidth,
			Utils::randomFloat() * GameHeight));
		foods.push_back(food);
	}

	


	while (window.isOpen())
	{
		Event ev;
		if (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
		}

		Vector2f inputDir;
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			inputDir += sf::Vector2f(-1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			inputDir += sf::Vector2f(1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			inputDir += sf::Vector2f(0, -1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			inputDir += sf::Vector2f(0, 1);
		}

		// normalize for get direction
		inputDir = Utils::getVectorSafeNorm(inputDir);

		snake.move(inputDir);
		snake.eatFood(foods);
		window.clear(Color::White);
		
		snake.draw(window);

		for (int i = 0; i < foods.size(); ++i)
		{
			foods[i].draw(window);
		}


		window.display();
	}
}