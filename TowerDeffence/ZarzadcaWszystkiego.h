#pragma once
#ifndef ZARZADCAWSZYSTKIEGO_HPP
#define ZARZADCAWSZYSTKIEGO_HPP

#include "ZarzadcaStartu.h"
#include "ZarzadcaPlanszy.h"
#include "ZarzadcaPoziomu.h"
#include "Statyczne.h"
#include "Matematyka.h"
#include <iostream>

enum class StanGry { start, plansza, poziom };

class ZarzadcaWszystkiego
{
private:
	void UsunPoprzedniStanGry();

public:
	sf::RenderWindow* okno;

	ZarzadcaPoziomu* zarzadcaPoziomu;
	ZarzadcaStartu* zarzadcaStartu;
	ZarzadcaPlanszy* zarzadcaPlanszy;
	StanGry aktualnyStan;
	bool wynik;

	ZarzadcaWszystkiego(sf::RenderWindow* window);
	static void Aktywacja();


	void UstawWskaznikOkna(sf::RenderWindow& window);
	void Ruch(const float& czas);
	void Rysoj();
	void Zarzadz(sf::Event& zdarzenie);
	void ZmienStan(StanGry stan);
	void ZmienStan(const ZwracanyTypPoziomu& typ);
	~ZarzadcaWszystkiego();	
};

#endif




