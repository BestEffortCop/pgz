#include "GenLagoonZone.h"

// Constructora.
GenLagoonZone::GenLagoonZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB)
			: GenZone(zone, zoneNumber, idTileSet, ow, numEnemies, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, decorator, myDB){
	
}

// Destructora.
GenLagoonZone::~GenLagoonZone()
{ 
}


int GenLagoonZone::makeItRain(int numLakes, int tam){
	int posLake;  //donde se va a encontrar
	int screenN; //actual screen number
	int screenX, screenY;  //coordenadas X Y de la screen Actual
	int tileX, tileY;  //coordenadas X Y sobre el mapa mundi del tile izq-arriba de la matriz de la pantalla
	int tileInic; // tile inicial de la matriz de la screen sobre el mapa mundi
	int numSolids = 0;

	int tilesPerRow = overworld->getTileWorldSizeW();

	int desp = screenList->size() / numLakes;
	int actualScreen = rand()%screenList->size();

	for(int i=0; i < numLakes; i++)
	{
		screenN = screenList->at(actualScreen)->getScreenNumber();  //cogemos una screen

		//coordenadas de la screenN dentro del mundo.
		screenX = screenN % overworld->getWorldSizeW();
		screenY = screenN / overworld->getWorldSizeW();

		// coordenada X e Y del tile inicial de pantalla
		tileX = screenX * SCREEN_WIDTH;
		tileY = screenY * SCREEN_HEIGHT;

		//seeds->push_back(tileInic + posLake);  //guardamos la posición de la semilla dentro del mapa mundi
		
		Metaball meta = Metaball(rand()%SCREEN_WIDTH + tileX, rand()%SCREEN_HEIGHT + tileY, (rand()%tam)+10, SHAPE_BALL);//rand()%3);
		meta.xm = rand()%50 * 0.01f;
		meta.ym = rand()%50 * 0.01f;
		lakes.push_back(meta);
		actualScreen = (actualScreen + desp) % screenList->size();
	}
	
	const float MAX_THRESHOLD = 1.1f;
	const float MIN_THRESHOLD = 0.9f;
	// Value to act as a summation of all Metaballs' fields applied to this particular tile
	float sum;

	// Pasamos por todas las screens de la zona
	for (int j=0; j<screenList->size(); j++)
	{
		screenN = screenList->at(j)->getScreenNumber();
		screenX = screenN % overworld->getWorldSizeW();
		screenY = screenN / overworld->getWorldSizeW();
		// coordenada X e Y del tile inicial de pantalla
		tileX = screenX * SCREEN_WIDTH;
		tileY = screenY * SCREEN_HEIGHT;

		// Iterate over every tile on the screen
		for(int x = 0; x < SCREEN_WIDTH; x++){
			for(int y = 0; y < SCREEN_HEIGHT; y++){
				// Reset the summation
				sum = 0;

				// Iterate through every Metaball in the zone
				for(int i = 0; i < lakes.size(); i++){
					sum += lakes[i].flow(tileX+x,tileY+y);
				}

				// Decide whether to draw a water tile
				if(sum >= MIN_THRESHOLD /*&& sum <= MAX_THRESHOLD*/)
				{
					screenList->at(j)->setSolid(x,y,2); // put water
					numSolids++;
				}
			}
		}
	}

	return numSolids;
}

void GenLagoonZone::genScreens(){
   	for (unsigned int i=0; i< screenList->size(); i++){
		OwScreen* screen = screenList->at(i);
		screen->placeDetails();
		screen->placeEnemies();
	}
}


void GenLagoonZone::placeDungeon()
{	
	int screenNumber = 0;

	int screensPerRow = overworld->getWorldSizeW() / SCREEN_WIDTH;
	int tilesPerRow = screensPerRow*SCREEN_WIDTH;
	// Pantalla de comienzo del gusano
	// por ahora se elige una al azar y creo que se va a quedar así
	int tile;
	if ( screenList->size() != 0 ){

		int iniTile = getTileOfScreen(screenNumber);
		tile = iniTile;
		bool placed = false;
		short range = 20;
		short tries = 0;
		
		while (!placed){
			if (tile < overworld->mapTileMatrix->size() &&
				overworld->mapTileMatrix->at(tile)->getZoneNumber() == this->zoneNumber && 
				overworld->mapTileMatrix->at(tile)->getSolid() > 0 ){
				if ( !isFrontierNear(tile, range) ){
					placed = true;
					dungEntranceTile = tile;
					dungEntranceScreenN = screenNumber;
					// Aqui se hara el new Dungeon tal tal
					// new Dungeon (bla bla); 
				}
				else{
					iniTile = getTileOfScreen(screenNumber);
					tile = iniTile;
				}
			}
			else{
				iniTile = getTileOfScreen(screenNumber);
				tile = iniTile;
			}
			tries++;

			if (tries == 10 || tries == 20 || tries == 30)
				range -=5;
			else if (tries == 40)
				range = 2;
		}
	}


	//coordenadas de la screenN dentro del mundo.
	int screenX = screenNumber % overworld->getWorldSizeW(); // % screensPerRow
	int screenY = screenNumber / overworld->getWorldSizeW();

	//introducimos en el mundo, la posición de la nueva dungeon:
	GPoint p;
	p.x = screenX;
	p.y = screenY;
	overworld->dungeonPoints.push_back(p);

	int tileX = (dungEntranceTile % overworld->getTileWorldSizeW()) % SCREEN_WIDTH; // % tilesPerRow
	int tileY = (dungEntranceTile / overworld->getTileWorldSizeW()) % SCREEN_HEIGHT;
	
	
	// el tile dentro del mapa de tiles grande.
	//int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

	DungeonPos dp;
	dp.screenX = screenX;
	dp.screenY = screenY;
	dp.tileX = tileX + tilesPerRow; //No queremos aparecer encima de la teleportacíon de la mazmorra!
	overworld->mapTileMatrix->at(dungEntranceTile+1)->setSolid(0); //nos aseguramos que no es sólido
	overworld->mapTileMatrix->at(dungEntranceTile+tilesPerRow)->setSolid(0); //como el player es cabezón pues nos aseguramos que quepa.
	dp.tileY = tileY;

	Dungeon* newDungeon = genDungeon->createDungeon(zone, gameDifficulty, numDungeon, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);
	int dunScreenX = newDungeon->getIniDScreenX();
	int dunScreenY = newDungeon->getIniDScreenY();
	int dunTileX = newDungeon->getIniDTileX();
	int dunTileY = newDungeon->getIniDTileY();
	
	EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, tileX, tileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
	overworld->screenList->at(screenNumber)->getEntities()->push_back(e);

	//////////////////////////////////////////////////// DEBUG!!
	// Aparecemos en la última mazmorra creada por el generador
	overworld->screenList->at(screenNumber)->setPosIni(tileX + tilesPerRow, tileY);
	//overworld->setStartLocation(screenX, screenY);
}

int GenLagoonZone::getTileOfScreen(int& screenNumber){
	int screensPerRow = overworld->getWorldSizeW();
	int tilesPerRow = overworld->getTileWorldSizeW();

	int startScreenN = screenList->at(rand() % screenList->size())->getScreenNumber();

	screenNumber = startScreenN;

	//coordenadas dentro de la matriz de screens de startScreenN
	int screenX = startScreenN % screensPerRow;
	int screenY = startScreenN / screensPerRow;

	// coordenada X e Y del tile incial de pantalla
	int tileY = screenY * SCREEN_HEIGHT;
	int tileX = screenX * SCREEN_WIDTH;
	
	// el tile dentro del mapa de tiles grande.
	int iniTile = (tileY * tilesPerRow) + tileX;

	int add = rand() % SCREEN_WIDTH*SCREEN_HEIGHT;

	iniTile += add % SCREEN_WIDTH;
	iniTile += (add / SCREEN_HEIGHT)*overworld->getTileWorldSizeW();

	return iniTile;
}

bool GenLagoonZone::isFrontierNear(int iniT, int range){

	int iniTile = iniT - range - (range*overworld->getWorldSizeW());
	if (iniTile < 0) 
		return true;

	bool frontierFound = false;
	int tile = 0;
	for (int i = 0; i < (range*2+1); i++){
		tile = iniTile + i*overworld->getWorldSizeW();
		for (int j = 0; j < (range*2+1); j++){
			if ( !frontierFound) 
				if (tile >= overworld->mapTileMatrix->size() || overworld->mapTileMatrix->at(tile)->getSolid() == 4
					|| overworld->mapTileMatrix->at(tile)->getZoneNumber() != overworld->mapTileMatrix->at(iniT)->getZoneNumber() )
					frontierFound = true;
			tile++;
		}	
	}

	if (frontierFound)
		return true;
	else
		return false;

}

// Por decidir, de primeras coloca la entrada a una zona segura.
void GenLagoonZone::placeSafeZone(int idZone,GPoint* pos)
{
	//cout << "Ejecutando funcion <>Zone::placeSafeZone()>" << endl;
}

void GenLagoonZone::placeBlockades(){
	int entrance = getDungEntranceTile();
	
	placeEntrance(entrance);

	int iniTile = entrance - overworld->getTileWorldSizeW() - 1;
	for (int i=0; i<3; i++){
		int tile = iniTile + overworld->getTileWorldSizeW()*i;
		for (int j=0; j<3; j++){
			if ( tile < overworld->mapTileMatrix->size() &&  tile != entrance && overworld->mapTileMatrix->at(tile)->getSolid() == 1){
				//short screenTileX = (tile % overworld->getTileWorldSizeW()) % SCREEN_WIDTH;
				//short screenTileY = (tile / overworld->getTileWorldSizeW()) % SCREEN_WIDTH;
				short screenTileX = tile % SCREEN_WIDTH;
				short screenTileY = tile % SCREEN_HEIGHT;
				EntityDmgBlockade* blockade = new EntityDmgBlockade(0,screenTileX, screenTileY,0,0,0,0,0);
				overworld->screenList->at(dungEntranceScreenN)->addEntity(blockade);
			}
			tile++;
		}
	}
}

void GenLagoonZone::placeEntrance(int entrance){
	
	queue<short>* directions = new queue<short>();

	//Hay camino a la izq y arriba
	if ( overworld->mapTileMatrix->at(dungEntranceTile-1)->getSolid() == 3 && overworld->mapTileMatrix->at(dungEntranceTile-2)->getSolid() == 3
		&& overworld->mapTileMatrix->at(dungEntranceTile-overworld->getTileWorldSizeW())->getSolid() == 3 && 
		overworld->mapTileMatrix->at(dungEntranceTile-2*overworld->getTileWorldSizeW())->getSolid() == 3){
			directions->push(DOWNDIR);
			directions->push(RIGHTDIR);
	}
	//Hay camino a la dcha y arriba
	else if ( overworld->mapTileMatrix->at(dungEntranceTile+1)->getSolid() == 3 && overworld->mapTileMatrix->at(dungEntranceTile+2)->getSolid() == 3 
			&& overworld->mapTileMatrix->at(dungEntranceTile-overworld->getTileWorldSizeW())->getSolid() == 3
			&& overworld->mapTileMatrix->at(dungEntranceTile-2*overworld->getTileWorldSizeW())->getSolid() == 3){
			directions->push(DOWNDIR);
			directions->push(LEFTDIR); 
	}
	//Hay camino a la dcha y abajo
	else if ( overworld->mapTileMatrix->at(dungEntranceTile+1)->getSolid() == 3 && overworld->mapTileMatrix->at(dungEntranceTile+2)->getSolid() == 3 
			&& overworld->mapTileMatrix->at(dungEntranceTile+overworld->getTileWorldSizeW())->getSolid() == 3
			&& overworld->mapTileMatrix->at(dungEntranceTile+2*overworld->getTileWorldSizeW())->getSolid() == 3){
				directions->push(UPDIR);
				directions->push(LEFTDIR);
	}
	//Hay camino a abajo y a la izq
	else if ( overworld->mapTileMatrix->at(dungEntranceTile-1)->getSolid() == 3 && overworld->mapTileMatrix->at(dungEntranceTile-2)->getSolid() == 3 
			&& overworld->mapTileMatrix->at(dungEntranceTile+overworld->getTileWorldSizeW())->getSolid() == 3
			&& overworld->mapTileMatrix->at(dungEntranceTile+2*overworld->getTileWorldSizeW())->getSolid() == 3){
				directions->push(UPDIR);
				directions->push(RIGHTDIR);
	}
	else {
		directions->push(DOWNDIR);
		directions->push(RIGHTDIR);
	}

	short direction = -1;
	while (!directions->empty()){
		direction= directions->front();
		directions->pop();

		int iniT;
		if (direction == UPDIR)
			iniT = dungEntranceTile - 2*overworld->getTileWorldSizeW() - 1;
		else if (direction == RIGHTDIR)
			iniT = dungEntranceTile - overworld->getTileWorldSizeW() + 1 + 1;
		else if ( direction == DOWNDIR)
			iniT = dungEntranceTile + overworld->getTileWorldSizeW() - 1;
		else if ( direction == LEFTDIR)
			iniT = dungEntranceTile - overworld->getTileWorldSizeW() - 2;

		short maxCols=0, maxRows=0;
		if (direction == UPDIR || direction == DOWNDIR){
			maxCols = 3; maxRows = 4;
		}
		else{
			maxCols = 4; maxRows = 3;
		}
	
		int tile = -1;
		for (short col = 0; col<maxCols; col++){
			tile = iniT + col*overworld->getTileWorldSizeW();
			for (short row = 0; row<maxRows; row++){
				if ( tile < overworld->mapTileMatrix->size())
					overworld->mapTileMatrix->at(tile)->setSolid(1);
				tile++;
			}
		}
	}
	delete directions;
	directions = NULL;
}

//Vamos a crear bosques
void GenLagoonZone::genGeoDetail()
{
	int numScreens = (3*screenList->size()) / 5;
	int tam = floor((SCREEN_WIDTH)*0.50);
	makeItRain(numScreens,tam);
}

void GenLagoonZone::genDetail()
{
	decorator->init("mipene", "roger", idTileSet);
	for(vector<OwScreen*>::iterator it = screenList->begin(); it != screenList->end(); it++)
		(*it)->generate(), decorator->decorate(*(it));
}