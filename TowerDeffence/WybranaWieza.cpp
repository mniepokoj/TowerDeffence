#include "WybranaWieza.h"


WybranaWieza::WybranaWieza(Wieza* wiezaa, int& Zloto) : zloto(Zloto)
{
	wieza = wiezaa;

	czyCzerwony = false;
	czyPodglad = false;

	sf::Color kolor(wieza->PobierzKolor());
	kolor.r = kolor.r > 155 ? 255 : kolor.r + 100;
	kolor.g = kolor.g > 155 ? 255 : kolor.g + 100;
	kolor.b = kolor.b > 155 ? 255 : kolor.b + 100;

	wieza->PobierzKoszt();

	nazwa[0].setString(wieza->PobierzNazwe());
	nazwa[0].setFont(StatyczneTekstury::getFont());
	nazwa[0].setFillColor(kolor);
	nazwa[0].setCharacterSize(16);
	nazwa[0].setOrigin(nazwa[0].getGlobalBounds().width / 2, 0);
	nazwa[0].setPosition(srodekMarginesu, 316);

	nazwa[1].setString(L"Wie¿a");
	nazwa[1].setFont(StatyczneTekstury::getFont());
	nazwa[1].setFillColor(kolor);
	nazwa[1].setCharacterSize(16);
	nazwa[1].setOrigin(nazwa[1].getGlobalBounds().width / 2, 0);
	nazwa[1].setPosition(srodekMarginesu, 316 + nazwa[0].getGlobalBounds().height + 6);

	ulepsz.setFont(StatyczneTekstury::getFont());
	ulepsz.setString("Ulepsz");
	ulepsz.setCharacterSize(22);
	ulepsz.setOrigin(ulepsz.getGlobalBounds().width / 2, 0);
	ulepsz.setFillColor(wieza->PobierzPoziom() <= wieza->MaxPoziom() ? sf::Color(40, 250, 70) : sf::Color(220, 30, 30));
	ulepsz.setPosition(srodekMarginesu, 355);

	wieza->PobierzKoszt();
	koszt.setFont(StatyczneTekstury::getFont());
	koszt.setString(L"Koszt " + (wieza->PobierzPoziom() >= wieza->MaxPoziom() ? L"-" : std::to_wstring(wieza->PobierzKoszt())));
	koszt.setCharacterSize(14);
	koszt.setFillColor(sf::Color(255, 255, 80));
	koszt.setPosition(margines, 386);

	kolo.setFillColor(sf::Color(255, 20, 20, 64));
	kolo.setRadius(wiezaa->PobierzZasieg());
	kolo.setPointCount(static_cast<size_t>(wiezaa->PobierzZasieg() / 2.f));
	kolo.setOrigin(wiezaa->PobierzZasieg(), wiezaa->PobierzZasieg());
	kolo.setPosition(wiezaa->PobierzModel().getPosition());

	poziom.setFont(StatyczneTekstury::getFont());
	poziom.setString(L"Poziom " + (wieza->PobierzPoziom() > wieza->MaxPoziom() ? L"MAX" : std::to_wstring(wieza->PobierzPoziom())));
	poziom.setCharacterSize(14);
	poziom.setFillColor(sf::Color(255, 255, 200));
	poziom.setPosition(margines, 408);

	obrazenia.setFont(StatyczneTekstury::getFont());
	obrazenia.setString(L"Obrazenia " + funkcje::Zaokraglij(wieza->PobierzObrazenia()));
	obrazenia.setCharacterSize(12);
	obrazenia.setFillColor(sf::Color(240, 240, 200));
	obrazenia.setPosition(margines, 425);

	szybkosc.setFont(StatyczneTekstury::getFont());
	szybkosc.setString(L"Szybkosc " + funkcje::Zaokraglij(float(1000.0f / wieza->PobierzSzybkoscOstrzalu())));
	szybkosc.setCharacterSize(12);
	szybkosc.setFillColor(sf::Color(240, 240, 200));
	szybkosc.setPosition(margines, 437);

	zasieg.setFont(StatyczneTekstury::getFont());
	zasieg.setString(L"Zasieg " + std::to_wstring(int(wieza->PobierzZasieg())));
	zasieg.setCharacterSize(12);
	zasieg.setFillColor(sf::Color(240, 240, 200));
	zasieg.setPosition(margines, 449);

	opis.setFont(StatyczneTekstury::getFont());
	opis.setString("Opis");
	opis.setCharacterSize(12u);
	opis.setFillColor(sf::Color(250, 250, 250));
	opis.setOrigin(opis.getGlobalBounds().width / 2, opis.getGlobalBounds().height / 2);
	opis.setPosition(srodekMarginesu, 470);

	opisWiezy = funkcje::NapisNaTekst(wieza->PobierzOpis(), 25);

	kolor.r = kolor.r > 200 ? 255 : kolor.r + 55;
	kolor.g = kolor.g > 200 ? 255 : kolor.g + 55;
	kolor.b = kolor.b > 200 ? 255 : kolor.b + 55;

	for (unsigned i = 0; i < opisWiezy.size(); i++)
	{
		opisWiezy[i]->setCharacterSize(11);
		opisWiezy[i]->setFillColor(kolor);
		opisWiezy[i]->setPosition(margines, 478.f + i * opisWiezy[i]->getCharacterSize());
	}

	czyDotyka = ulepsz.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()));
	czyPoziom = !(wieza->PobierzPoziom() > wieza->MaxPoziom());
	SprawdzCzerwony();
	SprawdzPodglad();
}
void WybranaWieza::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nazwa[0]);
	target.draw(nazwa[1]);
	target.draw(ulepsz);
	target.draw(koszt);
	target.draw(poziom);
	target.draw(obrazenia);
	target.draw(szybkosc);
	target.draw(zasieg);
	target.draw(opis);
	for (auto& i : opisWiezy) target.draw(*i);
}

void WybranaWieza::RysojZasieg(sf::RenderTarget& target) const
{
	target.draw(kolo);
}

bool WybranaWieza::CzyMoznaUsunac(const sf::Vector2f& mysz) const
{
	return (mysz.x < margines && !wieza->PobierzModel().getGlobalBounds().contains(mysz));
}

void WybranaWieza::Ruch()
{
	CzerwonaWieza* wiezaa = dynamic_cast<CzerwonaWieza*>(wieza);

	if (wiezaa != NULL)
	{
		if (wiezaa->aktualizacjaObrazen == true)
		{
			obrazenia.setString(L"Obrazenia " + funkcje::Zaokraglij(wiezaa->PobierzObrazenia()));
		}
	}
}

void WybranaWieza::Ulepsz()
{
		int ulepszenie = wieza->PobierzKoszt();
		wieza->Ulepsz();
		zloto -= ulepszenie;
		SprawdzPoziom();
		kolo.setRadius(wieza->PobierzZasieg());
		kolo.setPointCount(static_cast<size_t> (wieza->PobierzZasieg() / 2 + 10));
		kolo.setOrigin(wieza->PobierzZasieg(), wieza->PobierzZasieg());

		czyZloto = false;
		SprawdzPodglad();

		sf::Color kolor(wieza->PobierzKolor());
		kolor.r = kolor.r > 155 ? 255 : kolor.r + 100;
		kolor.g = kolor.g > 155 ? 255 : kolor.g + 100;
		kolor.b = kolor.b > 155 ? 255 : kolor.b + 100;
		nazwa[0].setFillColor(kolor);
		nazwa[1].setFillColor(kolor);

		nazwa[0].setString(wieza->PobierzNazwe());

		koszt.setString(L"Koszt " + (wieza->PobierzPoziom() >= wieza->MaxPoziom() ? L"-" : std::to_wstring(wieza->PobierzKoszt())));
		poziom.setString(L"Poziom " + (wieza->PobierzPoziom() > wieza->MaxPoziom() ? L"MAX" : std::to_wstring(wieza->PobierzPoziom())));

		for (auto& i : opisWiezy) delete i;
		opisWiezy = funkcje::NapisNaTekst(wieza->PobierzOpis(), 25);

		kolor.r = kolor.r > 200 ? 255 : kolor.r + 55;
		kolor.g = kolor.g > 200 ? 255 : kolor.g + 55;
		kolor.b = kolor.b > 200 ? 255 : kolor.b + 55;

		for (unsigned i = 0; i < opisWiezy.size(); i++)
		{
			opisWiezy[i]->setCharacterSize(11);
			opisWiezy[i]->setFillColor(kolor);
			opisWiezy[i]->setPosition(margines, 478.f + i * opisWiezy[i]->getCharacterSize());
		}
}

void WybranaWieza::SprawdzCzerwony()
{
	if (!czyCzerwony)
	{
		if (!czyPoziom || !czyZloto)
		{
			czyCzerwony = true;
			ulepsz.setFillColor(sf::Color(220, 30, 30));
		}
	}
	else if (czyPoziom && czyZloto)
	{
		czyCzerwony = false;
		ulepsz.setFillColor(sf::Color(40, 250, 70));
	}
}

void WybranaWieza::SprawdzPodglad()
{
	if (!czyPodglad)
	{
		if (czyDotyka && czyPoziom && czyZloto)
		{

			Wieza* mWieza = ZarzadcaWiez::StworzWieze(wieza);
			mWieza->Ulepsz();

			sf::Color kolor(mWieza->PobierzKolor());
			kolor.r = kolor.r > 155 ? 255 : kolor.r + 100;
			kolor.g = kolor.g > 135 ? 255 : kolor.g + 120;
			kolor.b = kolor.b > 155 ? 255 : kolor.b + 100;
			nazwa[0].setFillColor(kolor);
			nazwa[1].setFillColor(kolor);
			nazwa[0].setString(mWieza->PobierzNazwe());
			nazwa[0].setOrigin(nazwa[0].getGlobalBounds().width / 2, 0);

			ulepsz.setStyle(sf::Text::Bold);

			ulepsz.setLetterSpacing(0.65f);

			obrazenia.setString(L"Obrazenia " + funkcje::Zaokraglij(mWieza->PobierzObrazenia()));
			obrazenia.setFillColor(sf::Color(100, 200, 100));

			szybkosc.setString(L"Szybkosc " + funkcje::Zaokraglij(float(1000.0f / mWieza->PobierzSzybkoscOstrzalu())));
			szybkosc.setFillColor(sf::Color(100, 200, 100));

			zasieg.setString(L"Zasieg " + std::to_wstring(int(mWieza->PobierzZasieg())));
			zasieg.setFillColor(sf::Color(100, 200, 100));

			for (auto& i : opisWiezy) delete i;
			opisWiezy = funkcje::NapisNaTekst(mWieza->PobierzOpis(), 25);
			for (unsigned i = 0; i < opisWiezy.size(); i++)
			{
				opisWiezy[i]->setCharacterSize(11);
				opisWiezy[i]->setFillColor(sf::Color(100, 200, 100));
				opisWiezy[i]->setPosition(margines, 478.f + i * opisWiezy[i]->getCharacterSize());
			}
			czyPodglad = true;
			delete mWieza;
		}
	}
	else if (!czyDotyka || !czyPoziom || !czyZloto)
	{
		sf::Color kolor(wieza->PobierzKolor());
		kolor.r = kolor.r > 155 ? 255 : kolor.r + 100;
		kolor.g = kolor.g > 155 ? 255 : kolor.g + 100;
		kolor.b = kolor.b > 155 ? 255 : kolor.b + 100;
		nazwa[0].setFillColor(kolor);
		nazwa[1].setFillColor(kolor);
		nazwa[0].setString(wieza->PobierzNazwe());
		nazwa[0].setOrigin(nazwa[0].getGlobalBounds().width / 2, 0);

		ulepsz.setStyle(sf::Text::Regular);

		ulepsz.setLetterSpacing(1);

		obrazenia.setString(L"Obrazenia " + funkcje::Zaokraglij(wieza->PobierzObrazenia()));
		obrazenia.setFillColor(sf::Color(240, 240, 200));

		szybkosc.setString(L"Szybkosc " + funkcje::Zaokraglij(float(1000.0f / wieza->PobierzSzybkoscOstrzalu())));
		szybkosc.setFillColor(sf::Color(240, 240, 200));

		zasieg.setString(L"Zasieg " + std::to_wstring(int(wieza->PobierzZasieg())));
		zasieg.setFillColor(sf::Color(240, 240, 200));

		for (auto& i : opisWiezy) delete i;
		opisWiezy = funkcje::NapisNaTekst(wieza->PobierzOpis(), 25);
		kolor.r = kolor.r > 200 ? 255 : kolor.r + 55;
		kolor.g = kolor.g > 200 ? 255 : kolor.g + 55;
		kolor.b = kolor.b > 200 ? 255 : kolor.b + 55;

		for (unsigned i = 0; i < opisWiezy.size(); i++)
		{
			opisWiezy[i]->setCharacterSize(11);
			opisWiezy[i]->setFillColor(kolor);
			opisWiezy[i]->setPosition(margines, 478.f + i * opisWiezy[i]->getCharacterSize());
		}
		czyPodglad = false;
	}

}

void WybranaWieza::SprawdzPoziom()
{
	czyPoziom = !(wieza->PobierzPoziom() > wieza->MaxPoziom());
	SprawdzCzerwony();
	SprawdzPodglad();
}
void WybranaWieza::SprawdzZloto()
{
	if (czyPoziom)
	{
		czyZloto = wieza->PobierzKoszt() <= zloto;
		SprawdzCzerwony();
		SprawdzPodglad();
	}
}
void WybranaWieza::SprawdzDotyk(const sf::Vector2f& mysz)
{
	czyDotyka = ulepsz.getGlobalBounds().contains(mysz);
	SprawdzPodglad();
}

WybranaWieza::~WybranaWieza()
{
	for (auto& i : opisWiezy) delete i;
}

SzybkaWybranaWieza::SzybkaWybranaWieza(Wieza* wieza, int& zloto) : WybranaWieza(wieza, zloto)
{
	ulepsz.setFillColor(sf::Color(220, 30, 30));
	koszt.setString("Koszt -");
}

void SzybkaWybranaWieza::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nazwa[1]);
	target.draw(ulepsz);
	target.draw(koszt);
	target.draw(poziom);
	target.draw(obrazenia);
	target.draw(szybkosc);
	target.draw(zasieg);
}