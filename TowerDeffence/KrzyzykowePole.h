#pragma once
#include "Pole.h"

class KrzyzykowePole : public Pole
{
private:
protected:
	sf::RectangleShape pion, poziom;
	KrzyzykowePole(const sf::Vector2f& pozycja, const std::wstring& napis, const sf::Color& kolorPola, const sf::Vector2f& rozmiarPola, unsigned rozmiar, float& rozmiarKola);
public:
	KrzyzykowePole(const sf::Vector2f& pozycja, const std::wstring& napis, const sf::Color& kolorPola, const sf::Vector2f& rozmiarPola, unsigned rozmiar);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool CzyZawieranie(const sf::Vector2f& mysz) const;
	virtual void ZmienRozmiarPola(const sf::Vector2f& nowyRozmiar, unsigned rozmiarCzcionki, bool czyPowiekszenie);
};


