#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <fstream>
#include <math.h>
#include "Mapa.h"
#include "Minion.h"
#include "Wieza.h"
#include "ZarzadcaZdarzen.h"

class ZarzadcaMapy : public sf::Drawable
{
public:
	ZarzadcaMapy(const int& numerPoziomu);
	Mapa* mapa;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~ZarzadcaMapy();
};


