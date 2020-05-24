#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>

class Utils
{
public:

	static void setCirclePos(sf::CircleShape& circle, sf::Vector2f center)
	{
		float radius = circle.getRadius();
		circle.setPosition(center + sf::Vector2f(-radius, -radius));
	}

	static float getVectorSize(sf::Vector2f v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	static float getVectorSizeSQ(sf::Vector2f v)
	{
		return v.x * v.x + v.y * v.y;
	}

	static float getDistanceSq(sf::Vector2f a, sf::Vector2f b)
	{
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}

	static float getDistance(sf::Vector2f a, sf::Vector2f b)
	{
		return sqrt(getDistanceSq(a, b));
	}

	static sf::Vector2f getVectorSafeNorm(sf::Vector2f v)
	{
		// size
		if (getVectorSizeSQ(v) < 0.00001f)
		{
			return sf::Vector2f();
		}

		return v / getVectorSize(v);
	}

	// random float 0~1
	static float randomFloat()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	static sf::Vector2f getCenter(const sf::CircleShape& circle)
	{
		return sf::Vector2f(circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius()));
	}

	static bool intersects(const sf::CircleShape& a, const sf::CircleShape& b)
	{
		float distance = getDistance(getCenter(a), getCenter(b));

		if (distance > a.getRadius() + b.getRadius())
		{
			return false;
		}

		if (distance > std::abs(a.getRadius() - b.getRadius()))
		{
			return true;
		}

		return false;
	}

};

