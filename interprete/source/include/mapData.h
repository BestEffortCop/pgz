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

	// Número de minibosses de la mazmorra
	int numMiniBosses;

	// Número de Puzzles de la mazmorra
	int numPuzzles;

	// Número de puertas en la mazmorra
	int numDoors;

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

	void init(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses);

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

	// getExit, getStartPoint, ...
	std::pair<int, int> getStartScreen();

	MapStatus* getMapStatus();
};
#endif
