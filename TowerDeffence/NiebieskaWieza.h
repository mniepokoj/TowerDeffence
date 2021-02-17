#pragma once
#include <SFML/Graphics.hpp>
#include "Wieza.h"

class NiebieskaWieza : public Wieza
{
private:
	void Level1();
	void Level2();
	void Level3();
	void Level4();
	void Strzelanie12();
	void Strzelanie34();
public:
	int PobierzKoszt(bool creatable = false) const;
	void Ruch(const float& czas);
	void Ulepsz();
	int MaxPoziom() const;
	TYP_WIEZY PobierzTyp() const;
	std::wstring PobierzNazwe() const;
	std::wstring PobierzOpis() const;


	NiebieskaWieza(const NiebieskaWieza& niebieskaWieza);

	NiebieskaWieza(const sf::Vector2f& polozenie = sf::Vector2f(0, 0));
};