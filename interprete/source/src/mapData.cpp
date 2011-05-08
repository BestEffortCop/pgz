#include "MapData.h"

#ifdef _CODEBLOCKS_
#include <cstdlib>
#endif

MapData::MapData(void)
{
	layout = NULL;
	mapStatus = NULL;
};

MapData::~MapData(void)
{
	// Se libera el layout
	freeLayout(layout);
	if (mapStatus != NULL)
		delete mapStatus, mapStatus = NULL;
};

void MapData::init(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMiniBosses, int numCollectables)
{
	this->mapId = mapId;
	mapType = type;
	width = w;
	height = h;

	// Liberar antes el layout por si hay varios init
	freeLayout(this->layout);

	// Se inicia el layout
	this->layout = (int**) malloc(sizeof(int*)*w);
	for (int i = 0; i < w; i++)
		this->layout[i] = (int*) malloc(sizeof(int)*h);

	// Se copia el layout nuevo
	for (int xx = 0; xx < w; xx++)
		for (int yy = 0; yy < h; yy++)
			this->layout[xx][yy] = layout[xx][yy];

	this->numPuzzles = numPuzzles;
	this->numDoors = numDoors;
	this->numMiniBosses = numMiniBosses;
	this->numCollectables = numCollectables;

	// Se inicia el mapStatus
	switch (type)
	{
	case 0: // OWorld
		mapStatus = new OverWorldMapStatus();
		((OverWorldMapStatus*) mapStatus)->init();
		break;
	case 1: // Dungeon
		mapStatus = new DungeonMapStatus();
		((DungeonMapStatus*) mapStatus)->init();
		break;
	default:
		break;
	}
};

void MapData::freeLayout(int** l)
{
	if (l == NULL) return;

	for (int i = 0; i < width; i++)
			free(l[i]), l[i] = NULL;
	free(l);
	l = NULL;
};

//! Obtiene el id del mapa
int MapData::getId()
{
	return mapId;
};

void MapData::setId(int id){
	mapId = id;
}

//! Obtiene el ancho del mapa (en pantallas)
int MapData::getWidth()
{
	return width;
};

void MapData::setWidth(int width){
	this->width = width;
}

//! Obtiene el alto del mapa (en pantallas)
int MapData::getHeight()
{
	return height;
};

void MapData::setHeight(int height){
	this->height = height;
}

//! Obtiene el layout del mapa
const int** MapData::getLayout()
{
	return (const int**) layout;
};

void MapData::setLayout(int** layout){
	// Liberar antes el layout por si hay varios init
	freeLayout(this->layout);

	// Se inicia el layout
	this->layout = (int**) malloc(sizeof(int*)*width);
	for (int i = 0; i < width; i++)
		this->layout[i] = (int*) malloc(sizeof(int)*height);

	// Se copia el layout nuevo
	for (int xx = 0; xx < width; xx++)
		for (int yy = 0; yy < height; yy++)
			this->layout[xx][yy] = layout[xx][yy];
}

//! Indica si la pantalla indicada existe o no
bool MapData::hasScreen(int x, int y)
{
	if (x >= 0 && y >= 0 && x < width && y < height && layout != NULL)
		return (layout[x][y] != 0);
	else return false;
};

//! Obtiene el número total de minibosses del mapa
int MapData::getNumMiniBosses()
{
	return numMiniBosses;
};

void MapData::setNumMiniBosses(int miniBosses){
	numMiniBosses = miniBosses;
}

//! Obtiene el número total de puzzles del mapa
int MapData::getNumPuzzles()
{
	return numPuzzles;
};

void MapData::setNumPuzzles(int puzzles){
	numPuzzles = puzzles;
}

//! Obtiene el número total de puertas del mapa
int MapData::getNumDoors()
{
	return numDoors;
};

void MapData::setNumDoors(int doors){
	numDoors = doors;
}

//! Obtiene el número de collectables del mapa
int MapData::getNumCollectables()
{
	return numCollectables;
};

void MapData::setNumCollectables(int collectables){
	numCollectables = collectables;
}

// getExit, getStartPoint, ...
std::pair<int, int> MapData::getStartScreen()
{
	return startScreen;
};

bool MapData::setStartScreen(int x, int y)
{
	// No se puede establecer una pantalla inicial inexistente
	if (!hasScreen(x, y))
		return false;
	else
		// Si existe, se establece
		startScreen.first = x,
		startScreen.second = y;

	return true;
};

MapStatus* MapData::getMapStatus()
{
	return mapStatus;
};

char MapData::getType()
{
	return mapType;
};

void MapData::save(FILE* f){
	// Tipo del mapa (0: ow, 1: d)
	char* buffer1 = new char[1];
	buffer1[0] = mapType;
	fwrite(buffer1, sizeof(char), 1, f);
	delete buffer1; buffer1 = NULL;

	if (mapType == 1){
		// Estado del mapa de mazmorra
		((DungeonMapStatus*) mapStatus)->save(f);
	}
	else if (mapType == 0){
		// Estado del mapa del mundo
		((OverWorldMapStatus*) mapStatus)->save(f);
	}
};

void MapData::load(FILE* f){
	// Tipo del mapa (0: ow, 1: d)
	char buffer1[1];
	fread(buffer1, sizeof(char), 1, f);
	mapType = buffer1[0];

	// Se inicia el mapStatus
	switch (mapType){
		case 0: // OWorld
			mapStatus = new OverWorldMapStatus();
			((OverWorldMapStatus*) mapStatus)->load(f);
			break;
		case 1: // Dungeon
			mapStatus = new DungeonMapStatus();
			((DungeonMapStatus*) mapStatus)->load(f);
			break;
		default:
			break;
	}
};