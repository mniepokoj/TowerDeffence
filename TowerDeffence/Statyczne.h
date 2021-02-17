#pragma once
#include "StatyczneDzwieki.h"
#include "StatyczneTekstury.h"
#include "Matematyka.h"

class Statyczne
{
private:
	Statyczne();
	static int aktywowane;
public:
	static void Aktywacja();
};