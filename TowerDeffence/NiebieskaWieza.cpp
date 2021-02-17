#include "NiebieskaWieza.h"

#include "NiebieskaWieza.h"


void NiebieskaWieza::Level1()
{
	model.setSize(sf::Vector2f(60, 60));
	model.setFillColor(sf::Color(20, 20, 250));
	model.setOrigin(30, 30);
	zasieg = 120.f;
	obrazenia = 2.f;
	szybkoscOstrzalu = 340.f;
	wielkoscPocisku = sf::Vector2f(6, 3);
	predkoscPocisku = 220.1f;
	CzasDoWystrzalu = szybkoscOstrzalu;
}
void NiebieskaWieza::Level2()
{
	zasieg = 150.f;
	obrazenia = 4.f;
	szybkoscOstrzalu = 300.f;
	wielkoscPocisku = sf::Vector2f(8, 4);
	predkoscPocisku = 200.1f;
	typWygladu = new TypWygladu(poziom, model.getPosition(), model.getSize().x);
}
void NiebieskaWieza::Level3()
{
	model.setFillColor(sf::Color(15, 82, 186));
	zasieg = 150.f;
	obrazenia = 5.f;
	szybkoscOstrzalu = 2000.f;
	wielkoscPocisku = sf::Vector2f(0, 0);
	predkoscPocisku = 78.f;
	typWygladu->zmienTyp(poziom);
}
void NiebieskaWieza::Level4()
{
	zasieg = 160.f;
	obrazenia = 7.f;
	szybkoscOstrzalu = 1600.f;
	wielkoscPocisku = sf::Vector2f(0, 0);
	predkoscPocisku = 80.f;
}
void NiebieskaWieza::Strzelanie12()
{
	for (unsigned i = 0; i < zarzadcaStworow->stwory.size(); i++)
	{
		if (!zarzadcaStworow->stwory[i]->CzyZabity())
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
void NiebieskaWieza::Strzelanie34()
{
	for (unsigned i = 0; i < zarzadcaStworow->stwory.size(); i++)
	{
		if (Collision::CirclePointContain(zasieg, model.getPosition(), zarzadcaStworow->stwory[i]->PobierzKolo().getPosition()))
		{
			zarzadcapociskow->Stworz(new FalistyPocisk(model.getPosition(),
				predkoscPocisku, 12.f, obrazenia, zasieg, &zarzadcaStworow->stwory));
			CzasDoWystrzalu = 0;
			break;
		}
	}
}

NiebieskaWieza::NiebieskaWieza(const sf::Vector2f& polozenie) : Wieza()
{
	typWygladu = NULL;

	poziom = 1;
	Level1();
	model.setPosition(polozenie);
}


NiebieskaWieza::NiebieskaWieza(const NiebieskaWieza& wieza) : Wieza()
{
	model.setSize(wieza.model.getSize());
	model.setFillColor(sf::Color::Blue);
	model.setOrigin(model.getSize().x / 2, model.getSize().y / 2);
	model.setPosition(wieza.model.getPosition());
	zasieg = wieza.zasieg;
	predkoscPocisku = wieza.predkoscPocisku;
	obrazenia = wieza.obrazenia;
	wielkoscPocisku = wieza.wielkoscPocisku;
	szybkoscOstrzalu = wieza.szybkoscOstrzalu;
	poziom = wieza.poziom;
	CzasDoWystrzalu = wieza.CzasDoWystrzalu;
	if (wieza.typWygladu)
	{
		typWygladu = new TypWygladu(*wieza.typWygladu);
	}
}

void NiebieskaWieza::Ruch(const float& czas)
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


void NiebieskaWieza::Ulepsz()
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
	CzasDoWystrzalu = szybkoscOstrzalu;
}


int NiebieskaWieza::PobierzKoszt(bool creatable) const
{
	switch (poziom - creatable)
	{
	case 0:	return 90;
	case 1:	return 100;
	case 2:	return 90;
	case 3:	return 60;
	default:	return 99999;
	}
};

int NiebieskaWieza::MaxPoziom() const 
{ 
	return 4; 
};

TYP_WIEZY NiebieskaWieza::PobierzTyp() const 
{ 
	return TYP_WIEZY::NIEBIESKA; 
};

std::wstring NiebieskaWieza::PobierzNazwe() const 
{ 
	return poziom > 2 ? L"Szafirowa" : L"Niebieska"; 
}

std::wstring NiebieskaWieza::PobierzOpis() const
{
	if (poziom <= 2)	
		return L"";
	else 
		return L"Wie¿a wysy³aj¹ce fale, zadaj¹ca obra¿enia sta³e i zalerzne od ¿ycia, wszystkim stworow na obszarze ra¿enia.";
}