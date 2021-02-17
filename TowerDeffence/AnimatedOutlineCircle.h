#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>
#include "AnimatedCircle.h"
#include "AnimatedOutLineStruct.h"


class AnimatedOutlineCircle : public sf::CircleShape
{
private:
	std::vector<Animation> animations1;
	std::vector<Animation> animations2;
	float maxWave;
public:
	AnimatedOutlineCircle(float radius = 0, std::size_t pointCount = 30);
	void create(const AnimatedOutlineCircleStruct& scheme);
	void motion(float czas);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setRadius(float radius);
	void setPointCount(std::size_t count);
	void setTexture(const sf::Texture* texture, bool resetRect = false);
	void setTextureRect(const sf::IntRect& rect);
	void setFillColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);
	void setOutlineThickness(float thickness);
	const sf::Texture* getTexture() const;
	float getOutlineThickness() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setRotation(float angle);
	void setScale(float factorX, float factorY);
	void setScale(const sf::Vector2f& factors);
	void setOrigin(float x, float y);
	void setOrigin(const sf::Vector2f& origin);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	void rotate(float angle);
	void scale(float factorX, float factorY);
	void scale(const sf::Vector2f& factor);
	const sf::Transform& getTransform() const;
	const sf::Transform& getInverseTransform() const;

	~AnimatedOutlineCircle();
};

