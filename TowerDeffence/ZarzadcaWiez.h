#pragma once
#include "NiebieskaWieza.h"
#include "ZoltaWieza.h"
#include "ZielonaWieza.h"
#include "CzerwonaWieza.h"
#include "PomaranczowaWieza.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ZarzadcaWiez : public sf::Drawable
{
public:
	ZarzadcaWiez();
	std::vector <Wieza*> wiezyczki;
	void Ruch(const float& czas);
	void DodajWieze(Wieza* wieza);
	void DodajWieze(TYP_WIEZY typ, const sf::Vector2f& pozycja);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~ZarzadcaWiez();

	static Wieza* StworzWieze(TYP_WIEZY typ, const sf::Vector2f& pozycja = sf::Vector2f(0, 0));
	static Wieza* StworzWieze(Wieza* wieza);
};

