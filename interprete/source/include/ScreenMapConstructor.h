#pragma once

#ifndef __SCREENMAPCONSTRUCTOR_H__
#define __SCREENMAPCONSTRUCTOR_H__

#include "ScreenMap.h"

class ScreenMap;

class ScreenMapConstructor
{
private:

	list< EnemySpawnData * > enemies;
	MapLocation screenLocation;

public:

	ScreenMapConstructor();
	~ScreenMapConstructor();

	// Proporciona funcionalidad para comprimir y descomprimir un ScreenMap
	void zip(ScreenMap* screenMap);
	ScreenMap* unzip();

	// Además, proporciona funcionalidad para consultar atributos del screenMap comprimido
	list< EnemySpawnData * > getEnemiesData();
	MapLocation getMapLocation();
};

#endif
