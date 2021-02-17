#include "Matematyka.h"

std::array<float, Matematyka::size> Matematyka::tab;

void Matematyka::Aktywacja()
{
	unsigned i;
	for (i = 0; i < size; i++)
	{
		tab[i] = std::cos(static_cast<float>(i) * unit);
	}
}

float Matematyka::cos(float x)
{
	if (x < 0 || x > 2 * PI)
	{
		return std::cos(x);
	}

	if (x < PI)
	{
		if (x < PI / 2.f)
		{
			return tab[static_cast<int>(x / unit)];
		}
		else
		{
			return -tab[static_cast<int>((PI - x) / unit)];
		}
	}
	else
	{
		if (x < 3.f / 2.f * PI)
		{
			return -tab[static_cast<int>((x - PI) / unit)];
		}
		else
		{
			return tab[static_cast<int>((2.f * PI - x) / unit)];
		}
	}
}

float Matematyka::sin(float x)
{
	if (x < 0 || x > 2 * PI)
	{
		return std::sin(x);
	}
	if (x < PI)
	{
		if (x < PI / 2.f)
		{
			return tab[static_cast<int>((PI/2.f - x) / unit)];
		}
		else
		{
			return tab[static_cast<int>((x - PI/2.f) / unit)];
		}
	}
	else
	{
		if (x < 3.f / 2.f * PI)
		{
			return -tab[static_cast<int>((PI*3.f/2.f - x) / unit)];
		}
		else
		{
			return -tab[static_cast<int>((x -  PI * 3.f / 2.f) / unit)];
		}
	}
}

float normaliseRad(float rad)
{
	while (rad > 2.f * PI)
	{
		rad -= 2.f * PI;
	}
	while (rad < 0.f)
	{
		rad += 2.f * PI;
	}
	return rad;
}

void Matematyka::Test()
{

}

