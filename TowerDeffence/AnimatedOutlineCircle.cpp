#include "AnimatedOutlineCircle.h"

using namespace sf;

AnimatedOutlineCircle::AnimatedOutlineCircle(float radius, std::size_t pointCount) : CircleShape(radius, pointCount), maxWave(0), animations1(), animations2()
{
}

void AnimatedOutlineCircle::create(const AnimatedOutlineCircleStruct& scheme)
{
	CircleShape::setPosition(scheme.position);
	CircleShape::setRadius(scheme.radius);
	CircleShape::setOrigin(scheme.radius, scheme.radius);
	CircleShape::setFillColor(scheme.inlineColor);
	CircleShape::setOutlineColor(scheme.outlineColor);
	CircleShape::setOutlineThickness(-scheme.outlineThickness);
	CircleShape::setPointCount(200);
	maxWave = scheme.maxWave;

	if (maxWave == 0.f) 
		maxWave = 0.0000001f;
	float promienRand, wychylenieRand, kat, predkosc;
	animations1.reserve(scheme.animationAmount);
	animations2.reserve(scheme.animationAmount);
	for (int i = 0; i < scheme.animationAmount; i++)
	{
		promienRand = static_cast<float>( rand() % static_cast<int>(scheme.radius * 20.f) / 200) + scheme.radius * 0.8f;
		wychylenieRand = (rand() % (int(maxWave * 100)) / 100.f);
		kat = rand() % 360 * PI_180;
		if (rand() % 2)
		{
			predkosc = ((rand() % 200) + 150) / (1800 * PI / 60);
		}
		else
		{
			predkosc = -((rand() % 200) + 150) / (1800 * PI / 60);
		}
		animations1.push_back(Animation(scheme.position, CircleShape::getRadius() - scheme.outlineThickness, promienRand - scheme.outlineThickness, maxWave + (scheme.radius - promienRand), predkosc, kat, scheme.inlineColor));
		animations2.push_back(Animation(scheme.position, CircleShape::getRadius() - scheme.outlineThickness, promienRand, maxWave + (scheme.radius - promienRand), predkosc, kat, scheme.outlineColor));
	}
}


void AnimatedOutlineCircle::motion(float czas)
{
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		animations1[i].motion(czas);
		animations2[i].motion(czas);
	}
}
void AnimatedOutlineCircle::draw(RenderTarget& target, RenderStates states) const
{
	for (auto& i : animations2) target.draw(i);
	target.draw(sf::CircleShape(*this));
	for (auto& i : animations1) target.draw(i);
}
void AnimatedOutlineCircle::setRadius(float radius)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	float scale = radius / CircleShape::getRadius();
	CircleShape::setRadius(radius);
	CircleShape::setOrigin(radius, radius);
	/*
	for (auto& i : animations1)
	{
		i.circle.setRadius(scale * i.circle.getRadius());
		i.circle.setOrigin(i.circle.getRadius(), i.circle.getRadius());
		i.distance *= scale;
		i.motion(0);
	}
	for (auto& i : animations2)
	{
		i.circle.setRadius(scale * i.circle.getRadius());
		i.circle.setOrigin(i.circle.getRadius(), i.circle.getRadius());
		i.distance *= scale;
		i.motion(0);
	}
	*/

}
void AnimatedOutlineCircle::setPointCount(std::size_t count)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	float scale = static_cast<float>(count) / CircleShape::getPointCount();
	/*
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		animations1[i].circle.setPointCount(static_cast<size_t> (animations1[i].circle.getPointCount() * scale));
		animations2[i].circle.setPointCount(static_cast<size_t> (animations1[i].circle.getPointCount() * scale));
	}
	*/
	CircleShape::setPointCount(count);
}


void AnimatedOutlineCircle::setTexture(const Texture* texture, bool resetRect)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
}
void AnimatedOutlineCircle::setTextureRect(const IntRect& rect)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
}
void AnimatedOutlineCircle::setFillColor(const Color& color)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::setFillColor(color);
	//for (auto& i : animations1) i.circle.setFillColor(color);
}
void AnimatedOutlineCircle::setOutlineColor(const Color& color)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::setOutlineColor(color);
	//for (auto&i : animations2) i.circle.setOutlineColor(color);
}
void AnimatedOutlineCircle::setOutlineThickness(float thickness)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	thickness = abs(thickness);
	float temp = CircleShape::getOutlineThickness() + thickness;
	//for(auto&i : animations1) i.distance -= temp;
	CircleShape::setOutlineThickness(-thickness);
}
const Texture* AnimatedOutlineCircle::getTexture() const
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	return NULL;
}


float AnimatedOutlineCircle::getOutlineThickness() const
{
	return -CircleShape::getOutlineThickness();
}

FloatRect AnimatedOutlineCircle::getLocalBounds() const
{
	FloatRect bound = CircleShape::getLocalBounds();
	float thickness = -getOutlineThickness();
	bound.left += thickness;
	bound.width -= thickness;
	bound.top += thickness;
	bound.height -= thickness;
	return bound;

}
FloatRect AnimatedOutlineCircle::getGlobalBounds() const
{
	FloatRect bound = CircleShape::getGlobalBounds();
	float thickness = getOutlineThickness();
	bound.left += thickness;
	bound.width -= thickness;
	bound.top += thickness;
	bound.height -= thickness;
	return bound;
}

void AnimatedOutlineCircle::setPosition(float x, float y)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[i].position.x = x;
		//animations1[i].position.y = y;
		animations1[i].motion(0);

		//animations2[i].position.x = x;
		//animations2[i].position.y = y;
		animations2[i].motion(0);
	}
	CircleShape::setPosition(x, y);
}
void AnimatedOutlineCircle::setPosition(const Vector2f& position)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[i].position = position;
		animations1[i].motion(0);

		//animations2[i].position = position;
		animations2[i].motion(0);
	}
	CircleShape::setPosition(position);
}
void AnimatedOutlineCircle::setRotation(float angle)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	float temp = angle - CircleShape::getRotation();
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[i].circle.rotate(temp);
		animations1[i].motion(0);

		//animations2[i].circle.rotate(temp);
		animations2[i].motion(0);
	}
	CircleShape::setRotation(angle);
}
void AnimatedOutlineCircle::setScale(float factorX, float factorY)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::setScale(factorX, factorY);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[i].circle.setScale(factorX, factorY);
		///animations2[i].circle.setScale(factorX, factorY);
	}
}
void AnimatedOutlineCircle::setScale(const Vector2f& factors)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::setScale(factors);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[i].circle.setScale(factors);
		//animations2[i].circle.setScale(factors);
	}
}
void AnimatedOutlineCircle::setOrigin(float x, float y)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
}
void AnimatedOutlineCircle::setOrigin(const Vector2f& origin)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
}

void AnimatedOutlineCircle::move(float offsetX, float offsetY)
{
	CircleShape::move(offsetX, offsetY);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		animations1[i].move(sf::Vector2f(offsetX, offsetY));
		animations2[i].move(sf::Vector2f(offsetX, offsetY));
	}
}
void AnimatedOutlineCircle::move(const Vector2f& offset)
{
	CircleShape::move(offset);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		animations1[i].move(sf::Vector2f(offset));
		animations2[i].move(sf::Vector2f(offset));
	}
}
void AnimatedOutlineCircle::rotate(float angle)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::rotate(angle);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[i].circle.rotate(angle);
		//animations1[i].motion(0);

		//animations2[i].circle.rotate(angle);
		//animations2[i].motion(0);
	}
}
void AnimatedOutlineCircle::scale(float factorX, float factorY)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::scale(factorX, factorY);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[1].circle.scale(factorX, factorY);
		//animations2[1].circle.scale(factorX, factorY);
	}

}
void AnimatedOutlineCircle::scale(const Vector2f& factor)
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	CircleShape::scale(factor);
	for (unsigned i = 0; i < animations1.size(); i++)
	{
		//animations1[1].circle.scale(factor);
		//animations2[1].circle.scale(factor);
	}
}
const Transform& AnimatedOutlineCircle::getTransform() const
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	return CircleShape::getTransform();
}
const Transform& AnimatedOutlineCircle::getInverseTransform() const
{
#ifdef _DEBUG
	std::cout << "Not supported" << __LINE__ << __FILE__ << std::endl;
#endif // DEBUG
	return CircleShape::getInverseTransform();
}
AnimatedOutlineCircle::~AnimatedOutlineCircle()
{
}
