#include "Triangle.h"

constexpr float AlphaChanging = 90;
constexpr float rotationSpeed = 40;
constexpr float localRotationSpeed = 40;

Triangle::Triangle() : VertexTriangle()
{
}

Triangle::Triangle(float size, const sf::Vector2f& Position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor, float Radius, float startRotation)
	: VertexTriangle(size, Position, outlineThickness, fillColor, outlineColor)
{
	Create(size, Position, outlineThickness, fillColor, outlineColor, Radius, startRotation);
}

void Triangle::Create(float size, const sf::Vector2f& Position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor, float Radius, float startRotation)
{
	VertexTriangle::Create(size, Position, outlineThickness, fillColor, outlineColor);
	radius = Radius;
	angle = startRotation + 45;
	alpha = 255;
	alphaIncrease = false;
	position = Position;

	float radian = to_rad(angle), x, y;
	float sinus = Matematyka::sin(radian), cosinus = Matematyka::cos(radian);
	x = (radius * cosinus - radius * sinus) * sqrt1_2;
	y = (radius * sinus + radius * cosinus) * sqrt1_2;
	VertexTriangle::setPosition(x + position.x, y + position.y);
}

void Triangle::Motion(float time)
{
	angle += rotationSpeed * time;
	float radian = to_rad(angle), x, y;
	float sinus = Matematyka::sin(radian), cosinus = Matematyka::cos(radian);
	x = radius * cosinus - radius * sinus;
	y = radius * sinus + radius * cosinus;
	VertexTriangle::setPosition(x + position.x, y + position.y);

/*	if (alphaIncrease)
	{
		alpha += AlphaChanging * time;
		if (alpha > 255)
		{
			alpha = 255;
			alphaIncrease = false;
		}
	}
	else
	{
		alpha -= AlphaChanging * time;
		if (alpha < 64)
		{
			alpha = 64;
			alphaIncrease = true;
		}
	}
	sf::Color color = VertexTriangle::getOutlineColor();
	color.a = Uint8(alpha);
	VertexTriangle::setOutlineColor(color);
	*/

	VertexTriangle::rotate(localRotationSpeed * time);
}

void Triangle::setPosition(float x, float y)
{
	VertexTriangle::move(x - position.x, y - position.y);
	position.x = x; 
	position.y = y;
}
void Triangle::setPosition(const Vector2f &Position)
{
	VertexTriangle::move(position - Position);
	position = Position;
}

Triangle::~Triangle()
{
}
