#include "ProstokatnePole.h"

PrastakatnePole::PrastakatnePole(const sf::Vector2f& pozycja, const std::wstring& Napis, const sf::Color& kolorPola, const sf::Vector2f& rozmiarPola, unsigned rozmiarCzcionki) : Pole(), prastakat(rozmiarPola)
{
	prastakat.setOrigin(rozmiarPola.x / 2.f, rozmiarPola.y / 2.f);
	prastakat.setFillColor(kolorPola);
	prastakat.setPosition(pozycja);

	napis.setFillColor(sf::Color::White);
	napis.setString(Napis);
	napis.setCharacterSize(rozmiarCzcionki);
	napis.setFont(StatyczneTekstury::getFont());
	napis.setOrigin(napis.getGlobalBounds().width / 2.f, napis.getGlobalBounds().height / 2.f + napis.getCharacterSize() / 4.f);
	napis.setPosition(pozycja);
}

void PrastakatnePole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	target.draw(prastakat); target.draw(napis); 
}

bool PrastakatnePole::CzyZawieranie(const sf::Vector2f& mysz) 
{ 
	return prastakat.getGlobalBounds().contains(mysz); 
}

void PrastakatnePole::ZmienRozmiarPola(const sf::Vector2f& rozmiarPola, unsigned rozmiarCzcionki, bool czy_powiekszenie)
{
	czyPowiekszenie = czy_powiekszenie;
	prastakat.setSize(rozmiarPola);
	prastakat.setOrigin(rozmiarPola.x / 2.f, rozmiarPola.y / 2.f);
	napis.setCharacterSize(rozmiarCzcionki);
	napis.setOrigin(napis.getGlobalBounds().width / 2.f, napis.getGlobalBounds().height / 2.f + napis.getCharacterSize() / 4.f);
}