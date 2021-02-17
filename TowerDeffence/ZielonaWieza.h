#pragma once
#include <SFML/Graphics.hpp>
#include "Wieza.h"

class ZielonaWieza : public Wieza
{
private:
	void Level1();
	void Level2();
	void Level3();
public:
	void Ruch(const float& czas);
	void Ulepsz();
	int PobierzKoszt(bool creatable = false) const;
	int MaxPoziom() const;
	TYP_WIEZY PobierzTyp() const { return TYP_WIEZY::ZIELONA; };
	std::wstring PobierzNazwe() const;
	std::wstring PobierzOpis() const;

	ZielonaWieza(sf::Vector2f polozenie = sf::Vector2f(0, 0));

	ZielonaWieza(const ZielonaWieza& wieza);
};
