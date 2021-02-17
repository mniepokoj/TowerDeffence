#include "IkonaWiezy.h"



IkonaWiezy::IkonaWiezy() : wieza(NULL)
{
}

IkonaWiezy::IkonaWiezy(TYP_WIEZY typ, const sf::Vector2f& pozycja)
{
	wieza = ZarzadcaWiez::StworzWieze(typ, pozycja);
}

void IkonaWiezy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(wieza->PobierzModel());
}

void IkonaWiezy::UstawTypWiezy(TYP_WIEZY typ)
{
	if (wieza) delete wieza;
	wieza = ZarzadcaWiez::StworzWieze(typ, sf::Vector2f(0, 0));
}
void IkonaWiezy::UstawPozycje(float x, float y)
{
	wieza->UstawPozycje(x , y);
}
void IkonaWiezy::UstawRozmiar(const sf::Vector2f& rozmiar)
{
	wieza->UstawRozmiar(rozmiar.x, rozmiar.y);
}
void IkonaWiezy::UstawKolor(const sf::Color& color)
{
	wieza->UstawKolor(color);
}

int  IkonaWiezy::PobierzKoszt(bool creatable) const
{
	return wieza->PobierzKoszt(creatable);
}
TYP_WIEZY IkonaWiezy::PobierzTyp() const 
{
	return wieza->PobierzTyp();
}
std::wstring IkonaWiezy::PobierzNazwe() const
{
	return wieza->PobierzNazwe();
}
sf::Color IkonaWiezy::PobierzKolor() const
{
	return wieza->PobierzKolor();
}
const sf::Vector2f& IkonaWiezy::PobierzRozmiar() const
{
	return wieza->PobierzRozmiar();
}
std::wstring IkonaWiezy::PobierzOpis() const
{
	return wieza->PobierzOpis();
}
float IkonaWiezy::PobierzObrazenia() const
{
	return wieza->PobierzObrazenia();
}
float IkonaWiezy::PobierzZasieg() const
{
	return wieza->PobierzZasieg();
}
float IkonaWiezy::PobierzSzybkoscOstrzalu() const
{
	return wieza->PobierzSzybkoscOstrzalu();
}
sf::Vector2f IkonaWiezy::PobierzPozycje() const
{
	return wieza->PobierzModel().getPosition();
}
sf::FloatRect IkonaWiezy::getGlobalBounds() const
{
	return wieza->PobierzModel().getGlobalBounds();
}

IkonaWiezy::~IkonaWiezy()
{
#ifdef _DEBUG
	if(wieza == NULL) std::cout << "Error File: " << __FILE__ << " Line: " << __LINE__ << " Wieza doesn't exsist. " << std::endl;
#endif _DEBUG
	delete wieza;
}
