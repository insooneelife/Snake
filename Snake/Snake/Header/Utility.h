#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include "Data.h"
#include "Globals.h"

class Utility
{
public:
	static void gotoxy(int x, int y)
	{
		COORD posXY = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
	}

	static void printStringOnPos(std::string part, sf::Vector2f pos)
	{
		gotoxy(pos.x * 2, pos.y);
		std::cout << part;
	}

	static float square(float val)
	{
		return val * val;
	}

	

	static sf::Vector2f getCenter(const sf::CircleShape& circle)
	{
		return sf::Vector2f(circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius()));
	}

	static sf::Vector2f getCenter(const sf::RectangleShape& rect)
	{
		return sf::Vector2f(
			rect.getPosition() + 
			sf::Vector2f(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2));
	}

	static float getVectorSize(const sf::Vector2f& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	static float getVectorSizeSQ(const sf::Vector2f& v)
	{
		return v.x * v.x + v.y * v.y;
	}

	static sf::Vector2f getVectorNorm(const sf::Vector2f& v)
	{
		return v / getVectorSize(v);
	}

	static sf::Vector2f getVectorSafeNorm(const sf::Vector2f& v)
	{
		if (getVectorSizeSQ(v) < 0.00001f)
			return sf::Vector2f();

		return v / getVectorSize(v);
	}

	static float getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return getVectorSize(a - b);
	}

	static float getDistanceSQ(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return getVectorSizeSQ(a - b);
	}

	static float getRectInnerRadius(const sf::FloatRect& r)
	{
		return std::min<float>(r.width / 2, r.height / 2);
	}

	static float getRectOuterRadius(const sf::FloatRect& r)
	{
		return sqrt(r.width * r.width + r.height * r.height);
	}

	static bool IsPointInRect(const sf::FloatRect& r, sf::Vector2f p)
	{
		return r.left < p.x &&
			r.left + r.width > p.y &&
			r.top < p.y &&
			r.top + r.height > p.y;
	}

	static bool intersects(const sf::FloatRect& r1, const sf::FloatRect& r2)
	{
		return !(r2.left > r1.left + r1.width
			|| r2.left + r2.width < r1.left
			|| r2.top > r1.top + r1.height
			|| r2.top + r2.height < r1.top);
	}

	static bool intersects(const sf::CircleShape& a, const sf::CircleShape& b)
	{
		float distance = getDistance(getCenter(a), getCenter(b));

		if (distance > a.getRadius() + b.getRadius())
			return false;

		if (distance > std::abs(a.getRadius() - b.getRadius()))
			return true;
		
		return false;
	}

	static bool intersects(const sf::CircleShape& c, const sf::RectangleShape& r)
	{
		return intersects(c.getGlobalBounds(), r.getGlobalBounds());
	}

	static bool intersects(const sf::CircleShape& circle, const sf::ConvexShape& convex)
	{
		return intersects(circle.getGlobalBounds(), convex.getGlobalBounds());
	}

	static bool intersects(const sf::RectangleShape& r1, const sf::RectangleShape& r2)
	{
		return intersects(r1.getGlobalBounds(), r2.getGlobalBounds());
	}

	static bool intersects(const sf::RectangleShape& r, const sf::CircleShape& c)
	{
		return intersects(r.getGlobalBounds(), c.getGlobalBounds());
	}

	static bool intersects(const sf::RectangleShape& r, const sf::ConvexShape& c)
	{
		return intersects(r.getGlobalBounds(), c.getGlobalBounds());
	}


	static bool intersects(const sf::ConvexShape& c1, const sf::ConvexShape& c2)
	{
		return intersects(c1.getGlobalBounds(), c2.getGlobalBounds());
	}

	static bool intersects(const sf::ConvexShape& convex, const sf::CircleShape& circle)
	{
		return intersects(convex.getGlobalBounds(), circle.getGlobalBounds());
	}

	static bool intersects(const sf::ConvexShape& c, const sf::RectangleShape& r)
	{
		return intersects(c.getGlobalBounds(), r.getGlobalBounds());
	}

	static void setCircle(
		sf::CircleShape& circle,
		float radius,
		sf::Vector2f centerPos = sf::Vector2f(0,0))
	{
		circle.setRadius(radius);
		circle.setPosition(centerPos + sf::Vector2f(-radius, -radius));
	}

	static void setCirclePos(sf::CircleShape& circle, sf::Vector2f centerPos)
	{
		circle.setPosition(centerPos + sf::Vector2f(-circle.getRadius(), -circle.getRadius()));
	}

	// 0 ~ 1
	static float randomFloat()
	{
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}

	static sf::Vector2f randomPosInCircle(sf::Vector2f pos, float radius)
	{
		float t = 2 * Globals::PI * randomFloat();
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
		return sf::Vector2f(r * cos(t), r * sin(t)) ;
	}
};