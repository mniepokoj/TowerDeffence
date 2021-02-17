#include "ZarzadcaStworow.h"


ZarzadcaStworow::ZarzadcaStworow() :
	zloto(0),
	zyciePoziomu(0),
	zarzadcaFal(0),
	zarzadcaDzwieku(0),
	czas(0) {}


void ZarzadcaStworow::ZarzadzajFala()
{
	if(zarzadcaFal->PossibleNextMinion())
	{
		if ( czas < 0 )
		{
			stwory.push_back(new Minion(zarzadcaFal->GetNextMinion()));
			czas += zarzadcaFal->GetTimeToNextMinion();
		}
	}
	else
	{
		if (zarzadcaFal->PossibleNextWave() && stwory.size() == 0)
		{
			zarzadcaFal->NextWave();
			czas = float(zarzadcaFal->GetTimeToNextMinion());
		}
	}
}



void ZarzadcaStworow::Ruch(float zegar)
{
	czas -= zegar * 1000;
	ZarzadzajFala();

	unsigned i;
	//ruch
	for (i = 0; i < stwory.size(); i++)
	{
		stwory[i]->Ruch(zegar);
	}

	//usuwanie
	i = 0;
	while (i < stwory.size())
	{
		if (stwory[i]->CzyZabity())
		{
			delete stwory[i];
			stwory.erase(stwory.begin() + i);
		}
		else	i++;
	}

	//czyZabity
	for (i = 0; i < stwory.size(); i++)
	{
		if (stwory[i]->PobierzZycie() <= 0)
		{
			stwory[i]->CzyZabity(true);
			*zloto += stwory[i]->PobierzZlotoZaZabicie();
			zarzadcaDzwieku->Dodaj(new sf::Sound(StatyczneDzwieki::zabityMinion));
		}
		else if (stwory[i]->PobierzAktualnyCel() == stwory[i]->PobierzRozmiarDocelowo())
		{
			*zyciePoziomu -= stwory[i]->PobierzPobieraneZycie();
			stwory[i]->CzyZabity(true);
		}
	}
}

void ZarzadcaStworow::ZaaktualizujZarzadceFal(Wave* zarzadca) 
{ 
	zarzadcaFal = zarzadca; 
	czas = static_cast<float>(zarzadca->GetTimeToNextMinion());
}
void ZarzadcaStworow::ZaaktualizujZarzadceDzwieku(ZarzadcaDzwiekow* zarzadca) 
{ 
	zarzadcaDzwieku = zarzadca; 
}
void ZarzadcaStworow::ZaaktualizujZloto(int* Zloto) 
{ 
	zloto = Zloto; 
}
void ZarzadcaStworow::ZaaktualizujZyciePoziomu(int* ZyciePoziomu) 
{ 
	zyciePoziomu = ZyciePoziomu; 
}


void ZarzadcaStworow::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& i : stwory)
		target.draw(*i);
}

ZarzadcaStworow::~ZarzadcaStworow()
{
	for (auto& i : stwory)
	{
		delete i;
	}
}

/////////////////////////////////
SzybkiZarzadcaStworow::SzybkiZarzadcaStworow()
{
	stwory.push_back(new SzybkiMinion());
}

void SzybkiZarzadcaStworow::Ruch(float zegar)
{

	unsigned i;
	if (stwory.size())
	{
		*zyciePoziomu = 0;
		for (i = 0; i < stwory.size(); i++)
		{
			stwory[i]->Ruch(zegar);
			*zyciePoziomu += static_cast<int>(stwory[i]->PobierzZycie());
		}
	}
	//usuwanie
	i = 0;
	while (i < stwory.size())
	{
		if (stwory[i]->CzyZabity())
		{
			delete stwory[i];
			stwory.erase(stwory.begin() + i);
		}
		else	i++;
	}

	//czyZabity
	for (i = 0; i < stwory.size(); i++)
	{
		if (stwory[i]->PobierzAktualnyCel() == stwory[i]->PobierzRozmiarDocelowo())
		{
			stwory[i]->CzyZabity(true);
		}
	}
}