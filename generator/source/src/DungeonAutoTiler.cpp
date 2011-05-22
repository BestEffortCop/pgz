#include "DungeonAutoTiler.h"

DungeonAutoTiler::DungeonAutoTiler(std::string tileSetPath){

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

	if (!loadDungeonDecoList(file))
		return false;

	fclose(file);
	return true;	
}

bool DungeonAutoTiler::loadWalls(FILE* file){

	if (file == NULL)
		return NULL;

	// nDunWalls
	int nDunWalls;
	if (fscanf_s(file, "%d", &nDunWalls) < 1)
		return false;

	// Cargamos cada muro
	DungeonWall* temp = NULL;
	for (int i = 0; i < nDunWalls; i++)
	{
		temp = loadWall(file);
		if (temp != NULL)
			terrainList.push_back(temp);
		else
			return false;
	}

	return true;
}

DungeonWall* DungeonAutoTiler::loadWall(FILE* file){
	
	if (file == NULL)
		return NULL;

	// Leemos el id
	int wallId;
	if (fscanf_s(file, "%d", &wallId) < 1)
		return NULL;

	// id del tile
	int tileId;
	if (fscanf_s(file, "%d", &tileId) < 1)
		return NULL;

	// Variaciones
	std::vector<int> variations;
	int numVariations;
	int idVariation;
	// Se lee el nº de variaciones
	if (fscanf_s(file, "%d", &numVariations) < 1)
		return NULL;
	
	for (int i = 0; i < numVariations; i++)
	{
		if (fscanf_s(file, "%d", &idVariation) < 1)
			return NULL;
		variations.push_back(idVariation);
	}

	// Se crea el terreno con los datos
	DungeonWall* wall = new DungeonWall();
	
	wall->init(wallId, tileId, variations, Terrain::dungeonWall, chipsetWidth);

	return wall;
}

bool DungeonAutoTiler::loadDungeonDecoList(FILE* file){
	if (file == NULL)
		return false;

	// nDecos
	int nDecos;
	if (fscanf_s(file, "%d", &nDecos) < 1)
		return false;

	// Cargamos cada decoración
	for (int i = 0; i < nDecos; i++)
		loadDungeonDeco(file);

	return true;
}

void DungeonAutoTiler::loadDungeonDeco(FILE* file){
	if (file == NULL)
		return;

	// idDeco
	int idDeco;
	if (fscanf_s(file, "%d", &idDeco) < 1)
		return;

	DungeonDecoData d;

	// si es una antorcha, nos interesa leer en qué pared va
	if (decorationList.at(idDeco).type == Decoration::DecorationType::hangable){
		// Leemos en que pared va (arriba, izquierda, derecha)
		DunDecorationPos posDeco;
		if (fscanf_s(file, "%d", &posDeco) < 1)
			return;

		d.pos = posDeco;
		// insertamos la decoración en la lista
		dungeonDecos.insert(make_pair(idDeco, d)); 
	}
}

Decoration* DungeonAutoTiler::getDungeonTorch(DunDecorationPos pos)
{
	// buscamos el la lista de decoraciones de mazmorra una antorcha en la pared que nos dicen
	std::map<int, DungeonDecoData>::iterator it = dungeonDecos.begin();
	while (it != dungeonDecos.end())
	{
		if (pos == it->second.pos)
			return new Decoration(decorationList.at(it->first));
		it++;
	}

	// si no lo hemos encontrado devolvemos NULL
	return NULL;
}