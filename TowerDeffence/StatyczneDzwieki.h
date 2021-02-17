#pragma once
#include <SFML/Audio.hpp>

class StatyczneDzwieki
{
private: 	
	StatyczneDzwieki() {};
	~StatyczneDzwieki() {};
public:
	
	static sf::SoundBuffer zabityMinion;

	static void Aktywacja();
};

