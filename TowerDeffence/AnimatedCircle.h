#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <list>
#include "Animation.h"


class AnimatedCircle : public sf::CircleShape
{
private:
	std::vector<Animation> animations;
	float maxWave;
public:
	AnimatedCircle(float radius = 0, std::size_t pointCount = 30);
	void create(const sf::Vector2f& position, float radius, const sf::Color& color, float maxWave, int AnimationAmount);
	void motion(float czas);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setRadius(float radius);
	void setPointCount(std::size_t count);  
	void setTexture(const sf::Texture* texture, bool resetRect = false); // not supported
	void setTextureRect(const sf::IntRect& rect); // not supported
	void setFillColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);	// not supported
	void setOutlineThickness(float thickness);	// not supported
	const sf::Texture* getTexture() const;	// not supported
	const sf::Color& getOutlineColor() const;	// not supported
	float getOutlineThickness() const;	// not supported
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setRotation(float radian);	// not supported
	void setScale(float factorX, float factorY); // not supported
	void setScale(const sf::Vector2f& factors); // not supported
	void setOrigin(float x, float y); // not supported
	void setOrigin(const sf::Vector2f& origin); // not supported
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	void rotate(float radian); // not supported
	void scale(float factorX, float factorY); // not supported
	void scale(const sf::Vector2f& factor);	// not supported

	~AnimatedCircle();
};

