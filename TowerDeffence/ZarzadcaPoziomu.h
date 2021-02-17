#pragma once

#include <SFML/Graphics.hpp>
#include "ZarzadcaMapy.h"
#include "ZarzadcaStworow.h"
#include "ZarzadcaWiez.h"
#include "ZarzadcaPociskow.h"
#include "ZarzadcaZdarzen.h"
#include "PasekWyboru.h"
#include "Wave.h"
#include "KoniecPoziomu.h"
#include "ZarzadcaDzwiekow.h"
#include "ZwracanyTypPoziomu.h"


class ZarzadcaPoziomu : public sf::Drawable
{
protected:
	sf::RenderWindow* okno;
	ZarzadcaMapy* mapa;
	PasekWyboru* pasek;
	Wave* zarzadcaFal;
	ZarzadcaStworow* zarzadcaStworow;
	ZarzadcaWiez* zarzadcaWiezyczek;
	ZarzadcaPociskow* zarzadcapociskow;
	ZarzadcaZdarzen* zarzadcazdarzen;
	KoniecPoziomu* koniecPoziomu;
	ZarzadcaDzwiekow* zarzadcadzwieku;

	ZwracanyTypPoziomu aktualnyPoziom;
	sf::Sprite kartka;
public:


	ZarzadcaPoziomu();
	ZarzadcaPoziomu(sf::RenderWindow* window, const ZwracanyTypPoziomu& numerPlanszy);

	virtual ZwracanyTypPoziomu PobierzAktualnyPoziom() const { return aktualnyPoziom; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual ZDARZENIE Zarzadzaj(sf::Event& zdarzenie, bool& Wynik);
	virtual void Ruch(float czas);
	~ZarzadcaPoziomu();
};




class NormalnyZarzadcaPoziomu : public ZarzadcaPoziomu
{
public:
	NormalnyZarzadcaPoziomu(sf::RenderWindow* window, const ZwracanyTypPoziomu& numerPlanszy);
	ZDARZENIE Zarzadzaj(sf::Event& zdarzenie, bool& Wynik);
	void Ruch(float czas);
};






class SzybkiZarzadcaPoziomu : public ZarzadcaPoziomu
{
public:
	SzybkiZarzadcaPoziomu(sf::RenderWindow* window, const ZwracanyTypPoziomu& numerPlanszy);
	ZDARZENIE Zarzadzaj(sf::Event& zdarzenie, bool& Wynik);
	void Ruch(float czas);
};