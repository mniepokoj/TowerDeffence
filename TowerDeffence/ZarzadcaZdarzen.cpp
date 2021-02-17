#include "ZarzadcaZdarzen.h"


ZarzadcaZdarzen::ZarzadcaZdarzen() :
	mysz(0.f, 0.f),
	pasek(NULL),
	zarzadcaWiezyczek(NULL),
	zarzadcaStworow(NULL),
	mapa(NULL),
	okno(NULL) {}

bool ZarzadcaZdarzen::ZgodaNaBudowe() const
{
	sf::FloatRect rama = pasek->PobierzWybranaBudowa().podglad->getGlobalBounds();
	//rama.left--; rama.width+=2;
	//rama.top--; rama.height+=2;

	if (rama.left < 0) return false;

	if (rama.top < 0) return false;

	if (rama.left + rama.width > margines - 6)	return false;
	
	if (rama.top + rama.height > 800) return false;

	for (auto& i : mapa->linie)
	{
		if (rama.intersects(i.getGlobalBounds()))
		{
			return false;
		}
	}
	for (auto& i : zarzadcaWiezyczek->wiezyczki)
	{
		if (rama.intersects(i->PobierzModel().getGlobalBounds()))
		{
			return false;
		}
	}

	if (rama.left + rama.width >= margines)
	{
		return false;
	}
	return true;
}

ZDARZENIE ZarzadcaZdarzen::LeftMousePressedEsc()
{
	if (pasek->CzyEsc())
	{
		ZDARZENIE zwracanaWartosc = pasek->PobierzEsc().Zarzadzaj();
		if (zwracanaWartosc == ZDARZENIE::WZNOW)
		{
			pasek->UsunEsc();
			return ZDARZENIE::NIC;
		}
		else
		{
			return zwracanaWartosc;
		}
	}
	else
	{
		return ZDARZENIE::BRAK;
	}
}

ZDARZENIE ZarzadcaZdarzen::LeftMousePressedTypuWiezy()
{
	TYP_WIEZY typWiezy = pasek->wyborWiez.SprawdzKolizje(mysz);
	if (typWiezy != TYP_WIEZY::ZADEN)
	{
		if (pasek->CzyWybranaWieza())
		{
			pasek->UsunWybranaWieza();
		}
		else if (pasek->CzyWybranyStwor())
		{
			pasek->UsunWybranyStwor();
		}

		if (pasek->CzyWybranaBudowa())
		{
			pasek->PobierzWybranaBudowa().ZmienTyp(typWiezy);
		}
		else
		{
			pasek->StworzWybranaBudowa(typWiezy);
		}
		return ZDARZENIE::NIC;
	}
	else
	{
		return ZDARZENIE::BRAK;
	}
}

ZDARZENIE ZarzadcaZdarzen::LeftMousePressedWybranaBudowa()
{
	if (pasek->CzyWybranaBudowa())	// tworzenie wie¿
	{
		if (pasek->PobierzWybranaBudowa().CzyZgodaNaBudowe())
		{
			if (pasek->PobierzZloto() >= pasek->PobierzWybranaBudowa().podglad->PobierzKoszt(true))
			{
				*(pasek->PobierzWskaznikZlota()) -= pasek->PobierzWybranaBudowa().podglad->PobierzKoszt(true);
				pasek->PobierzWybranaBudowa().Zarzadzaj(ZgodaNaBudowe());
				zarzadcaWiezyczek->DodajWieze(pasek->PobierzWybranaBudowa().PobierzTyp(), mysz);
			}
		}
		return ZDARZENIE::NIC;//niepewne
	}
	else
	{
		return ZDARZENIE::BRAK;
	}
}

ZDARZENIE ZarzadcaZdarzen::LeftMousePressedWybranaWieza()
{
	//zalorzenie ze nie istnieje wybrana budowa w czasie wywolywania funkcji

	if (pasek->CzyWybranaWieza()) // ulepszenie lub usuniêcie wybranej wie¿y
	{
		if (pasek->PobierzWybranaWieza().ulepsz.getGlobalBounds().contains(mysz))
		{
			if (pasek->PobierzWybranaWieza().wieza->MaxPoziom() > pasek->PobierzWybranaWieza().wieza->PobierzPoziom())
			{
				if (pasek->PobierzZloto() >= pasek->PobierzWybranaWieza().wieza->PobierzKoszt())
				{
					pasek->PobierzWybranaWieza().Ulepsz();
				}
			}
			return ZDARZENIE::NIC;
		}
		else
		{
			if (pasek->PobierzWybranaWieza().CzyMoznaUsunac(mysz))
			{
				pasek->UsunWybranaWieza();
				for (auto& i : zarzadcaWiezyczek->wiezyczki)
				{
					if (i->PobierzModel().getGlobalBounds().contains(mysz))
					{
						if (pasek->CzyWybranyStwor()) pasek->UsunWybranyStwor();
						pasek->StworzWybranaWieza(i);
						return ZDARZENIE::NIC;
					}
				}
			}
			return ZDARZENIE::BRAK;
		}
	}
	else // Stworzenie Wybranej Wie¿y
	{
		for (auto& i : zarzadcaWiezyczek->wiezyczki)
		{
			if (i->PobierzModel().getGlobalBounds().contains(mysz))
			{
				if (pasek->CzyWybranyStwor()) pasek->UsunWybranyStwor();
				pasek->StworzWybranaWieza(i);
				return ZDARZENIE::NIC;
			}
		}
		return ZDARZENIE::BRAK;
	}
}

ZDARZENIE ZarzadcaZdarzen::LeftMousePressedWybranyStwor()
{
	//zalorzenie ze nie istnieje wybrana budowa i wybrana Wieza

	for (auto& i : zarzadcaStworow->stwory) // tworzenie WybranegoStwora
	{
		if (i->PobierzKolo().getGlobalBounds().contains(mysz))
		{
			if (pasek->CzyWybranyStwor())
			{
				pasek->PobierzWybranyStwor().ZmienStwora(i);
			}
			else
			{
				pasek->StworzWybranyStwor(i);
			}
			return ZDARZENIE::NIC;
		}
	}
	return ZDARZENIE::BRAK;
}

ZDARZENIE ZarzadcaZdarzen::LeftMouseButtomPressed()
{
	ZDARZENIE zwracanaWartosc = LeftMousePressedEsc();//Esc
	if (zwracanaWartosc != ZDARZENIE::BRAK) return zwracanaWartosc;
	zwracanaWartosc = LeftMousePressedTypuWiezy(); //typBudowy
	if (zwracanaWartosc != ZDARZENIE::BRAK) return zwracanaWartosc;
	zwracanaWartosc = LeftMousePressedWybranaBudowa(); //wybranaBudowa
	if (zwracanaWartosc != ZDARZENIE::BRAK) return zwracanaWartosc;
	zwracanaWartosc = LeftMousePressedWybranaWieza(); //wybrana wieza
	if (zwracanaWartosc != ZDARZENIE::BRAK) return zwracanaWartosc;
	zwracanaWartosc = LeftMousePressedWybranyStwor(); // wybranyStwor
	if (zwracanaWartosc != ZDARZENIE::BRAK) return zwracanaWartosc;
	return ZDARZENIE::NIC;
}

ZDARZENIE ZarzadcaZdarzen::RightMouseButtomPressed()
{
	//usuniêcie podgl¹dy
	if (pasek->CzyWybranaBudowa())
	{
		pasek->UsunWybranaBudowa();
	}
	else if (pasek->CzyWybranaWieza())
	{
		pasek->UsunWybranaWieza();
	}
	else if (pasek->CzyWybranyStwor())
	{
		pasek->UsunWybranyStwor();
	}
	return ZDARZENIE::NIC;
}

ZDARZENIE ZarzadcaZdarzen::MouseWheelScrolled(sf::Event& zdarzenie)
{
	if (pasek->CzyWybranaBudowa())
	{
		int aktualnyPasek = static_cast<int>(pasek->PobierzWybranaBudowa().PobierzTyp());
		if (aktualnyPasek != lbWiez)
		{
			if (zdarzenie.mouseWheelScroll.delta > 0)
			{
				aktualnyPasek--;
				if (aktualnyPasek < 0)	aktualnyPasek = lbWiez - 1;
			}
			else
			{
				aktualnyPasek++;
				if (aktualnyPasek > lbWiez - 1)	aktualnyPasek = 0;
			}
			pasek->PobierzWybranaBudowa().ZmienTyp(TYP_WIEZY(aktualnyPasek));
			pasek->PobierzWybranaBudowa().Zarzadzaj(ZgodaNaBudowe());
		}
	}
	return ZDARZENIE::NIC;
}

ZDARZENIE ZarzadcaZdarzen::MouseMoved(sf::Event& zdarzenie)
{
	mysz = sf::Vector2f(static_cast<float>(zdarzenie.mouseMove.x), static_cast<float>(zdarzenie.mouseMove.y));
	if (pasek->CzyWybranaBudowa())
	{
		pasek->PobierzWybranaBudowa().podglad->UstawPozycje(mysz.x, mysz.y);
		pasek->PobierzWybranaBudowa().Zarzadzaj(ZgodaNaBudowe());
	}
	else if (pasek->CzyWybranaWieza())
	{
		pasek->PobierzWybranaWieza().SprawdzDotyk(mysz);
	}
	else if (pasek->CzyEsc())
	{
		pasek->PobierzEsc().SprawdzAnimacje(mysz);
	}
	return ZDARZENIE::NIC;
}

ZDARZENIE ZarzadcaZdarzen::KeyReleased(sf::Event& zdarzenie)
{
	switch (zdarzenie.key.code)
	{
		case sf::Keyboard::Escape:
		{
			if (pasek->CzyEsc())
			{
				pasek->UsunEsc();
				return ZDARZENIE::WZNOW;
			}
			else
			{
				if (pasek->CzyWybranaBudowa()) pasek->UsunWybranaBudowa();
				if (pasek->CzyWybranaWieza()) pasek->UsunWybranaWieza();
				if (pasek->CzyWybranyStwor()) pasek->UsunWybranyStwor();
				pasek->StworzEsc();
			}
			break;
		}
		case sf::Keyboard::Add:
			pasek->ZmienTempo(true);
			break;
		case sf::Keyboard::Subtract:
			pasek->ZmienTempo(false);
			break;
		default:
			break;
	}
	return ZDARZENIE::NIC;
}

ZDARZENIE ZarzadcaZdarzen::MouseButtomPressed(sf::Event& zdarzenie)
{
	switch (zdarzenie.mouseButton.button)
	{
	case sf::Mouse::Button::Left:
		return LeftMouseButtomPressed();
		break;
	case sf::Mouse::Right:
		return RightMouseButtomPressed();
		break;
	default:
		return ZDARZENIE::NIC;
		break;
	}
}

ZDARZENIE ZarzadcaZdarzen::Zarzadzaj(sf::Event& zdarzenie)
{
	switch (zdarzenie.type)
	{
	case sf::Event::MouseMoved:
		return MouseMoved(zdarzenie);
		break;
	case sf::Event::MouseButtonPressed:
		return MouseButtomPressed(zdarzenie);
		break;
	case sf::Event::MouseWheelScrolled:
		return MouseWheelScrolled(zdarzenie);
		break;
	case sf::Event::KeyReleased:
		return KeyReleased(zdarzenie);
		break;		
	default:
		return ZDARZENIE::NIC;
		break;
	}
}
ZarzadcaZdarzen::~ZarzadcaZdarzen()
{
}
