#pragma once
#include <SFML/Graphics.hpp>
#include "Wieza.h"

class ZoltaWieza : public Wieza
{
private:
	void Level1();
	void Level2();
	void Level3();
	void Level4();
	void Strzelanie12();
	void Strzelanie34();
	int liczbaStrzalow;
public:

	void Ruch(const float& czas);
	void Ulepsz();
	int PobierzKoszt(bool creatable = false) const;
	int MaxPoziom() const;
	TYP_WIEZY PobierzTyp() const { return TYP_WIEZY::ZOLTA; };
	std::wstring PobierzNazwe() const;
	std::wstring PobierzOpis() const;

	ZoltaWieza(const sf::Vector2f& polozenie = sf::Vector2f(0, 0));
	ZoltaWieza(const ZoltaWieza& wieza);
};