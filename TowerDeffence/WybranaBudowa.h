#pragma once
#include <SFML/Graphics.hpp>
#include "StatyczneTekstury.h"
#include "ZarzadcaWiez.h"
#include "DefinicjePaskaWyboru.h"
#include "IkonaWiezy.h"


class WybranaBudowa : public sf::Drawable
{
protected:
	void UstawTyp(TYP_WIEZY typ, const sf::Vector2f& pozycja);
	sf::Text obrazenia;
	sf::Text szybkosc;
	sf::Text zasieg;
	sf::Text nazwa[2];
	sf::Text koszt;
	sf::Text opis;
	std::vector <sf::Text*> opisWiezy;
	bool czyMozliwaBudowa;
	sf::Color M_kolor;
public:
	WybranaBudowa(TYP_WIEZY typ, const sf::Vector2f& pozycja);

	IkonaWiezy* podglad;

	virtual TYP_WIEZY PobierzTyp() const { return podglad->PobierzTyp(); }
	virtual bool CzyZgodaNaBudowe() const { return czyMozliwaBudowa; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void ZmienTyp(TYP_WIEZY typ);
	virtual void Zarzadzaj(bool CzyMozliwaBudowa);

	~WybranaBudowa();
};


class SzybkaWybranaBudowa : public WybranaBudowa
{
public:
	SzybkaWybranaBudowa(TYP_WIEZY typ, const sf::Vector2f& pozycja) : WybranaBudowa(typ, pozycja) {};
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};