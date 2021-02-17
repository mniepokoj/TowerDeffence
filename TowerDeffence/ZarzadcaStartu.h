#pragma once

#include "SFML/Graphics.hpp"
#include <fstream>
#include "Statyczne.h"


class ZarzadcaStartu : public sf::Drawable
{
public:
	ZarzadcaStartu(sf::RenderWindow* window);
	sf::RenderWindow* okno;
	sf::Text tekst;

	bool Zarzadzaj(sf::Event& zdarzenie);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	~ZarzadcaStartu();
};

