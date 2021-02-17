#pragma once
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "ZarzadcaStworow.h"
#include "Collision.h"
#include "ZarzadcaPociskow.h"
#include "Pocisk.h"
#include "TypWygladu.h"


constexpr unsigned lbWiez = 5;

enum class TYP_WIEZY { NIEBIESKA = 0, ZOLTA = 1, ZIELONA = 2, CZERWONA = 3, POMARANCZOWA = 4, ZADEN = -1 };

class Wieza : public sf::Drawable
{
protected:
	Wieza();
	Wieza(const sf::Vector2f& wielkoscPocisku, const sf::RectangleShape& model);
	float CzasDoWystrzalu;
	float predkoscPocisku;
	float obrazenia;
	sf::Vector2f wielkoscPocisku;
	float zasieg;
	float szybkoscOstrzalu;
	int poziom;
	sf::RectangleShape model;
	TypWygladu* typWygladu;
public:
	static ZarzadcaStworow* zarzadcaStworow;
	static ZarzadcaPociskow* zarzadcapociskow;

public:
	virtual void Ruch(const float& czas) = 0;
	virtual void Ulepsz() = 0;
	virtual int PobierzKoszt(bool creatable = false) const = 0;
	virtual int PobierzPoziom() const { return poziom; }
	virtual int MaxPoziom() const = 0;
	virtual TYP_WIEZY PobierzTyp() const = 0;
	virtual std::wstring PobierzNazwe() const = 0;
	virtual sf::Color PobierzKolor() const;
	virtual const sf::Vector2f& PobierzRozmiar() const;
	virtual std::wstring PobierzOpis() const;
	virtual float PobierzObrazenia() const;
	virtual float PobierzZasieg() const;
	virtual float PobierzSzybkoscOstrzalu() const;
	virtual const sf::RectangleShape& PobierzModel() const;
	virtual const TypWygladu* PobierzTypWygladu() const;
	virtual void UstawRozmiar(float x, float y);
	virtual void UstawPozycje(float x, float y);
	virtual void UstawKolor(const sf::Color& kolor);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual ~Wieza();
};