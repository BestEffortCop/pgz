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

		// Ahora se guarda en screen (de terrenos)
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
				screen->setSolid(i, j, 0);
				((DungeonAutoTiler*) autoTiler)->getTerrain(terrainId)->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
			}
		}
	}

	// limpiamos la matriz de terrenos
	clearTerrains();
	
	// Decoraciones ---------------------------------------------------------------------------------------------------------------

	place_torchs(screen);

	for (int i = 0; i < SCREEN_WIDTH; i++)	
		for (int j = 0; j < SCREEN_HEIGHT; j++){
			// Si leemos un sólido (ponemos estatua)
			if (screen->getSolid(i, j) == 2){	// Identificar que hay un solido (estatua)
				Decoration* decoStatue = autoTiler->getDecoration(Decoration::dungeonStatue, Decoration::small, terrainId);
				// Inicializamos la decoración
				decoStatue->init(i, j - (decoStatue->getDecorationData().height - 1));
				// Cambiamos el sólido para que sea pasable por detrás
				screen->setSolid(i,j, 0);
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

	// Fin decoraciones*/         --------------------------------------------------------------------------------------------
}

void DunDecorator::place_torchs(Screen* screen)
{
	int row;
	int col;

	// intentamos poner antorchas arriba -----------------------------------------------
	row = 1;
	col = SCREEN_WIDTH / 4;

	// ponemos la antorcha de la izq.
	if (screen->getSolid(col, row) == 1 && screen->getSolid(col, row + 1) == 0 
		&& screen->getSolid(col - 1, row) == 1 && screen->getSolid(col + 1, row) == 1)
	{
		Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonTorch(DunDecorationPos::top);
		if (decoTorch != NULL)
		{
			// Inicializamos la decoración
			decoTorch->init(col, row);
			// La añadimos a la lista de decoraciones
			decorationList.push_back(decoTorch);
		}
	}

	row = 1;
	col =  3 * (SCREEN_WIDTH / 4);

	// ponemos la antorcha de la der.
	if (screen->getSolid(col, row) == 1 && screen->getSolid(col, row + 1) == 0 
		&& screen->getSolid(col - 1, row) == 1 && screen->getSolid(col + 1, row) == 1)
	{
		Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonTorch(DunDecorationPos::top);
		if (decoTorch != NULL)
		{
			// Inicializamos la decoración
			decoTorch->init(col, row);
			// La añadimos a la lista de decoraciones
			decorationList.push_back(decoTorch);
		}
	}

}