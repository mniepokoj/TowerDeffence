#pragma once

#include "KrzyzykowePole.h"
#include "OkraglePole.h"
#include "ProstokatnePole.h"
#include "ZwracanyTypPoziomu.h"

class RodzajPoziomu : public sf::Drawable
{
public:
	int poziom;
	sf::RectangleShape tablica;
	Pole* normalny;
	Pole* szybki;
	/////
	//Pozycja œrodka górnej krawêdzi pola
	/////
	RodzajPoziomu(float x, float y, int poziom);

	TYP_POZIOMU Zarzadzaj(sf::Event& zdarzenie, sf::Vector2f& mysz);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~RodzajPoziomu();
};