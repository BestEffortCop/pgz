#include "GameData.h"


GameData::GameData(int numDungeons, int numOverWorlds)
{
	// creamos el vector de estados de mazmorras (todas a NULL de momento)
	dungeonMapStates = std::vector<DungeonMapState*>(numDungeons, NULL);

	// creamos el vector de estados de overworlds (todos a NULL de momento)
	overWorldMapStates = std::vector<OverWorldMapState*>(numOverWorlds, NULL);

	// creamos el estado del juego por defecto
	gameStatus = new GameStatus();
}

GameData::~GameData()
{
	// borramos todos los elementos creados del array de estados de mazmorras
	for (int i=0; i<dungeonMapStates.size(); i++)
		if (dungeonMapStates[i] != NULL) // si no existe no se borra
		{
			delete dungeonMapStates[i]; dungeonMapStates[i] = NULL;
		}

	// borramos todos los elementos creados del array de estados de overworlds
		for (int i=0; i<overWorldMapStates.size(); i++)
		if (overWorldMapStates[i] != NULL) // si no existe no se borra
		{
			delete overWorldMapStates[i]; overWorldMapStates[i] = NULL;
		}

	// borramos el gameStatus
	if (gameStatus == NULL) {delete gameStatus; gameStatus = NULL;}
}

void GameData::initDungeonMapState(int dungeonID, std::map<int, bool> collectables, std::map<int, bool> doors,
			std::map<int, bool> puzzles, std::map<int, bool> minibosses,	bool bossDefeated, bool gotBossKey,
			bool gotCompass, bool gotMap, bool gotPowerUp)
{
	dungeonMapStates[dungeonID]->init(collectables, doors, puzzles, minibosses, bossDefeated, gotBossKey, gotCompass,
										gotMap, gotPowerUp);
}

void GameData::initOverWorldMapState(int overWorldID, std::map<int, bool> collectables, std::map<int, bool> doors,
	std::map<int, bool> puzzles, std::map<int, bool> minibosses)
{
	overWorldMapStates[overWorldID]->init(collectables, doors, puzzles, minibosses);
}

void GameData::initGameStatus(int numKeyItems, int maxLife, std::map<int,ToolInfo> tools, int actualMoney,
					MapId actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPidgeons,
					int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress)
{
	gameStatus->init(numKeyItems, maxLife, tools, actualMoney, actualScreen, lastPos, numPlayers, numPidgeons, numHeartPieces,
					maxHeartPieces, barterProgress, gameProgress);
}

DungeonMapState* GameData::getDungeonMapState(int i)
{
	// Devolvemos la mazmorra pedida siempre que esté dentro del rango
	if (i >= 0 && i < dungeonMapStates.size())
		return dungeonMapStates[i];
	else // Si no existe la mazmorra requerida devolvemos NULL
		return NULL;
}

OverWorldMapState* GameData::getOverWorldMapState(int i)
{
	// Devolvemos el overworld pedido siempre que esté dentro del rango
	if (i >= 0 && i < overWorldMapStates.size())
		return overWorldMapStates[i];
	else // Si no existe el overworld requerido devolvemos NULL
		return NULL;
}

GameStatus* GameData::getGameStatus()
{
	return gameStatus;
}
