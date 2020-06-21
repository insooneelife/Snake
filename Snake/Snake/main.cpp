#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>

using namespace std;
using namespace sf;

const float GameWidth = 960;
const float GameHeight = 640;
const float Pi = 3.14159265358979323846f;

static float getVectorSize(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

static float getVectorSizeSq(sf::Vector2f v)
{
	return v.x * v.x + v.y * v.y;
}

static sf::Vector2f getVectorNorm(sf::Vector2f v)
{
	// v / v size
	return v / getVectorSize(v);
}

static bool isVectorZero(sf::Vector2f v)
{
	return getVectorSizeSq(v) < 0.000001f;
}

static sf::Vector2f getVectorSafeNorm(sf::Vector2f v)
{
	if (isVectorZero(v))
	{
		return sf::Vector2f();
	}
	return v / getVectorSize(v);
}

// 0 ~ 1
static float randomFloat()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

static sf::Vector2f randomPosInCircle(sf::Vector2f pos, float radius)
{
	float t = 2 * Pi * randomFloat();
	float u = randomFloat() + randomFloat();

	float r;
	if (u > 1)
	{
		r = (2 - u) * radius;
	}
	else
	{
		r = u * radius;
	}
	return sf::Vector2f(r * cos(t), r * sin(t));
}

static float distanceSq(sf::Vector2f a, sf::Vector2f b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

static float distance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(distanceSq(a, b));
}

static bool intersects(const sf::CircleShape& a, const sf::CircleShape& b)
{
	float dis = distance(a.getPosition(), b.getPosition());

	if (dis > a.getRadius() + b.getRadius())
		return false;

	if (dis > std::abs(a.getRadius() - b.getRadius()))
		return true;

	return false;
}


class Food
{
private:
	sf::Vector2f _pos;
	sf::CircleShape _shape;

public:

	Food(sf::Vector2f start)
	{
		_pos = start;
		_shape.setRadius(10);
		_shape.setOrigin(_shape.getRadius(), _shape.getRadius());
		_shape.setFillColor(Color::Red);
		_shape.setPosition(_pos);
	}

	const sf::CircleShape& getShape() const { return _shape; }


	void draw(sf::RenderWindow& window)
	{
		window.draw(_shape);
	}
};

std::vector<Food> foods;


class Snake
{
private:
	sf::Vector2f _direction;
	std::vector<sf::Vector2f> _bodies;
	sf::CircleShape _shape;

public:
	Snake(sf::Vector2f start)
	{
		_direction = Vector2f(1, 0);
		_bodies.push_back(start + Vector2f(0, 20));
		_bodies.push_back(start + Vector2f(0, 40));
		_bodies.push_back(start + Vector2f(0, 60));

		_shape.setPosition(start);
		_shape.setRadius(10);
		_shape.setFillColor(Color::Black);
		_shape.setOrigin(_shape.getRadius(), _shape.getRadius());
	}

	sf::Vector2f getBody(int i) const { return _bodies[i]; }
	void setBody(int i, sf::Vector2f pos) { _bodies[i] = pos; }

	sf::Vector2f getTail() const { return getBody(_bodies.size() - 1); }
	sf::Vector2f getHead() const { return getBody(0); }

	sf::Vector2f getDirection() const { return _direction; }

	void draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < _bodies.size(); ++i)
		{
			_shape.setPosition(_bodies[i]);
			window.draw(_shape);
		}
	}

	void move(sf::Vector2f direction)
	{
		Vector2f tailPos = getTail();

		for (int i = _bodies.size() - 1; i >= 1; --i)
		{
			setBody(i, getBody(i - 1));
		}

		if(!isVectorZero(direction))
		{ 
			_direction = direction;
		}

		Vector2f head = getHead();
		setBody(0, head + _direction * 10.0f);
	}

	void eatFood(std::vector<Food>& foods)
	{
		Vector2f head = getHead();

		int foodIdx = -1;
		for (int i = 0; i < foods.size(); ++i)
		{
			sf::CircleShape headCircle;
			headCircle.setRadius(_shape.getRadius());
			headCircle.setOrigin(_shape.getOrigin());
			headCircle.setPosition(head);

			// intersects circles
			if (intersects(headCircle, foods[i].getShape()))
			{
				foodIdx = i;
				break;
			}
		}

		if (foodIdx == -1)
		{
			// not found
		}
		else
		{
			foods.erase(foods.begin() + foodIdx);
			_bodies.push_back(getTail());
		}
	}

	bool checkDie(const sf::CircleShape& boundingCircle)
	{
		Vector2f head = getHead();
		sf::CircleShape headCircle;
		headCircle.setRadius(_shape.getRadius());
		headCircle.setOrigin(_shape.getOrigin());
		headCircle.setPosition(head);

		if (intersects(headCircle, boundingCircle))
		{
			return true;
		}
		return false;
	}
};



int main()
{
	srand((unsigned int)time(0));
	RenderWindow window(VideoMode(GameWidth, GameHeight), "snake");
	View view(FloatRect(0, 0, GameWidth, GameHeight));

	CircleShape circle;
	circle.setPosition(Vector2f(0, 0));
	circle.setRadius(1500);
	circle.setFillColor(Color::Transparent);
	circle.setOutlineColor(Color::Black);
	circle.setOutlineThickness(5);
	circle.setPointCount(100);
	circle.setOrigin(Vector2f(circle.getRadius(), circle.getRadius()));

	Snake snake(Vector2f(200, 200));


	for (int i = 0; i < 400; ++i)
	{
		// random pos
		Food food(randomPosInCircle(circle.getPosition(), circle.getRadius()));

		foods.push_back(food);
	}

	

	while (window.isOpen())
	{
		Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
		}

		Vector2f inputDir;
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			inputDir += Vector2f(-1, 0);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			inputDir += Vector2f(1, 0);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			inputDir += Vector2f(0, -1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			inputDir += Vector2f(0, 1);
		}

		inputDir = getVectorSafeNorm(inputDir);

		// update
		snake.move(inputDir);
		
		if (snake.checkDie(circle))
		{
			window.close();
		}
		
		snake.eatFood(foods);



		view.setCenter(snake.getHead());
		window.setView(view);

		// render
		window.clear(Color::White);
		snake.draw(window);
	
		for (int i = 0; i < foods.size(); ++i)
		{
			foods[i].draw(window);
		}

		window.draw(circle);
		window.display();
	}

	return 0;
}