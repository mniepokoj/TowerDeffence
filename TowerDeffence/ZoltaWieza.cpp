#include "ZoltaWieza.h"



void ZoltaWieza::Level1()
{
	model.setSize(sf::Vector2f(50, 50));
	model.setFillColor(sf::Color(210, 200, 0));
	model.setOrigin(50 / 2.f, 50 / 2.f);
	zasieg = 75.f;
	obrazenia = 1.f;
	szybkoscOstrzalu = 175.f;
	wielkoscPocisku = sf::Vector2f(5, 2);
	predkoscPocisku = 200.f;
	CzasDoWystrzalu = szybkoscOstrzalu;
	liczbaStrzalow = 1;
}
void ZoltaWieza::Level2()
{
	zasieg = 90.f;
	obrazenia = 2.f;
	szybkoscOstrzalu = 140.f;
	wielkoscPocisku = sf::Vector2f(6, 3);
	predkoscPocisku = 225.1f;
	liczbaStrzalow = 1;
	typWygladu = new TypWygladu(poziom, model.getPosition(), model.getSize().x);
}
void ZoltaWieza::Level3()
{
	zasieg = 90.f;
	obrazenia = 1.f;
	szybkoscOstrzalu = 170.f;
	wielkoscPocisku = sf::Vector2f(5, 2);
	predkoscPocisku = 230.1f;
	model.setFillColor(sf::Color(240, 210, 0));
	liczbaStrzalow = 3;
	typWygladu->zmienTyp(poziom);
}
void ZoltaWieza::Level4()
{
	szybkoscOstrzalu = 120;
	zasieg = 95;
	liczbaStrzalow = 5;
}

void ZoltaWieza::Strzelanie12()
{
	for (unsigned i = 0; i < zarzadcaStworow->stwory.size(); i++)
	{
		if (!zarzadcaStworow->stwory[i]->CzyZabity())
		{
			if (CzasDoWystrzalu >= szybkoscOstrzalu)
			{
				if (Collision::CircleCollision(zasieg, model.getPosition(), zarzadcaStworow->stwory[i]->PobierzKolo().getRadius(), zarzadcaStworow->stwory[i]->PobierzKolo().getPosition()))
				{
					zarzadcapociskow->Stworz(new ZwyklyPocisk(model.getPosition(), zarzadcaStworow->stwory[i],
						predkoscPocisku, obrazenia, wielkoscPocisku));
					CzasDoWystrzalu = 0;
					break;
				}
			}
		}
	}
}
void ZoltaWieza::Strzelanie34()
{
	int licznik = 0;
	for (unsigned i = 0; i < zarzadcaStworow->stwory.size(); i++)
	{
		if (!zarzadcaStworow->stwory[i]->CzyZabity())
		{
			if (Collision::CircleCollision(zasieg, model.getPosition(), zarzadcaStworow->stwory[i]->PobierzKolo().getRadius(), zarzadcaStworow->stwory[i]->PobierzKolo().getPosition()))
			{

				zarzadcapociskow->Stworz(new ZwyklyPocisk(model.getPosition(), zarzadcaStworow->stwory[i], predkoscPocisku, obrazenia, wielkoscPocisku));
				CzasDoWystrzalu = 0;
				licznik++;
				if (licznik >= liczbaStrzalow) break;
			}
		}
	}
}

ZoltaWieza::ZoltaWieza(const sf::Vector2f& polozenie) : Wieza()
{
	typWygladu = NULL;
	poziom = 1;
	Level1();
	model.setPosition(polozenie);
}

ZoltaWieza::ZoltaWieza(const ZoltaWieza& wieza) : Wieza()
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
	liczbaStrzalow = wieza.liczbaStrzalow;
	poziom = wieza.poziom;
	CzasDoWystrzalu = wieza.CzasDoWystrzalu;
	if (wieza.typWygladu)
	{
		typWygladu = new TypWygladu(*wieza.typWygladu);
	}
}

void ZoltaWieza::Ruch(const float& czas)
{
	CzasDoWystrzalu += czas * 1000.0f;
	if (CzasDoWystrzalu >= szybkoscOstrzalu)
	{
		if (poziom <= 2)
		{
			Strzelanie12();
		}
		else
		{
			Strzelanie34();
		}
	}
}


void ZoltaWieza::Ulepsz()
{
	switch (++poziom)
	{
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	case 4:
		Level4();
		break;
	default:
		poziom = 99999;
		break;
	}
}

int ZoltaWieza::PobierzKoszt(bool creatable) const 
{ 
	switch (poziom - creatable)
	{
	case 0: return 80;
	case 1:	return 80;
	case 2:	return 110;
	case 3:	return 100;
	default:
		return 99999;
		break;
	}
};

int ZoltaWieza::MaxPoziom() const { return 4; };

std::wstring ZoltaWieza::PobierzNazwe() const { return poziom > 2 ? L"Z³ota" : L"¯ó³ta"; }

std::wstring ZoltaWieza::PobierzOpis() const
{
	if (poziom < 3)	return L"";
	else return L"Z³ota wie¿a potrafi atakowaæ 4 przeciwników jednoczeœnie.";
}