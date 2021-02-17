#pragma once
#include <SFML/Graphics.hpp>
#include "Matematyka.h"


class OptimisedCirclePart : public sf::Drawable
{
protected:
	static constexpr float optimal_point_count_by_radian = PI / 16.f;
	static constexpr float optimal_point_count_by_radius = 14 * PI;

	float radius;
	const float radian;
	int number;
	float optim;
	std::vector<sf::Vertex> v;
public:
	OptimisedCirclePart(const sf::Vector2f& position, float radStart, float radius, float radian, const sf::Color& color);
	virtual void rotate(float radian, const sf::Vector2f& position);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void move(const sf::Vector2f& v);

	//not save fun, if scale > 1 demand update
	void setScale(float scale, sf::Vector2f& pos);
	void setColor(const sf::Color& color);
};

