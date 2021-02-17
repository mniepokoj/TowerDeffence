#include "ZarzadcaPoziomu.h"



ZarzadcaPoziomu::ZarzadcaPoziomu(sf::RenderWindow* window, const ZwracanyTypPoziomu& typ)
{
	mapa = new ZarzadcaMapy(typ.poziom);
	pasek = new NormalnyPasekWyboru();
	zarzadcaFal = new Wave(typ.poziom);
	zarzadcaStworow = new ZarzadcaStworow();
	zarzadcaWiezyczek = new ZarzadcaWiez();
	zarzadcapociskow = new ZarzadcaPociskow();
	zarzadcazdarzen = new ZarzadcaZdarzen();
	zarzadcadzwieku = new ZarzadcaDzwiekow();
	koniecPoziomu = NULL;

	kartka.setPosition(0, 0);
	kartka.setTexture(StatyczneTekstury::kartkaWKratke);

	aktualnyPoziom = typ;


	okno = window;
	Wieza::zarzadcaStworow = zarzadcaStworow;
	Wieza::zarzadcapociskow = zarzadcapociskow;
	pasek->ZaaktualizujWskaznikZarzadcyFal(zarzadcaFal);
	pasek->ZaaktualizujWskaznikOkna(okno);
	zarzadcazdarzen->pasek = pasek;
	zarzadcazdarzen->zarzadcaWiezyczek = zarzadcaWiezyczek;
	zarzadcazdarzen->mapa = mapa->mapa;
	zarzadcazdarzen->zarzadcaStworow = zarzadcaStworow;
	zarzadcaStworow->ZaaktualizujZarzadceFal(zarzadcaFal);
	zarzadcaStworow->ZaaktualizujZarzadceDzwieku(zarzadcadzwieku);
	zarzadcazdarzen->okno = okno;
}

ZarzadcaPoziomu::ZarzadcaPoziomu()
{

}


ZDARZENIE ZarzadcaPoziomu::Zarzadzaj(sf::Event& zdarzenie, bool& Wynik)
{
	Wynik = false;
	if (!koniecPoziomu)
	{
		return zarzadcazdarzen->Zarzadzaj(zdarzenie);
	}
	else
	{
		return koniecPoziomu->Zarzadzaj(zdarzenie, Wynik);
	}
}

void ZarzadcaPoziomu::Ruch(float czas)
{ 
	czas *= pasek->PobierzTempo();
	if (!pasek->CzyEsc())
	{
		if (!koniecPoziomu)
		{
			zarzadcaWiezyczek->Ruch(czas);
		}
		pasek->Ruch();
		zarzadcapociskow->Ruch(czas);
		zarzadcaStworow->Ruch(czas);
		if (koniecPoziomu == NULL)
		{
			if ( !zarzadcaFal->PossibleNextWave() && !zarzadcaFal->PossibleNextMinion() && zarzadcaStworow->stwory.size() == 0 )
			{
				koniecPoziomu = new KoniecPoziomu(true);
				koniecPoziomu->okno = okno;
				if (pasek->CzyWybranaBudowa())
				{
					pasek->UsunWybranaBudowa();
				}
			}
			if ( pasek->PobierzZycie() == 0)
			{
				koniecPoziomu = new KoniecPoziomu(false);
				koniecPoziomu->okno = okno;
				if (pasek->CzyWybranaBudowa())
				{
					pasek->UsunWybranaBudowa();
				}
			}
		}
	}
}

void ZarzadcaPoziomu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(kartka);
	target.draw(*mapa);
	target.draw(*zarzadcaStworow);
	target.draw(*zarzadcaWiezyczek);
	target.draw(*zarzadcapociskow);
	target.draw(*pasek);
	
	if (koniecPoziomu)
	{
		target.draw(*koniecPoziomu);
	}
}

ZarzadcaPoziomu::~ZarzadcaPoziomu()
{
	delete mapa;
	delete pasek;
	delete zarzadcaFal;
	delete zarzadcaStworow;
	delete zarzadcaWiezyczek;
	delete zarzadcapociskow;
	delete zarzadcazdarzen;
	delete zarzadcadzwieku;
	delete koniecPoziomu;
}



//////////////////NormalnyZarzadcaPoziomu

NormalnyZarzadcaPoziomu::NormalnyZarzadcaPoziomu(sf::RenderWindow* window, const ZwracanyTypPoziomu& typ)
{
	mapa = new ZarzadcaMapy(typ.poziom);
	pasek = new NormalnyPasekWyboru();
	zarzadcaFal = new Wave(typ.poziom);
	zarzadcaStworow = new ZarzadcaStworow();
	zarzadcaWiezyczek = new ZarzadcaWiez();
	zarzadcapociskow = new ZarzadcaPociskow();
	zarzadcazdarzen = new ZarzadcaZdarzen();
	zarzadcadzwieku = new ZarzadcaDzwiekow();
	koniecPoziomu = NULL;

	kartka.setPosition(0, 0);
	kartka.setTexture(StatyczneTekstury::kartkaWKratke);

	aktualnyPoziom = typ;


	okno = window;
	Wieza::zarzadcaStworow = zarzadcaStworow;
	Wieza::zarzadcapociskow = zarzadcapociskow;
	zarzadcaStworow->ZaaktualizujZloto(pasek->PobierzWskaznikZlota());
	zarzadcaStworow->ZaaktualizujZyciePoziomu(pasek->PobierzWskaznikZycia());
	pasek->ZaaktualizujWskaznikZarzadcyFal(zarzadcaFal);
	pasek->ZaaktualizujWskaznikOkna(okno);
	zarzadcazdarzen->pasek = pasek;
	zarzadcazdarzen->zarzadcaWiezyczek = zarzadcaWiezyczek;
	zarzadcazdarzen->mapa = mapa->mapa;
	zarzadcazdarzen->zarzadcaStworow = zarzadcaStworow;
	zarzadcaStworow->ZaaktualizujZarzadceFal(zarzadcaFal);
	zarzadcaStworow->ZaaktualizujZarzadceDzwieku(zarzadcadzwieku);
	zarzadcazdarzen->okno = okno;
}

ZDARZENIE NormalnyZarzadcaPoziomu::Zarzadzaj(sf::Event& zdarzenie, bool& Wynik)
{
	Wynik = false;
	if (!koniecPoziomu)
	{
		return zarzadcazdarzen->Zarzadzaj(zdarzenie);
	}
	else
	{
		return koniecPoziomu->Zarzadzaj(zdarzenie, Wynik);
	}
}

void NormalnyZarzadcaPoziomu::Ruch(float czas)
{
	czas *= pasek->PobierzTempo();
	if (!pasek->CzyEsc())
	{
		if (!koniecPoziomu)
		{
			zarzadcaWiezyczek->Ruch(czas);
		}
		pasek->Ruch();
		zarzadcaStworow->Ruch(czas);
		zarzadcapociskow->Ruch(czas);

		if (koniecPoziomu == NULL&& !zarzadcaFal->PossibleNextWave() && !zarzadcaFal->PossibleNextMinion() && zarzadcaStworow->stwory.size() == 0)
		{
			koniecPoziomu = new KoniecPoziomu(true);
			koniecPoziomu->okno = okno;
			if (pasek->CzyWybranaBudowa())
			{
				pasek->UsunWybranaBudowa();
			}
		}
		if (koniecPoziomu == NULL && pasek->PobierzZycie() == 0)
		{
			koniecPoziomu = new KoniecPoziomu(false);
			koniecPoziomu->okno = okno;
			if (pasek->CzyWybranaBudowa())
			{
				pasek->UsunWybranaBudowa();
			}
		}
	}
}




//////////////////SzybkiZarzadcaPoziomu


SzybkiZarzadcaPoziomu::SzybkiZarzadcaPoziomu(sf::RenderWindow* window, const ZwracanyTypPoziomu& typ)
{
	mapa = new ZarzadcaMapy(typ.poziom);
	pasek = new SzybkiPasekWyboru();
	zarzadcaFal = new Wave(typ.poziom);
	zarzadcaStworow = new SzybkiZarzadcaStworow();
	zarzadcaWiezyczek = new ZarzadcaWiez();
	zarzadcapociskow = new ZarzadcaPociskow();
	zarzadcazdarzen = new ZarzadcaZdarzen();
	koniecPoziomu = NULL;

	kartka.setPosition(0, 0);
	kartka.setTexture(StatyczneTekstury::kartkaWKratke);

	aktualnyPoziom = typ;


	okno = window;
	Wieza::zarzadcaStworow = zarzadcaStworow;
	Wieza::zarzadcapociskow = zarzadcapociskow;
	zarzadcaStworow->ZaaktualizujZloto(pasek->PobierzWskaznikZlota());
	zarzadcaStworow->ZaaktualizujZyciePoziomu(pasek->PobierzWskaznikZycia());
	pasek->ZaaktualizujWskaznikZarzadcyFal(zarzadcaFal);
	pasek->ZaaktualizujWskaznikOkna(okno);
	zarzadcazdarzen->pasek = pasek;
	zarzadcazdarzen->zarzadcaWiezyczek = zarzadcaWiezyczek;
	zarzadcazdarzen->mapa = mapa->mapa;
	zarzadcazdarzen->zarzadcaStworow = zarzadcaStworow;
	zarzadcaStworow->ZaaktualizujZarzadceFal(zarzadcaFal);
	zarzadcaStworow->ZaaktualizujZarzadceDzwieku(zarzadcadzwieku);
	zarzadcazdarzen->okno = okno;
}

ZDARZENIE SzybkiZarzadcaPoziomu::Zarzadzaj(sf::Event& zdarzenie, bool& Wynik)
{
	Wynik = false;
	if (!koniecPoziomu)
	{
		return zarzadcazdarzen->Zarzadzaj(zdarzenie);
	}
	else
	{
		return koniecPoziomu->Zarzadzaj(zdarzenie, Wynik);
	}
}

void SzybkiZarzadcaPoziomu::Ruch(float czas)
{
	czas *= pasek->PobierzTempo();
	if (!pasek->CzyEsc())
	{
		if (!koniecPoziomu)
		{
			zarzadcaWiezyczek->Ruch(czas);
		}
		pasek->Ruch();
		zarzadcaStworow->Ruch(czas);
		zarzadcapociskow->Ruch(czas);

		if (koniecPoziomu == NULL && !zarzadcaFal->PossibleNextWave() && !zarzadcaFal->PossibleNextMinion() && zarzadcaStworow->stwory.size()== 0)
		{
			koniecPoziomu = new KoniecPoziomu(true);
			koniecPoziomu->okno = okno;
			if (pasek->CzyWybranaBudowa())
			{
				pasek->UsunWybranaBudowa();
			}
		}
		
	}
}



