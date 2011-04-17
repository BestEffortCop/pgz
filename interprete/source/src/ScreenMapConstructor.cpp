#include "ScreenMapConstructor.h"


ScreenMapConstructor::ScreenMapConstructor()
{
}

ScreenMapConstructor::~ScreenMapConstructor()
{
}

void ScreenMapConstructor::zip(ScreenMap* screenMap)
{
	enemies = screenMap->enemies;
	this->screenLocation = screenMap->screenLocation;
}

ScreenMap* ScreenMapConstructor::unzip()
{
	// Not yet implemented
	return NULL;
}

list< EnemySpawnData * > ScreenMapConstructor::getEnemiesData()
{
	return enemies;
}

MapLocation ScreenMapConstructor::getMapLocation()
{
	return screenLocation;
}
