#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Matematyka.h"

using namespace sf;


class VertexTriangle : public sf::Drawable
{
private:
	sf::VertexArray data;
	sf::Vector2f position;
	sf::Vector2f inOrigin;
	sf::Vector2f outOrigin;
	sf::Vector2f vertexs[6];
	float angle;
public:
	VertexTriangle();
	VertexTriangle(float size, const sf::Vector2f& position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor);
	void Create(float size, const sf::Vector2f& position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void rotate(float angle);
	void setFillColor(const Color &color);
	void setOutlineColor(const Color &color);
	void setOutlineThickness(float thickness);
	void setSize(float size);
	const Color & getFillColor() const;
	const Color & getOutlineColor() const;
	float getOutlineThickness() const;
	float getSize() const;
	 std::size_t getPointCount() const;
	const Vector2f& getPoint(std::size_t index) const;
	FloatRect getGlobalBounds() const;
	void setPosition(float x, float y);
	void setPosition(const Vector2f &position);
	void setRotation(float angle);
	const Vector2f& getPosition() const;
	float getRotation() const;
	const Vector2f& getOrigin() const;
	void move(float offsetX, float offsetY);
	void move(const Vector2f& offset);

	~VertexTriangle();
};

