#include "WybranyStwor.h"

using std::to_wstring;

WybranyStwor::WybranyStwor(Minion* Stwor)
{
	stwor = Stwor;

	std::vector <std::wstring> wektor = stwor->PobierzNazwe();

	sf::Color kolor = stwor->PobierzKolo().getFillColor();
	kolor.r = kolor.r > 120 ? 255 : kolor.r + 135;
	kolor.g = kolor.g > 120 ? 255 : kolor.g + 135;
	kolor.b = kolor.b > 120 ? 255 : kolor.b + 135;


	for (unsigned i = 0; i < wektor.size(); i++)
	{
		nazwa.push_back(sf::Text());
		nazwa[i].setFont(StatyczneTekstury::getFont());
		nazwa[i].setCharacterSize(20);
		nazwa[i].setFillColor(kolor);
		nazwa[i].setPosition(srodekMarginesu, 330.f + i * 20.f);
		nazwa[i].setString(wektor[i]);
		nazwa[i].setOrigin(nazwa[i].getGlobalBounds().width / 2.f, 0.f);
	}

	zycie.setFont(StatyczneTekstury::getFont());
	zycie.setString(L"¯ycie " + to_wstring(static_cast<int>(ceil(stwor->PobierzZycie()))));
	zycie.setCharacterSize(18);
	zycie.setFillColor(sf::Color(250, 85, 85));
	zycie.setPosition(margines, 400.f);

	nagroda.setFont(StatyczneTekstury::getFont());
	nagroda.setString(L"Nagroda " + to_wstring(stwor->PobierzZlotoZaZabicie()));
	nagroda.setCharacterSize(16u);
	nagroda.setFillColor(sf::Color(240, 240, 200));
	nagroda.setPosition(margines, 425.f);

	utrata.setFont(StatyczneTekstury::getFont());
	utrata.setString(L"Utrata " + to_wstring(stwor->PobierzPobieraneZycie()));
	utrata.setCharacterSize(16);
	utrata.setFillColor(sf::Color(240, 240, 200));
	utrata.setPosition(margines, 450.f);
}

void WybranyStwor::ZmienStwora(Minion* Stwor)
{
	stwor = Stwor;

	sf::Color kolor = stwor->PobierzKolo().getFillColor();
	kolor.r = kolor.r > 120 ? 255 : kolor.r + 135;
	kolor.g = kolor.g > 120 ? 255 : kolor.g + 135;
	kolor.b = kolor.b > 120 ? 255 : kolor.b + 135;

	std::vector <std::wstring> wektor = stwor->PobierzNazwe();
	nazwa.clear();
	for (unsigned i = 0; i < wektor.size(); i++)
	{
		nazwa.push_back(sf::Text());
		nazwa[i].setFont(StatyczneTekstury::getFont());
		nazwa[i].setCharacterSize(20u);
		nazwa[i].setFillColor(kolor);
		nazwa[i].setPosition(srodekMarginesu, 330.f + i * 20.f);
		nazwa[i].setString(wektor[i]);
		nazwa[i].setOrigin(nazwa[i].getGlobalBounds().width / 2.f, 0.f);
	}
	nagroda.setString(L"Nagroda " + to_wstring(stwor->PobierzZlotoZaZabicie()));
	utrata.setString(L"Utrata " + to_wstring(stwor->PobierzPobieraneZycie()));
}

bool WybranyStwor::Ruch()
{
	if (stwor->CzyZabity() == false)
	{
		zycie.setString(L"¯ycie " + to_wstring(static_cast<int>(ceil(stwor->PobierzZycie()))));
		return true;
	}
	else
	{
		return false;
	}
}

void WybranyStwor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : nazwa) { target.draw(i); }
	target.draw(zycie);
	target.draw(nagroda);
	target.draw(utrata);
}