#include "DataPersistence.h"

DataPersistence::DataPersistence()
{
	gameData = new GameData();
};

bool DataPersistence::addMapData(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses)
{
	if ((mapId >= 0) && (mapId < mapDataList.size()))
		if (mapDataList[mapId] != NULL) return false;
	
	MapData* newmap = new MapData();
	newmap->init(mapId, type, w, h, layout, numPuzzles, numDoors, numMinibosses);

	std::vector<MapData*>::iterator it = mapDataList.begin();
	for (int i = 0; i < mapId; i++)
		it++;

	mapDataList.insert(it, newmap);

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