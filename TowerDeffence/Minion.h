#pragma once
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "AnimatedCircle.h"
#include "AnimatedOutlineCircle.h"
#include <vector>
#include <ctime>
#include <math.h>
#include "Matematyka.h"
#include "PasekZycia.h"

namespace Stwory
{	
	enum class typ 
	{ 
		malyZolty,
		zolty, //sredniapredkosc, hp = 24
		bordowy, //duzaPredkosc, hp = 30
		niebieski, //malaPredkosc, hp = 90
		zielona, //duzaPredkosc, hp = 36
		fioletowy, //duzaPredkosc, hp = 18
		blekitny, //duzaPredkosc, hp = 25 //do napisania
		boss, // bardzoMalaPredkosc, hp = 1200
		szybki //----
	};
}

struct PasekZycia;

class Minion : public sf::Drawable
{
	friend PasekZycia;
protected:
	static Mapa* mapa;
	static std::vector<float> SzablonDrogiDoPrzebycia;
	Stwory::typ rodzaj;
	AnimatedOutlineCircle kolo;
	sf::Vector2f predkosc;
	float szybkosc;
	std::vector <sf::Vector2f> docelowo;
	std::vector <float> modyfikatorPredkosci;
	float drogaDoPrzebycia;
	int aktualnyCel;
	float zycie;
	float maxZycie;
	int pobieraneZycie;
	int zlotoZaZabicie;
	bool czyZabity;
	float wspolczynnik;
public:
	PasekZycia* pasekZycia;
protected:
	void WyznaczKurs();
	bool NastepnyCel();
	void WyznaczPredkosc();
	void WyznaczDrogeDoPrzebycia();

	static void Polnoc(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien);
	static void Poludnie(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien);
	static void Wschod(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien);
	static void Zachod(STR_SW kierunekPrzed, STR_SW kierunekPo, int aktualnyPrastakat, std::vector <sf::Vector2f>& docelowo, float wspolczynnik, float promien);
	//wyznacza wspolczynnik bedacy odlegloscia srodka, od boku planszy
	float WyznaczWspolczynnik(float r) const;
	void MalyZolty();
	void Zolty();
	void Bordowy();
	void Niebieski();
	void Zielona();
	void Fioletowy();
	void Boss();


public:
	static void UstawMape(Mapa* Mapa);
	virtual const AnimatedOutlineCircle& PobierzKolo() const { return kolo; }
	virtual float PobierzZycie() const { return zycie; }
	virtual int PobierzPobieraneZycie() const { return pobieraneZycie; }
	virtual bool CzyZabity() const { return czyZabity; }
	virtual int PobierzAktualnyCel() const { return aktualnyCel; }
	virtual size_t PobierzRozmiarDocelowo() const { return docelowo.size(); }
	virtual void CzyZabity(bool CzyZabity) { czyZabity = CzyZabity; }
	virtual int PobierzZlotoZaZabicie() const 	{ return zlotoZaZabicie; }
	virtual float PobierzMaxZycie() const { return maxZycie; }
	virtual bool PobierzZycie(float obrazenia); // zwraca true, jesli pocisk zabije miniona
	virtual std::vector<std::wstring> PobierzNazwe() const;
	
	Minion();
	Minion(Stwory::typ rodzaj);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Ruch(float czas);
	~Minion();
};

class SzybkiMinion : public Minion
{
protected:
	void Szybki();
public:
	SzybkiMinion();
	virtual float PobierzZycie() const { return zycie; }
	virtual int PobierzPobieraneZycie() const { return 0; }
	virtual bool CzyZabity() const { return czyZabity; }
	virtual int PobierzAktualnyCel() const { return aktualnyCel; }
	virtual size_t PobierzRozmiarDocelowo() const { return docelowo.size(); }
	virtual void CzyZabity(const bool CzyZabity) { czyZabity = CzyZabity; }
	virtual int PobierzZlotoZaZabicie() const { return 0; }
	virtual void PobierzZycie(const float& obrazenia) { zycie += obrazenia; }
	std::vector<std::wstring> PobierzNazwe() const;
};