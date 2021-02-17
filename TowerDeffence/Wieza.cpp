#include "Wieza.h"

ZarzadcaStworow* Wieza::zarzadcaStworow;
ZarzadcaPociskow* Wieza::zarzadcapociskow;



Wieza::Wieza() :
	CzasDoWystrzalu(0.f),
	predkoscPocisku(0.f),
	obrazenia(0.f),
	wielkoscPocisku(0, 0),
	zasieg(0),
	szybkoscOstrzalu(0.f),
	poziom(0),
	model(),
	typWygladu(NULL)
{

}

Wieza::Wieza(const sf::Vector2f& wielkoscPocisku, const sf::RectangleShape& model) :
	model(model),
	wielkoscPocisku(wielkoscPocisku),
	CzasDoWystrzalu(0.f),
	predkoscPocisku(0.f),
	obrazenia(0.f),
	zasieg(0),
	szybkoscOstrzalu(0.f),
	poziom(0),
	typWygladu(NULL)
{

}

void Wieza::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(model);
	if (typWygladu)
	{
		target.draw(*typWygladu);
	}
}

sf::Color Wieza::PobierzKolor() const 
{ 
	return model.getFillColor(); 
}
const sf::Vector2f& Wieza::PobierzRozmiar() const 
{ 
	return model.getSize(); 
};
std::wstring Wieza::PobierzOpis() const 
{ 
	return L"Zwyk³a wie¿a"; 
}
float Wieza::PobierzObrazenia() const 
{ 
	return obrazenia; 
};
float Wieza::PobierzZasieg() const 
{
	return zasieg; 
}
float Wieza::PobierzSzybkoscOstrzalu() const 
{ 
	return szybkoscOstrzalu; 
}
const sf::RectangleShape& Wieza::PobierzModel() const
{
	return model;
}
const TypWygladu* Wieza::PobierzTypWygladu() const
{
	return typWygladu;
}
void Wieza::UstawRozmiar(float x, float y) 
{ 
	model.setSize(sf::Vector2f(x, y)); 
	model.setOrigin(x / 2, y / 2); 
}
void Wieza::UstawPozycje(float x, float y) 
{ 
	model.setPosition(x, y); 
}
void Wieza::UstawKolor(const sf::Color& kolor) 
{ 
	model.setFillColor(kolor); 
}

Wieza::~Wieza()
{
	if (typWygladu)
	{
		delete typWygladu;
	}
}