#pragma once
#include "Pole.h"

namespace Collision 
{
	bool CircleRectangleCollision(sf::CircleShape& circle, sf::RectangleShape& rectangle);

	bool CircleCollision(float radious1, const sf::Vector2f& position1, float radious2, const sf::Vector2f& position2);

	bool CirclePointContain(float radius, const sf::Vector2f& position, const sf::Vector2f& point);

	bool CirclePointContain(const sf::CircleShape& circle, const sf::Vector2f& point);

	bool OutlineCircleCollision(const sf::CircleShape& outLineCircle, const sf::CircleShape& circle);
}