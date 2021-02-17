#include "Pole.h"

Pole::Pole() : czyPowiekszenie(false) {}

bool Pole::CzyPowiekszenie() const
{ 
	return czyPowiekszenie; 
}

void Pole::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{ 
	target.draw(napis); 
};

const sf::Text& Pole::getText() const
{
	return napis;
}

Pole::~Pole() {};