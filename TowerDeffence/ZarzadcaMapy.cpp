#include "ZarzadcaMapy.h"


ZarzadcaMapy::ZarzadcaMapy(const int& numerPoziomu)
{
	mapa = new Mapa(numerPoziomu);
	Minion::UstawMape(mapa);
}

void ZarzadcaMapy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*mapa);
}

ZarzadcaMapy::~ZarzadcaMapy()
{
	delete mapa;
}