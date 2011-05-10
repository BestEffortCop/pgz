#include "Decorator.h"

Decorator::Decorator()
{
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

void Decorator::init(string zone, string theme, string tileSetPath)
{
	this->zone = zone;
	this->theme = theme;

	if (autoTiler != NULL) delete autoTiler; // si había un autotiler anterior lo borramos
	autoTiler = new AutoTiler(tileSetPath);	 // creamos el nuevo
}

void Decorator::decorate(Screen* screen)
{
	// Magic goes here!
	// recorremos poniendo 0 en no solid, 1 en solid
	// Y currando a 16x16!

	// Colocamos terrenos
	int waterId = autoTiler->getTerrainId(Terrain::water);
	int floorId = autoTiler->getVariation(waterId, Terrain::walk);
	int solidId = autoTiler->getTerrainId(Terrain::solid);
	int pathId = autoTiler->getVariation(floorId, Terrain::walk);

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

	// FALTA COMPROBAR QUE LAS ENTIDADES QUEPAN Y TOENTITIES!!!!!!!!!!!!!!!!*************************

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
			if (checkDecoCollision(decoPath))
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
			if (checkDecoCollision(decoFloor))
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
			if (checkDecoCollision(decoMedium))
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
			if (checkDecoCollision(decoBig))
				decorationList.push_back(decoBig);
		}

		// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
		list<Decoration*>::iterator it;
		std::vector<Entity*> ents;
		for (it = decorationList.begin(); it != decorationList.end(); it++)
			if (*it != NULL){
				ents = (*it)->toEntities();
				for (int i = 0; i < ents.size(); i++)
					// Añadimos las entidades a la screen
					ows->addEntity(ents[i]);
				//delete (*it);
				//(*it) = NULL;
			}

		// Borramos el vector de posiciones
		delete posUsed;
		posUsed = NULL;

		// Borramos la lista de decoraciones
		clearDecorations();
	}	

	// Ahora se guarda en screen
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			autoTiler->getTerrain(terrainIdMatrix[i][j])->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
		}
	}

	// limpiamos la matriz de terrenos
	clearTerrains();
};

void Decorator::clearDecorations()
{
	// borramos las decoraciones que no hayan sido borradas
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++){
		if (*it != NULL) delete (*it);
	}

	decorationList.clear();
}

void Decorator::clearTerrains()
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
		delete (terrainIdMatrix[i]);

	delete (terrainIdMatrix);
}

short Decorator::gimmeTile() {
	// To be implemented
	return 0;
}

short Decorator::gimmeFloorButton() {
	return 0;
}

bool Decorator::checkDecoCollision(Decoration* d)
{
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
		}
	// hemos recorrido toda la lista sin ninguna colisión
	return true;
}