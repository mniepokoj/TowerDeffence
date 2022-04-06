#pragma once
#include "Wieza.h"
#include "Triangle.h"

constexpr size_t lbTrojkatow = 5;


//still in testing
class PomaranczowaWieza : public Wieza 
{
	void Level1();
	void Strzelanie();

	Triangle triangle[lbTrojkatow];
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int PobierzKoszt(bool creatable = false) const;
	void Ruch(const float& czas);
	void Ulepsz();
	int MaxPoziom() const;
	TYP_WIEZY PobierzTyp() const { return TYP_WIEZY::POMARANCZOWA; };
	std::wstring PobierzNazwe() const;
	std::wstring PobierzOpis() const;
	void UstawPozycje(const sf::Vector2f& pozycja);

	PomaranczowaWieza(const PomaranczowaWieza& pomaranczowaWieza);

	PomaranczowaWieza(const sf::Vector2f& polozenie = sf::Vector2f(0, 0));
};

