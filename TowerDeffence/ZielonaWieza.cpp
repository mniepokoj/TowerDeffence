#include "ZielonaWieza.h"



void ZielonaWieza::Level1()
{
	model.setSize(sf::Vector2f(75, 75));
	model.setFillColor(sf::Color(0, 220, 0));
	model.setOrigin(75 / 2.f, 75 / 2.f);
	zasieg = 180.f;
	obrazenia = 7.f;
	szybkoscOstrzalu = 1500.f;
	wielkoscPocisku = sf::Vector2f(0, 0);
	predkoscPocisku = 420.1f;
	CzasDoWystrzalu = szybkoscOstrzalu;
}
void ZielonaWieza::Level2()
{
	zasieg = 220.0f;
	obrazenia = 18.f;
	szybkoscOstrzalu = 2000.f;
	wielkoscPocisku = sf::Vector2f(0, 0);
	predkoscPocisku = 460.1f;
	typWygladu = new TypWygladu(poziom, model.getPosition(), model.getSize().x);
}
void ZielonaWieza::Level3()
{
	model.setFillColor(sf::Color(0, 160, 117));
	zasieg = 270.0f;
	obrazenia = 30.f;
	szybkoscOstrzalu = 2000.f;
	wielkoscPocisku = sf::Vector2f(0, 0);
	predkoscPocisku = 465.f;
	typWygladu->zmienTyp(poziom);
}

ZielonaWieza::ZielonaWieza(sf::Vector2f polozenie) : Wieza()
{
	typWygladu = NULL;
	poziom = 1;
	Level1();
	model.setPosition(polozenie);
}


ZielonaWieza::ZielonaWieza(const ZielonaWieza& wieza) : Wieza()
{
	model.setSize(wieza.model.getSize());
	model.setFillColor(wieza.model.getFillColor());
	model.setOrigin(wieza.model.getSize().x / 2, wieza.model.getSize().y / 2);
	model.setPosition(wieza.model.getPosition());
	zasieg = wieza.zasieg;
	predkoscPocisku = wieza.predkoscPocisku;
	obrazenia = wieza.obrazenia;
	wielkoscPocisku = wieza.wielkoscPocisku;
	szybkoscOstrzalu = wieza.szybkoscOstrzalu;
	CzasDoWystrzalu = wieza.CzasDoWystrzalu;
	if (wieza.typWygladu)
	{
		typWygladu = new TypWygladu(*wieza.typWygladu);
	}
	poziom = wieza.poziom;
}

void ZielonaWieza::Ruch(const float& czas)
{
	CzasDoWystrzalu += czas * 1000.0f;
	if (CzasDoWystrzalu >= szybkoscOstrzalu)
	{
		for (unsigned i = 0; i < zarzadcaStworow->stwory.size(); i++)
		{
			if (!zarzadcaStworow->stwory[i]->CzyZabity())
			{
				if (Collision::CircleCollision(zasieg, model.getPosition(), zarzadcaStworow->stwory[i]->PobierzKolo().getRadius(), zarzadcaStworow->stwory[i]->PobierzKolo().getPosition()))
				{
					zarzadcapociskow->Stworz(new WyrzucanyPocisk(model.getPosition(), zarzadcaStworow->stwory[i],
						predkoscPocisku, obrazenia));
					CzasDoWystrzalu = 0;
					break;
				}
			}
		}
	}
}

void ZielonaWieza::Ulepsz()
{
	poziom++;
	switch (poziom)
	{
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	default:
		poziom = 99999;
		break;
	}
}


int ZielonaWieza::PobierzKoszt(bool creatable) const 
{ 
	switch (poziom - creatable)
	{
		case 0:	return 130;
		case 1:	return 120;
		case 2:	return 160;
		default:	return 99999;
	}
};

int ZielonaWieza::MaxPoziom() const { return 3; };

std::wstring ZielonaWieza::PobierzNazwe() const { return poziom > 2 ? L"Morska" : L"Zielona"; }


std::wstring ZielonaWieza::PobierzOpis() const
{
	if (poziom < 3)	return L"";
	else return L"Wie¿a snajperska.";
}

#undef definowanaSzybkoscOstrzalu
#undef definowaneObrazenia
#undef definowanyZasieg