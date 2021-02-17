#include "ZarzadcaDzwiekow.h"

void ZarzadcaDzwiekow::Dodaj(sf::Sound* dzwiek)
{
	dzwiek->setVolume(50u);
	dzwiek->setAttenuation(0.5f);
	dzwiek->setPitch(1.6f);
	dzwiek->play(); 
	dzwieki.push_back(dzwiek);
}

void ZarzadcaDzwiekow::Ruch()
{
	for (unsigned i = 0; i < dzwieki.size(); i++)
	{
		if (dzwieki[i]->getStatus() == sf::Sound::Stopped)
		{
			delete dzwieki[i];
			dzwieki.erase(i + dzwieki.begin());
		}
	}
}
