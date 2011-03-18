#include "DungeonMapState.h"

DungeonMapState::DungeonMapState() : MapState()
{
}

DungeonMapState::DungeonMapState(std::map<int, bool> collectables,	std::map<int, bool> doors, std::map<int, bool> puzzles,	
					std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey,
				bool gotCompass, bool gotMap, bool gotPowerUp): MapState()
{
	init(collectables, doors, puzzles, minibosses, bossDefeated,gotBossKey,gotCompass,gotMap,gotPowerUp);
}

void DungeonMapState::init(std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles,	
							std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey, bool gotCompass, 
							bool gotMap, bool gotPowerUp)
{
	MapState::init(collectables, doors, puzzles, minibosses);
	this->bossDefeated = bossDefeated;
	this->gotBossKey = gotBossKey;
	this->gotCompass = gotCompass;
	this->gotMap = gotMap;
	this->gotPowerUp = gotPowerUp;
}

bool DungeonMapState::isBossDefeated()
{
	return bossDefeated;
}
void DungeonMapState::setBossDefeated(bool bossDefeated)
{
	this->bossDefeated = bossDefeated;
}

bool DungeonMapState::isGotBossKey()
{
	return gotBossKey;
}

void DungeonMapState::setGotBossKey(bool gotBossKey)
{
	this->gotBossKey = gotBossKey;
}

bool DungeonMapState::isGotCompass()
{
	return gotCompass;
}

void DungeonMapState::setGotCompass(bool gotCompass)
{
	this->gotCompass = gotCompass;
}

bool DungeonMapState::isGotMap()
{
	return gotMap;
}

void DungeonMapState::setGotMap(bool gotMap)
{
	this->gotMap = gotMap;
}

bool DungeonMapState::isGotPowerUp()
{
	return gotPowerUp;
}

void DungeonMapState::isGotPowerUp(bool gotPowerUp)
{
	this->gotPowerUp = gotPowerUp;
}