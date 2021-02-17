#include "KoniecPoziomu.h"



KoniecPoziomu::KoniecPoziomu(bool Wynik)
{
	okno = NULL;
	zaciemnienie.setFillColor(sf::Color(0, 0, 0, 80));
	zaciemnienie.setPosition(sf::Vector2f(0, 0));
	zaciemnienie.setSize(sf::Vector2f(800, 600));

	tablica.setFillColor(sf::Color(80, 200, 120, 255));
	tablica.setPosition(225, 50);
	tablica.setSize(sf::Vector2f(350, 500));

	bilans = Wynik;

	float srodek = tablica.getPosition().x + tablica.getSize().x / 2;

	sf::Vector2f polozenie(srodek, 140);
	std::wstring napis(bilans ? L"Zwyciêstwo" : L"Pora¿ka");
	sf::Color kolorPola(bilans ? sf::Color(30, 100, 220) : sf::Color(220, 30, 30));
	sf::Vector2f rozmiarPola(280, 100);
	unsigned rozmiarCzcionki = 54;
	wynik = new KrzyzykowePole(polozenie, napis, kolorPola, rozmiarPola, rozmiarCzcionki);

	kolorPola = sf::Color(220, 50, 70);
	rozmiarCzcionki = 40;
	polozenie.y = 280.f;
	rozmiarPola = sf::Vector2f(250, 75);
	dalej = new KrzyzykowePole(polozenie, L"Dalej", kolorPola, rozmiarPola, rozmiarCzcionki);

	polozenie.y = 400;
	rozmiarPola = sf::Vector2f(250, 75);
	powtorz = new KrzyzykowePole(polozenie, L"Powtórz", kolorPola, rozmiarPola, rozmiarCzcionki);
}

ZDARZENIE KoniecPoziomu::Zarzadzaj(sf::Event& zdarzenie, bool& Wynik)
{
	sf::Vector2f mysz = sf::Vector2f(sf::Mouse::getPosition(*okno));

	if ( dalej->CzyZawieranie(mysz))
	{
		if (!dalej->CzyPowiekszenie())
		{
			dalej->ZmienRozmiarPola(sf::Vector2f(300, 80), 42, true);
		}

		if (zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Wynik = bilans;
			return ZDARZENIE::WYJDZ;
		}
	}
	else
	{
		if (dalej->CzyPowiekszenie())
		{
			dalej->ZmienRozmiarPola(sf::Vector2f(250, 75), 40, false);
		}
	}

	if (powtorz->CzyZawieranie(mysz))
	{
		if (!powtorz->CzyPowiekszenie())
		{
			powtorz->ZmienRozmiarPola(sf::Vector2f(300, 80), 42, true);
		}

		if (zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Wynik = bilans;
			return ZDARZENIE::POWTORZ;
		}
	}
	else
	{
		if (powtorz->CzyPowiekszenie())
		{
			powtorz->ZmienRozmiarPola(sf::Vector2f(250, 75), 40, false);
		}
	}
	return ZDARZENIE::NIC;

}


void KoniecPoziomu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(zaciemnienie);
	target.draw(tablica);
	target.draw(*wynik);
	target.draw(*dalej);
	target.draw(*powtorz);
}

KoniecPoziomu::~KoniecPoziomu()
{
	delete wynik;
	delete powtorz;
	delete dalej;
}