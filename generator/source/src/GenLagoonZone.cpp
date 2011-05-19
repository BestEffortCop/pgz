#include "GenLagoonZone.h"

// Constructora.
GenLagoonZone::GenLagoonZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies, short difficulty,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB)
			: GenZone(zone, zoneNumber, idTileSet, ow, numEnemies, difficulty, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, decorator, myDB){
	
}

// Destructora.
GenLagoonZone::~GenLagoonZone()
{ 
}

int GenLagoonZone::makeItRain(int numLakes, int tam){
	int screenN; //actual screen number
	int screenX, screenY;  //coordenadas X Y de la screen Actual
	int tileX, tileY;  //coordenadas X Y sobre el mapa mundi del tile izq-arriba de la matriz de la pantalla
	int numSolids = 0;

	int tilesPerRow = overworld->getTileWorldSizeW();

	//int desp = screenList->size() / numLakes;
	int actualScreen = rand()%screenList->size();
	vector<bool> visited(screenList->size());
	bool foundNew = false;

	for(int i=0; i < numLakes; i++)
	{
		foundNew = false;
		screenN = screenList->at(actualScreen)->getScreenNumber();  //cogemos una screen

		//coordenadas de la screenN dentro del mundo.
		screenX = screenN % overworld->getWorldSizeW();
		screenY = screenN / overworld->getWorldSizeW();

		// coordenada X e Y del tile inicial de pantalla
		tileX = screenX * SCREEN_WIDTH;
		tileY = screenY * SCREEN_HEIGHT;
				
		Metaball meta = Metaball(rand()%SCREEN_WIDTH + tileX, rand()%SCREEN_HEIGHT + tileY, (float)(rand()%tam)+10, SHAPE_BALL);//rand()%3);
		meta.xm = rand()%50 * 0.01f;
		meta.ym = rand()%50 * 0.01f;
		lakes.push_back(meta);
		//actualScreen = (actualScreen + desp) % screenList->size();
		while(!foundNew)
		{
			actualScreen = rand()%screenList->size();
			if (!visited[actualScreen])
			{
				visited[actualScreen] = true;
				foundNew = true;
			}
		}
	}
	
	const float MAX_THRESHOLD = 1.1f;
	const float MIN_THRESHOLD = 0.9f;
	// Value to act as a summation of all Metaballs' fields applied to this particular tile
	float sum;

	// Pasamos por todas las screens de la zona
	for (int j=0; j<(int)screenList->size(); j++)
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
				for(int i = 0; i < (int)lakes.size(); i++){
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


void GenLagoonZone::placeDungeon(dungeonType type)
{	
	int screenNumber = 0;

	int screensPerRow = overworld->getWorldSizeW() / SCREEN_WIDTH;
	int tilesPerRow = screensPerRow*SCREEN_WIDTH;
	// Pantalla de comienzo del gusano
	// por ahora se elige una al azar y creo que se va a quedar así
	int tile;

	if(type == NORMAL)
	{
		if ( screenList->size() != 0 )
		{

			int iniTile = getTileOfScreen(screenNumber);
			tile = iniTile;
			bool placed = false;
			short range = 20;
			short tries = 0;
		
			while (!placed){
				if (tile < (int)overworld->mapTileMatrix->size() &&
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
	}
	/*else
	{
		//la ponemos en medio del mundo
		screenNumber = (overworld->getWorldSizeW()/2)+(overworld->getWorldSizeW()*(overworld->getWorldSizeH()/2));
		dungEntranceTile = (((screenNumber % overworld->getWorldSizeW())*SCREEN_WIDTH)+SCREEN_WIDTH/2)+(((screenNumber / overworld->getWorldSizeW())*SCREEN_HEIGHT)+SCREEN_HEIGHT/2);
	}*/

	int tileX, tileY;
	int dunScreenX, dunScreenY, dunTileX, dunTileY;
	
	if(type == NORMAL)
	{
		//coordenadas de la screenN dentro del mundo.
		int screenX = screenNumber % overworld->getWorldSizeW(); // % screensPerRow
		int screenY = screenNumber / overworld->getWorldSizeW();

		//introducimos en el mundo, la posición de la nueva dungeon:
		GPoint p;
		p.x = screenX;
		p.y = screenY;
		overworld->dungeonPoints.push_back(p);

		tileX = (dungEntranceTile % overworld->getTileWorldSizeW()) % SCREEN_WIDTH; // % tilesPerRow
		tileY = (dungEntranceTile / overworld->getTileWorldSizeW()) % SCREEN_HEIGHT;
	
	
		// el tile dentro del mapa de tiles grande.
		//int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

		DungeonPos dp;
		dp.screenX = screenX;
		dp.screenY = screenY;
		dp.tileX = tileX; 
		dp.tileY = tileY+1; //No queremos aparecer encima de la teleportacíon de la mazmorra!

		Dungeon* newDungeon = genDungeon->createDungeon(zone, gameDifficulty, numDungeon, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);

		dunScreenX = newDungeon->getIniDScreenX();
		dunScreenY = newDungeon->getIniDScreenY();
		dunTileX = newDungeon->getIniDTileX();
		dunTileY = newDungeon->getIniDTileY();

		EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, tileX, tileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
		overworld->screenList->at(screenNumber)->getEntities()->push_back(e);

	}
	else //ESTAMOS CON LA MAZMORRA FINAL
	{
		tileX = SCREEN_WIDTH/2;
		tileY = SCREEN_HEIGHT/2;
		DungeonPos dp;
		dp.screenX = overworld->getWorldSizeW()/2;
		dp.screenY = overworld->getWorldSizeH()/2;
		dp.tileX = tileX; 
		dp.tileY = tileY+1; //No queremos aparecer encima de la teleportacíon de la mazmorra!

		Dungeon* newDungeon = genDungeon->createDungeon(zone, gameDifficulty, numDungeon+1, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);

		dunScreenX = newDungeon->getIniDScreenX();
		dunScreenY = newDungeon->getIniDScreenY();
		dunTileX = newDungeon->getIniDTileX();
		dunTileY = newDungeon->getIniDTileY();

		EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, tileX, tileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon+1/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
		overworld->screenList->at(screenNumber)->getEntities()->push_back(e);

		//PARA QUE QUEDE BONITO:
		placeEntrance((tileY * overworld->getTileWorldSizeW()) + tileX);

	}

	//////////////////////////////////////////////////// DEBUG!!
	// Aparecemos en la última mazmorra creada por el generador
	//overworld->screenList->at(screenNumber)->setPosIni(tileX + tilesPerRow, tileY);
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

	int tileScreenX = (rand()%(SCREEN_WIDTH-6))+3;
	int tileScreenY = (rand()%(SCREEN_HEIGHT-8))+4;

	// coordenada X e Y del tile incial de pantalla
	int tileY = screenY * SCREEN_HEIGHT	+ tileScreenY;
	int tileX = screenX * SCREEN_WIDTH + tileScreenX;

	// el tile dentro del mapa de tiles grande.
	int iniTile = (tileY * tilesPerRow) + tileX;

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
				if (tile >= (int)overworld->mapTileMatrix->size() || overworld->mapTileMatrix->at(tile)->getSolid() == 4
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

void GenLagoonZone::placeBlockades()
{
	/*	
						  * * * * *
						  *	0 0 0 *
	v2: Cómo funciona:	  * 0 D 0 *		D es la posicion del teleporte e I es la posición Inicial de vuelta de la mazmorra.
			Solución:	  *	+ I + *		Los 0 son sólidos y los * son pasables
						  *	+ + + *		Los + son blockades.
						  * * * * *
	*/
	int screensPerRow = overworld->getWorldSizeW();
	int tilesPerRow = overworld->getTileWorldSizeW();

	int entrance = getDungEntranceTile();
	
	placeEntrance(entrance);
	
	//tiles respecto a la matriz grande
	int tileX = entrance % tilesPerRow;
	int tileY = entrance / tilesPerRow;

	//pantalla
	int screenX = tileX / SCREEN_WIDTH;
	int screenY = tileY / SCREEN_HEIGHT;

	//tiles respecto a la pantalla
	int screenTileX = (entrance % overworld->getTileWorldSizeW()) % SCREEN_WIDTH; // % tilesPerRow
	int screenTileY = (entrance / overworld->getTileWorldSizeW()) % SCREEN_HEIGHT;

	EntityDmgBlockade* blockade;
	short idBlockade = myDB->getBlock(zone,idTool);
	short idGfx = myDB->getGfxId("Blockade",idBlockade);
	//short idDmg = myDB->getDmgType(idBlockade);

	screenTileX = screenTileX-1;
	screenTileY = screenTileY+1;
	blockade = new EntityDmgBlockade(/*type*/DMGBLOCKADE,screenTileX, screenTileY,/*idCollectable*/-1,/*linkedTo*/-1, idGfx,/*typeB No se usa*/-1,/*idDmg Random*/1);
	overworld->screenList->at(screenX+screenY*screensPerRow)->addEntity(blockade);

	screenTileX = screenTileX+2;
	blockade = new EntityDmgBlockade(/*type*/DMGBLOCKADE,screenTileX, screenTileY,/*idCollectable*/-1,/*linkedTo*/-1, idGfx,/*typeB No se usa*/-1,/*idDmg Random*/1);
	overworld->screenList->at(screenX+screenY*screensPerRow)->addEntity(blockade);

	screenTileX = screenTileX-2;
	screenTileY = screenTileY+1;
	blockade = new EntityDmgBlockade(/*type*/DMGBLOCKADE,screenTileX, screenTileY,/*idCollectable*/-1,/*linkedTo*/-1, idGfx,/*typeB No se usa*/-1,/*idDmg Random*/1);
	overworld->screenList->at(screenX+screenY*screensPerRow)->addEntity(blockade);

	screenTileX = screenTileX+1;
	blockade = new EntityDmgBlockade(/*type*/DMGBLOCKADE,screenTileX, screenTileY,/*idCollectable*/-1,/*linkedTo*/-1, idGfx,/*typeB No se usa*/-1,/*idDmg Random*/1);
	overworld->screenList->at(screenX+screenY*screensPerRow)->addEntity(blockade);

	screenTileX = screenTileX+1;
	blockade = new EntityDmgBlockade(/*type*/DMGBLOCKADE,screenTileX, screenTileY,/*idCollectable*/-1,/*linkedTo*/-1, idGfx,/*typeB No se usa*/-1,/*idDmg Random*/1);
	overworld->screenList->at(screenX+screenY*screensPerRow)->addEntity(blockade);

	blockade = NULL;
}

void GenLagoonZone::placeEntrance(int entrance)
{	
	/*	
						  * * * * *
						  *	0 0 0 *
	v2: Cómo funciona:	  * 0 D 0 *		D es la posicion del teleporte e I es la posición de vuelta de la mazmorra.
			Solución:	  *	+ I + *		Las * son o sólidos o blockades.
						  *	+ + + *
						  * * * * *
	*/
	int tilesPerRow = overworld->getTileWorldSizeW();
	int pos = (entrance - 2) - 2*tilesPerRow;

	for(int i = 0; i < 5; i++)
		overworld->getMapTile(pos+i)->setSolid(0);

	pos = pos+tilesPerRow;

	for(int i = 0; i < 5; i++)
		if(i == 0 || i == 4)
			overworld->getMapTile(pos+i)->setSolid(0);
		else
			overworld->getMapTile(pos+i)->setSolid(1);
	
	pos = pos+tilesPerRow;

	for(int i = 0; i < 5; i++)
		if( i % 2 == 0)
			overworld->getMapTile(pos+i)->setSolid(0);
		else
			overworld->getMapTile(pos+i)->setSolid(1);

	pos = pos+tilesPerRow;

	for(int i = 0; i < 5; i++)
		overworld->getMapTile(pos+i)->setSolid(0);

	pos = pos+tilesPerRow;

	for(int i = 0; i < 5; i++)
		overworld->getMapTile(pos+i)->setSolid(0);

	pos = pos+tilesPerRow;

	for(int i = 0; i < 5; i++)
		overworld->getMapTile(pos+i)->setSolid(0);
}

//Vamos a crear lagos
void GenLagoonZone::genGeoDetail()
{
	int numScreens = (4*screenList->size()) / 5;
	int tam = (int)floor((SCREEN_WIDTH)*0.50);
	makeItRain(numScreens,tam);
}

void GenLagoonZone::genDetail()
{
	decorator->init("mipene", "roger", idTileSet);
	for(vector<OwScreen*>::iterator it = screenList->begin(); it != screenList->end(); it++)
		(*it)->generate(), decorator->decorate(*(it));
}