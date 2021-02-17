#include "ZarzadcaJedzenia.h"

using namespace jedzenie;



Modyfikatory::Modyfikatory(float Promien, sf::Vector2f Pozycja, float Wartosc, float CzasDzialania) 
	: promien(Promien), poz(Pozycja), wartosc(Wartosc), czas(CzasDzialania)
{
    tab = new float[int(promien)+1];
    Promien = promien * promien;
    for (int x = 0; x <= promien; x++)
    {
        tab[x] = sqrt(Promien - int(x * x));
    }
};

float Modyfikatory::PobierzWartosc(int index) const
{
	return tab[index];
}

Modyfikatory::~Modyfikatory()
{
	delete[] tab;
}
sf::Color ZarzadcaJedzenia::koloruj(float wartosc) const
{
	float wspolczynnik;
#ifdef _DEBUG
	if (wartosc < niebieski)
	{
		std::cout << "Error!   File: " << __FILE__ << "Line " << __LINE__ <<" Value out of limits"<< std::endl;
	}else
#endif // DEBUG
	if (wartosc < zielony)
	{
		wspolczynnik = wartosc / (zielony);
		return sf::Color(0, static_cast<sf::Uint8> (wspolczynnik * 255), static_cast<sf::Uint8> ((1.f - wspolczynnik) * 255));
	}
	else if (wartosc < czerwony)
	{
		wspolczynnik = wartosc / (czerwony);
		return sf::Color(static_cast<sf::Uint8> (wspolczynnik * 255), static_cast<sf::Uint8> ((1.f - wspolczynnik) * 255), 0);
	}
	else if (wartosc > czarny)
	{
		wspolczynnik = wartosc / (czarny);
		return sf::Color(static_cast<sf::Uint8> ((1.f-wspolczynnik) * 255), 0, 0);
	}
#ifdef _DEBUG
	else std::cout << "Error!   File: " << __FILE__ << "Line " << __LINE__ << " Value out of limits" << std::endl;
#endif // DEBUG
	return sf::Color(255, 255, 255);
}

ZarzadcaJedzenia::ZarzadcaJedzenia(sf::Vector2f rozdzielczosc, float wartoscPodstawowa)
{
	mapa.resize(static_cast<unsigned>(rozdzielczosc.x));
	for (auto& i : mapa) 
	{ 
		i.resize(static_cast<unsigned>(rozdzielczosc.y));
		std::fill(i.begin(), i.end(), wartoscPodstawowa);
	}
	zoobrazowanie.setPrimitiveType(sf::PrimitiveType::Points);
	sf::Vertex v;
	for (unsigned i = 0; i < mapa.size(); i++) //ZALORZENIE ze mapa jest prostakatna
	{
		for (unsigned j = 0; j < mapa[0].size(); j++)
		{
			v.position = sf::Vector2f(static_cast<float>(i), static_cast<float>(j));
			v.color = koloruj(mapa[static_cast<size_t>(v.position.x)][static_cast<size_t>(v.position.y)]);
			zoobrazowanie.append(v);
		}
	}
}


void ZarzadcaJedzenia::Modyfikuj(const Modyfikatory& mod)
{
	for (int i = 0; i <= int(mod.promien); i++)
	{
		mapa[static_cast<size_t>(mod.poz.x + i)][static_cast<size_t>(mod.poz.y + mod.PobierzWartosc(i))] += mod.wartosc;
		mapa[static_cast<size_t>(mod.poz.x + i)][static_cast<size_t>(mod.poz.y - mod.PobierzWartosc(i))] += mod.wartosc;
		mapa[static_cast<size_t>(mod.poz.x - i)][static_cast<size_t>(mod.poz.y + mod.PobierzWartosc(i))] += mod.wartosc;
		mapa[static_cast<size_t>(mod.poz.x - i)][static_cast<size_t>(mod.poz.y - mod.PobierzWartosc(i))] += mod.wartosc;
	}
}

void ZarzadcaJedzenia::Cofnij(const Modyfikatory& mod)
{
	for (int i = 0; i <= int(mod.promien); i++)
	{
		mapa[static_cast<size_t>(mod.poz.x + i)][static_cast<size_t>(mod.poz.y + mod.PobierzWartosc(i))] -= mod.wartosc;
		mapa[static_cast<size_t>(mod.poz.x + i)][static_cast<size_t>(mod.poz.y - mod.PobierzWartosc(i))] -= mod.wartosc;
		mapa[static_cast<size_t>(mod.poz.x - i)][static_cast<size_t>(mod.poz.y + mod.PobierzWartosc(i))] -= mod.wartosc;
		mapa[static_cast<size_t>(mod.poz.x - i)][static_cast<size_t>(mod.poz.y - mod.PobierzWartosc(i))] -= mod.wartosc;
		zoobrazowanie[static_cast<size_t>((mod.poz.x + i) * mapa[0].size() + mod.poz.y + mod.PobierzWartosc(i))].color = koloruj(mapa[static_cast<size_t>(mod.poz.x + i)][static_cast<size_t>(mod.poz.y + mod.PobierzWartosc(i))]);
		zoobrazowanie[static_cast<size_t>((mod.poz.x + i) * mapa[0].size() + mod.poz.y - mod.PobierzWartosc(i))].color = koloruj(mapa[static_cast<size_t>(mod.poz.x + i)][static_cast<size_t>(mod.poz.y - mod.PobierzWartosc(i))]);
		zoobrazowanie[static_cast<size_t>((mod.poz.x - i) * mapa[0].size() + mod.poz.y + mod.PobierzWartosc(i))].color = koloruj(mapa[static_cast<size_t>(mod.poz.x - i)][static_cast<size_t>(mod.poz.y + mod.PobierzWartosc(i))]);
		zoobrazowanie[static_cast<size_t>((mod.poz.x - i) * mapa[0].size() + mod.poz.y - mod.PobierzWartosc(i))].color = koloruj(mapa[static_cast<size_t>(mod.poz.x - i)][static_cast<size_t>(mod.poz.y - mod.PobierzWartosc(i))]);
	}
}



void ZarzadcaJedzenia::DodajZdarzenie(float promien,const sf::Vector2f& pozycja, float wartosc, float czasDzialania)
{
	modyfikatory.push_back(new jedzenie::Modyfikatory(promien, pozycja, wartosc, czasDzialania));
	Modyfikuj(*modyfikatory.back());
}

void ZarzadcaJedzenia::ZarzadcaJedzenia::Ruch(float time)
{
	bool zmiana = false;
	for (size_t i = 0; i < modyfikatory.size(); i++)
	{
		if(modyfikatory[i]->czas )
		modyfikatory[i]->czas -= time;
		if (modyfikatory[i]->czas < 0.f)
		{
			Cofnij(*modyfikatory[i]);
			delete modyfikatory[i];
			modyfikatory.erase(modyfikatory.begin() + i);
		}
	}
}

void ZarzadcaJedzenia::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(zoobrazowanie);
}

ZarzadcaJedzenia::~ZarzadcaJedzenia()
{
	for (size_t i = 0; i < modyfikatory.size(); i++)
	{
		delete modyfikatory[i];
	}
}
