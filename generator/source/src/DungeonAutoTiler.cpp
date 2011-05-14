#include "DungeonAutoTiler.h"

DungeonAutoTiler::DungeonAutoTiler(std::string tileSetPath){
	// hardcodeo
	tileSetPath = "dunWalls";

	loadDungeonConfig(loadTilesetConfig(tileSetPath));
}

DungeonAutoTiler::~DungeonAutoTiler(){
	AutoTiler::~AutoTiler();
}

bool DungeonAutoTiler::loadDungeonConfig(FILE* file){

	if (file == NULL)
		return NULL;

	// Cargamos los muros 
	if (!loadWalls(file))
		return false; 

	fclose(file);
	return true;	
}

bool DungeonAutoTiler::loadWalls(FILE* file){

	if (file == NULL)
		return NULL;

	// nDunWalls
	int nDunWalls;
	if (fscanf(file, "%d", &nDunWalls) < 1)
		return false;

	// 
	DungeonWall* temp = NULL;
	for (int i = 0; i < nDunWalls; i++)
	{
		temp = loadWall(file);
		if (temp != NULL)
			wallList.push_back(temp);
	}

	return wallList.size() == nDunWalls;
}

DungeonWall* DungeonAutoTiler::loadWall(FILE* file){
	
	if (file == NULL)
		return NULL;

	// Leemos el id
	int wallId;
	if (fscanf(file, "%d", &wallId) < 1)
		return NULL;

	// id del tile
	int tileId;
	if (fscanf(file, "%d", &tileId) < 1)
		return NULL;

	// Variaciones
	std::vector<int> variations;
	int numVariations;
	int idVariation;
	// Se lee el nº de variaciones
	if (fscanf(file, "%d", &numVariations) < 1)
		return NULL;
	
	for (int i = 0; i < numVariations; i++)
	{
		if (fscanf(file, "%d", &idVariation) < 1)
			return NULL;
		variations.push_back(idVariation);
	}

	// Se crea el terreno con los datos
	DungeonWall* wall = new DungeonWall();
	
	wall->init(wallId, tileId, variations, chipsetWidth);
		
	return wall;
}

int DungeonAutoTiler::getDunWallId(){

	int pos = rand() % wallList.size();
	return wallList[pos]->getId();
}

DungeonWall* DungeonAutoTiler::getDunWall(int id){

	return wallList[id];
}