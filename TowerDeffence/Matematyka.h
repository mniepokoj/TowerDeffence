#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

constexpr float PI = 3.14159265358979323846f;
constexpr float PI_180 = PI / 180.f; // PI/180
constexpr float PI1_180 = 1 / PI_180; //180/PI
constexpr float sqrt2 = 1.41421356237309504880f;
constexpr float sqrt1_2 = 1 / sqrt2; // 1/sqrt(2)
constexpr float sqrt3 = 1.73205080756887729352f;



class Matematyka
{
private:
	constexpr static float unit = (PI/2.f)/(1023.f);
	constexpr static unsigned size = 1024;
	static std::array<float, size> tab;
	Matematyka();
public:
	static void Aktywacja();
	static float cos(float x);
	static float sin(float x);
	static void Test();
};


inline float vector_length(float x, float y)
{
	return sqrt(x * x + y * y);
}

inline float vector_length(const sf::Vector2f& v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}


template<typename type> inline float to_rad(type radian)
{
	return radian * PI_180;
}

template<typename type> inline float to_angle(type radian)
{
	return radian * PI1_180;
}

inline void normaliseVector(sf::Vector2f& vector)
{
	vector /= vector_length(vector);
}

float normaliseRad(float rad);