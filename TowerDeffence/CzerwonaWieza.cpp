#include "CzerwonaWieza.h"

void CzerwonaWieza::Level1()
{
	model.setSize(sf::Vector2f(70, 70));
	model.setFillColor(sf::Color(240, 20, 20));
	model.setOrigin(70 / 2.f, 70 / 2.f);
	zasieg = 100.f;
	obrazenia = 4.f;
	szybkoscOstrzalu = 2500.f;
	wielkoscPocisku = sf::Vector2f(6, 4);
	predkoscPocisku = 200.08f;
	CzasDoWystrzalu = szybkoscOstrzalu;
	zwiekszenieObrazen = 0.5f;
	wielkoscWzmocnienia = 0;
	aktualizacjaObrazen = false;
}
void CzerwonaWieza::Level2()
{
	zasieg = 100.f;
	szybkoscOstrzalu = 2100.f;
	predkoscPocisku = 500.1f;
	typWygladu = new TypWygladu(poziom, model.getPosition(), model.getSize().x);
	aktualizacjaObrazen = false;
}
void CzerwonaWieza::Level3()
{
	zasieg = 110.f;
	predkoscPocisku = 1800.1f;
	typWygladu->zmienTyp(poziom);
	aktualizacjaObrazen = false;
}

void CzerwonaWieza::Strzelanie()
{
	for (unsigned i = 0; i < zarzadcaStworow->stwory.size(); i++)
	{
		if (!zarzadcaStworow->stwory[i]->CzyZabity())
		{
			if (CzasDoWystrzalu >= szybkoscOstrzalu)
			{
				if (Collision::CircleCollision(zasieg, model.getPosition(), zarzadcaStworow->stwory[i]->PobierzKolo().getRadius(), zarzadcaStworow->stwory[i]->PobierzKolo().getPosition()))
				{
					zarzadcapociskow->Stworz(new PociskWzmacniajacy(model.getPosition(), zarzadcaStworow->stwory[i], predkoscPocisku, obrazenia + wielkoscWzmocnienia, wielkoscPocisku, this, zwiekszenieObrazen));
					CzasDoWystrzalu = 0;
					break;
				}
			}
		}
	}
}

CzerwonaWieza::CzerwonaWieza() : Wieza()
{
	typWygladu = NULL;
	CzasDoWystrzalu = 0;
	poziom = 1;
	Level1();
}
CzerwonaWieza::CzerwonaWieza(const sf::Vector2f& polozenie) : Wieza()
{
	typWygladu = NULL;
	CzasDoWystrzalu = 0;
	poziom = 1;
	Level1();
	model.setPosition(polozenie);
}
CzerwonaWieza::CzerwonaWieza(const CzerwonaWieza & wieza) 
	: Wieza(wieza.wielkoscPocisku, model)
{
	zasieg = wieza.zasieg;
	predkoscPocisku = wieza.predkoscPocisku;
	obrazenia = wieza.obrazenia;
	szybkoscOstrzalu = wieza.szybkoscOstrzalu;
	poziom = wieza.poziom;
	CzasDoWystrzalu = wieza.CzasDoWystrzalu;
	wielkoscWzmocnienia = wieza.wielkoscWzmocnienia;
	zwiekszenieObrazen = 0;
	aktualizacjaObrazen = 0;
	if (wieza.typWygladu)
	{
		typWygladu = new TypWygladu(*wieza.typWygladu);
	}
}
void CzerwonaWieza::Ruch(const float& czas)
{
	CzasDoWystrzalu += czas * 1000.f;
	Strzelanie();
}
void CzerwonaWieza::Ulepsz()
{
	switch (++poziom)
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
int CzerwonaWieza::PobierzKoszt(bool creatable) const
{
	switch (poziom - creatable)
	{
	case 0: return 120;
	case 1:	return 70;
	case 2:	return 70;
	default:
		return 99999;
		break;
	}
}
int CzerwonaWieza::MaxPoziom() const
{
	return 3;
}
TYP_WIEZY CzerwonaWieza::PobierzTyp() const
{
	return TYP_WIEZY::CZERWONA;
}
std::wstring CzerwonaWieza::PobierzNazwe() const
{
	return L"Czerwona";
}
std::wstring CzerwonaWieza::PobierzOpis() const
{
	return L"";
}

CzerwonaWieza::CzerwonaWieza::~CzerwonaWieza()
{
}

void CzerwonaWieza::ZwiekszObrazenia(float oIle)
{
	aktualizacjaObrazen = true;
	wielkoscWzmocnienia += oIle;
}

float CzerwonaWieza::PobierzObrazenia()
{
	return obrazenia + wielkoscWzmocnienia;
}
