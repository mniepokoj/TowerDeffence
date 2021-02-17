#include "ZarzadcaWszystkiego.h"


ZarzadcaWszystkiego::ZarzadcaWszystkiego(sf::RenderWindow* window) :
	okno(window),
	aktualnyStan(StanGry::start),
	zarzadcaStartu(new ZarzadcaStartu(window)),
	zarzadcaPoziomu(NULL),
	zarzadcaPlanszy(NULL),
	wynik(false)
{

};

void ZarzadcaWszystkiego::Aktywacja()
{
	ZarzadcaPlanszy::Aktywacja();
}

void ZarzadcaWszystkiego::UstawWskaznikOkna(sf::RenderWindow& window)
{
	okno = &window;
}


void ZarzadcaWszystkiego::UsunPoprzedniStanGry()
{
	switch (aktualnyStan)
	{
	case StanGry::start:
		delete zarzadcaStartu;
		break;

	case StanGry::plansza:
		delete zarzadcaPlanszy;
		break;

	case StanGry::poziom:
		delete zarzadcaPoziomu;
		break;

	default:
		break;
	}
}


void ZarzadcaWszystkiego::Ruch(const float& czas)
{
	switch (aktualnyStan)
	{
	case StanGry::start:
		break;

	case StanGry::poziom:
		zarzadcaPoziomu->Ruch(czas);
		break;

	default:
		break;
	}
}

void ZarzadcaWszystkiego::Rysoj()
{
	switch (aktualnyStan)
	{
	case StanGry::start:
		okno->draw(*zarzadcaStartu);
		break;

	case StanGry::plansza:
		okno->draw(*zarzadcaPlanszy);
		break;

	case StanGry::poziom:
		okno->draw(*zarzadcaPoziomu);
		break;
	default:
		break;
	}
}

void ZarzadcaWszystkiego::Zarzadz(sf::Event& zdarzenie)
{
	switch (aktualnyStan)
	{
	case StanGry::start:
		if (zarzadcaStartu->Zarzadzaj(zdarzenie))
		{
			ZmienStan(StanGry::plansza);
		}
		break;

	case StanGry::plansza:
	{
		ZwracanyTypPoziomu typ = zarzadcaPlanszy->Zarzadzaj(zdarzenie);
		if (typ.typPoziomu != TYP_POZIOMU::NIC)
		{
			ZmienStan(typ);
		}
		break;
	}
	case StanGry::poziom:
		switch (zarzadcaPoziomu->Zarzadzaj(zdarzenie, wynik))
		{
		case ZDARZENIE::NIC:
				break;
			case ZDARZENIE::WYJDZ:
				if (wynik)
				{
					ZarzadcaPlanszy::czyWygrana->at(zarzadcaPoziomu->PobierzAktualnyPoziom().poziom-1) = wynik;
				}
				ZmienStan(StanGry::plansza);
				break;
			case ZDARZENIE::POWTORZ:
				if (wynik)
				{
					ZarzadcaPlanszy::czyWygrana->at(zarzadcaPoziomu->PobierzAktualnyPoziom().poziom - 1) = wynik;
				}
				ZmienStan(zarzadcaPoziomu->PobierzAktualnyPoziom());
			default:
				break;
		}

		break;
	default:
		break;
	}
}

void ZarzadcaWszystkiego::ZmienStan(StanGry stan)
{
	switch (stan)
	{
	case StanGry::start:
		UsunPoprzedniStanGry();
		zarzadcaStartu = new ZarzadcaStartu(okno);
		aktualnyStan = StanGry::start;
		break;

	case StanGry::plansza:
		UsunPoprzedniStanGry();
		zarzadcaPlanszy = new ZarzadcaPlanszy(okno);
		aktualnyStan = StanGry::plansza;
		break;

	default:
		break;
	}
}


void ZarzadcaWszystkiego::ZmienStan(const ZwracanyTypPoziomu& typ)
{
	UsunPoprzedniStanGry();
	switch (typ.typPoziomu)
	{
	case TYP_POZIOMU::NORMALNY:
		zarzadcaPoziomu = new NormalnyZarzadcaPoziomu(okno, typ);
		break;
	case TYP_POZIOMU::SZYBKI:
		zarzadcaPoziomu = new SzybkiZarzadcaPoziomu(okno, typ);
	default:
		break;
	}
	aktualnyStan = StanGry::poziom;
}

ZarzadcaWszystkiego::~ZarzadcaWszystkiego()
{
	UsunPoprzedniStanGry();
}