#pragma once
#include <SFML/Graphics.hpp>
#include "StatyczneTekstury.h"
#include "Minion.h"
#include "DefinicjePaskaWyboru.h"

class WybranyStwor : public sf::Drawable
{
public:
	WybranyStwor(Minion* stwor);
	Minion* stwor;

	std::vector <sf::Text> nazwa;
	sf::Text zycie;
	sf::Text nagroda;
	sf::Text utrata;

	void ZmienStwora(Minion* stwor);
	bool Ruch();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};