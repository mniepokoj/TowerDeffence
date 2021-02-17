#pragma once
#include <SFML/Graphics.hpp>
#include "ZarzadcaWiez.h"
#include "DefinicjePaskaWyboru.h"
#include "IkonaWiezy.h"


struct WyborWiez : public sf::Drawable
{
private:
	sf::RectangleShape ramka[6];
public:
	WyborWiez();
	IkonaWiezy ikonaWiezy[lbWiez];

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	TYP_WIEZY SprawdzKolizje(const sf::Vector2f& punkt) const;
};
