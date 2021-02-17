#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <limits>
#include <iostream>

namespace jedzenie
{
	struct Modyfikatory
	{
	private:
		float* tab;
	public:
		float promien;
		float wartosc;
		float czas;
		sf::Vector2f poz;
		float PobierzWartosc(int index) const;
		Modyfikatory(float Promien, sf::Vector2f Pozycja, float Wartosc, float CzasDzialania);
		~Modyfikatory();
	};
	
}

class ZarzadcaJedzenia : public sf::Drawable
{
private:
	const float niebieski = 0, zielony = 12.f, czerwony = 24.f, czarny = 48.f;
	std::vector< std::vector <float>> mapa;
	std::vector< jedzenie::Modyfikatory* > modyfikatory;
	sf::VertexArray zoobrazowanie;
	void Modyfikuj(const jedzenie::Modyfikatory& modyfikator);
	void Cofnij(const jedzenie::Modyfikatory& modyfikator);
	sf::Color koloruj(float wartosc) const;
public:
	ZarzadcaJedzenia(sf::Vector2f rozdzielczosc, float wartoscPodstawowa);
	// dodaje kolo, ktore zwieksza lub zmniejsze ilosc produkowanego jedzeni
	void DodajZdarzenie(float promien,const sf::Vector2f& pozycja, float wartosc, float czasDzialania = _FMAX); 
	void Ruch(float time);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	~ZarzadcaJedzenia();
};

