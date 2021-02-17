#pragma once
#include "Wieza.h"

class CzerwonaWieza :	public Wieza
{
private:
	float wielkoscWzmocnienia;
	float zwiekszenieObrazen;
public:
	bool aktualizacjaObrazen;
private:
	void Level1();
	void Level2();
	void Level3();
	void Strzelanie();
public:
	CzerwonaWieza();
	CzerwonaWieza(const sf::Vector2f& polozenie);
	CzerwonaWieza(const CzerwonaWieza & wieza);
	void Ruch(const float& czas);
	void Ulepsz();
	int PobierzKoszt(bool creatable = false) const;
	int MaxPoziom() const;
	TYP_WIEZY PobierzTyp() const;
	std::wstring PobierzNazwe() const;
	std::wstring PobierzOpis() const;
	void ZwiekszObrazenia(float oIle);
	float PobierzObrazenia();
	~CzerwonaWieza();
};

