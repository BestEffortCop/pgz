#include "DunDecorator.h"

DunDecorator::DunDecorator(DBManager* db) : Decorator(db){}

DunDecorator::~DunDecorator(){}

void DunDecorator::init(string zone, string theme, short tileSetId){
	Decorator::init(zone, theme, tileSetId);

	info.terrainId = -1;
	info.statueId = -1;
	info.torchId = -1;

	if (autoTiler != NULL) delete autoTiler; // si había un autotiler anterior lo borramos
	autoTiler = new DungeonAutoTiler(db->getPath("TileSet", tileSetId));	 // creamos el nuevo
}

void DunDecorator::decorate(Screen* screen){

	screen->setIdTileset(idTileset);

// TERRENOS ----------------------------------------------------------------------------------------------------------

	int terrainVar; // variación del terreno principal que puede aparecer en ciertas pantallas de la mazmorra

	// Cambiamos o mantenemos los terrenos con los que estamos decorando
	if (changedZone) // tenemos que cambiar de terrenos
	{
		info.wallId = ((DungeonAutoTiler*) autoTiler)->getTerrainId(Terrain::TerrainType::dungeonWall);
		info.terrainId = autoTiler->getTerrainId(Terrain::TerrainType::walk);
	}
	else // cogemos una variación para el suelo
	{
		terrainVar = autoTiler->getVariation(info.terrainId, Terrain::TerrainType::walk);
		if (terrainVar != -1)	// si hay variaciones, intentamos variar el terreno principal
		{
			// damos un 33% de posibilidades de que se ponga la variación
			int r = rand() % 3;
			if (r == 0)
				info.terrainId = terrainVar;
		}
	}

	// colocación de los terrenos en la mazmorra
	terrainIdMatrix = (int**) malloc(sizeof(int*)*SCREEN_WIDTH);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		terrainIdMatrix[i] = (int*) malloc(sizeof(int)*SCREEN_HEIGHT);
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			short type = screen->getSolid(i, j);
			if (type == 1)
				terrainIdMatrix[i][j] = info.wallId;
			else
				terrainIdMatrix[i][j] = info.terrainId;
		}
	}

	// Ahora se guarda en screen (los terrenos)
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			((DungeonAutoTiler*) autoTiler)->getTerrain(terrainIdMatrix[i][j])->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
		}
	}

	// colocamos suelo debajo de las entidades (muros) para cosas de perspectiva del player
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			if (screen->isThereAnyEntityAt(screen->getEntities(), j*SCREEN_WIDTH + i)){
				screen->setSolid(i, j, 0);
				((DungeonAutoTiler*) autoTiler)->getTerrain(info.terrainId)->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
			}
		}
	}

	// limpiamos la matriz de terrenos
	clearTerrains();
	
// DECORACIONES ---------------------------------------------------------------------------------------------------------------

	// colocamos objetos en las paredes (antorchas o lo que toque)
	place_torchs(screen);

	// colocamos estatuas (o lo que toque) en las posiciones indicadas por el generador
	for (int i = 0; i < SCREEN_WIDTH; i++)	
		for (int j = 0; j < SCREEN_HEIGHT; j++){
			// Si leemos un sólido (ponemos estatua)
			if (screen->getSolid(i, j) == 2){	// Identificar que hay un solido (estatua)
				Decoration* decoStatue = autoTiler->getDecoration(Decoration::dungeonStatue, Decoration::small, info.terrainId);
				// Inicializamos la decoración
				decoStatue->init(i, j - (decoStatue->getDecorationData().height - 1));
				// Cambiamos el sólido para que sea pasable por detrás
				screen->setSolid(i, j, 0);
				// La añadimos a la lista de decoraciones
				if (checkDecoCollision(decoStatue) && isInBounds(decoStatue, screen) && checkSolidCollision(decoStatue, screen))
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

// Fin decoraciones  ------------------------------------------------------------------------------------------------
}

bool DunDecorator::place_upperTorch(Screen* screen, int col, int row)
{
	if (screen->getSolid(col, row) == 1 && screen->getSolid(col, row + 1) != 1 
		&& screen->getSolid(col - 1, row) == 1 && screen->getSolid(col + 1, row) == 1)
	{
		Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonTorch(DunDecorationPos::top);
		if (decoTorch != NULL)
		{
			// Inicializamos la decoración
			decoTorch->init(col, row);
			// La añadimos a la lista de decoraciones
			decorationList.push_back(decoTorch);
			return true;
		}
	}

	// si algo ha salido mal
	return false;
}

bool DunDecorator::place_siderTorch(Screen* screen, int col, int row, DunDecorationPos pos)
{
	if (screen->getSolid(col, row) == 1 && screen->getSolid(col + 1, row) != 1 
		&& screen->getSolid(col, row - 1) == 1 && screen->getSolid(col, row + 1) == 1)
	{
		Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonTorch(pos);
		if (decoTorch != NULL)
		{
			// Inicializamos la decoración
			decoTorch->init(col, row);
			// La añadimos a la lista de decoraciones
			decorationList.push_back(decoTorch);
			return true;
		}
	}

	// si algo ha salido mal
	return false;
}

void DunDecorator::place_torchs(Screen* screen)
{
	int row;
	int col;
	bool placed = false;

	// intentamos poner antorchas ARRIBA -----------------------------------------------

	// ponemos la de la izq.
	row = 1;
	col = SCREEN_WIDTH / 4;
	// intentamos ponerla en las dos primeras filas
	while (!placed && row < 3)
	{
		if (!(placed = place_upperTorch(screen, col, row)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_upperTorch(screen, col -1, row)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_upperTorch(screen, col +1, row);
		row++;
	}

	// ponemos la antorcha de la der.
	row = 1;
	col =  3 * (SCREEN_WIDTH / 4);

	// intentamos ponerla en las dos primeras filas
	placed = false;
	while (!placed && row < 3)
	{
		if (!(placed = place_upperTorch(screen, col, row)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_upperTorch(screen, col -1, row)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_upperTorch(screen, col +1, row);
		row++;
	}
/*
	// intentamos poner antorchas A LA DERECHA -----------------------------------------------

	// ponemos la de la arriba
	row = SCREEN_HEIGHT / 4;
	col = 1;
	// intentamos ponerla en las dos primeras columnas
	placed = false;
	while (!placed && col < 3)
	{
		if (!(placed = place_siderTorch(screen, col, row, DunDecorationPos::right)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_siderTorch(screen, col, row -1, DunDecorationPos::right)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_siderTorch(screen, col, row +1, DunDecorationPos::right);
		col++;
	}

	// ponemos la antorcha de la abajo
	row = 3 * (SCREEN_HEIGHT / 4);
	col = 1;

	// intentamos ponerla en las dos primeras filas
	placed = false;
	while (!placed && col < 3)
	{
		if (!(placed = place_siderTorch(screen, col, row, DunDecorationPos::right)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_siderTorch(screen, col, row -1, DunDecorationPos::right)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_siderTorch(screen, col, row +1, DunDecorationPos::right);
		col++;
	}

	// intentamos poner antorchas A LA IZQUIERDA -----------------------------------------------

	// ponemos la de la arriba
	row = SCREEN_HEIGHT / 4;
	col = SCREEN_WIDTH - 2;
	// intentamos ponerla en las dos primeras columnas
	placed = false;
	while (!placed && col < 3)
	{
		if (!(placed = place_siderTorch(screen, col, row, DunDecorationPos::left)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_siderTorch(screen, col, row -1, DunDecorationPos::left)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_siderTorch(screen, col, row +1, DunDecorationPos::left);
		col++;
	}

	// ponemos la antorcha de la abajo
	row = 3 * (SCREEN_HEIGHT / 4);
	col = SCREEN_WIDTH - 2;

	// intentamos ponerla en las dos primeras filas
	placed = false;
	while (!placed && col < 3)
	{
		if (!(placed = place_siderTorch(screen, col, row, DunDecorationPos::left)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_siderTorch(screen, col, row -1, DunDecorationPos::left)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_siderTorch(screen, col, row +1, DunDecorationPos::left);
		col++;
	}*/
}