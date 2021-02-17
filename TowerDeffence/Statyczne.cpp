#include "Statyczne.h"

int Statyczne::aktywowane = 0;

void Statyczne::Aktywacja()
{
	if (!aktywowane)
	{
		StatyczneDzwieki::Aktywacja();
		StatyczneTekstury::Aktywacja();
		Matematyka::Aktywacja();
		Matematyka::Test();
		aktywowane = true;
	}
}