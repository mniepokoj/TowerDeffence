#include "PomaranczowaWieza.h"

const sf::Vector2f squareSize(100, 100);
const sf::Color squareColor(255, 128, 0);
constexpr float triangleRadius = 100;
constexpr float triangleSize = 30;
constexpr float triangleOutlineThickness = 10;
const sf::Color triangleFillColor(20, 240, 0);
const sf::Color triangleOutlineColor(200, 20, 240);

void PomaranczowaWieza::Level1()
{
	model.setFillColor(squareColor);
	model.setOrigin(squareSize.x / 2, squareSize.y / 2);
	model.setSize(squareSize);

	float angle = 360.f / lbTrojkatow;
	for (int i = 0; i < lbTrojkatow; i++)
	{
		triangle[i].Create(triangleSize, sf::Vector2f(0, 0), triangleOutlineThickness, triangleFillColor, triangleOutlineColor, triangleRadius, i * angle);
	}

	zasieg = 160.f;
	obrazenia = 2.f;
	szybkoscOstrzalu = 400.f;
	wielkoscPocisku = sf::Vector2f(3, 1);
	predkoscPocisku = 300.1f;
	CzasDoWystrzalu = szybkoscOstrzalu;
}

void PomaranczowaWieza::Strzelanie()
{

}

PomaranczowaWieza::PomaranczowaWieza(const PomaranczowaWieza& wieza) : Wieza()
{
	model.setSize(model.getSize());
	model.setFillColor(wieza.model.getFillColor());
	model.setOrigin(model.getSize().x / 2, model.getSize().y / 2);
	model.setPosition(wieza.model.getPosition());
	zasieg = wieza.zasieg;
	predkoscPocisku = wieza.predkoscPocisku;
	obrazenia = wieza.obrazenia;
	wielkoscPocisku = wieza.wielkoscPocisku;
	szybkoscOstrzalu = wieza.szybkoscOstrzalu;
	poziom = wieza.poziom;
	CzasDoWystrzalu = wieza.CzasDoWystrzalu;
	for (int i = 0; i < lbTrojkatow; i++) triangle[i] = wieza.triangle[i];
	if (wieza.typWygladu)
	{
		typWygladu = new TypWygladu(*wieza.typWygladu);
	}
}

PomaranczowaWieza::PomaranczowaWieza(const sf::Vector2f& polozenie)
{
	typWygladu = NULL;
	poziom = 1;
	Level1();
	UstawPozycje(polozenie);
}

void PomaranczowaWieza::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < lbTrojkatow; i++)
	{
		target.draw(triangle[i], states);
	}
	target.draw(model, states);
}

int PomaranczowaWieza::PobierzKoszt(bool creatable) const
{
	switch (poziom - creatable)
	{
	case 0:	return 100;
	default:	return 99999;
	}
}
void PomaranczowaWieza::Ruch(const float& czas)
{
	for (int i = 0; i < lbTrojkatow; i++)
	{
		triangle[i].Motion(czas);
	}
}

void PomaranczowaWieza::Ulepsz()
{
	poziom = 99999;
}
int PomaranczowaWieza::MaxPoziom() const
{
	return 1;
}
std::wstring PomaranczowaWieza::PobierzNazwe() const
{
	return L"Pomaranczowa";
}
std::wstring PomaranczowaWieza::PobierzOpis() const
{
	return L"Wieza posiada kilka trójk¹tów lataj¹cych wokó³ niej i atakuj¹cych pobliskich przeciwników.";
}

void PomaranczowaWieza::UstawPozycje(const sf::Vector2f& pozycja)
{
	for (size_t i = 0; i < lbTrojkatow; i++)
	{
		triangle[i].setPosition(pozycja);
	}
	model.setPosition(pozycja);
}