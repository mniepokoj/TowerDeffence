#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class StatyczneTekstury
{
private:
	StatyczneTekstury();
	static sf::Font arial;
public:
	static const sf::Font& getFont();
	static sf::Texture kartkaWKratke;
	static void Aktywacja();
	~StatyczneTekstury();
};


namespace funkcje
{
	std::wstring Zaokraglij(float liczba);
	std::wstring ZaokraglijZPrzecinkiem(float liczba);
	std::vector <sf::Text*> NapisNaTekst(const std::wstring&, int);
}