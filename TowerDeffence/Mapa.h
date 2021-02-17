#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Matematyka.h"
#include <math.h>

using std::vector;

enum class STR_SW	{ N , E , S , W , Brak  };

class Mapa : public sf::Drawable
{
private:
	void ObliczKaty(std::vector <float>& katy, const std::vector <sf::Vector2f>& wspolrzedne);
	void SprawdzZmianeStrony(std::vector <bool>& czyPrawo, std::vector <float>& katy);
	void StworzPrastakaty(const vector<sf::Vector2f>& wspolrzedne,vector<float>& katy,vector<bool>CzyPrawa,vector<bool>& CzyZmiana,vector<STR_SW>& strony);
	void Polnoc(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii);
	void Poludnie(const sf::Vector2f& temp1,const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii);
	void Wschod(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii);
	void Zachod(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii);

public:
	Mapa(int numerPoziomu);
	sf::VertexArray tablica;
	float rozmiarLinii;
	std::vector <STR_SW> kierunek;
	std::vector <sf::RectangleShape> linie;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void StworzLiniePomozniecze(const std::vector<sf::Vector2f>& wspolrzedne);
	~Mapa();
};

