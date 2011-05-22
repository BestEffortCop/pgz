#include "WorldDecorator.h"

WorldDecorator::WorldDecorator(DBManager* db) : Decorator(db){}

WorldDecorator::~WorldDecorator(){}

void WorldDecorator::init(string zone, string theme, short tileSetId)
{
	Decorator::init(zone, theme, tileSetId);

	info.floorId = -1;
	info.pathId = -1;
	info.solidId = -1;
	info.waterId = -1;

	if (autoTiler != NULL) delete autoTiler; // si había un autotiler anterior lo borramos
	autoTiler = new WorldAutoTiler(db->getPath("TileSet", tileSetId));	 // creamos el nuevo
}

void WorldDecorator::decorate(Screen* screen)
{
	// Magic goes here!
	// recorremos poniendo 0 en no solid, 1 en solid
	// Y currando a 16x16!

	screen->setIdTileset(idTileset);	// le decimos a la screen cuál es su tileset

	// Cambiamos o mantenemos los terrenos con los que estamos decorando
	if (changedZone) // tenemos que cambiar de terrenos
	{
		info.waterId = autoTiler->getTerrainId(Terrain::water);
		info.floorId = autoTiler->getVariation(info.waterId, Terrain::walk);
		info.solidId = autoTiler->getTerrainId(Terrain::solid);
		info.pathId = autoTiler->getVariation(info.floorId, Terrain::walk);
	}
/*
//-------------------------------------------------- ALGORITMO DE COLOCAR DECORACIONES -----------------------------------------------------------	
	//Colocamos decoraciones
	int screenSize = SCREEN_WIDTH * SCREEN_HEIGHT;
	
	int idDeco = -1;
	int auxId = idDeco;
	int nDeco = 0;	//nº decoraciones a colocar
	int auxDeco = 0;	//nº decoraciones colocadas

	//Calculamos el número de decoraciones grandes a colocar
	if (getFreeSpace(screen) > screenSize / 4)
		nDeco = 1;

	vector<int>* posUsed = new vector<int>; // Vector de posiciones utilizadas
	int pos;
	int auxPos;

	while (auxDeco < nDeco)
	{
		pos = screen->getFreePos(posUsed);
		auxPos = pos;
		auxId = -1;

		while(auxId == -1)
		{
			auxId = place_deco(screen,Decoration::DecorationSize::big, Decoration::DecorationType::tNone, idDeco, pos);
			auxPos = (auxPos + 1) % (SCREEN_WIDTH*SCREEN_HEIGHT);

			if(auxDeco != -1)
				idDeco = auxId;

			if(auxPos == pos)
				auxId = 0;
		}
		auxDeco++;
		posUsed->push_back(pos);
	}

	//Calculamos nº de decoraciones medianas a colocar
	if(getFreeSpace(screen) > screenSize / 16)
	{
		auxDeco = 0;
		nDeco = 2;
		idDeco = -1;
	}

	//Colocamos las decoraciones medianas
	while (auxDeco < nDeco)
	{
		pos = screen->getFreePos(posUsed);
		auxPos = pos;
		auxId = -1;

		while(auxId == -1)
		{
			auxId = place_deco(screen,Decoration::DecorationSize::medium, Decoration::DecorationType::tNone, idDeco, pos);
			auxPos = (auxPos + 1) % (SCREEN_WIDTH*SCREEN_HEIGHT);

			if(auxId != -1)
				idDeco = auxId;

			if(auxPos == pos)
				auxId = 0;
		}
		auxDeco++;
		posUsed->push_back(pos);
	}

	//Calculamos nº de decoracioens pequeñas a colocar
	if(getFreeSpace(screen) > screenSize/32)
	{
		auxDeco = 0;
		nDeco = ((rand() % 7) + 1);
		idDeco = -1;
	}

	//Colocamos las decoraciones pequeñas
	while (auxDeco < nDeco)
	{
		pos = screen->getFreePos(posUsed);
		auxPos = pos;
		auxId = -1;

		while(auxId == -1)
		{
			auxId = place_deco(screen,Decoration::DecorationSize::small, Decoration::DecorationType::tNone, idDeco, pos);
			auxPos = (auxPos + 1) % (SCREEN_WIDTH*SCREEN_HEIGHT);

			if(auxId != -1)
				idDeco = auxId;

			if(auxPos == pos)
				auxId = 0;
		}
		auxDeco++;
		posUsed->push_back(pos);
	}

	delete posUsed; posUsed = NULL;

	// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != NULL)
			screen->addEntity((*it)->toEntities());

	clearDecorations();
//--------------------------------------------HASTA AQUI DECORACIONES -----------------------------------------------------------------------
*/	
	// Terrenos

	// los colocamos en la screen
	terrainIdMatrix = (int**) malloc(sizeof(int*)*SCREEN_WIDTH);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		terrainIdMatrix[i] = (int*) malloc(sizeof(int)*SCREEN_HEIGHT);
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			short type = screen->getSolid(i, j);
			if (type == 0)
				terrainIdMatrix[i][j] = info.floorId;
			else if (type == 1)
				terrainIdMatrix[i][j] = info.solidId;
			else if (type == 2)
				terrainIdMatrix[i][j] = info.waterId;//, screen->setSolid(i, j, 1);
			else if (type == 3)
				terrainIdMatrix[i][j] = info.pathId, screen->setSolid(i, j, 0);
			else if (type == 4)
				terrainIdMatrix[i][j] = info.solidId, screen->setSolid(i, j, 1);
			else
				terrainIdMatrix[i][j] = info.solidId, screen->setSolid(i, j, 1);
		}
	}

	// los pintamos en la screen
	terrainsToTiles(screen);

	// limpiamos la matriz de terrenos
	clearTerrains();
};

int WorldDecorator::place_deco(Screen* s, Decoration::DecorationSize size, Decoration::DecorationType type, int idDeco,int pos)
{
	int x = pos % SCREEN_WIDTH;
	int y = pos / SCREEN_WIDTH;
	short tileType = -1;
	int distMin = 100;
	int distAux;
	int near = Decoration::DecorationNear::nNone;
	Decoration* decoFloor;

	if(idDeco == -1)
	{

	//Calculo que elementos rodean la posición donde queremos colocar la decoración
	for(int i = x; i < x + 3; i++)
		for(int j = y; j < y + 3; j++)
		{
			if(!(i > SCREEN_WIDTH || j > SCREEN_HEIGHT))
			{
				//Calculo la distancia a la que me encuentro de la decoración
				distAux = max(abs(x - i),abs(y - j));

				short tileType = s->getSolid(i, j);

				if (tileType == 1)
				{
					if (distAux < distMin)
					{
						near = 3;
						distMin = distAux;
					}
				}
				else if (tileType == 2)
				{
					if (distAux < distMin)
					{
						near = 2;
						distMin = distAux;
					}
				}
				else if (tileType == 3)
				{
					if (distAux < distMin)
					{
						near = 1;
						distMin = distAux;
					}
				}
			}
	}//for

	// colocamos la decoración
	decoFloor = autoTiler->getDecoration(type, size, -1, (Decoration::DecorationNear) near); 
	}
	else
		decoFloor = autoTiler->getDecoration(idDeco);

	if(decoFloor != NULL)
	{
		decoFloor->init(pos % SCREEN_WIDTH, pos / SCREEN_WIDTH);
		// La guardamos en la lista de decoraciones (si no colisiona con ninguna)
		if (checkDecoCollision(decoFloor) && isInBounds(decoFloor, s) && checkSolidCollision(decoFloor, s))
		{
			decorationList.push_back(decoFloor);
			return decoFloor->getDecorationData().idDeco;
		}	
	}

	return -1;
}

//	if (free_space > screenSize / 4)
//		free_space = place_templates();

	// función de calcular mierda de johan


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

	// Terrenos -----------------------------------------------------------------------------------

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
*/