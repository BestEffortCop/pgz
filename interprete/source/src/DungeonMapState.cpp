#include "DungeonMapState.h"

DungeonMapState::DungeonMapState(std::map<int, bool> collectables,	std::map<int, bool> doors, std::map<int, bool> puzzles,	
					std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey,
				bool gotCompass, bool gotMap, bool gotPowerUp): MapState(collectables, doors, puzzles, minibosses)
{
	init(bossDefeated,gotBossKey,gotCompass,gotMap,gotPowerUp);
}

void DungeonMapState::init(bool bossDefeated, bool gotBossKey, bool gotCompass, bool gotMap, bool gotPowerUp)
{
	this->bossDefeated = bossDefeated;
	this->gotBossKey = gotBossKey;
	this->gotCompass = gotCompass;
	this->gotMap = gotMap;
	this->gotPowerUp = gotPowerUp;
}

bool DungeonMapState::isBossDefeated();
void DungeonMapState::setBossDefeated(bool bossDefeated);

bool DungeonMapState::isGotBossKey();
void DungeonMapState::setGotBossKey(bool gotBossKey);

bool DungeonMapState::isGotCompass();
void DungeonMapState::setGotCompass(bool gotCompass);

bool DungeonMapState::isGotMap();
void DungeonMapState::setGotMap(bool gotMap);

bool DungeonMapState::isGotPowerUp();
void DungeonMapState::isGotPowerUp(bool gotPowerUp);