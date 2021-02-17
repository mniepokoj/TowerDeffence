#pragma once
#ifndef GRA_H
#define GRA_H

#include <SFML/Graphics.hpp>
#include "ZarzadcaWszystkiego.h"
#include "Statyczne.h"
#include <iostream>


class Gra
{
private:
	sf::ContextSettings ustawienia;
	sf::Clock czas;
	ZarzadcaWszystkiego* zarzadca;
	sf::RenderWindow okno;
public:
	Gra();
	void Dzialaj();
	~Gra();
};

#endif // !GRA_H