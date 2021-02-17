#pragma once

#include "Minion.h"

class Minion;

struct PasekZycia : public sf::Drawable
{
	Minion* stwor;
	PasekZycia();
	void Ustaw(Minion* stwor);
	sf::RectangleShape tloZycia;
	sf::RectangleShape zycie;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Ruch();
};