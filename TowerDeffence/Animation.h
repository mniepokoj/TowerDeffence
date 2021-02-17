#pragma once
#include <SFML/Graphics.hpp>
#include "Matematyka.h"
#include "OptimisedCirclePart.h"

struct Animation : public sf::Drawable
{
protected:
	float rotation;
	float speed;
	float distance;
	sf::Vector2f position;
	OptimisedCirclePart circle;
public:
	Animation(const sf::Vector2f& pozycja, float R, float r, float Odleglosc, float predkoscRad, float rad,const sf::Color& kolor);
	void motion(float czas);
	void move(const sf::Vector2f& dystans);
	void setScale(float scale);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& pos);
};