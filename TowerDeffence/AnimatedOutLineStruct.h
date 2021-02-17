#pragma once
#include <SFML/Graphics.hpp>


struct AnimatedOutlineCircleStruct
{
public:
	AnimatedOutlineCircleStruct();
	sf::Vector2f position;
	float radius;
	sf::Color inlineColor;
	sf::Color outlineColor;
	float maxWave;
	float outlineThickness;
	int animationAmount;
};