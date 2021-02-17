#pragma once

#include <SFML/Graphics.hpp>
#include "Matematyka.h"
#include "StatyczneTekstury.h"
#include "MojeFigury.h"
#include "ZwracanyTypPoziomu.h"



class Esc : public sf::Drawable
{
protected:
	Pole* menu;

	Pole* wznow;

	Pole* wyjdz;

	Pole* powtorz;

	sf::RectangleShape zaciemnienie;
	sf::RectangleShape obwod;
	sf::RectangleShape tablica;

public:
	Esc();

	ZDARZENIE Zarzadzaj(const sf::Event& zdarzenie,const sf::Vector2f& mysz) const;

	ZDARZENIE Zarzadzaj() const;
	void SprawdzAnimacje(const sf::Vector2f& mysz) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~Esc();
};

