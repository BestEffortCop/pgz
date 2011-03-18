#pragma once
#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include "DungeonMapState.h"
#include "OverWorldMapState.h"
#include "GameStatus.h"

class GameData
{

private:

	int nDung; // número de estados de mazmorras almacenados en el vector
	int nOver; // número de estados de overworld almacenados en el vector

	DungeonMapState** dungeonMapStates;		// vector de estados de mazmorras
	OverWorldMapState** overWorldMapStates;	// vector de estados de overworlds
	GameStatus* gameStatus;					// estado del juego entre otras cosas

public:

	GameData(int numDungeons, int numOverWorlds);
	~GameData();

	void initDungeonMapState(int dungeonID, std::map<int, bool> collectables, std::map<int, bool> doors,
			std::map<int, bool> puzzles, std::map<int, bool> minibosses,	bool bossDefeated, bool gotBossKey,
			bool gotCompass, bool gotMap, bool gotPowerUp);

	void initOverWorldMapState(int overWorldID, std::map<int, bool> collectables, std::map<int, bool> doors,
								std::map<int, bool> puzzles, std::map<int, bool> minibosses);

	void initGameStatus(); // Los atributos no están definidos todavía

};


#endif