#include "KrzyzykowePole.h"

KrzyzykowePole::KrzyzykowePole(const sf::Vector2f& pozycja, const std::wstring& Napis, const sf::Color& kolorPola, const sf::Vector2f& rozmiarPola, unsigned rozmiarCzionki) : Pole()
{
	float rozmiarKola = sqrt(pow(rozmiarPola.x, 2) + pow(rozmiarPola.y, 2)) / 20.f;

	///////////
	pion.setSize(sf::Vector2f(rozmiarPola.x - rozmiarKola * 2.f, rozmiarPola.y));
	poziom.setSize(sf::Vector2f(rozmiarPola.x, rozmiarPola.y - rozmiarKola * 2.0f));
	/////////
	pion.setOrigin(pion.getSize().x / 2.f, pion.getSize().y / 2.f);
	poziom.setOrigin(poziom.getSize().x / 2.f, poziom.getSize().y / 2.f);
	//////////////
	pion.setPosition(pozycja);
	poziom.setPosition(pozycja);
	///////////////
	pion.setFillColor(kolorPola);
	poziom.setFillColor(kolorPola);
	/////////////////////

	napis.setFillColor(sf::Color::White);
	napis.setString(Napis);
	napis.setCharacterSize(rozmiarCzionki);
	napis.setFont(StatyczneTekstury::getFont());
	napis.setOrigin(napis.getGlobalBounds().width / 2.f, napis.getGlobalBounds().height / 2.f + napis.getCharacterSize() / 4.f);
	napis.setPosition(pozycja);

	czyPowiekszenie = false;
}

///do dziedziczenia
KrzyzykowePole::KrzyzykowePole(const sf::Vector2f& pozycja, const std::wstring& Napis, const sf::Color& kolorPola, const sf::Vector2f& rozmiarPola, unsigned rozmiarCzionki, float& rozmiarKola) : Pole()
{
	rozmiarKola = sqrt(pow(rozmiarPola.x, 2) + pow(rozmiarPola.y, 2)) / 20.f;
	///////////
	pion.setSize(sf::Vector2f(rozmiarPola.x - rozmiarKola * 2.f, rozmiarPola.y));
	poziom.setSize(sf::Vector2f(rozmiarPola.x, rozmiarPola.y - rozmiarKola * 2.f));
	/////////
	pion.setOrigin(pion.getSize().x / 2.f, pion.getSize().y / 2.f);
	poziom.setOrigin(poziom.getSize().x / 2.f, poziom.getSize().y / 2.f);
	//////////////
	pion.setPosition(pozycja);
	poziom.setPosition(pozycja);
	///////////////
	pion.setFillColor(kolorPola);
	poziom.setFillColor(kolorPola);
	/////////////////////
	napis.setFillColor(sf::Color::White);
	napis.setString(Napis);
	napis.setCharacterSize(rozmiarCzionki);
	napis.setFont(StatyczneTekstury::getFont());
	napis.setOrigin(napis.getGlobalBounds().width / 2.f, napis.getGlobalBounds().height / 2.f + napis.getCharacterSize() / 4.f);
	napis.setPosition(pozycja);
	czyPowiekszenie = false;
}

void KrzyzykowePole::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{ 
	target.draw(pion); 
	target.draw(poziom); 
	target.draw(napis); 
}

bool KrzyzykowePole::CzyZawieranie(const sf::Vector2f& mysz) const 
{ 
	return (pion.getGlobalBounds().contains(mysz) || poziom.getGlobalBounds().contains(mysz)); 
}

void KrzyzykowePole::ZmienRozmiarPola(const sf::Vector2f& rozmiarPola, unsigned rozmiarCzcionki, bool CzyPowiekszenie)
{
	czyPowiekszenie = CzyPowiekszenie;
	float rozmiarKola = sqrt(pow(rozmiarPola.x, 2) + pow(rozmiarPola.y, 2)) / 20.f;

	napis.setCharacterSize(rozmiarCzcionki);
	napis.setOrigin(napis.getGlobalBounds().width / 2.f, napis.getGlobalBounds().height / 2.f + napis.getCharacterSize() / 4.f);
	///////////
	pion.setSize(sf::Vector2f(rozmiarPola.x - rozmiarKola * 2.f, rozmiarPola.y));
	poziom.setSize(sf::Vector2f(rozmiarPola.x, rozmiarPola.y - rozmiarKola * 2.0f));
	/////////
	pion.setOrigin(pion.getSize().x / 2.f, pion.getSize().y / 2.f);
	poziom.setOrigin(poziom.getSize().x / 2.f, poziom.getSize().y / 2.f);
	//////////////
}