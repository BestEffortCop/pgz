#include "GenLagoonZone.h"

int GenLagoonZone::ballCount = 0;

// Constructora.
GenLagoonZone::GenLagoonZone(string theme, string zone, int zoneNumber, GPolygon* zoneShape, Overworld* ow, short numEnemies,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB)
			: GenZone(theme, zone, zoneNumber, zoneShape, ow, numEnemies, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, decorator, myDB){
	
}

// Destructora.
GenLagoonZone::~GenLagoonZone()
{ 
}


void GenLagoonZone::makeItRain(){
	int posLake;  //donde se va a encontrar
	int screenN; //actual screen number
	int screenX, screenY;  //coordenadas X Y de la screen Actual
	int tileX, tileY;  //coordenadas X Y sobre el mapa mundi del tile izq-arriba de la matriz de la pantalla
	int tileInic; // tile inicial de la matriz de la screen sobre el mapa mundi

	int tilesPerRow = overworld->getTileWorldSizeW();

	for(int i=1; i < 6; i++)
	{
		screenN = screenList->at(rand()%screenList->size())->getScreenNumber();  //cogemos una screen

		posLake = ((rand()%SCREEN_HEIGHT) * overworld->getTileWorldSizeW()) + rand()%SCREEN_WIDTH; //donde se va a ubicar la semilla (offSet)

		//coordenadas de la screenN dentro del mundo.
		screenX = screenN % overworld->getWorldSizeW();
		screenY = screenN / overworld->getWorldSizeW();

		// coordenada X e Y del tile inicial de pantalla
		tileX = screenX * SCREEN_WIDTH;
		tileY = screenY * SCREEN_HEIGHT;	

		// el tile dentro del mapa de tiles grande.
		tileInic = (tileY * overworld->getTileWorldSizeW()) + tileX;

		//seeds->push_back(tileInic + posBall);  //guardamos la posición de la semilla dentro del mapa mundi
		
		Metaball meta = Metaball(rand()%SCREEN_WIDTH + tileX, rand()%SCREEN_HEIGHT + tileY, rand()%250+300, SHAPE_ELLIPSE);
		meta.xm = rand()%100 * 0.01f;
		meta.ym = rand()%100 * 0.01f;
		lakes.push_back(meta);
	}

	const float MAX_THRESHOLD = 1.1f;
	const float MIN_THRESHOLD = 0.9f;
	// Value to act as a summation of all Metaballs' fields applied to this particular tile
	float sum;

	// Iterate over every tile on the screen
	for(int y = 0; y < SCREEN_HEIGHT; y++){
		for(int x = 0; x < SCREEN_WIDTH; x++){
			// Reset the summation
			sum = 0;

			// Iterate through every Metaball in the zone
			for(int i = 0; i < lakes.size(); i++){
				sum += lakes[i].flow(x,y);
			}

			// Decide whether to draw a water tile
			if(sum >= MIN_THRESHOLD && sum <= MAX_THRESHOLD)
				overworld->getMapTile(posLake-tilesPerRow)->setSolid(2); // put water
		}
	}
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
					overworld->mapTileMatrix->at(tile)->setTileId(0);
					dungEntranceTile = tile;
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

	int tileX = (dungEntranceTile % overworld->getTileWorldSizeW()) % SCREEN_WIDTH; // % tilesPerRow
	int tileY = (dungEntranceTile / overworld->getTileWorldSizeW()) / SCREEN_WIDTH;
	
	
	// el tile dentro del mapa de tiles grande.
	//int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

	DungeonPos dp;
	dp.screenX = screenX;
	dp.screenY = screenY;
	dp.tileX = tileX + 1; //No queremos aparecer encima de la teleportacíon de la mazmorra!
	overworld->mapTileMatrix->at(dungEntranceTile+1)->setSolid(0); //nos aseguramos que no es sólido
	dp.tileY = tileY;
	genDungeon->createDungeon(zone, theme, gameDifficulty, numDungeon, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);

	Dungeon* newDungeon = genDungeon->createDungeon(zone, theme, gameDifficulty, numDungeon, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);
	int dunScreenX = newDungeon->getIniDScreenX();
	int dunScreenY = newDungeon->getIniDScreenY();
	int dunTileX = newDungeon->getIniDTileX();
	int dunTileY = newDungeon->getIniDTileY();
	
	EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, tileX, tileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
	overworld->screenList->at(screenNumber)->getEntities()->push_back(e);

	//////////////////////////////////////////////////// DEBUG!!
	// Aparecemos en la última mazmorra creada por el generador
	overworld->screenList->at(screenNumber)->setPosIni(tileX+1, tileY);
	overworld->setStartLocation(screenX, screenY);
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

//Vamos a crear bosques
void GenLagoonZone::genGeoDetail()
{
	int numScreens = screenList->size();
	int numSolids = floor((numScreens*SCREEN_HEIGHT*SCREEN_WIDTH)*0.60);
}

void GenLagoonZone::genDetail()
{
	decorator->init("mipene", "roger", "world.png");
	for(vector<OwScreen*>::iterator it = screenList->begin(); it != screenList->end(); it++)
		(*it)->generate(), decorator->decorate(*(it));
}