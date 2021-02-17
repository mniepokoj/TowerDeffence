#pragma once


#include <SFML\Graphics.hpp>
#include <math.h>
#include "Collision.h"

namespace Collision
{
	template <typename T> T clamp(const T& value, const T& low, const T& high)
	{
		return value < low ? low : (value > high ? high : value);
	}


	bool Collision::CircleRectangleCollision(sf::CircleShape& circle, sf::RectangleShape& rectangle)
	{
		float closestX = clamp(circle.getPosition().x, rectangle.getGlobalBounds().left, rectangle.getGlobalBounds().width);
		float closestY = clamp(circle.getPosition().y, rectangle.getGlobalBounds().top, rectangle.getGlobalBounds().height);

		// Calculate the distance between the circle's center and this closest point
		float distanceX = circle.getPosition().x + circle.getRadius() - closestX;
		float distanceY = circle.getPosition().y + circle.getRadius() - closestY;

		// If the distance is less than the circle's radius, an intersection occurs
		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		return distanceSquared < (circle.getRadius() * circle.getRadius());
	}

	bool CircleCollision(const sf::CircleShape& circle1, const sf::CircleShape& circle2)
	{
		float distance1 = circle1.getPosition().x - circle2.getPosition().x;
		float distance2 = circle1.getPosition().y - circle2.getPosition().y;
		distance1 = pow(distance1, 2) + pow(distance2, 2);
		distance2 = pow(circle1.getRadius() + circle2.getRadius(), 2);
		return (distance2 >= distance1);
	}

	bool CircleCollision(float radious1, const sf::Vector2f& position1, float radious2, const sf::Vector2f& position2)
	{
		float distance1 = position1.x - position2.x;
		float distance2 = position1.y - position2.y;
		distance1 = pow(distance1, 2) + pow(distance2, 2);
		distance2 = pow(radious1 + radious2, 2);
		return (distance2 >= distance1);
	}

	bool CirclePointContain(float radius, const sf::Vector2f& position, const sf::Vector2f& point)
	{
		return (pow(radius, 2) >= pow(position.x - point.x, 2) + pow(position.y - point.y, 2));
	}

	bool CirclePointContain(const sf::CircleShape& circle, const sf::Vector2f& point)
	{
		return (pow(circle.getRadius(), 2) >= pow(circle.getPosition().x - point.x, 2) + pow(circle.getPosition().y - point.y, 2));
	}

	bool OutlineCircleCollision(const sf::CircleShape& circle1, const sf::CircleShape& circle2)
	{
		float r = circle1.getRadius() + circle1.getOutlineThickness() - circle2.getRadius();
		float R = circle1.getRadius() + circle1.getOutlineThickness() + circle2.getRadius();
		float distance = pow(circle1.getPosition().x - circle2.getPosition().x, 2) + pow(circle1.getPosition().y - circle2.getPosition().y, 2);

		if (pow(r, 2) <= distance && distance <= pow(R, 2))
		{
			return true;
		}
		else
		{
			r = circle1.getRadius() - circle2.getRadius();
			R = circle1.getRadius() + circle2.getRadius();
			return (pow(r, 2) <= distance && distance <= pow(R, 2));
		}
	}
}


