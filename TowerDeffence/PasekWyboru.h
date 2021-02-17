#pragma once

#ifndef PASEKWYBORU_H

#define PASEKWYBORU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Wieza.h"
#include "Wave.h"
#include "StatyczneTekstury.h"
#include "Matematyka.h"
#include "WybranaBudowa.h"
#include "WybranaWieza.h"
#include "WybranyStwor.h"
#include "ESC.h"
#include "WyborWiez.h"
#include "DefinicjePaskaWyboru.h"

class PasekWyboru : public sf::Drawable
{
private:
protected:
	sf::RectangleShape tlo;
	int zycie;
	int zloto;
	sf::Text tZycie;
	sf::Text tZloto;
	float tempo;
	sf::Text tTempo;
	sf::RenderWindow* okno;
	Wave* zarzadcaFal;
	WybranaBudowa* wybranaBudowa;
	WybranaWieza* wybranaWieza;
	WybranyStwor* wybranyStwor;
	Esc* esc;
public:
	PasekWyboru();
	WyborWiez wyborWiez;
	////WybranaBudowa
	virtual bool CzyWybranaBudowa() const;
	virtual WybranaBudowa& PobierzWybranaBudowa() const;
	virtual void StworzWybranaBudowa(TYP_WIEZY i);
	virtual void UsunWybranaBudowa();

	////WybranaWieza
	WybranaWieza& PobierzWybranaWieza() const;
	virtual bool CzyWybranaWieza() const;
	virtual void StworzWybranaWieza(Wieza* wieza);
	virtual void UsunWybranaWieza();

	////WybranyStwor
	virtual bool CzyWybranyStwor() const;
	virtual void StworzWybranyStwor(Minion* Stwor);
	virtual void UsunWybranyStwor();
	virtual WybranyStwor& PobierzWybranyStwor();

	/////ESC
	virtual bool CzyEsc() const;
	virtual void StworzEsc();
	virtual void UsunEsc();
	virtual Esc& PobierzEsc() const;

	virtual void ZaaktualizujWskaznikOkna(sf::RenderWindow* wskaznik);
	virtual void ZaaktualizujWskaznikZarzadcyFal(Wave* wskaznik);

	virtual int* PobierzWskaznikZycia();
	virtual int* PobierzWskaznikZlota();
	virtual int PobierzZycie() const;
	virtual int PobierzZloto() const;

	virtual void Ruch() = 0;
	virtual float PobierzTempo() const;
	virtual void ZmienTempo(bool zmiana);
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual ~PasekWyboru();
};

class NormalnyPasekWyboru : public PasekWyboru
{
private:
	sf::Text tFala;
	int zycieMax;

public:
	NormalnyPasekWyboru();
	int PobierzZycie() const;
	int PobierzZloto() const;

	virtual void Ruch();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class SzybkiPasekWyboru : public PasekWyboru
{
private:
	sf::Text tWynik;
public:
	SzybkiPasekWyboru();
	virtual void StworzWybranaBudowa(const TYP_WIEZY& i) { wybranaBudowa = new SzybkaWybranaBudowa(i, sf::Vector2f(sf::Mouse::getPosition(*okno))); }
	virtual void StworzWybranaWieza(Wieza* wieza);
	virtual void Ruch();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void ZmienTempo(bool zmiana) {};
	~SzybkiPasekWyboru();
};

#endif // PASEKWYBORU_H