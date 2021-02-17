#include "WybranaBudowa.h"

 
void WybranaBudowa::UstawTyp(TYP_WIEZY typ, const sf::Vector2f& pozycja)
{
	czyMozliwaBudowa = false;
	podglad = new IkonaWiezy(typ, pozycja);
	sf::Color Kolor = podglad->PobierzKolor();
	Kolor.a = 128u;
	M_kolor = Kolor;
	podglad->UstawKolor(sf::Color(M_kolor.r / 3 + 50, M_kolor.g / 3 + 50, M_kolor.b / 3 + 50, M_kolor.a));
	Kolor.a = 255u;
	Kolor.r = Kolor.r > 155 ? 255 : Kolor.r + 100;
	Kolor.g = Kolor.g > 155 ? 255 : Kolor.g + 100;
	Kolor.b = Kolor.b > 155 ? 255 : Kolor.b + 100;

	nazwa[0].setFillColor(Kolor);
	nazwa[1].setFillColor(Kolor);
	nazwa[0].setString(podglad->PobierzNazwe());
	nazwa[1].setString(L"Wie¿a");

	koszt.setString(L"Koszt " + std::to_wstring(podglad->PobierzKoszt(true)));
	obrazenia.setString(L"Obra¿enia " + funkcje::Zaokraglij(podglad->PobierzObrazenia()));
	szybkosc.setString(L"Szybkosc " + funkcje::Zaokraglij(1000.0f / podglad->PobierzSzybkoscOstrzalu()));
	zasieg.setString(L"Zasieg " + funkcje::Zaokraglij(podglad->PobierzZasieg()));
	Kolor.r = Kolor.r > 180 ? 255 : Kolor.r + 75;
	Kolor.g = Kolor.g > 180 ? 255 : Kolor.g + 75;
	Kolor.b = Kolor.b > 180 ? 255 : Kolor.b + 75;

	opisWiezy = funkcje::NapisNaTekst(podglad->PobierzOpis(), 30);
	for (auto& i : opisWiezy) i->setFillColor(Kolor);
}

WybranaBudowa::WybranaBudowa(TYP_WIEZY typ, const sf::Vector2f& pozycja)
{
	czyMozliwaBudowa = false;
	
	UstawTyp(typ, pozycja);

	nazwa[0].setFont(StatyczneTekstury::getFont());
	nazwa[0].setCharacterSize(19);
	nazwa[0].setOrigin(nazwa[0].getGlobalBounds().width / 2, 0);
	nazwa[0].setPosition(srodekMarginesu, 320);

	nazwa[1].setFont(StatyczneTekstury::getFont());
	nazwa[1].setCharacterSize(19);
	nazwa[1].setOrigin(nazwa[1].getGlobalBounds().width / 2, 0);
	nazwa[1].setPosition(srodekMarginesu, 320 + nazwa[0].getGlobalBounds().height + 6);

	koszt.setFont(StatyczneTekstury::getFont());
	koszt.setCharacterSize(18);
	koszt.setFillColor(sf::Color(255, 255, 80));
	koszt.setPosition(margines, 370);

	obrazenia.setFillColor(sf::Color(240, 240, 200));
	obrazenia.setFont(StatyczneTekstury::getFont());
	obrazenia.setCharacterSize(13);
	obrazenia.setPosition(margines, 400);

	szybkosc.setFillColor(sf::Color(240, 240, 200));
	szybkosc.setFont(StatyczneTekstury::getFont());
	szybkosc.setCharacterSize(13);
	szybkosc.setPosition(margines, 415);

	zasieg.setFillColor(sf::Color(240, 240, 200));
	zasieg.setFont(StatyczneTekstury::getFont());
	zasieg.setCharacterSize(13);
	zasieg.setPosition(margines, 430);

	opis.setFont(StatyczneTekstury::getFont());
	opis.setString("Opis");
	opis.setCharacterSize(12u);
	opis.setFillColor(sf::Color(250, 250, 250));
	opis.setOrigin(opis.getGlobalBounds().width / 2, opis.getGlobalBounds().height / 2);
	opis.setPosition(srodekMarginesu, 457);

	for (unsigned i = 0; i < opisWiezy.size(); i++)
	{
		opisWiezy[i]->setCharacterSize(11);
		opisWiezy[i]->setLetterSpacing(0.8f);
		opisWiezy[i]->setLineSpacing(1.8f);
		opisWiezy[i]->setPosition(margines, 478.f + i * opisWiezy[i]->getCharacterSize());
	}
}

void WybranaBudowa::ZmienTyp(TYP_WIEZY typ)
{
	for (auto& i : opisWiezy) delete i;
	sf::Vector2f pozycja = podglad->PobierzPozycje();
	delete podglad;
	UstawTyp(typ, pozycja);
	/*Aktualizacja opisów wie¿*/ 
	for (unsigned i = 0; i < opisWiezy.size(); i++)
	{
		opisWiezy[i]->setCharacterSize(11);
		opisWiezy[i]->setPosition(margines, 478.f + i * opisWiezy[i]->getCharacterSize());
	}
	nazwa[0].setOrigin(nazwa[0].getGlobalBounds().width / 2, 0);
}

void WybranaBudowa::Zarzadzaj(bool CzyBudowa)
{
	if (CzyBudowa != czyMozliwaBudowa)
	{
		if (CzyBudowa)
		{
			podglad->UstawKolor(M_kolor);
		}
		else
		{
			podglad->UstawKolor(sf::Color(M_kolor.r / 2 + 40, M_kolor.g / 3 + 40, M_kolor.b / 3 + 40, M_kolor.a));
		}
		czyMozliwaBudowa = CzyBudowa;
	}
}

void WybranaBudowa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nazwa[0], states);
	target.draw(nazwa[1], states);

	target.draw(obrazenia, states);
	target.draw(szybkosc, states);
	target.draw(zasieg, states);

	target.draw(koszt, states);
	target.draw(*podglad, states);

	target.draw(opis, states);
	for (auto& i : opisWiezy) target.draw(*i, states);
}

WybranaBudowa::~WybranaBudowa()
{
	for (auto& i : opisWiezy) delete i;
	delete podglad;
}

///////////////////

void SzybkaWybranaBudowa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nazwa[0]);
	target.draw(nazwa[1]);

	target.draw(obrazenia);
	target.draw(szybkosc);
	target.draw(zasieg);
	target.draw(*podglad);
}