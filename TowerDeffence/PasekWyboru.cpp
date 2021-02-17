#include "PasekWyboru.h"

using std::to_wstring;

const sf::Vector2f rozmiarIkony = sf::Vector2f(50, 50);



PasekWyboru::PasekWyboru(): 
	tlo(sf::Vector2f(131, 600)),
	zycie(10),
	zloto(0),
	tZycie(),
	tZloto(),
	tempo(1.f),
	tTempo(L"Tempo  " + funkcje::ZaokraglijZPrzecinkiem(tempo), StatyczneTekstury::getFont(), 12u),
	okno(NULL),
	zarzadcaFal(NULL),
	wybranaBudowa(NULL),
	wybranaWieza(NULL),
	wybranyStwor(NULL),
	esc(NULL)
{
	tlo.setFillColor(sf::Color(15, 10, 5));
	tlo.setPosition(liniaMarginesu, 0);

	tTempo.setFillColor(sf::Color(250, 250, 250));
	tTempo.setPosition(margines, 580);
}

void PasekWyboru::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tlo);
	target.draw(tZloto);
	target.draw(tTempo);

	if (esc)
	{
		target.draw(*esc, states);
	}
	else if (wybranaBudowa)
	{
		target.draw(*wybranaBudowa, states);
	}

	else if (wybranaWieza)
	{
		target.draw(*wybranaWieza, states);
	}
	else if (wybranyStwor)
	{
		target.draw(*wybranyStwor, states);
	}
	target.draw(wyborWiez, states);
}
void PasekWyboru::ZmienTempo(bool zmiana)
{
	float roznica = 0.5f * (zmiana ? 1.0f : -1.0f);

	tempo += roznica;

	if (tempo < 0.f || tempo > 5.f)	tempo -= roznica;

	tTempo.setString(L"Tempo  " + funkcje::ZaokraglijZPrzecinkiem(tempo));
}
PasekWyboru::~PasekWyboru()
{
	if (wybranaWieza) delete wybranaWieza;
	if (wybranyStwor) delete wybranyStwor;
	if (wybranaBudowa) delete wybranaBudowa;
	if (esc) delete esc;
}

//wybranaWieza
WybranaWieza& PasekWyboru::PobierzWybranaWieza() const
{ 
	return *wybranaWieza; 
}
bool PasekWyboru::CzyWybranaWieza() const 
{ 
	return wybranaWieza ? true : false; 
}
void PasekWyboru::StworzWybranaWieza(Wieza* wieza) 
{ 
	wybranaWieza = new WybranaWieza(wieza, zloto); 
}
void PasekWyboru::UsunWybranaWieza() 
{ 
	delete wybranaWieza; 
	wybranaWieza = NULL; 
}

//wybranaBudowa
bool PasekWyboru::CzyWybranaBudowa() const 
{ 
	return wybranaBudowa ? true : false; 
}
WybranaBudowa& PasekWyboru::PobierzWybranaBudowa() const 
{ 
	return *wybranaBudowa; 
}
void PasekWyboru::StworzWybranaBudowa(TYP_WIEZY i) 
{ 
	sf::Vector2f pozycja = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*okno));
	wybranaBudowa = new WybranaBudowa(i, pozycja); 
}
void PasekWyboru::UsunWybranaBudowa() 
{ 
	delete wybranaBudowa; 
	wybranaBudowa = NULL; 
}
//wybranyStwor
bool PasekWyboru::CzyWybranyStwor() const 
{ 
	return wybranyStwor ? true : false; 
}
void PasekWyboru::StworzWybranyStwor(Minion* Stwor) 
{ 
	wybranyStwor = new WybranyStwor(Stwor); 
}
void PasekWyboru::UsunWybranyStwor() 
{ 
	delete wybranyStwor; 
	wybranyStwor = NULL; 
}
WybranyStwor& PasekWyboru::PobierzWybranyStwor() 
{ 
	return *wybranyStwor; 
};

//esc
bool PasekWyboru::CzyEsc() const 
{ 
	return esc ? true : false; 
}
void PasekWyboru::StworzEsc() 
{ 
	esc = new Esc(); 
}
void PasekWyboru::UsunEsc() 
{ 
	delete esc; 
	esc = NULL; 
}
Esc& PasekWyboru::PobierzEsc() const 
{ 
	return *esc; 
}
//////////////////////////////////////////

void PasekWyboru::ZaaktualizujWskaznikOkna(sf::RenderWindow* wskaznik) 
{ 
	okno = wskaznik; 
};
void PasekWyboru::ZaaktualizujWskaznikZarzadcyFal(Wave* wskaznik) 
{ 
	zarzadcaFal = wskaznik; 
};

int* PasekWyboru::PobierzWskaznikZycia()
{ 
	return &zycie; 
};
int* PasekWyboru::PobierzWskaznikZlota() 
{ 
	return &zloto; 
};
int PasekWyboru::PobierzZycie() const 
{ 
	return 0; 
};
int PasekWyboru::PobierzZloto() const 
{ 
	return zloto; 
};
float PasekWyboru::PobierzTempo() const
{
	return tempo;
}

//////////////////NORMALNY
NormalnyPasekWyboru::NormalnyPasekWyboru() : PasekWyboru()
{
	zloto = 500;
	zycieMax = 50;
	zycie = zycieMax;

	tZloto.setCharacterSize(16u);
	tZloto.setFont(StatyczneTekstury::getFont());
	tZloto.setFillColor(sf::Color(240, 240, 60));
	tZloto.setPosition(margines, 245);

	tFala.setCharacterSize(16u);
	tFala.setFont(StatyczneTekstury::getFont());
	tFala.setFillColor(sf::Color(240, 240, 60));
	tFala.setPosition(margines, 268);

	tZycie.setCharacterSize(16u);
	tZycie.setFont(StatyczneTekstury::getFont());
	tZycie.setFillColor(sf::Color(250, 85, 85));
	tZycie.setPosition(margines, 291);
}

void NormalnyPasekWyboru::Ruch()
{
	if (zycie < 0) zycie = 0;	
	if (wybranaWieza) wybranaWieza->Ruch();
	if(CzyWybranaWieza()) wybranaWieza->SprawdzZloto();
	else if (wybranyStwor)
	{
		if (!wybranyStwor->Ruch())
		{
			delete wybranyStwor;
			wybranyStwor = NULL;
		}
	}

	tZloto.setString(L"Z³oto: " + std::to_wstring(zloto));

	tFala.setString(L"Fala " + to_wstring(zarzadcaFal->GetWaveNubmer()) + L"/"
		+ to_wstring(zarzadcaFal->GetMaxWaveNumber()));

	tZycie.setString(L"¯ycie " + to_wstring(zycie) + L"/" + to_wstring(zycieMax));
}
void NormalnyPasekWyboru::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (wybranaWieza)
	{
		wybranaWieza->RysojZasieg(target);
	}
	target.draw(tlo);
	target.draw(tZloto);
	target.draw(tFala);
	target.draw(tZycie);
	target.draw(tTempo);
	if (wybranaWieza)
	{
		target.draw(*wybranaWieza);
	}
	else if (wybranyStwor)
	{
		target.draw(*wybranyStwor);
	}
	if (esc)
	{
		target.draw(*esc);
	}
	if (wybranaBudowa)
	{
		target.draw(*wybranaBudowa);
	}
	target.draw(wyborWiez, states);
}
int NormalnyPasekWyboru::PobierzZycie() const 
{ 
	return zycie; 
};
int NormalnyPasekWyboru::PobierzZloto() const 
{ 
	return zloto; 
};

///////////////////SZYBKI
SzybkiPasekWyboru::SzybkiPasekWyboru() : PasekWyboru()
{
	esc = new Esc();
	tempo = 1.0f;
	zycie = 0;
	zloto = 99999;

	tWynik.setCharacterSize(30u);
	tWynik.setString(L"Wynik");
	tWynik.setFont(StatyczneTekstury::getFont());
	tWynik.setOrigin(tWynik.getGlobalBounds().width / 2, 0);
	tWynik.setFillColor(sf::Color(60, 180, 240));
	tWynik.setPosition(srodekMarginesu, 300);


	tZycie.setCharacterSize(25u);
	tZycie.setString(std::to_wstring(zycie));
	tZycie.setFont(StatyczneTekstury::getFont());
	tZycie.setOrigin(tWynik.getGlobalBounds().width / 2, 0);
	tZycie.setFillColor(sf::Color(60, 180, 240));
	tZycie.setPosition(srodekMarginesu, 340);
}
void SzybkiPasekWyboru::Ruch()
{
	sf::Vector2f polozenie = sf::Vector2f(sf::Mouse::getPosition(*okno));

	tZycie.setString(std::to_wstring(zycie));
	tZycie.setOrigin(tZycie.getGlobalBounds().width / 2, 0);

	if (wybranaBudowa)
	{
		wybranaBudowa->podglad->UstawPozycje(polozenie.x, polozenie.y);
	}
	else if (wybranyStwor)
	{
		if (!wybranyStwor->Ruch())
		{
			delete wybranyStwor;
			wybranyStwor = NULL;
		}
	}
}
void SzybkiPasekWyboru::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (wybranaWieza)
	{
		wybranaWieza->RysojZasieg(target);
	}

	else if (wybranyStwor)
	{
		target.draw(*wybranyStwor, states);
	}
	if (esc)
	{
		target.draw(*esc, states);
	}
	target.draw(tlo, states);
	target.draw(tZloto, states);
	target.draw(tZycie, states);
	target.draw(tTempo, states);
	target.draw(wyborWiez, states);
	if (wybranaWieza)
	{
		target.draw(*wybranaWieza, states);
	}
	if (wybranaBudowa)
	{
		target.draw(*wybranaBudowa, states);
	}
}
SzybkiPasekWyboru::~SzybkiPasekWyboru()
{
}
void SzybkiPasekWyboru::StworzWybranaWieza(Wieza* wieza)
{ 
	wybranaWieza = new SzybkaWybranaWieza(wieza, PasekWyboru::zloto);
}