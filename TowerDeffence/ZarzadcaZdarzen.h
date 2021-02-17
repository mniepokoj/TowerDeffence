#pragma once

#include "PasekWyboru.h"
#include "SFML/Graphics.hpp"
#include "ZarzadcaWiez.h"
#include "ZarzadcaStworow.h"
#include "mapa.h"
#include "Matematyka.h"
#include "ZwracanyTypPoziomu.h"


class ZarzadcaZdarzen
{
private:
	sf::Vector2f mysz;
public:
	PasekWyboru* pasek;
	ZarzadcaWiez* zarzadcaWiezyczek;
	ZarzadcaStworow* zarzadcaStworow;
	Mapa* mapa;
	sf::RenderWindow* okno;
private:
	bool ZgodaNaBudowe() const;
	//funkcje obslugujace nacisniecie lewego przycisku myszki, zwrocenie brak oznacza brak czynnosci i dalsze wykonywanie zdarzenia,
	//kolejnosc wykonywania czynnosci ma znaczenie
	ZDARZENIE LeftMousePressedEsc();
	ZDARZENIE LeftMousePressedTypuWiezy(); // sprawdza czy mozliwe jest stworzenie wybranej budowy i ja tworzy
	ZDARZENIE LeftMousePressedWybranaBudowa(); // sprawdzwa mozliwosc utowrzenia nowej wiezy
	ZDARZENIE LeftMousePressedWybranaWieza(); // sprawdza mozliwosc ulepszenia wiezy, usuniecia wybranej wiezy lub jej utworzenia
	ZDARZENIE LeftMousePressedWybranyStwor(); // tworzy lub zmienia wybranego stwora
	ZDARZENIE LeftMouseButtomPressed();
	ZDARZENIE RightMouseButtomPressed();
	ZDARZENIE MouseMoved(sf::Event& event);
	ZDARZENIE MouseButtomPressed(sf::Event& event);
	ZDARZENIE MouseWheelScrolled(sf::Event& event);
	ZDARZENIE KeyReleased(sf::Event& event);
public:
	ZarzadcaZdarzen();
	ZDARZENIE Zarzadzaj(sf::Event& zdarzenie);
	~ZarzadcaZdarzen();
};

