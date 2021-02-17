#pragma once
#include <SFML/Graphics.hpp>
#include "StatyczneTekstury.h"
#include "Matematyka.h"
#include "ZarzadcaWiez.h"
#include "DefinicjePaskaWyboru.h"


class WybranaWieza : public sf::Drawable
{
private:
	bool czyPodglad;
	bool czyCzerwony;
	int& zloto;

	bool czyPoziom;
	bool czyZloto;
	bool czyDotyka;
	virtual void SprawdzCzerwony();
	virtual void SprawdzPodglad();
public:
	WybranaWieza(Wieza* wiezaa, int& zloto);
	sf::CircleShape kolo;
	Wieza* wieza;

	sf::Text nazwa[2];
	sf::Text ulepsz;
	sf::Text koszt;
	sf::Text poziom;

	sf::Text obrazenia;
	sf::Text szybkosc;
	sf::Text zasieg;

	sf::Text opis;
	std::vector <sf::Text*> opisWiezy;

	virtual void SprawdzPoziom();
	virtual void SprawdzZloto();
	virtual void SprawdzDotyk(const sf::Vector2f& mysz);
	virtual bool CzyMoznaUsunac(const sf::Vector2f& mysz) const;
	virtual void Ruch();
	virtual void Ulepsz();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void RysojZasieg(sf::RenderTarget& target) const; // dla polepszenia grafiki
	virtual ~WybranaWieza();
};


class SzybkaWybranaWieza : public WybranaWieza
{
public:
	SzybkaWybranaWieza(Wieza* wieza, int& zloto);
	int Zarzadzaj() { return 0; };
	void PodgladUlepszenia(const sf::Vector2f& mysz) {};
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};