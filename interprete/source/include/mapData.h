#ifndef _MAPDATA_H
#define _MAPDATA_H

#include <utility>

#include "OverWorldMapStatus.h"
#include "DungeonMapStatus.h"

class MapData 
{

private:
	// Ancho en pantallas del mapa
	int width;

	// Alto en pantallas del mapa
	int height;

	// Layout del mapa
	int** layout;

	// Número de minibosses del mapa
	int numMiniBosses;

	// Número de Puzzles del mapa
	int numPuzzles;

	// Número de puertas del mapa
	int numDoors;

	// Número de collectables del mapa
	int numCollectables;

	// Identificador del mapa
	int mapId;

	// Tipo del mapa (0: ow, 1: d)
	char mapType;

	// Pantalla inicial del mapa
	std::pair<int, int> startScreen;

	// Estado del mapa
	MapStatus* mapStatus;

	// Libera la memoria del layout
	void freeLayout(int** layout);

public:
	MapData(void);

	~MapData(void);

	void init(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses, int numCollectables);

	//! Obtiene el id del mapa
	int getId();

	//! Obtiene el ancho del mapa (en pantallas)
	int getWidth();

	//! Obtiene el alto del mapa (en pantallas)
	int getHeight();

	//! Obtiene el layout del mapa
	const int** getLayout();

	//! Indica si la pantalla indicada existe o no
	bool hasScreen(int x, int y);

	//! Obtiene el número total de minibosses del mapa
	int getNumMiniBosses();

	//! Obtiene el número total de puzzles del mapa
	int getNumPuzzles();

	//! Obtiene el número total de puertas del mapa
	int getNumDoors();

	//! Obtiene el número de collectables
	int getNumCollectables();

	// getExit, getStartPoint, ...
	std::pair<int, int> getStartScreen();

	//! Establece la pantalla inicial del mapa
	bool setStartScreen(int screenX, int screenY);

	MapStatus* getMapStatus();

	char getType();

	void save(FILE* f);
};
#endif
