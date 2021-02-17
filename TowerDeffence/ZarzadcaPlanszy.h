#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MojeFigury.h"
#include "RodzajPoziomu.h"



class ZarzadcaPlanszy : public sf::Drawable
{
public:
	sf::RenderWindow* okno;

	std::vector <sf::CircleShape*> kola;

	RodzajPoziomu* rodzajPoziomu;

	ZarzadcaPlanszy(sf::RenderWindow* window);

	static void Aktywacja();

	static std::vector <bool>* czyWygrana;

	static void ZmienStanWybranegoPoziomnu(int poziom);
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	ZwracanyTypPoziomu Zarzadzaj(sf::Event& zdarzenie);

	~ZarzadcaPlanszy();
};

