#include "TypWygladu.h"

TypWygladu::TypWygladu(int typ, const sf::Vector2f& pozycja, const float& rozmiar)
{
	float wielkosc = 3;
	switch (typ)
	{
	case 2:
		wyglad.push_back(new sf::CircleShape(rozmiar / 2 - wielkosc, 4));
		wyglad.back()->setPosition(pozycja);
		wyglad.back()->setOrigin(rozmiar / 2 - wielkosc, rozmiar / 2 - wielkosc);
		wyglad.back()->setFillColor(sf::Color::Transparent);
		wyglad.back()->setOutlineColor(sf::Color(0, 0, 0, 192));
		wyglad.back()->setOutlineThickness(wielkosc);

	default:
		break;
	}
}

TypWygladu::TypWygladu(const TypWygladu& typWygladu)
{
	size_t rozmiar = typWygladu.wyglad.size();
	wyglad.resize(rozmiar);
	for (unsigned i = 0; i < rozmiar; i++)
	{
		wyglad.at(i) = new sf::CircleShape(*typWygladu.wyglad[i]);
	}
}

void TypWygladu::zmienTyp(int& typ)
{
	sf::Color kolor;
	switch (typ)
	{
	case 3:
		for (unsigned i = 0; i < wyglad.size(); i++)
		{
			kolor = wyglad[i]->getOutlineColor();
			kolor.a -= 96;
			wyglad[i]->setOutlineColor(kolor);
		}

		wyglad[0]->setFillColor(sf::Color::Transparent);

		wyglad.push_back(new sf::CircleShape(*wyglad[0]));
		wyglad.back()->setOutlineColor(sf::Color(0, 0, 0, 192));


		wyglad.back()->setPointCount(static_cast<size_t> (wyglad[0]->getRadius() + 10));
		break;

	default:
		break;
	}
}

void TypWygladu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : wyglad)
		target.draw(*i);
}

TypWygladu::~TypWygladu()
{
	for (auto& i : wyglad)
		delete i;
}