#include "Pocisk.h"
#include "CzerwonaWieza.h"


void WyznaczPredkosc(const sf::Vector2f& dystans, sf::Vector2f& predkosc, float szybkosc)
{
	float kat = atan2f(dystans.x, dystans.y);
	predkosc.x = Matematyka::sin(kat) * szybkosc;
	predkosc.y = Matematyka::cos(kat) * szybkosc;
}

Pocisk::Pocisk(float predkosc, float Obrazenia) : szybkosc(predkosc), obrazenia(Obrazenia), czyZabity(false)
{
}

Pocisk::Pocisk() : szybkosc(0.f), obrazenia(0.f), czyZabity(false) {};

void Pocisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

Pocisk::~Pocisk()
{

}

ZwyklyPocisk::ZwyklyPocisk(const sf::Vector2f& Polozenie, Minion* target, float predkosc, float Obrazenia,const sf::Vector2f& rozmiar) : Pocisk(predkosc, Obrazenia)
{
	stwor = target;
	obrazPocisku.setSize(rozmiar);
	obrazPocisku.setOrigin(rozmiar.x / 2, rozmiar.y);
	obrazPocisku.setPosition(Polozenie);
	obrazPocisku.setFillColor(sf::Color::Red);
}

void ZwyklyPocisk::Ruch(float czas)
{
	sf::Vector2f predkosc;

	sf::Vector2f dystans = stwor->PobierzKolo().getPosition() - obrazPocisku.getPosition();

	WyznaczPredkosc(dystans, predkosc, szybkosc);

	float kat = atan(predkosc.y / predkosc.x) * PI1_180;
	obrazPocisku.setRotation(kat);

	obrazPocisku.move(predkosc.x * czas, predkosc.y * czas);
	if (obrazPocisku.getGlobalBounds().intersects(stwor->PobierzKolo().getGlobalBounds()) || stwor->CzyZabity())
	{
		stwor->PobierzZycie(obrazenia);
		czyZabity = true;
	}
}

void ZwyklyPocisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(obrazPocisku);
}


WyrzucanyPocisk::WyrzucanyPocisk(const sf::Vector2f& Polozenie, Minion* target, float predkosc, float Obrazenia) : Pocisk(predkosc, Obrazenia)
{
	stwor = target;
	obrazPocisku.setRadius(5);
	obrazPocisku.setOrigin(2.5, 2.5);
	obrazPocisku.setPosition(Polozenie);
	obrazPocisku.setFillColor(sf::Color::Red);
}

void WyrzucanyPocisk::Ruch(float czas)
{
	sf::Vector2f predkosc;

	sf::Vector2f dystans(stwor->PobierzKolo().getPosition() - obrazPocisku.getPosition());

	WyznaczPredkosc(dystans, predkosc, szybkosc);

	float kat(atan(predkosc.y / predkosc.x) * PI1_180);
	obrazPocisku.setRotation(kat);

	obrazPocisku.move(predkosc.x * czas, predkosc.y * czas);
	if (stwor->CzyZabity() || Collision::CircleCollision(obrazPocisku.getRadius(), obrazPocisku.getPosition(), stwor->PobierzKolo().getRadius(), stwor->PobierzKolo().getPosition()))
	{
		stwor->PobierzZycie(obrazenia);
		czyZabity = true;
	}
}

void WyrzucanyPocisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(obrazPocisku);
}

std::vector <Minion*>* FalistyPocisk::stwory;


FalistyPocisk::FalistyPocisk(const sf::Vector2f& Polozenie, float predkosc, float Wielkosc, float Obrazenia, float Zasieg, std::vector <Minion*>* Stwory) :
	Pocisk(predkosc, Obrazenia), 
	wielkosc(Wielkosc), 
	zasieg(Zasieg), 
	obrazPocisku(5.f, static_cast<size_t> (zasieg / 2))
{
	stwory = Stwory;
	obrazPocisku.setOrigin(5, 5);
	obrazPocisku.setPosition(Polozenie);
	obrazPocisku.setFillColor(sf::Color::Transparent);
	obrazPocisku.setOutlineColor(sf::Color(0, 140, 240));
	obrazPocisku.setOutlineThickness(Wielkosc);
}

void FalistyPocisk::Ruch(float czas)
{
	obrazPocisku.setRadius(obrazPocisku.getRadius() + szybkosc * czas);
	obrazPocisku.setOrigin(obrazPocisku.getRadius(), obrazPocisku.getRadius());
	obrazPocisku.setOutlineThickness(obrazPocisku.getOutlineThickness() / 1.6f + wielkosc);

	sf::Color kolor(obrazPocisku.getOutlineColor());
	kolor.a = sf::Uint8(255.f - 128.f * obrazPocisku.getRadius() / zasieg);

	obrazPocisku.setOutlineColor(kolor);

	for (auto& i : *stwory)
	{
		if (Collision::OutlineCircleCollision(obrazPocisku, i->PobierzKolo()))
		{
			i->PobierzZycie(i->PobierzMaxZycie() * obrazenia * 0.005f * czas + obrazenia * czas);
		}
	}
	if (obrazPocisku.getRadius() + obrazPocisku.getOutlineThickness() > zasieg)
	{
		czyZabity = true;
	}
}

void FalistyPocisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(obrazPocisku);
}

PociskWzmacniajacy::PociskWzmacniajacy(const sf::Vector2f& Polozenie, Minion* target, float predkosc, float Obrazenia, const sf::Vector2f& rozmiar,
	CzerwonaWieza* wiezaa, float ZwiekszenieObrazen) : ZwyklyPocisk(Polozenie, target, predkosc, Obrazenia, rozmiar)
{
	wieza = wiezaa;
	zwiekszenieObrazen = ZwiekszenieObrazen;
}
void PociskWzmacniajacy::Ruch(float czas)
{
	if (obrazPocisku.getGlobalBounds().intersects(stwor->PobierzKolo().getGlobalBounds()) || stwor->CzyZabity())
	{
		if (stwor->PobierzZycie(obrazenia)) wieza->ZwiekszObrazenia(zwiekszenieObrazen);
		czyZabity = true;
	}

	sf::Vector2f predkosc;

	sf::Vector2f dystans = stwor->PobierzKolo().getPosition() - obrazPocisku.getPosition();

	WyznaczPredkosc(dystans, predkosc, szybkosc);

	float kat = atan(predkosc.y / predkosc.x) * PI1_180;
	obrazPocisku.setRotation(kat);

	obrazPocisku.move(predkosc.x * czas, predkosc.y * czas);
}
