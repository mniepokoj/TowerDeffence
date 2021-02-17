#include "Wave.h"

GroupStruct::GroupStruct(Stwory::typ Type, size_t Quantity, unsigned TimeBetwen, unsigned TimeBefore)
	: type(Type), quantity(Quantity), timeBetwen(TimeBetwen), timeBefore(TimeBefore) {}

GroupStruct::GroupStruct() : type(Stwory::typ::malyZolty), quantity((size_t)0), timeBetwen(0u), timeBefore(0u) {};


////////////LEVEL_1
void Wave::Wave11(std::vector<GroupStruct>& groups)
{
	for (int i = 0; i < 6; i++)
	{
		groups.push_back(GroupStruct(Stwory::typ::malyZolty, 4, 280, 300));
		groups.push_back(GroupStruct(Stwory::typ::zolty, 1, 320, 300));
	}
}
void Wave::Wave12(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::fioletowy, 2, 450, 2000));
	groups.push_back(GroupStruct(Stwory::typ::bordowy, 1, 450, 350));
	for (int i = 0; i <= 10; i++)
	{
		groups.push_back(GroupStruct(Stwory::typ::fioletowy, 2, 500, 500));
		groups.push_back(GroupStruct(Stwory::typ::bordowy, 1, 500, 500));
	}
}
void Wave::Wave13(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::niebieski, 20, 800, 500));
}
void Wave::Wave14(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::zielona, 40, 500, 2000));
}

void Wave::Wave15(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::boss, 1, 0, 2000));
}
////////////LEVEL_2
void Wave::Wave21(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::zolty, 1, 600, 0));
}
void Wave::Wave22(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::bordowy, 12, 500, 2000));
}
void Wave::Wave23(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::zielona, 16, 500, 2000));
}
void Wave::Wave24(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::bordowy, 30, 400, 2000));
}
void Wave::Wave25(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::boss, 1, 0, 2000));
}



////////////LEVEL_3
void Wave::Wave31(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::fioletowy, 10, 500, 0));
}
void Wave::Wave32(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::bordowy, 16, 450, 2000));
}
void Wave::Wave33(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::fioletowy, 50, 400, 2000));
}
void Wave::Wave34(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::niebieski, 30, 500, 2000));
}
void Wave::Wave35(std::vector<GroupStruct>& groups)
{
	groups.push_back(GroupStruct(Stwory::typ::boss, 1, 0, 10000));
}


Wave::Wave(unsigned LevelNumber)  : 
	waveNumber(0),
	maxWaveNumber(),
	teamNumber(0),
	quantityMinions(),
	groups(),
	time(),
	possibleNextMinion(true)
{
	switch (LevelNumber)
	{
	case 1: Level1();	break;
	case 2: Level2();	break;
	case 3: Level3();	break;
	default: std::cout << "Error File: " << __FILE__ << " Line: " << __LINE__ <<" Undefined Level "<< std::endl;	break;
	}
}


void Wave::Level1()
{
	waveArray[0] = std::bind(&Wave::Wave11, this, std::placeholders::_1);
	waveArray[1] = std::bind(&Wave::Wave12, this, std::placeholders::_1);
	waveArray[2] = std::bind(&Wave::Wave13, this, std::placeholders::_1);
	waveArray[3] = std::bind(&Wave::Wave14, this, std::placeholders::_1);
	waveArray[4] = std::bind(&Wave::Wave15, this, std::placeholders::_1);

	maxWaveNumber = 4;
	quantityMinions = 0;
	waveArray[waveNumber](groups);
	time = groups[teamNumber].timeBefore;
}
void Wave::Level2()
{
	waveArray[0] = std::bind(&Wave::Wave11, this, std::placeholders::_1);
	waveArray[1] = std::bind(&Wave::Wave12, this, std::placeholders::_1);
	waveArray[2] = std::bind(&Wave::Wave13, this, std::placeholders::_1);
	waveArray[3] = std::bind(&Wave::Wave14, this, std::placeholders::_1);
	waveArray[4] = std::bind(&Wave::Wave15, this, std::placeholders::_1);

	maxWaveNumber = 4;
	quantityMinions = 0;
	waveArray[waveNumber](groups);
	time = groups[teamNumber].timeBefore;
}
void Wave::Level3()
{
	waveArray[0] = std::bind(&Wave::Wave11, this, std::placeholders::_1);
	waveArray[1] = std::bind(&Wave::Wave12, this, std::placeholders::_1);
	waveArray[2] = std::bind(&Wave::Wave13, this, std::placeholders::_1);
	waveArray[3] = std::bind(&Wave::Wave14, this, std::placeholders::_1);
	waveArray[4] = std::bind(&Wave::Wave15, this, std::placeholders::_1);

	maxWaveNumber = 4;
	quantityMinions = 0;
	waveArray[waveNumber](groups);
	time = groups[teamNumber].timeBefore;
}

bool Wave::PossibleNextMinion() const
{
	return possibleNextMinion;
}

unsigned Wave::GetTimeToNextMinion() const
{
	return time;
}

Stwory::typ Wave::GetNextMinion()
{
	if (quantityMinions + 1 == groups[teamNumber].quantity)
	{
		if (groups.size() - 1 > teamNumber)
		{
			teamNumber++;
			time = groups[teamNumber].timeBefore;
			quantityMinions = 0;
			return groups[teamNumber - 1].type;
		}
		else
		{
			time = 0;
			possibleNextMinion = false;
			return groups[teamNumber].type;
		}
	}
	else
	{
		time = groups[teamNumber].timeBetwen;
		quantityMinions++;
		return groups[teamNumber].type;
	}
}

bool Wave::PossibleNextWave() const
{
	return (maxWaveNumber > waveNumber);
}
void Wave::NextWave()
{
	groups.clear();
	waveNumber++;
	waveArray[waveNumber](groups);
	teamNumber = 0;
	quantityMinions = 0;
	possibleNextMinion = true;
	time = groups[teamNumber].timeBefore;
}

unsigned Wave::GetWaveNubmer() const
{
	return waveNumber+1;
}

unsigned Wave::GetMaxWaveNumber() const
{
	return maxWaveNumber+1;
}

Wave::~Wave()
{
}