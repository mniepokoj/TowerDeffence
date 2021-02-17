#pragma once

#include "Pocisk.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class ZarzadcaPociskow : public sf::Drawable
{
public:
	std::list <Pocisk*> pociski;
	ZarzadcaPociskow();
	void Ruch(float czas);
	void Stworz(Pocisk* pocisk);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	~ZarzadcaPociskow();
};

