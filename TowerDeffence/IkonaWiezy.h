#pragma once
#include <SFML/Graphics.hpp>
#include "ZarzadcaWiez.h"

class IkonaWiezy : public sf::Drawable
{
	Wieza* wieza;
public:
	IkonaWiezy();
	IkonaWiezy(TYP_WIEZY typ, const sf::Vector2f& pozycja);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void UstawTypWiezy(TYP_WIEZY typ);
	void UstawPozycje(float x, float y);
	void UstawRozmiar(const sf::Vector2f& rozmiar);
	void UstawKolor(const sf::Color& color);
	int PobierzKoszt(bool creatable = false) const;
	TYP_WIEZY PobierzTyp() const;
	std::wstring PobierzNazwe() const;
	sf::Color PobierzKolor() const;
	const sf::Vector2f& PobierzRozmiar() const;
	std::wstring PobierzOpis() const;
	float PobierzObrazenia() const;
	float PobierzZasieg() const;
	float PobierzSzybkoscOstrzalu() const;
	sf::Vector2f PobierzPozycje() const;
	sf::FloatRect getGlobalBounds() const;
	~IkonaWiezy();
};

