#include "Decorator.h"

Decorator::Decorator(DBManager* db)
{
	this->db = db;
	theme = "";
	zone = "";
	autoTiler = NULL;
	terrainIdMatrix = NULL;
}

Decorator::~Decorator()
{
	if (autoTiler != NULL) delete autoTiler;

	clearDecorations();
}

void Decorator::init(string zone, string theme, short tileSetId)
{
	this->zone = zone;
	this->theme = theme;
	idTileset = tileSetId;
}

void Decorator::decorate(Screen* screen)
{
	// Magic goes here!
	// recorremos poniendo 0 en no solid, 1 en solid
	// Y currando a 16x16!
	/*
	// Colocamos terrenos
	int waterId = autoTiler->getTerrainId(Terrain::water);
	int floorId = autoTiler->getVariation(waterId, Terrain::walk);
	int solidId = autoTiler->getTerrainId(Terrain::solid);
	int pathId = autoTiler->getVariation(floorId, Terrain::walk);

	if (OwScreen* ows = dynamic_cast<OwScreen*> (screen)){
		// Colocamos decoraciones
		Decoration* decoPath = autoTiler->getDecoration(Decoration::solid, Decoration::small, pathId); 
		Decoration* decoFloor = autoTiler->getDecoration(Decoration::solid, Decoration::small, floorId); 
		Decoration* decoMedium = autoTiler->getDecoration(Decoration::solid, Decoration::medium, floorId);
		Decoration* decoBig = autoTiler->getDecoration(Decoration::solid, Decoration::big, pathId);

		// Buscamos una posición libre
		vector<int>* posUsed = new vector<int>; // Vector de posiciones utilizadas
		int pos;

		// Deco1
		pos = ows->getFreePos(posUsed);
		if (pos != -1){
			// Ponemos alguna decoracion en la posición pos
			posUsed->push_back(pos);
			// Inicializamos la decoración
			decoPath->init(pos % SCREEN_WIDTH, pos / SCREEN_WIDTH);
			// La guardamos en la lista de decoraciones (si no colisiona con ninguna)
			if (checkDecoCollision(decoPath) && isInBounds(decoPath, screen) && checkSolidCollision(decoPath, screen))
				decorationList.push_back(decoPath);
		}

		// Deco2
		pos = ows->getFreePos(posUsed);
		if (pos != -1){
			// Ponemos alguna decoracion en la posición pos
			posUsed->push_back(pos);
			// Inicializamos la decoración
			decoFloor->init(pos % SCREEN_WIDTH, pos / SCREEN_WIDTH);
			// La guardamos en la lista de decoraciones (si no colisiona con ninguna)
			if (checkDecoCollision(decoFloor) && isInBounds(decoFloor, screen) && checkSolidCollision(decoFloor, screen))
				decorationList.push_back(decoFloor);
		}

		// Deco3
		pos = ows->getFreePos(posUsed);
		if (pos != -1){
			// Ponemos alguna decoracion en la posición pos
			posUsed->push_back(pos);
			// Inicializamos la decoración
			decoMedium->init(pos % SCREEN_WIDTH, pos / SCREEN_WIDTH);
			// La guardamos en la lista de decoraciones (si no colisiona con ninguna)
			if (checkDecoCollision(decoMedium) && isInBounds(decoMedium, screen) && checkSolidCollision(decoMedium, screen))
				decorationList.push_back(decoMedium);
		}

		// Deco4
		pos = ows->getFreePos(posUsed);
		if (pos != -1){
			// Ponemos alguna decoracion en la posición pos
			posUsed->push_back(pos);
			// Inicializamos la decoración
			decoBig->init(pos % SCREEN_WIDTH, pos / SCREEN_WIDTH);
			// La guardamos en la lista de decoraciones (si no colisiona con ninguna)
			if (checkDecoCollision(decoBig) && isInBounds(decoBig, screen) && checkSolidCollision(decoBig, screen))
				decorationList.push_back(decoBig);
		}

		// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
		list<Decoration*>::iterator it;
		for (it = decorationList.begin(); it != decorationList.end(); it++)
			if (*it != NULL)
				ows->addEntity((*it)->toEntities());

		// Borramos el vector de posiciones
		delete posUsed;
		posUsed = NULL;

		// Borramos la lista de decoraciones
		clearDecorations();
	}	

	// Terrenos

	terrainIdMatrix = (int**) malloc(sizeof(int*)*SCREEN_WIDTH);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		terrainIdMatrix[i] = (int*) malloc(sizeof(int)*SCREEN_HEIGHT);
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			short type = screen->getSolid(i, j);
			if (type == 0)
				terrainIdMatrix[i][j] = floorId;
			else if (type == 1)
				terrainIdMatrix[i][j] = solidId;
			else if (type == 2)
				terrainIdMatrix[i][j] = waterId;//, screen->setSolid(i, j, 1);
			else if (type == 3)
				terrainIdMatrix[i][j] = pathId, screen->setSolid(i, j, 0);
			else if (type == 4)
				terrainIdMatrix[i][j] = solidId, screen->setSolid(i, j, 1);
			else
				terrainIdMatrix[i][j] = solidId, screen->setSolid(i, j, 1);
		}
	}

	terrainsToTiles(screen);

	// limpiamos la matriz de terrenos
	clearTerrains();*/
};

void Decorator::terrainsToTiles(Screen* screen)
{/*
	// Ahora se guarda en screen
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			autoTiler->getTerrain(terrainIdMatrix[i][j])->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
		}
	}*/
}

void Decorator::clearDecorations()
{/*
	// borramos las decoraciones que no hayan sido borradas
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++){
		if (*it != NULL) delete (*it);
	}

	decorationList.clear();*/
}

void Decorator::clearTerrains()
{/*
	if (terrainIdMatrix == NULL) return;

	for (int i = 0; i < SCREEN_WIDTH; i++)
		if (terrainIdMatrix[i] != NULL) delete (terrainIdMatrix[i]);

	delete (terrainIdMatrix);*/
}

short Decorator::gimmeTile() {
	// To be implemented
	return 0;
}

short Decorator::gimmeFloorButton() {
	return 0;
}

bool Decorator::isInBounds(Decoration* d, Screen* s)
{/*
	// comprobamos que no se salga de la pantalla
	if (d->x + d->getDecorationData().width > SCREEN_WIDTH || d->y + d->getDecorationData().height > SCREEN_HEIGHT)
		return false;
	else*/
		return true;
}

bool Decorator::checkDecoCollision(Decoration* d)
{/*
	// variables auxiliares para trabajar más cómodamente
	int itx, ity, itw, ith;
	int dw = d->getDecorationData().width;	// ancho de la decoración con la que se comprueba
	int dh = d->getDecorationData().height;	// alto de la decoración con la que se comprueba
	int dx = d->x;	
	int dy = d->y;

	// recorremos la lista de decoraciones para ver si colisiona con alguna
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != d) // si no es la propia decoración (que podría estar dentro de la lista)
		{
			// guardamos los valores de la decoración de la lista para trabajar más cómodamente
			itx = (*it)->x;
			ity = (*it)->y;
			itw = (*it)->getDecorationData().width;
			ith = (*it)->getDecorationData().height;
			
			// comprobamos colisión entre los cuadrados de las decoraciones
			if (dx + dw <= itx || dy + dh <= ity)
				continue;	// no colisionan y seguimos evaluando con otras decoraciones

			if (dx >= itx + itw || dy >= ity + ith)
				continue;	// no colisionan y seguimos evaluando con otras decoraciones

			// ha habido colisión
			return false;
		}*/
	// hemos recorrido toda la lista sin ninguna colisión
	return true;
}

bool Decorator::checkSolidCollision(Decoration* d, Screen* s){
	/*
	// Recocrremos la decoración
	for (int i = 0; i < d->getDecorationData().height; i++)
		for (int j = 0; j < d->getDecorationData().width; j++)
			// Si en la posición de la decoración hay algo que no sea libre devolvemos false
			if (s->getSolid(d->y + j, d->x + i) != 0)
				return false;*/
	return true;
}