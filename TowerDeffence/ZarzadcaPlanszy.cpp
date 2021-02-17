#include "ZarzadcaPlanszy.h"

std::vector <bool>* ZarzadcaPlanszy::czyWygrana;

void ZarzadcaPlanszy::Aktywacja()
{
	czyWygrana = new std::vector <bool>(3);
	std::fill(czyWygrana->begin(), czyWygrana->end(), true);
}



ZarzadcaPlanszy::ZarzadcaPlanszy(sf::RenderWindow* window) : okno(window), kola(), rodzajPoziomu(NULL)
{
	okno = window;
	float r = 45;
	kola.push_back(new sf::CircleShape() );
	kola.back()->setFillColor(czyWygrana->at(0) ? sf::Color(5, 200, 5) : sf::Color(20, 190, 220));
	kola.back()->setOutlineThickness(-4);
	kola.back()->setOutlineColor(sf::Color(240, 240, 0));
	kola.back()->setOrigin(r, r);
	kola.back()->setPosition(125, 125);

	kola.push_back(new sf::CircleShape());
	kola.back()->setPosition(255, 200);

	kola.push_back(new sf::CircleShape());
	kola.back()->setPosition(425, 180);


	for (unsigned i = 1; i < kola.size(); i++)
	{
		kola[i]->setRadius(r);
		kola[i]->setFillColor(czyWygrana->at(i) ? sf::Color(5, 190, 5) : czyWygrana->at(i-1) ? sf::Color(20, 190, 220) : sf::Color(220, 5, 5));
		kola[i]->setOutlineThickness(-4);
		kola[i]->setOutlineColor(sf::Color(240, 240, 0));
		kola[i]->setOrigin(r, r);
	}
}

void ZarzadcaPlanszy::ZmienStanWybranegoPoziomnu(int poziom)
{
	czyWygrana->at(poziom) = true;
}

void ZarzadcaPlanszy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : kola)
	{
		target.draw(*i);
	}
	if (rodzajPoziomu) 
		target.draw(*rodzajPoziomu);
}

ZwracanyTypPoziomu ZarzadcaPlanszy::Zarzadzaj(sf::Event& zdarzenie)
{
	sf::Vector2f mysz = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*okno));

	if (rodzajPoziomu)
	{
		if (zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right) ||
			zdarzenie.type == zdarzenie.KeyReleased && zdarzenie.key.code == sf::Keyboard::Escape)
		{
			delete rodzajPoziomu;
			rodzajPoziomu = NULL;
		}
		else
		{
			TYP_POZIOMU typ = rodzajPoziomu->Zarzadzaj(zdarzenie, mysz);
			if (typ != TYP_POZIOMU::NIC)
			{
				return ZwracanyTypPoziomu(rodzajPoziomu->poziom, typ);
			}
		}
	}

	for (unsigned i = 0; i< kola.size(); i++)
	{
		if (kola[i]->getGlobalBounds().contains(mysz))
		{

			if (zdarzenie.type == zdarzenie.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (i == 0 || czyWygrana->at(i - 1))
				{
					if (rodzajPoziomu) delete rodzajPoziomu;
					rodzajPoziomu = new RodzajPoziomu(kola[i]->getPosition().x, kola[i]->getPosition().y + kola[i]->getRadius()*1.25f, i + 1);
				}
				return ZwracanyTypPoziomu();
			}
			else
			{
				float r = 50;
				kola[i]->setRadius(r);
				kola[i]->setOutlineThickness(-5);
				kola[i]->setOrigin(r, r);
			}
		}
		else
		{
			float r = 45;
			kola[i]->setRadius(r);
			kola[i]->setOutlineThickness(-3);
			kola[i]->setOrigin(r, r);
		}
	}
	return ZwracanyTypPoziomu();
}


ZarzadcaPlanszy::~ZarzadcaPlanszy()
{
	for (auto& i : kola)
	{
		delete i;
	}
	delete rodzajPoziomu;
}