#include "DunDecorator.h"

DunDecorator::DunDecorator(DBManager* db) : Decorator(db){}

DunDecorator::~DunDecorator(){}

void DunDecorator::init(string zone, string theme, short tileSetId){
	Decorator::init(zone, theme, tileSetId);
	
	if (autoTiler != NULL) delete autoTiler; // si había un autotiler anterior lo borramos
	autoTiler = new DungeonAutoTiler(db->getPath("TileSet", tileSetId));	 // creamos el nuevo
}

void DunDecorator::decorate(Screen* screen){

	screen->setIdTileset(idTileset);

	int wallId = ((DungeonAutoTiler*) autoTiler)->getTerrainId(Terrain::TerrainType::dungeonWall);
	int terrainId = autoTiler->getTerrainId(Terrain::TerrainType::walk);

	terrainIdMatrix = (int**) malloc(sizeof(int*)*SCREEN_WIDTH);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		terrainIdMatrix[i] = (int*) malloc(sizeof(int)*SCREEN_HEIGHT);
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			short type = screen->getSolid(i, j);
			if (type == 1)
				terrainIdMatrix[i][j] = wallId;
			else
				terrainIdMatrix[i][j] = terrainId;
		}
	}
	/*
	// Decoraciones
	Decoration* decoTorch = autoTiler->getDecoration(0);	// Antorcha
	Decoration* decoStatue = autoTiler->getDecoration(1);	// Estatua

	for (int i = 0; i < SCREEN_WIDTH; i++)	
		for (int j = 0; j < SCREEN_HEIGHT; j++){
			// Si leemos un muro
			/*if (screen->getSolid(i,j) == 1){
				// Inicializamos la decoración
				decoTorch->init(i,j);
				// La añadimos a la lista de decoraciones
				decorationList.push_back(decoTorch);
			}*//*
			// Si leemos un sólido
			if (screen->getSolid(i, j) == 2){	// Identificar que hay un solido		**** NO SE COMO ESTA IDENTIFICADO
				// Inicializamos la decoración
				decoStatue->init(j, i);
				// La añadimos a la lista de decoraciones
				decorationList.push_back(decoStatue);
			}
		}

	// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != NULL)
			screen->addEntity((*it)->toEntities());

	// Borramos la lista de decoraciones
	clearDecorations();

	// Fin decoraciones*/

	// Ahora se guarda en screen
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			((DungeonAutoTiler*) autoTiler)->getTerrain(terrainIdMatrix[i][j])->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
		}
	}

	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			if (screen->isThereAnyEntityAt(screen->getEntities(), j*SCREEN_WIDTH + i)){
				((DungeonAutoTiler*) autoTiler)->getTerrain(terrainId)->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
			}
		}
	}

	// limpiamos la matriz de terrenos
	clearTerrains();
}

bool DunDecorator::isInBounds(Decoration* d, Screen* s){
	return true;
}