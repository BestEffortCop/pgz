#include "DataPersistence.h"

DataPersistence::DataPersistence()
{
	gameData = new GameData();
};

DataPersistence::~DataPersistence()
{
	for (std::vector<MapData*>::iterator it = mapDataList.begin(); it != mapDataList.end(); it++)
	{
		delete (*it);
	} 
	mapDataList.clear();

	delete gameData;
}


bool DataPersistence::addMapData(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses, int numCollectables)
{
	if ((mapId >= 0) && (mapId < mapDataList.size()))
		if (mapDataList[mapId] != NULL) return false;
	
	MapData* newmap = new MapData();
	newmap->init(mapId, type, w, h, layout, numPuzzles, numDoors, numMinibosses, numCollectables);

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

int DataPersistence::getMapNumber()
{
	return mapDataList.size();
};

void DataPersistence::save(){
	FILE* f = fopen("data/save", "w");

	vector<MapData*>::iterator it = mapDataList.begin();

	// Guardamos los datos del juego
	gameData->save(f);

	// Escribimos el número de mapas del juego
	short* buffer = new short[1];
	buffer[0] = mapDataList.size();
	fwrite(buffer, sizeof(short), 1, f);
	// Escribimos los datos de los mapas
	while (it != mapDataList.end()){
		(*it)->save(f);	
		it++;
	}

	fclose(f);

};