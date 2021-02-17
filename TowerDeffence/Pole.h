#pragma once

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "StatyczneTekstury.h"
#include "Matematyka.h"

namespace POLE
{
	enum Stan { NORMALNY, POWIEKSZONY };
}

class Pole : public sf::Drawable
{
protected:
	bool czyPowiekszenie;
	sf::Text napis;

public:
	Pole();
	virtual bool CzyPowiekszenie() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool CzyZawieranie(const sf::Vector2f& mysz) const = 0;
	virtual void ZmienRozmiarPola(const sf::Vector2f& nowyRozmiar, unsigned rozmiarCzcionki, bool czyPowiekszenie) = 0;
	virtual const sf::Text& getText() const;
	virtual ~Pole();
};