#pragma once

#include <vector>
#include "Minion.h"
#include "Wave.h"
#include "StatyczneDzwieki.h"
#include "ZarzadcaDzwiekow.h"

class ZarzadcaStworow : public sf::Drawable
{
private:
	void ZarzadzajFala();
protected:
	int* zloto;
	int* zyciePoziomu;
	Wave* zarzadcaFal;
	ZarzadcaDzwiekow* zarzadcaDzwieku;
	float czas; // w milisekundach
public:
	ZarzadcaStworow();

	std::vector<Minion*> stwory;
	virtual void ZaaktualizujZarzadceFal(Wave* zarzadca);
	virtual void ZaaktualizujZarzadceDzwieku(ZarzadcaDzwiekow* zarzadca);
	virtual void ZaaktualizujZloto(int* Zloto);
	virtual void ZaaktualizujZyciePoziomu(int* ZyciePoziomu);
	virtual void Ruch(float czas);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	~ZarzadcaStworow();
};

class SzybkiZarzadcaStworow : public ZarzadcaStworow
{
public:
	SzybkiZarzadcaStworow();
	void Ruch(float czas);
};

