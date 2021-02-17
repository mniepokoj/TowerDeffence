#pragma once

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "StatyczneTekstury.h"
#include "MojeFigury.h"
#include "ZwracanyTypPoziomu.h"

class KoniecPoziomu : public sf::Drawable
{
public:
	KoniecPoziomu(bool wynik);
	sf::RenderWindow* okno;
	sf::RectangleShape zaciemnienie;
	sf::RectangleShape tablica;

	bool bilans;

	Pole* wynik;
	Pole* powtorz;
	Pole* dalej;

	ZDARZENIE Zarzadzaj(sf::Event& zdarzenie, bool& wynik);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~KoniecPoziomu();
};

