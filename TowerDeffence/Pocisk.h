#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Collision.h"
#include "Minion.h"
#include "Matematyka.h"

class CzerwonaWieza;



class Pocisk : public sf::Drawable
{
private:
protected:
	float szybkosc;
	float obrazenia;
public:
	Pocisk(float predkosc, float Obrazenia);
	bool czyZabity;
	Pocisk();

	virtual void Ruch(float czas) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual ~Pocisk();
};

class ZwyklyPocisk : public Pocisk
{
protected:
	sf::RectangleShape obrazPocisku;
	Minion* stwor;
public:
	ZwyklyPocisk(const sf::Vector2f& Polozenie, Minion* target, float predkosc, float Obrazenia, const sf::Vector2f& rozmiar);
	virtual void Ruch(float czas);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class WyrzucanyPocisk : public Pocisk
{
protected:
	Minion* stwor;
	sf::CircleShape obrazPocisku;
public:
	WyrzucanyPocisk(const sf::Vector2f& Polozenie, Minion* target, float predkosc, float Obrazenia);
	
	void Ruch(float czas);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class FalistyPocisk : public Pocisk
{
private:
	sf::CircleShape obrazPocisku;
	float zasieg;
	float wielkosc;
	static std::vector <Minion*>* stwory;
public:
	FalistyPocisk(const sf::Vector2f& Polozenie,float predkosc,float wielkosc,float Obrazenia,float zasieg, std::vector <Minion*>*);
	void Ruch(float czas);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

//posiada wskaznik na wieze
class PociskWzmacniajacy : public ZwyklyPocisk
{
private:
	CzerwonaWieza* wieza;
	float zwiekszenieObrazen;
public:
	PociskWzmacniajacy(const sf::Vector2f& Polozenie, Minion* target, float predkosc, float Obrazenia, const sf::Vector2f& rozmiar,
						CzerwonaWieza* wieza, float zwiekszenieObrazen);
	void Ruch(float czas);
};
