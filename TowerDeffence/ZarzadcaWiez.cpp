#include "ZarzadcaWiez.h"



ZarzadcaWiez::ZarzadcaWiez()
{
}


void ZarzadcaWiez::Ruch(const float& czas)
{
	for (auto& i : wiezyczki)
	{
		i->Ruch(czas);
	}
}

void ZarzadcaWiez::DodajWieze(Wieza* wieza)
{
	wiezyczki.push_back(wieza);
}

void ZarzadcaWiez::DodajWieze(TYP_WIEZY typ, const sf::Vector2f& pozycja)
{	
	wiezyczki.push_back(StworzWieze(typ, pozycja));
}

void ZarzadcaWiez::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : wiezyczki)
	{
		target.draw(*i);
	}
}

ZarzadcaWiez::~ZarzadcaWiez()
{
	for (auto& i : wiezyczki)
	{
		delete i;
	}
}

Wieza* ZarzadcaWiez::StworzWieze(TYP_WIEZY typ, const sf::Vector2f& pozycja)
{
	switch (typ)
	{
	case TYP_WIEZY::NIEBIESKA:
		return new NiebieskaWieza(pozycja);
		break;
	case TYP_WIEZY::ZOLTA:
		return new ZoltaWieza(pozycja);
		break;
	case TYP_WIEZY::ZIELONA:
		return new ZielonaWieza(pozycja);
		break;
	case TYP_WIEZY::CZERWONA:
		return new CzerwonaWieza(pozycja);
		break;
	case TYP_WIEZY::POMARANCZOWA:
		return new PomaranczowaWieza(pozycja);
		break;
	default:
		return new NiebieskaWieza(pozycja);
		break;
	}
}

Wieza* ZarzadcaWiez::StworzWieze(Wieza* wieza)
{
	switch (wieza->PobierzTyp())
	{
	case TYP_WIEZY::NIEBIESKA:
		return new NiebieskaWieza(*dynamic_cast<NiebieskaWieza*>(wieza));
		break;
	case TYP_WIEZY::ZOLTA:
		return new ZoltaWieza(*dynamic_cast<ZoltaWieza*>(wieza));
		break;
	case TYP_WIEZY::ZIELONA:
		return new ZielonaWieza(*dynamic_cast<ZielonaWieza*>(wieza));
		break;
	case TYP_WIEZY::CZERWONA:
		return new CzerwonaWieza(*dynamic_cast<CzerwonaWieza*>(wieza));
		break;
	default:
		return new NiebieskaWieza();
		break;
	}
}