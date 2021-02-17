#pragma once
#include <SFML/Audio.hpp>
#include <vector>

class ZarzadcaDzwiekow
{
private:
	std::vector <sf::Sound*> dzwieki;
public:
	ZarzadcaDzwiekow() {};
	void Dodaj(sf::Sound* dzwiek);
	void Ruch(); 

	~ZarzadcaDzwiekow() { for (auto& i : dzwieki) delete i; };
};

