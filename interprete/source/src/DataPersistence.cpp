#include "DataPersistence.h"

DataPersistence::DataPersistence()
{
	gameData = new GameData();
};

bool DataPersistence::addMapData(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses)
{
	if (mapDataList.at(mapId) != NULL) return false;

	MapData* newmap = new MapData();
	newmap->init(mapId, type, w, h, layout, numPuzzles, numDoors, numMinibosses);

	mapDataList[mapId] = newmap;

	return true;
};

GameData* DataPersistence::getGameData()
{
	return gameData;
};

MapData* DataPersistence::getMapData(int mapId)
{
	// ABSOLUTELY NOT ERROR PROOF!
	return mapDataList[mapId];
};