#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include "Minion.h"


struct GroupStruct
{
	GroupStruct(Stwory::typ Type, size_t Quantity, unsigned timeBetwen, unsigned timeBefore);
	GroupStruct();

	Stwory::typ type;
	size_t quantity;
	unsigned timeBetwen;
	unsigned timeBefore;
};


class Wave
{
//minion->group->team->wave->level
//groups are minions in single wave, waves are alleys in single level
//team cant be empty
private:
	size_t waveNumber, maxWaveNumber;
	size_t teamNumber, quantityMinions;
	std::vector <GroupStruct> groups;
	unsigned time;
	bool possibleNextMinion;
	std::function <void(std::vector<GroupStruct>&)> waveArray[10];
private:

	void Level1();
	void Wave11(std::vector<GroupStruct>& groups);
	void Wave12(std::vector<GroupStruct>& groups);
	void Wave13(std::vector<GroupStruct>& groups);
	void Wave14(std::vector<GroupStruct>& groups);
	void Wave15(std::vector<GroupStruct>& groups);

	void Level2();
	void Wave21(std::vector<GroupStruct>& groups);
	void Wave22(std::vector<GroupStruct>& groups);
	void Wave23(std::vector<GroupStruct>& groups);
	void Wave24(std::vector<GroupStruct>& groups);
	void Wave25(std::vector<GroupStruct>& groups);

	void Level3();
	void Wave31(std::vector<GroupStruct>& groups);
	void Wave32(std::vector<GroupStruct>& groups);
	void Wave33(std::vector<GroupStruct>& groups);
	void Wave34(std::vector<GroupStruct>& groups);
	void Wave35(std::vector<GroupStruct>& groups);
public:
	Wave(unsigned LevelNumber);
	bool PossibleNextMinion() const;
	bool PossibleNextWave() const;
	unsigned GetTimeToNextMinion() const; // time in milliseconds
	Stwory::typ GetNextMinion();
	unsigned GetWaveNubmer() const;
	unsigned GetMaxWaveNumber() const;
	void NextWave();
	~Wave();
};

