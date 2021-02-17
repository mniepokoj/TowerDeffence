#include "Animation.h"

//twierdzenie cosinosow
float inline calculateRadian(float R, float r, float d)
{
	float rr = r * r;
	float RR = R * R;
	float dd = d * d;
	float rsubR = rr - RR;

	return acosf((dd * dd - 2 * dd * RR + rsubR * rsubR) / (2 * dd * rr));
}

//przeksztalcenie wzgledem kata
sf::Vector2f rotate_transform(float distance, float rad)
{
	return sf::Vector2f((distance * Matematyka::cos(rad) - distance * Matematyka::sin(rad)),
						(distance * Matematyka::sin(rad) + distance * Matematyka::cos(rad)));
}

Animation::Animation(const sf::Vector2f& pos, float R,  float r, float d, float predkoscRad, float rad, const sf::Color& color) : 
	distance(d*sqrt1_2),
	circle(pos + rotate_transform(distance, rad), rad , r, calculateRadian(R, r, d), color)
{
	speed = predkoscRad;
	position = pos;
	rotation = rad;
}

void Animation::move(const sf::Vector2f& dystans)
{
	circle.move(dystans);
	position += dystans;
}

void Animation::motion(float czas)
{
	rotation = normaliseRad(rotation + speed * czas);
	circle.rotate(rotation, position + rotate_transform(distance, rotation));
}

void Animation::setScale(float scale)
{
	circle.setScale(scale, position);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle);
}

void Animation::setColor(const sf::Color& color)
{
	circle.setColor(color);
}

void Animation::setPosition(const sf::Vector2f& pos)
{
	circle.move(pos - position);
	position = pos;
}