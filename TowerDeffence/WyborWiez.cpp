#include "WyborWiez.h"

const sf::Vector2f rozmiarIkon = sf::Vector2f(50, 50);

WyborWiez::WyborWiez()
{
	size_t i = 0;

	ramka[i].setFillColor(sf::Color::White);
	ramka[i].setSize(sf::Vector2f(koniecMarginesu - liniaMarginesu, 3));
	ramka[i].setPosition(liniaMarginesu, 0);
	ramka[++i].setFillColor(sf::Color::White);
	ramka[i].setSize(sf::Vector2f(koniecMarginesu - liniaMarginesu, 3));
	ramka[i].setPosition(liniaMarginesu, 59);
	ramka[++i].setFillColor(sf::Color::White);
	ramka[i].setSize(sf::Vector2f(koniecMarginesu - liniaMarginesu, 3));
	ramka[i].setPosition(liniaMarginesu, 118);
	ramka[++i].setFillColor(sf::Color::White);
	ramka[i].setSize(sf::Vector2f(koniecMarginesu - liniaMarginesu, 3));
	ramka[i].setPosition(liniaMarginesu, 177);

	i = 0;
	ikonaWiezy[i].UstawTypWiezy(TYP_WIEZY::NIEBIESKA);
	ikonaWiezy[i].UstawRozmiar(rozmiarIkon);
	ikonaWiezy[i].UstawPozycje(srodekMarginesu, 31);
	ikonaWiezy[++i].UstawTypWiezy(TYP_WIEZY::ZOLTA);
	ikonaWiezy[i].UstawRozmiar(rozmiarIkon);
	ikonaWiezy[i].UstawPozycje(srodekMarginesu, 90);
	ikonaWiezy[++i].UstawTypWiezy(TYP_WIEZY::ZIELONA);
	ikonaWiezy[i].UstawRozmiar(rozmiarIkon);
	ikonaWiezy[i].UstawPozycje(srodekMarginesu, 149);
	ikonaWiezy[++i].UstawTypWiezy(TYP_WIEZY::CZERWONA);
	ikonaWiezy[i].UstawRozmiar(rozmiarIkon);
	ikonaWiezy[i].UstawPozycje(srodekMarginesu, 210);

	/*
	ikonaWiezy[++i].UstawTypWiezy(TYP_WIEZY::POMARANCZOWA);
	ikonaWiezy[i].UstawRozmiar(rozmiarIkon);
	ikonaWiezy[i].UstawPozycje(srodekMarginesu, 271);
	*/
}

void WyborWiez::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 4; i++)
	{
		target.draw(ramka[i], states);
	}
	for (size_t i = 0; i < lbWiez; i++) target.draw(ikonaWiezy[i], states);
}

TYP_WIEZY WyborWiez::SprawdzKolizje(const sf::Vector2f& punkt) const
{
	for (size_t i = 0; i < lbWiez; i++)
	{
		if (ikonaWiezy[i].getGlobalBounds().contains(punkt)) 
			return ikonaWiezy[i].PobierzTyp();
	}
	return TYP_WIEZY::ZADEN;
}