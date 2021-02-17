#include "Minion.h"

Mapa* Minion::mapa;

constexpr float bardzoMalaPredkosc = 65.f;
constexpr float malaPredkosc = 80.f;
constexpr float sredniaPredkosc = 100.f;
constexpr float duzaPredkosc = 120.f;
constexpr float bardzoDuzaPredkosc = 160.f;
constexpr float ogromnaPredkosc = 200.f;

////////////////////////////////////////////////////

float dlugosc(sf::Vector2f& wektor)
{
	return sqrt(pow(wektor.x, 2) + pow(wektor.y, 2));
}

std::vector<float> Minion::SzablonDrogiDoPrzebycia;

void Minion::UstawMape(Mapa* mapaa)
{
	mapa = mapaa;

	float promien = 12;
	float wspolczynnik = (mapa->rozmiarLinii - promien * 2) / 2;
	int ilosc;
	float odcinek;

	std::vector<sf::Vector2f> pomocniczy;
	for (unsigned aktualnyPrastakat = 1; aktualnyPrastakat <= mapa->linie.size(); aktualnyPrastakat++)
	{
		odcinek = 0;
		ilosc = pomocniczy.size();
		switch (mapa->kierunek[aktualnyPrastakat])
		{
		case STR_SW::N:
			Polnoc(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, pomocniczy, wspolczynnik, promien); break;
		case STR_SW::E:
			Wschod(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, pomocniczy, wspolczynnik, promien); break;
		case STR_SW::S:
			Poludnie(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, pomocniczy, wspolczynnik, promien); break;
		case STR_SW::W:
			Zachod(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, pomocniczy, wspolczynnik, promien); break;
		default:
			break;
		}
		for (unsigned i = ilosc; i < pomocniczy.size(); i++)
		{
			odcinek += abs(pomocniczy[i].x);
			odcinek += abs(pomocniczy[i].y);
		}
		SzablonDrogiDoPrzebycia.push_back(odcinek);
	}
}


Minion::Minion() : rodzaj(Stwory::typ::malyZolty), kolo(), predkosc(), szybkosc(), docelowo(), modyfikatorPredkosci(), drogaDoPrzebycia(), aktualnyCel(), zycie(),
maxZycie(), pobieraneZycie(), zlotoZaZabicie(), czyZabity(),  pasekZycia(NULL), wspolczynnik() {}

Minion::Minion(Stwory::typ Rodzaj)
{
	rodzaj = Rodzaj;
	pobieraneZycie = 1;
	pasekZycia = new PasekZycia();
	switch (Rodzaj)
	{
	case Stwory::typ::malyZolty:
		MalyZolty();
		break;
	case Stwory::typ::zolty:
		Zolty(); 
		break;
	case Stwory::typ::bordowy:
		Bordowy(); 
		break;
	case Stwory::typ::niebieski:
		Niebieski();
		break;
	case Stwory::typ::zielona:
		Zielona();
		break;
	case Stwory::typ::fioletowy:
		Fioletowy();
		break;
	case Stwory::typ::boss:
		Boss();
		break;
	default:
		break;
	}
	maxZycie = zycie;
	pasekZycia->Ustaw(this);
	aktualnyCel = 0;
	czyZabity = false;
	WyznaczKurs();
	WyznaczPredkosc();
	WyznaczDrogeDoPrzebycia();
}

float Minion::WyznaczWspolczynnik(float r) const
{
	float pom = mapa->linie[0].getSize().y - 3 * r;
	return (int)pom ? r / 2 + rand() % int(mapa->linie[0].getSize().y - 3 * r) * (pom > 0 ? 1 : -1) : pom;
}

void Minion::MalyZolty()
{
	float r = 10.0f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 8;
	scheme.inlineColor = sf::Color(190, 190, 0);
	scheme.maxWave = r / 20;
	scheme.outlineColor = sf::Color(50, 30, 120);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;

	kolo.create(scheme);
	szybkosc = sredniaPredkosc;
	zycie = 9.f;
	zlotoZaZabicie = 8;
}

//Œrednioszybki minion, daj¹cy du¿o z³ota za zabicie, posiadaj¹cy ma³¹ iloœæ ¿ycia
void Minion::Zolty()
{
	float r = 13.0f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 8;
	scheme.inlineColor = sf::Color(190, 190, 0);
	scheme.maxWave = r / 20;
	scheme.outlineColor = sf::Color(50, 30, 120);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;

	kolo.create(scheme);
	szybkosc = sredniaPredkosc;
	zycie = 16.f;
	zlotoZaZabicie = 10;
}

//Szybki minion, daj¹cy ma³o z³ota za zabicie, posiadaj¹cy ma³¹ iloœæ ¿ycia
void Minion::Bordowy()
{
	float r = 12.f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 8;
	scheme.inlineColor = sf::Color(140, 15, 15);
	scheme.maxWave = r / 20;
	scheme.outlineColor = sf::Color(200, 50, 20);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;
	kolo.create(scheme);
	szybkosc = duzaPredkosc;
	zycie = 30.0f;
	zlotoZaZabicie = 6;
}

//Powolny minion, daj¹cy œredni¹ iloœæ z³ota za zabicie, posiadaj¹cy du¿¹ iloœæ ¿ycia
void Minion::Niebieski()
{
	float r = 17.0f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 8;
	scheme.inlineColor = sf::Color(60, 60, 200);
	scheme.maxWave = r / 20;
	scheme.outlineColor = sf::Color(200, 50, 20);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;
	kolo.create(scheme);
	szybkosc = malaPredkosc;
	zycie = 90.0f;
	zlotoZaZabicie = 12;
}

//Bardzo szybki minion, daj¹cy œredni¹ iloœæ z³ota za zabicie, posiadaj¹cy œredni¹ iloœæ ¿ycia
void Minion::Zielona()
{
	float r = 13.0f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 8;
	scheme.inlineColor = sf::Color(30, 230, 30);
	scheme.maxWave = r / 20;
	scheme.outlineColor = sf::Color(200, 50, 20);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;
	kolo.create(scheme);
	szybkosc = duzaPredkosc;
	zycie = 36.0f;
	zlotoZaZabicie = 5;
}

// Szybki minion, daj¹cy ma³¹ iloœæ z³ota za zabicie, posiadaj¹cy mal¹ iloœæ ¿ycia
void Minion::Fioletowy()
{
	float r = 11.0f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 8;
	scheme.inlineColor = sf::Color(130, 10, 150);
	scheme.maxWave = r / 20;
	scheme.outlineColor = sf::Color(200, 50, 20);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;
	kolo.create(scheme);
	szybkosc = duzaPredkosc;
	zycie = 18.0f;
	zlotoZaZabicie = 3;
}

void Minion::Boss()
{
	float r = 20.0f;
	wspolczynnik = WyznaczWspolczynnik(r);
	AnimatedOutlineCircleStruct scheme;
	scheme.animationAmount = 14;
	scheme.inlineColor = sf::Color(230, 230, 240);
	scheme.maxWave = r / 30;
	scheme.outlineColor = sf::Color(20, 20, 40);
	scheme.outlineThickness = r / 4;
	scheme.position.x = mapa->linie[0].getPosition().x + r + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180);
	scheme.position.y = mapa->linie[0].getPosition().y + r + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180);
	scheme.radius = r;
	kolo.create(scheme);
	szybkosc = bardzoMalaPredkosc;
	zycie = 1200.0f;
	pobieraneZycie = 5;
	zlotoZaZabicie = 150;
}


void Minion::Polnoc(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien)
{
	sf::Vector2f pom;
	if (kierunekPrzed ==  STR_SW::E && kierunekPo ==  STR_SW::W)
	{
		pom.x = mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if(kierunekPrzed ==  STR_SW::W && kierunekPo ==  STR_SW::E)
	{

		pom.x = mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0.0f;
		docelowo.push_back(pom);

	}
	else if (kierunekPrzed ==  STR_SW::E && kierunekPo ==  STR_SW::E)
	{
		pom.x = mapa->linie[aktualnyPrastakat-1].getSize().x - mapa->rozmiarLinii;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if(kierunekPrzed ==  STR_SW::W && kierunekPo ==  STR_SW::W)
	{
		pom.x = mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if(kierunekPrzed ==  STR_SW::Brak && kierunekPo ==  STR_SW::E)
	{
		pom.x = mapa->linie[aktualnyPrastakat-1].getSize().x - mapa->rozmiarLinii;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::Brak && kierunekPo ==  STR_SW::W)
	{
		pom.x = mapa->linie[aktualnyPrastakat - 1].getSize().x;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
}

void Minion::Poludnie(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien)
{
	sf::Vector2f pom;
	if (kierunekPrzed ==  STR_SW::E && kierunekPo ==  STR_SW::W)
	{
		pom.x = -mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::W && kierunekPo ==  STR_SW::E)
	{
		pom.x = -mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::E && kierunekPo ==  STR_SW::E)
	{
		pom.x = -mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::W && kierunekPo ==  STR_SW::W)
	{
		pom.x = -mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else
	{
		pom.x = -mapa->linie[aktualnyPrastakat-1].getSize().x;
		pom.y = 0;
		docelowo.push_back(pom);
	}
}

void Minion::Wschod(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien)
{
	sf::Vector2f pom;
	if (kierunekPrzed ==  STR_SW::N && kierunekPo ==  STR_SW::S)
	{
		pom.x = mapa->rozmiarLinii - promien * 2 - wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);
		
		pom.x = 0;
		pom.y = mapa->linie[aktualnyPrastakat-1].getSize().x - promien * 2 - wspolczynnik * 2;
		docelowo.push_back(pom);

		pom.x = -mapa->rozmiarLinii + wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::S && kierunekPo ==  STR_SW::N)
	{
		pom.x = -wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);

		pom.x = 0.0f;
		pom.y = mapa->linie[aktualnyPrastakat-1].getSize().x - 2 * mapa->rozmiarLinii + promien * 2 + wspolczynnik * 2;
		docelowo.push_back(pom);

		pom.x = promien * 2.0f + wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::N && kierunekPo ==  STR_SW::N)
	{
		pom.x = mapa->rozmiarLinii - 2 * promien - wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);

		pom.x = 0;
		pom.y = mapa->linie[aktualnyPrastakat-1].getSize().x - mapa->rozmiarLinii;
		docelowo.push_back(pom);

		pom.x = promien * 2 + wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::S && kierunekPo ==  STR_SW::S)
	{
		pom.x = -wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);

		pom.x = 0;
		pom.y = mapa->linie[aktualnyPrastakat-1].getSize().x - mapa->rozmiarLinii;
		docelowo.push_back(pom);

		pom.x = -mapa->rozmiarLinii + wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);
	}
	else if(kierunekPrzed ==  STR_SW::S && kierunekPo ==  STR_SW::Brak )
	{
		pom.x = - wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);

		pom.x = 0;
		pom.y = mapa->linie[aktualnyPrastakat-1].getSize().x -  mapa->rozmiarLinii;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::N && kierunekPo ==  STR_SW::Brak)
	{
		pom.x = mapa->rozmiarLinii - promien * 2 - wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);

		pom.x = 0;
		pom.y = mapa->linie[aktualnyPrastakat - 1].getSize().x - promien * 2 - wspolczynnik * 2;
		docelowo.push_back(pom);

		pom.x = -mapa->rozmiarLinii + wspolczynnik;
		pom.y = 0;
		docelowo.push_back(pom);
	}
}

void Minion::Zachod(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien)
{
	sf::Vector2f pom;
	if (kierunekPrzed ==  STR_SW::N && kierunekPo ==  STR_SW::S)
	{
		pom.x =   + wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);

		pom.x = 0.0f;
		pom.y = -mapa->linie[aktualnyPrastakat-1].getSize().x + 2 * mapa->rozmiarLinii - 2 * wspolczynnik - promien * 2;
		docelowo.push_back(pom);

		pom.x = -promien * 2 - wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::S && kierunekPo ==  STR_SW::N)
	{
		pom.x = -mapa->rozmiarLinii + promien * 2 + wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);

		pom.x = 0.0f;
		pom.y = -mapa->linie[aktualnyPrastakat-1].getSize().x + mapa->rozmiarLinii;
		docelowo.push_back(pom);

		pom.x = -promien * 2 - wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::N && kierunekPo ==  STR_SW::N)
	{
		pom.x = wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);

		pom.x = 0.0f;
		pom.y = -mapa->linie[aktualnyPrastakat-1].getSize().x + mapa->rozmiarLinii;
		docelowo.push_back(pom);

		pom.x = mapa->rozmiarLinii - wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else if (kierunekPrzed ==  STR_SW::S && kierunekPo ==  STR_SW::S)
	{
		pom.x = -mapa->rozmiarLinii + promien * 2.f + wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);

		pom.x = 0.0f;
		pom.y = -mapa->linie[aktualnyPrastakat-1].getSize().x + mapa->rozmiarLinii;
		docelowo.push_back(pom);

		pom.x = -promien * 2.0f - wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
	else
	{
		pom.x = -mapa->rozmiarLinii + promien * 2.0f + wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);

		pom.x = 0.0f;
		pom.y = -mapa->linie[aktualnyPrastakat-1].getSize().x + mapa->rozmiarLinii;
		docelowo.push_back(pom);

		pom.x = -promien * 2.0f - wspolczynnik;
		pom.y = 0.0f;
		docelowo.push_back(pom);
	}
}


void Minion::WyznaczPredkosc()
{
	szybkosc *= modyfikatorPredkosci[aktualnyCel];
	float kat = normaliseRad(atan2f(docelowo[aktualnyCel].x, docelowo[aktualnyCel].y));
	predkosc.x = Matematyka::sin(kat) * szybkosc;
	predkosc.y = Matematyka::cos(kat) * szybkosc;
}

void Minion::WyznaczDrogeDoPrzebycia()
{
	drogaDoPrzebycia = dlugosc(docelowo[aktualnyCel]);
}

void Minion::WyznaczKurs()
{
	int ilosc;
	float dlugoscOdcinkaPrastakata = 0;
	for (unsigned aktualnyPrastakat = 1; aktualnyPrastakat <= mapa->linie.size(); aktualnyPrastakat++)
	{
		ilosc = docelowo.size();
		dlugoscOdcinkaPrastakata = 0;
		switch (mapa->kierunek[aktualnyPrastakat])
		{
		case STR_SW::N:
			Polnoc(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, docelowo, wspolczynnik, kolo.getRadius()); break;
		case STR_SW::E:
			Wschod(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, docelowo, wspolczynnik, kolo.getRadius()); break;
		case STR_SW::S:
			Poludnie(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, docelowo, wspolczynnik, kolo.getRadius()); break;
		case STR_SW::W:
			Zachod(mapa->kierunek[aktualnyPrastakat - 1], mapa->kierunek[aktualnyPrastakat + 1], aktualnyPrastakat, docelowo, wspolczynnik, kolo.getRadius()); break;
		default:
			break;
		}
		for (unsigned i = ilosc; i < docelowo.size(); i++)
		{
			if (!docelowo[i].x && !docelowo[i].y)
			{
				docelowo.erase(docelowo.begin() + i);
				i--;
			}
			else
			{
				dlugoscOdcinkaPrastakata += abs(docelowo[i].x);
				dlugoscOdcinkaPrastakata += abs(docelowo[i].y);
			}
		}
		for (unsigned i = 0; i < docelowo.size() - ilosc; i++)
		{
			modyfikatorPredkosci.push_back(dlugoscOdcinkaPrastakata / SzablonDrogiDoPrzebycia[aktualnyPrastakat - 1]);
		}
	}
}

bool Minion::NastepnyCel()
{
	szybkosc /= modyfikatorPredkosci[aktualnyCel];
	aktualnyCel++;
	if (aktualnyCel != docelowo.size())
	{
		WyznaczPredkosc();
		WyznaczDrogeDoPrzebycia();
		return true;
	}
	return false;
}

bool Minion::PobierzZycie(float obrazenia)
{
	bool czyZyje = (zycie > 0);
	zycie -= obrazenia;
	return (czyZyje == true && zycie <= 0);
}

std::vector<std::wstring> Minion::PobierzNazwe() const
{
	std::vector <std::wstring> wektor;
	switch (rodzaj)
	{
	case Stwory::typ::zolty:
		wektor.push_back(L"¯ó³ty");
		wektor.push_back(L"stwór");
		break;
	case Stwory::typ::bordowy:
		wektor.push_back(L"Bordowy");
		wektor.push_back(L"stwór");
		break;
	case Stwory::typ::niebieski:
		wektor.push_back(L"Niebieski");
		wektor.push_back(L"stwór");
		break;
	case Stwory::typ::zielona:
		wektor.push_back(L"Zielony");
		wektor.push_back(L"stwór");
		break;
	case Stwory::typ::fioletowy:
		wektor.push_back(L"Fioletowy");
		wektor.push_back(L"stwór");
		break;
		
	case Stwory::typ::boss:
		wektor.push_back(L"Boss");
		break;
	default:
		wektor.push_back(L"B³¹d");
		break;
	}

	return wektor;
}


void Minion::Ruch(float czas)
{
	if (!czyZabity)
	{
		if (szybkosc * czas < drogaDoPrzebycia)
		{
			kolo.move(predkosc * czas);
			drogaDoPrzebycia -= szybkosc * czas;
		}
		else
		{
			float czasDoPrzebyciaOdleglosci = drogaDoPrzebycia / szybkosc;
			czas -= czasDoPrzebyciaOdleglosci;
			kolo.move(czasDoPrzebyciaOdleglosci * predkosc);
			do
			{
				if (NastepnyCel())
				{
					czasDoPrzebyciaOdleglosci = drogaDoPrzebycia / szybkosc;
					if (czasDoPrzebyciaOdleglosci > czas)
					{
						kolo.move(predkosc * czas);
						drogaDoPrzebycia -= czas * szybkosc;
						break;
					}
					else
					{
						kolo.move(predkosc * czasDoPrzebyciaOdleglosci);
						czas -= czasDoPrzebyciaOdleglosci;
					}

				}
				else
				{
					break;
				}
			} while (true);
		}
	}
	pasekZycia->Ruch();
	kolo.motion(czas);
}

void Minion::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(kolo);
	target.draw(*pasekZycia);
}

Minion::~Minion()
{
	delete pasekZycia;
}

////////////////////////////////////////////////////////////
void SzybkiMinion::Szybki()
{
	float r = 20.0f;
	kolo.setFillColor(sf::Color(240, 240, 250));
	kolo.setRadius(r);
	kolo.setOrigin(r, r);
	sf::Vector2f pozycja = mapa->linie[0].getPosition() + sf::Vector2f(r, r);
	wspolczynnik = 5.f;
	kolo.setPosition(pozycja.x + wspolczynnik * Matematyka::sin(mapa->linie[0].getRotation() * PI_180), pozycja.y + wspolczynnik * Matematyka::cos(mapa->linie[0].getRotation() * PI_180));
	szybkosc = 120.03f;
	zycie = 0;
}

SzybkiMinion::SzybkiMinion() : Minion()
{
	Szybki();
	pasekZycia->Ustaw(this);
	aktualnyCel = 0;
	czyZabity = false;
	WyznaczKurs();
	WyznaczPredkosc();
}


std::vector<std::wstring> SzybkiMinion::PobierzNazwe() const
{
	std::vector<std::wstring> wektor(2);
	wektor[0] = L"Szybki";
	wektor[1] = L"Minion";
	return wektor;
}