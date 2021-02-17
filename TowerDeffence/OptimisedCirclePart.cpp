#include "OptimisedCirclePart.h"

OptimisedCirclePart::OptimisedCirclePart(const sf::Vector2f& position, float radStart, float _radius, float _radian, const sf::Color& color) :
    radius(_radius* sqrt1_2),
    radian(_radian / 2.f),
    number(static_cast<int>(radian / optimal_point_count_by_radian + radius / optimal_point_count_by_radius)),
    optim(radian / number),
    v(number * 2 + 1, sf::Vertex(sf::Vector2f(0, 0), color))
{
    rotate(radStart, position);
}

void OptimisedCirclePart::rotate(float _radian, const sf::Vector2f& position)
{
    float k = _radian - radian;
    for (int i = number; i > 0; --i)
    {
        v[number - i].position.x = radius * (Matematyka::cos(k) -  Matematyka::sin(k)) + position.x;
        v[number - i].position.y = radius * (Matematyka::cos(k) + Matematyka::sin(k)) + position.y;
        k += optim;
    }

    for (int i = 0; i <= number; ++i)
    {
        v[i + number].position.x = radius * (Matematyka::cos(k) - Matematyka::sin(k)) + position.x;
        v[i + number].position.y = radius * (Matematyka::cos(k) + Matematyka::sin(k)) + position.y;
        k += optim;
    }
}

void OptimisedCirclePart::move(const sf::Vector2f& vector)
{
    for (int i = 0; i <= 2 * number; i++)
    {
        v[i].position += vector;
    }
}

void OptimisedCirclePart::setScale(float scale, sf::Vector2f& position)
{
   
}

void OptimisedCirclePart::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(&v[0], v.size(), sf::TriangleFan);
}

void OptimisedCirclePart::setColor(const sf::Color& color)
{
    for (int i = number; i >= 0; --i)
    {
        v[2 * i].color = color;
        v[2 * i + 1].color = color;
    }
}