#include "OkraglePole.h"

OkraglePole::OkraglePole(const sf::Vector2f& pozycja, const std::wstring& napis, const sf::Color& kolorPola, const sf::Vector2f& rozmiarPola, unsigned rozmiar)
	: KrzyzykowePole(pozycja, napis, kolorPola, rozmiarPola, rozmiar, rozmiarKola)
{
	for (int i = 0; i < 4; i++)
	{
		kola[i].setRadius(rozmiarKola);
		kola[i].setPointCount(static_cast<size_t> (rozmiarKola / 2 + 10u));
	}
	for (int i = 0; i < 4; i++) kola[i].setOrigin(rozmiarKola, rozmiarKola);
	for (int i = 0; i < 4; i++) kola[i].setFillColor(kolorPola);

	kola[0].setPosition(pion.getGlobalBounds().left, poziom.getGlobalBounds().top);
	kola[1].setPosition(pion.getGlobalBounds().left + pion.getGlobalBounds().width, poziom.getGlobalBounds().top);
	kola[2].setPosition(pion.getGlobalBounds().left, poziom.getGlobalBounds().top + poziom.getGlobalBounds().height);
	kola[3].setPosition(pion.getGlobalBounds().left + pion.getGlobalBounds().width, poziom.getGlobalBounds().top + poziom.getGlobalBounds().height);
}

void OkraglePole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pion);
	target.draw(poziom);
	for (int i = 0; i < 4; i++)
		target.draw(kola[i]);
	target.draw(napis);
}

bool OkraglePole::CzyZawieranie(const sf::Vector2f& mysz) const
{
	if (pion.getGlobalBounds().contains(mysz) || poziom.getGlobalBounds().contains(mysz))	return true;
	for (int i = 0; i < 4; i++)
	{
		if (Collision::CirclePointContain(kola[i], mysz)) return true;
	}
	return false;
}

void OkraglePole::ZmienRozmiarPola(const sf::Vector2f& rozmiarPola, unsigned rozmiarCzcionki, bool czy_powiekszenie)
{
	czyPowiekszenie = czy_powiekszenie;

	float rozmiarKola = vector_length(rozmiarPola) / 20.f;

	napis.setCharacterSize(rozmiarCzcionki);
	napis.setOrigin(napis.getGlobalBounds().width / 2, napis.getGlobalBounds().height / 2 + napis.getCharacterSize() / 4);

	///////////
	pion.setSize(sf::Vector2f(rozmiarPola.x - rozmiarKola * 2.f, rozmiarPola.y));
	poziom.setSize(sf::Vector2f(rozmiarPola.x, rozmiarPola.y - rozmiarKola * 2.f));
	for (int i = 0; i < 4; i++) kola[i].setRadius(rozmiarKola);
	/////////
	pion.setOrigin(pion.getSize().x / 2.f, pion.getSize().y / 2.f);
	poziom.setOrigin(poziom.getSize().x / 2.f, poziom.getSize().y / 2.f);
	for (int i = 0; i < 4; i++) kola[i].setOrigin(rozmiarKola, rozmiarKola);
	//////////////
	kola[0].setPosition(pion.getGlobalBounds().left, poziom.getGlobalBounds().top);
	kola[1].setPosition(pion.getGlobalBounds().left + pion.getGlobalBounds().width, poziom.getGlobalBounds().top);
	kola[2].setPosition(pion.getGlobalBounds().left, poziom.getGlobalBounds().top + poziom.getGlobalBounds().height);
	kola[3].setPosition(pion.getGlobalBounds().left + pion.getGlobalBounds().width,
		poziom.getGlobalBounds().top + poziom.getGlobalBounds().height);
}