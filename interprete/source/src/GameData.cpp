#include "GameData.h"


GameData::GameData(int numDungeons, int numOverWorlds)
{
	// asignamos el número de elemntos que contendrá cada vector
	nDung = numDungeons;
	nOver = numOverWorlds;
		
	// PRUEBA SI RULAAAA

	// creamos el vector de estados (por defecto) de mazmorras
	*dungeonMapStates = new DungeonMapState[numDungeons];

	// creamos el vector de estados (por defecto) de overworlds
	*overWorldMapStates = new OverWorldMapState[numOverWorlds];

	// creamos el estado del juego por defecto
	gameStatus = new GameStatus();
}

GameData::~GameData(void)
{
	// borramos todos los elementos creados del array de estados de mazmorras
	for (int i=0; i<nDung; i++)
		if (dungeonMapStates[i] != NULL) // si no existe no se borra
		{
			delete dungeonMapStates[i]; dungeonMapStates[i] = NULL;
		}

	// borramos todos los elementos creados del array de estados de overworlds
	for (int i=0; i<nOver; i++)
		if (overWorldMapStates[i] != NULL) // si no existe no se borra
		{
			delete overWorldMapStates[i]; overWorldMapStates[i] = NULL;
		}

	// borramos el gameStatus
	delete gameStatus; gameStatus = NULL;
}

void GameData::initDungeonMapState(int dungeonID, std::map<int, bool> collectables, std::map<int, bool> doors,
			std::map<int, bool> puzzles, std::map<int, bool> minibosses,	bool bossDefeated, bool gotBossKey,
			bool gotCompass, bool gotMap, bool gotPowerUp)
{
	dungeonMapStates[dungeonID]->init(collectables, doors, puzzles, minibosses, bossDefeated, gotBossKey, gotCompas,
										gotMap, gotPowerUp);
}

void GameData::initOverWorldMapState(int overWorldID, std::map<int, bool> collectables, std::map<int, bool> doors,
	std::map<int, bool> puzzles, std::map<int, bool> minibosses)
{
	overWorldMapStates[overWorldID]->init(collectables, doors, puzzles, minibosses);
}
