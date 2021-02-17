#include "AnimatedCircle.h"

using namespace sf;

AnimatedCircle::AnimatedCircle(float radius, std::size_t pointCount) : CircleShape(radius, pointCount)
{
	maxWave = 0;
}

void AnimatedCircle::create(const Vector2f& position, float radius, const Color& color, float MaxWave, int animationAmount)
{
	maxWave = MaxWave;
	CircleShape::setPosition(position);
	CircleShape::setRadius(radius);
	CircleShape::setOrigin(radius, radius);
	CircleShape::setPointCount(static_cast<size_t>(radius * 0.8f + 10.f));
	CircleShape::setFillColor(color);
	animations.reserve(animationAmount);
	if (maxWave > 0)
	{
		float promienRand, wychylenieRand, kat, predkosc;
		for (int i = 0; i < animationAmount; i++)
		{
			promienRand = static_cast<float>(rand() % static_cast<int>(radius  * 10)/200) + radius * 0.9f;
			wychylenieRand = (rand() % (int(maxWave * 100)) / 100.f);
			kat = to_rad(rand() % 360);
			if (rand() % 2)
			{
				predkosc = ((rand() % 200) + 150) / (1800 * PI / 60);
			}
			else
			{
				predkosc = -((rand() % 200) + 150) / (1800 * PI / 60);
			}
			animations.push_back(Animation(position, radius, promienRand, maxWave + (radius - promienRand), predkosc, kat, color));
		}
	}
}
void AnimatedCircle::motion(float czas)
{
	for (auto& i : animations) i.motion(czas);
}
void AnimatedCircle::draw(RenderTarget& target, RenderStates states) const
{
	for (auto& i : animations) target.draw(i);
	target.draw(static_cast<CircleShape>(*this));
}

void AnimatedCircle::setRadius(float radius)
{
	if (animations.size())
	{	
		float scale = radius / CircleShape::getRadius();
		for (auto& i : animations)
		{
			i.setScale(scale);
		}
	}
	CircleShape::setRadius(radius);
	CircleShape::setOrigin(radius, radius);
}

void AnimatedCircle::setPointCount(std::size_t count)
{
	CircleShape::setPointCount(count);
}

void AnimatedCircle::setTexture(const Texture* texture, bool resetRect)
{

}
void AnimatedCircle::setTextureRect(const IntRect& rect)
{

}
void AnimatedCircle::setFillColor(const Color& color)
{
	CircleShape::setFillColor(color);
	for (auto& i : animations)
	{
		i.setColor(color);
	}

}
void AnimatedCircle::setOutlineColor(const Color& color)
{
}
void AnimatedCircle::setOutlineThickness(float thickness)
{
}
const Texture* AnimatedCircle::getTexture() const
{
	return NULL;
}

const Color& AnimatedCircle::getOutlineColor() const
{
	return CircleShape::getOutlineColor();
}
float AnimatedCircle::getOutlineThickness() const
{
	return 0;
}


void AnimatedCircle::setPosition(float x, float y)
{
	for (auto& i : animations)
	{
		i.setPosition(sf::Vector2f(x, y));
	}
	CircleShape::setPosition(x, y);
}
void AnimatedCircle::setPosition(const Vector2f& position)
{
	for (auto& i : animations)
	{
		i.setPosition(position);
	}
	CircleShape::setPosition(position);
}


void AnimatedCircle::setRotation(float radian)
{	float temp = radian - CircleShape::getRotation();
	CircleShape::setRotation(radian);
}
void AnimatedCircle::setScale(float factorX, float factorY)
{
	CircleShape::setScale(factorX, factorY);
}
void AnimatedCircle::setScale(const Vector2f& factors)
{
	CircleShape::setScale(factors);
}

void AnimatedCircle::setOrigin(float x, float y)
{

}
void AnimatedCircle::setOrigin(const Vector2f& origin)
{
}

void AnimatedCircle::move(float offsetX, float offsetY)
{
	CircleShape::move(offsetX, offsetY);
	for (auto& i : animations)
	{
		i.move(sf::Vector2f(offsetX, offsetY));
	}
}
void AnimatedCircle::move(const Vector2f& offset)
{
	CircleShape::move(offset);
	for (auto& i : animations)
	{
		i.move(offset);
	}
}

void AnimatedCircle::rotate(float radian)
{
	CircleShape::rotate(radian);
	for (auto& i : animations)
	{
	}
}
void AnimatedCircle::scale(float factorX, float factorY)
{

}
void AnimatedCircle::scale(const Vector2f& factor)
{

}

AnimatedCircle::~AnimatedCircle()
{
}
