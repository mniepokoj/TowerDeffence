#include "ZarzadcaPociskow.h"



ZarzadcaPociskow::ZarzadcaPociskow()
{

}

void ZarzadcaPociskow::Ruch(float czas)
{
	pociski.remove_if([](const Pocisk* pocisk) { return pocisk->czyZabity; });
	for (auto& i : pociski)
	{
		i->Ruch(czas);
	}
}

void ZarzadcaPociskow::Stworz(Pocisk* pocisk)
{
	pociski.push_back( pocisk );
}


void ZarzadcaPociskow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : pociski)
	{
		target.draw(*i);
	}
}

ZarzadcaPociskow::~ZarzadcaPociskow()
{
	for (auto& i : pociski)
	{
		delete i;
	}
}
