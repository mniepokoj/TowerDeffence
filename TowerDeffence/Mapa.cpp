#include "Mapa.h"


//Pobiera dane w pliku tekstowego "zbiorLini.txt" i na ich podstawie tworzy wektor RectangleSchape
//Konstruktor pobiera tylka katy proste

using std::vector;

void Mapa::Polnoc(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii)
{	
	if (stronaPrzed == STR_SW::W && stronaPo == STR_SW::E)
	{
		prastakat.setPosition(temp1.x + rozmiarLinii, temp1.y);
		prastakat.setSize(sf::Vector2f(temp2.x - temp1.x - rozmiarLinii * 2, rozmiarLinii));
	}
	else if(stronaPrzed == STR_SW::W && stronaPo == STR_SW::W)
	{
		prastakat.setPosition(temp1.x + rozmiarLinii, temp1.y);
		prastakat.setSize(sf::Vector2f(temp2.x - temp1.x - rozmiarLinii, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::E && stronaPo == STR_SW::W)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp2.x - temp1.x, rozmiarLinii));
	}

	else if(stronaPrzed == STR_SW::E && stronaPo == STR_SW::E)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp2.x - temp1.x, rozmiarLinii));
	}
	else
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp2.x - temp1.x, rozmiarLinii));
	}
	prastakat.setRotation(0);
}

void Mapa::Poludnie(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii)
{
	if (stronaPrzed == STR_SW::W && stronaPo == STR_SW::E)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.x - temp2.x, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::W && stronaPo == STR_SW::W)
	{
		prastakat.setPosition(temp1.x - rozmiarLinii, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.x - temp2.x - 2 * rozmiarLinii, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::E && stronaPo == STR_SW::W)
	{
		prastakat.setPosition(temp1.x - rozmiarLinii, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.x - temp2.x - 2 * rozmiarLinii, rozmiarLinii));
	}

	else if (stronaPrzed == STR_SW::E && stronaPo == STR_SW::E)
	{
		prastakat.setPosition(temp1.x - rozmiarLinii, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.x - temp2.x -  rozmiarLinii, rozmiarLinii));
	}
	else
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.x - temp2.x, rozmiarLinii));
	}
	prastakat.setRotation(180);
}

void Mapa::Wschod(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii)
{
	if (stronaPrzed == STR_SW::N && stronaPo == STR_SW::S)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f( temp2.y - temp1.y, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::S && stronaPo == STR_SW::N)
	{
		prastakat.setPosition(temp1.x, temp1.y - rozmiarLinii);
		prastakat.setSize(sf::Vector2f(temp2.y - temp1.y + 2 * rozmiarLinii, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::S && stronaPo == STR_SW::S)
	{
		prastakat.setPosition(temp1.x, temp1.y - rozmiarLinii);
		prastakat.setSize(sf::Vector2f(temp2.y - temp1.y + rozmiarLinii, rozmiarLinii));
	}

	else if (stronaPrzed == STR_SW::N && stronaPo == STR_SW::N)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp2.y - temp1.y + rozmiarLinii, rozmiarLinii));
	}
	else
	{
		prastakat.setPosition(temp1.x, temp1.y - rozmiarLinii);
		prastakat.setSize(sf::Vector2f(abs(temp2.y - temp1.y), rozmiarLinii));
	}
	prastakat.setRotation(90);
}

void Mapa::Zachod(const sf::Vector2f& temp1, const sf::Vector2f& temp2, sf::RectangleShape& prastakat, STR_SW stronaPrzed, STR_SW stronaPo, float rozmiarLinii)
{
	if (stronaPrzed == STR_SW::N && stronaPo == STR_SW::S)
	{
		prastakat.setPosition(temp1.x, temp1.y + rozmiarLinii);
		prastakat.setSize(sf::Vector2f(temp1.y - temp2.y + rozmiarLinii * 2, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::S && stronaPo == STR_SW::N)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.y - temp2.y + rozmiarLinii, rozmiarLinii));
	}
	else if (stronaPrzed == STR_SW::S && stronaPo == STR_SW::S)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.y - temp2.y + rozmiarLinii, rozmiarLinii));
	}

	else if (stronaPrzed == STR_SW::N && stronaPo == STR_SW::N)
	{
		prastakat.setPosition(temp1.x, temp1.y + rozmiarLinii);
		prastakat.setSize(sf::Vector2f(temp1.y - temp2.y + rozmiarLinii, rozmiarLinii));
	}
	else if(stronaPrzed == STR_SW::S && stronaPo == STR_SW::Brak)
	{
		prastakat.setPosition(temp1.x, temp1.y);
		prastakat.setSize(sf::Vector2f(temp1.y - temp2.y + rozmiarLinii, rozmiarLinii));
	}
	else
	{
		prastakat.setPosition(temp1.x, temp1.y + rozmiarLinii);
		prastakat.setSize(sf::Vector2f(temp1.y - temp2.y + rozmiarLinii, rozmiarLinii));
	}
	prastakat.setRotation(270);
}

void Pobierz(std::vector <sf::Vector2f>& wspolrzedne, std::string nazwa)
{
	std::fstream plik;

	plik.open(nazwa, std::ios::in);
	sf::Vector2f pom;
	if (plik.good())
	{
		 while(!plik.eof())
		{
			plik >> pom.x;
			plik >> pom.y;
			wspolrzedne.push_back(pom);
		}
	}
	plik.close();
}

void Mapa::ObliczKaty(std::vector <float>& katy, const std::vector <sf::Vector2f>& wspolrzedne)
{
	float kat;
	for (unsigned i = 1; i < wspolrzedne.size(); i++)
	{
		kat = atan2( wspolrzedne[i].y - wspolrzedne[i-1].y, wspolrzedne[i].x - wspolrzedne[i - 1].x) * PI1_180;
		if (kat < 0) kat += 360;
		kat = round(kat);
		katy.push_back(kat);
	}
}

void Mapa::SprawdzZmianeStrony(std::vector <bool>& czyPrawo, std::vector <float>& katy)
{
	czyPrawo.push_back(true);
	for (unsigned i = 1; i < katy.size(); i++)
	{
		if (katy[i] == 0.0f && katy[i - 1] == 270.0f)
		{
			czyPrawo.push_back(true);
		}
		else if (katy[i] == 270.0f && katy[i - 1] == 0.0f)
		{
			czyPrawo.push_back(false);
		}
		else
		{
			katy[i] > katy[i - 1] ? czyPrawo.push_back(true) : czyPrawo.push_back(false);
		}
	}
}

void ObliczStrony(std::vector <STR_SW>& strony, std::vector <bool>& czyPrawa, std::vector <float> katy)
{
	strony.push_back(STR_SW::Brak);
	katy[0] == 0.0f ? strony.push_back(STR_SW::N) : strony.push_back(STR_SW::S);

	int pom = static_cast<int>(strony.back());

	for (unsigned i = 1; i < czyPrawa.size(); i++)
	{
		czyPrawa[i] ? pom++ : pom--;
		if (pom > 3) pom = 0; 	else if (pom < 0) pom = 3;
		strony.push_back(STR_SW(pom));
	}
	strony.push_back(STR_SW::Brak);
}

void SprawdzZmianeLP(std::vector <bool>& czyZmiana, std::vector <bool>& czyPrawa, std::vector <STR_SW> kierunek)
{
	czyZmiana.push_back(false);

	bool pom;
	for (unsigned i = 1; i < czyPrawa.size(); i++)
	{
		pom = czyPrawa[i] == czyPrawa[i - 1] ? false : true;
		if (static_cast<int>(kierunek[i]) % 2 == 0 && pom == true)
		{
			czyZmiana[i - 1] = true;
			czyZmiana.push_back(false);
		}
		else
		{
			czyZmiana.push_back(false);
		}
	}
}

void Mapa::StworzPrastakaty(const vector<sf::Vector2f>&wspolrzedne,vector<float>&katy,vector<bool>CzyPrawa,vector<bool>& CzyZmiana,vector<STR_SW>&strony)
{
	srand((unsigned)time(NULL));
	sf::RectangleShape prastakat;
	sf::Color kolor(rand() % 64 + 15, rand() % 100 + 15, rand() % 64 + 15);

	for (unsigned i = 1; i < wspolrzedne.size(); i++)
	{
		prastakat.setFillColor(kolor);
		switch (strony[i])
		{
		case STR_SW::N:
			Polnoc(wspolrzedne[i-1], wspolrzedne[i], prastakat, strony[i-1], strony[i+1], rozmiarLinii);	break;
		case STR_SW::E:
			Wschod(wspolrzedne[i - 1], wspolrzedne[i], prastakat, strony[i - 1], strony[i + 1], rozmiarLinii);	break;
		case STR_SW::S:
			Poludnie(wspolrzedne[i - 1], wspolrzedne[i], prastakat, strony[i - 1], strony[i + 1], rozmiarLinii);	break;
		case STR_SW::W:
			Zachod(wspolrzedne[i - 1], wspolrzedne[i], prastakat, strony[i - 1], strony[i + 1], rozmiarLinii);	break;
		default:
			break;
		}
		linie.push_back(prastakat);
	}
}

void Mapa::StworzLiniePomozniecze(const std::vector<sf::Vector2f>& wspolrzedne)
{
	sf::Vertex wertex;
	wertex.color = sf::Color::Red;
	tablica.setPrimitiveType(sf::LinesStrip);

	for (unsigned i = 0; i < wspolrzedne.size(); i++)
	{
		wertex.position = sf::Vector2f(wspolrzedne[i]);
		tablica.append(wertex);
	}
}


Mapa::Mapa(int numerPoziomu)
{
	rozmiarLinii = 40;
	std::string nazwa = "Poziom " + std::to_string(numerPoziomu) + ".txt";

	std::vector <bool> CzyPrawa;
	std::vector <bool> CzyZmiana;
	std::vector <sf::Vector2f> wspolrzedne;

	Pobierz(wspolrzedne, nazwa);
	
	//StworzLiniePomozniecze(wspolrzedne);

	std::vector <float> katy;
	ObliczKaty(katy, wspolrzedne);

	SprawdzZmianeStrony(CzyPrawa, katy);

	ObliczStrony(kierunek, CzyPrawa, katy);

	SprawdzZmianeLP(CzyZmiana, CzyPrawa, kierunek);

	StworzPrastakaty(wspolrzedne, katy, CzyPrawa, CzyZmiana, kierunek);
}


void Mapa::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& i : linie)
	{
		target.draw(i);
	}

	target.draw(tablica);
	//target.draw(tablica);
}

Mapa::~Mapa()
{
}


