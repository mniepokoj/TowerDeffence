#include "RodzajPoziomu.h"

RodzajPoziomu::RodzajPoziomu(float x, float y, int Poziom)
{
	poziom = Poziom;
	tablica.setFillColor(sf::Color(80, 200, 120, 255));
	tablica.setPosition(x, y);
	tablica.setSize(sf::Vector2f(200, 150));
	tablica.setOrigin(tablica.getSize().x / 2, 0);

	sf::Vector2f polozenie(x, y + 40);
	std::wstring napis(L"Normalny");
	sf::Color kolorPola(220, 40, 40);
	sf::Vector2f rozmiarPola(150, 50);
	unsigned rozmiarCzcionki = 30;
	normalny = new OkraglePole(polozenie, napis, kolorPola, rozmiarPola, rozmiarCzcionki);

	polozenie = sf::Vector2f(x, y + 105);
	napis = std::wstring(L"Szybki");
	szybki = new OkraglePole(polozenie, napis, kolorPola, rozmiarPola, rozmiarCzcionki);
}

TYP_POZIOMU RodzajPoziomu::Zarzadzaj(sf::Event& zdarzenie, sf::Vector2f& mysz)
{
	bool klikniecie(zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left));
	if (normalny->CzyZawieranie(mysz))
	{
		if (klikniecie)
		{
			return TYP_POZIOMU::NORMALNY;
		}
		if (!normalny->CzyPowiekszenie())
		{
			normalny->ZmienRozmiarPola(sf::Vector2f(170, 55), 34, true);
		}
	}
	else
	{
		if (normalny->CzyPowiekszenie())
		{
			normalny->ZmienRozmiarPola(sf::Vector2f(150, 50), 30, false);
		}
	}

	if (szybki->CzyZawieranie(mysz))
	{
		if (klikniecie)
		{
			return TYP_POZIOMU::SZYBKI;
		}
		if (!szybki->CzyPowiekszenie())
		{
			szybki->ZmienRozmiarPola(sf::Vector2f(170, 55), 34, true);
		}
	}
	else
	{
		if (szybki->CzyPowiekszenie())
		{
			szybki->ZmienRozmiarPola(sf::Vector2f(150, 50), 30, false);
		}
	}

	return TYP_POZIOMU::NIC;
}

void RodzajPoziomu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tablica);
	target.draw(*normalny);
	target.draw(*szybki);
}

RodzajPoziomu::~RodzajPoziomu()
{
	delete normalny;
	delete szybki;
}