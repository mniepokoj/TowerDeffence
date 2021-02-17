#include "StatyczneDzwieki.h"

sf::SoundBuffer StatyczneDzwieki::zabityMinion;

void StatyczneDzwieki::Aktywacja()
{
	zabityMinion.loadFromFile("zabityMinion2.wav");
}