#include "ZwracanyTypPoziomu.h"

ZwracanyTypPoziomu::ZwracanyTypPoziomu(const int& Poziom, const TYP_POZIOMU& TypPoziomu) : poziom(Poziom), typPoziomu(TypPoziomu)
{

}

ZwracanyTypPoziomu::ZwracanyTypPoziomu() : typPoziomu(TYP_POZIOMU::NIC), poziom(0)
{
}