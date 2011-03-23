#include "DungeonMapStatus.h"

DungeonMapStatus::DungeonMapStatus() : MapStatus()
{
}

void DungeonMapStatus::init(/*std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles,	
							std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey, bool gotCompass, 
							bool gotMap, bool gotPowerUp*/)
{
	MapStatus::init();
	/*this->bossDefeated = bossDefeated;
	this->gotBossKey = gotBossKey;
	this->gotCompass = gotCompass;
	this->gotMap = gotMap;
	this->gotPowerUp = gotPowerUp;*/
}

bool DungeonMapStatus::isBossDefeated()
{
	return bossDefeated;
}
void DungeonMapStatus::setBossDefeated(bool bossDefeated)
{
	this->bossDefeated = bossDefeated;
}

bool DungeonMapStatus::isBossKeyGot()
{
	return gotBossKey;
}

void DungeonMapStatus::setBossKeyGot(bool gotBossKey)
{
	this->gotBossKey = gotBossKey;
}

bool DungeonMapStatus::isCompassGot()
{
	return gotCompass;
}

void DungeonMapStatus::setCompassGot(bool gotCompass)
{
	this->gotCompass = gotCompass;
}

bool DungeonMapStatus::isMapGot()
{
	return gotMap;
}

void DungeonMapStatus::setMapGot(bool gotMap)
{
	this->gotMap = gotMap;
}