#include "ESC.h"



Esc::Esc()
{
	zaciemnienie.setFillColor(sf::Color(0, 0, 0, 80));
	zaciemnienie.setPosition(sf::Vector2f(0, 0));
	zaciemnienie.setSize(sf::Vector2f(800, 600));

	tablica.setFillColor(sf::Color(80, 200, 120, 255));
	tablica.setPosition(225, 50);
	tablica.setSize(sf::Vector2f(350, 500));

	obwod.setFillColor(sf::Color::Black);
	obwod.setPosition(222, 47);
	obwod.setSize(sf::Vector2f(356, 506));

	float srodek = tablica.getPosition().x + tablica.getSize().x / 2;

	sf::Vector2f polozenie(srodek, 130);
	sf::Color kolorPola( 40, 110, 160 );
	sf::Vector2f rozmiarPola(300, 90);
	menu = new OkraglePole(polozenie, L"Menu", kolorPola, rozmiarPola, 65);

	kolorPola = sf::Color(220, 50, 70);
	rozmiarPola = sf::Vector2f(250, 70);

	wznow = new KrzyzykowePole(sf::Vector2f(srodek, 250), L"Wznów", kolorPola, rozmiarPola, 40u );

	powtorz = new KrzyzykowePole(sf::Vector2f(srodek, 350), L"Powtórz", kolorPola, rozmiarPola, 40u);

	wyjdz = new KrzyzykowePole(sf::Vector2f(srodek, 450), L"Wyjdz", kolorPola, rozmiarPola, 40u);

}

ZDARZENIE Esc::Zarzadzaj(const sf::Event& zdarzenie, const sf::Vector2f& mysz) const
{
	SprawdzAnimacje(mysz);
	if (zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (wznow->CzyPowiekszenie())
		{
			return ZDARZENIE::WZNOW;
		}
		else if (powtorz->CzyPowiekszenie())
		{
			return ZDARZENIE::POWTORZ;
		}
		else if (wyjdz->CzyPowiekszenie())
		{
			return ZDARZENIE::WYJDZ;
		}
	}
	return ZDARZENIE::NIC;
}

ZDARZENIE Esc::Zarzadzaj() const
{
	if (wznow->CzyPowiekszenie())
	{
		return ZDARZENIE::WZNOW;
	}
	else if (powtorz->CzyPowiekszenie())
	{
		return ZDARZENIE::POWTORZ;
	}
	else if (wyjdz->CzyPowiekszenie())
	{
		return ZDARZENIE::WYJDZ;
	}
	return ZDARZENIE::NIC;
}

void Esc::SprawdzAnimacje(const sf::Vector2f& mysz) const
{
	if (wznow->CzyZawieranie(mysz))
	{
		if (wznow->CzyPowiekszenie() == false)
		{
			wznow->ZmienRozmiarPola(sf::Vector2f(300, 80), 42, true);
		}
		return;
	}
	else if (wznow->CzyPowiekszenie() == true)
	{
		wznow->ZmienRozmiarPola(sf::Vector2f(250, 75), 40, false);
	}

	if (powtorz->CzyZawieranie(mysz))
	{
		if (powtorz->CzyPowiekszenie() == false)
		{
			powtorz->ZmienRozmiarPola(sf::Vector2f(300, 80), 42, true);
		}
		return;
	}
	else if (powtorz->CzyPowiekszenie() == true)
	{
		powtorz->ZmienRozmiarPola(sf::Vector2f(250, 75), 40, false);
	}

	if (wyjdz->CzyZawieranie(mysz))
	{
		if (wyjdz->CzyPowiekszenie() == false)
		{
			wyjdz->ZmienRozmiarPola(sf::Vector2f(300, 80), 42, true);
		}
		return;
	}
	else if (wyjdz->CzyPowiekszenie() == true)
	{
		wyjdz->ZmienRozmiarPola(sf::Vector2f(250, 75), 40, false);
	}
	return;
}

void Esc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int n = wznow->getText().getCharacterSize();
	target.draw(zaciemnienie);
	target.draw(obwod);
	target.draw(tablica);
	target.draw(*menu);
	target.draw(*wznow);
	target.draw(*powtorz);
	target.draw(*wyjdz);
}

Esc::~Esc()
{
	delete menu;
	delete wznow;
	delete powtorz;
	delete wyjdz;
}
