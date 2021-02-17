#pragma once

enum class ZDARZENIE { NIC, WZNOW, POWTORZ, WYJDZ, BRAK }; //brak w przypadku nie wykonania zadnej czynnosci

enum class TYP_POZIOMU { NIC, NORMALNY, SZYBKI };

struct ZwracanyTypPoziomu
{
	ZwracanyTypPoziomu(const int& Poziom, const TYP_POZIOMU& TypPoziomu);
	ZwracanyTypPoziomu();
	int poziom;
	TYP_POZIOMU typPoziomu;
};