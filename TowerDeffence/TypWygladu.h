#pragma once
#include <SFML/Graphics.hpp>

class TypWygladu : public sf::Drawable
{
public:
	TypWygladu(int typ, const sf::Vector2f& pozycja, const float& rozmiar);
	TypWygladu(const TypWygladu& typWygladu);
	std::vector <sf::CircleShape*> wyglad;

	void zmienTyp(int& typ);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~TypWygladu();
};
