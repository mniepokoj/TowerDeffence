#pragma once

#include "VertexTriangle.h"

class Triangle : public VertexTriangle
{
	float radius;
	sf::Vector2f position;
	float angle;
	float alpha;
	bool alphaIncrease;
public:
	Triangle();
	Triangle(float size, const sf::Vector2f& position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor, float radius, float StartRotation);
	void Create(float size, const sf::Vector2f& position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor, float radius, float StartRotation);
	void Motion(float time);
	void setPosition(float x, float y);
	void setPosition(const Vector2f &position);

	~Triangle();
};

