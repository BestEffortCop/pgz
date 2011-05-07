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

//! Obtiene el ancho del mapa (en pantallas)
int MapData::getWidth()
{
	return width;
};

//! Obtiene el alto del mapa (en pantallas)
int MapData::getHeight()
{
	return height;
};

//! Obtiene el layout del mapa
const int** MapData::getLayout()
{
	return (const int**) layout;
};

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

//! Obtiene el número total de puzzles del mapa
int MapData::getNumPuzzles()
{
	return numPuzzles;
};

//! Obtiene el número total de puertas del mapa
int MapData::getNumDoors()
{
	return numDoors;
};

//! Obtiene el número de collectables del mapa
int MapData::getNumCollectables()
{
	return numCollectables;
};

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

	if (mapType == '1'){
		// Estado del mapa de mazmorra
		((DungeonMapStatus*) mapStatus)->save(f);
	}
	else if (mapType == '0'){
		// Estado del mapa del mundo
		((OverWorldMapStatus*) mapStatus)->save(f);
	}

	int* buffer = new int[9];

	// Ancho
	buffer[0] = width;
	// Alto
	buffer[1] = height;
	// Minibosses
	buffer[2] = numMiniBosses;
	// Número de puzzles
	buffer[3] = numPuzzles;
	// Número de puertas
	buffer[4] = numDoors;
	// Número de coleccionables
	buffer[5] = numCollectables;
	// Id del mapa
	buffer[6] = mapId;
	// Pantalla inicial del mapa
	buffer[7] = startScreen.first;
	buffer[8] = startScreen.second;

	fwrite(buffer, sizeof(int), 9, f);
	delete buffer; buffer = new int[1];

	// Layout del mapa
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++){
			buffer[0] = layout[i][j];
			fwrite(buffer, sizeof(int), 1, f);
		}
	delete buffer; buffer = NULL;
};

void MapData::load(FILE* f){
	// Tipo del mapa (0: ow, 1: d)
	fscanf(f, "%c", &mapType);

	if (mapType == '1'){
		// Estado del mapa de mazmorra
		((DungeonMapStatus*) mapStatus)->load(f);
	}
	else if (mapType == '0'){
		// Estado del mapa del mundo
		((OverWorldMapStatus*) mapStatus)->load(f);
	}

	// Ancho
	fscanf(f, "%d", &width);
	// Alto
	fscanf(f, "%d", &height);
	// Minibosses
	fscanf(f, "%d", &numMiniBosses);
	// Número de puzzles
	fscanf(f, "%d", &numPuzzles);
	// Número de puertas
	fscanf(f, "%d", &numDoors);
	// Número de coleccionables
	fscanf(f, "%d", &numCollectables);
	// Id del mapa
	fscanf(f, "%d", &mapId);
	// Pantalla inicial del mapa
	fscanf(f, "%d", &startScreen.first);
	fscanf(f, "%d", &startScreen.second);

	// Layout del mapa
    layout = new int*[width];
    for (int i = 0; i < width; i++)
        layout[i] = new int[height];

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++){
			fscanf(f, "%d", &layout[i][j]);
		}
};