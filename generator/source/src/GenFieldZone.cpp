#include "GenFieldZone.h"

// Constructora.
GenFieldZone::GenFieldZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies, short difficulty,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB, short keyObj)
			: GenZone(zone, zoneNumber, idTileSet, ow, numEnemies, difficulty, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, decorator, myDB, keyObj){
	seeds = new vector<int>();
}

// Destructora.
GenFieldZone::~GenFieldZone()
{ 
	seeds->clear();
	delete seeds;
	seeds = NULL;
}


void GenFieldZone::genScreens()
{
	//queremos que la pantalla inicial no tenga enemigos:
	GPoint p;
	p = overworld->getStartLocation();
	int screenIni = p.x + (p.y*overworld->getWorldSizeW());

   	for (unsigned int i=0; i< screenList->size(); i++){
		OwScreen* screen = screenList->at(i);
		screen->placeDetails();
		if(screenIni != screen->getScreenNumber())
			screen->placeEnemies();
	}
}


void GenFieldZone::placeDungeon(dungeonType type)
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
					if ( !isFrontierNear(tile, range) && (screenNumber != (overworld->getWorldSizeW()*overworld->getWorldSizeH())/2)){
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
				else if (tries == 50)
					range = 0;
			}
		}
	}
	/*else
	{
		//la ponemos en medio del mundo
		screenNumber = (overworld->getWorldSizeW()/2)+(overworld->getWorldSizeW()*(overworld->getWorldSizeH()/2));
		dungEntranceTile = (((screenNumber % overworld->getWorldSizeW())*SCREEN_WIDTH)+SCREEN_WIDTH/2)+(((screenNumber / overworld->getWorldSizeW())*SCREEN_HEIGHT)+SCREEN_HEIGHT/2);
	}*/

	int tileX, tileY, screenTileX, screenTileY;
	int screenX, screenY;
	int dunScreenX, dunScreenY, dunTileX, dunTileY;
	
	if(type == NORMAL)
	{
		//coordenadas de la screenN dentro del mundo.
		screenX = screenNumber % overworld->getWorldSizeW(); // % screensPerRow
		screenY = screenNumber / overworld->getWorldSizeW();

		//introducimos en el mundo, la posición de la nueva dungeon:
		GPoint p;
		p.x = screenX;
		p.y = screenY;
		overworld->dungeonScreenPoints.push_back(p);

		screenTileX = (dungEntranceTile % overworld->getTileWorldSizeW()) % SCREEN_WIDTH; // % tilesPerRow
		screenTileY = (dungEntranceTile / overworld->getTileWorldSizeW()) % SCREEN_HEIGHT;
	
	
		// el tile dentro del mapa de tiles grande.
		//int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

		DungeonPos dp;
		dp.screenX = screenX;
		dp.screenY = screenY;
		dp.tileX = screenTileX; 
		dp.tileY = screenTileY+1; //No queremos aparecer encima de la teleportacíon de la mazmorra!

		Dungeon* newDungeon = genDungeon->createDungeon(zone, gameDifficulty, numDungeon, ratioDungeon, idTool, keyObj, dp/*Posición de la mazmorra*/, myDB);

		dunScreenX = newDungeon->getIniDScreenX();
		dunScreenY = newDungeon->getIniDScreenY();
		dunTileX = newDungeon->getIniDTileX();
		dunTileY = newDungeon->getIniDTileY();

		EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, screenTileX, screenTileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
		overworld->screenList->at(screenNumber)->getEntities()->push_back(e);

	}
	else //ESTAMOS CON LA MAZMORRA FINAL
	{
		screenTileX = SCREEN_WIDTH/2;
		screenTileY = SCREEN_HEIGHT/2;
		screenX = overworld->getWorldSizeW()/2;
		screenY = overworld->getWorldSizeH()/2;

		//introducimos en el mundo, la posición de la nueva dungeon:
		GPoint p;
		p.x = screenX;
		p.y = screenY;
		overworld->dungeonScreenPoints.push_back(p);

		DungeonPos dp;
		dp.screenX = screenX;
		dp.screenY = screenY;
		dp.tileX = screenTileX; 
		dp.tileY = screenTileY+1; //No queremos aparecer encima de la teleportacíon de la mazmorra!

		Dungeon* newDungeon = genDungeon->createFinalDungeon(zone, gameDifficulty, numDungeon+1, ratioDungeon, idTool, keyObj, dp/*Posición de la mazmorra*/, myDB);

		dunScreenX = newDungeon->getIniDScreenX();
		dunScreenY = newDungeon->getIniDScreenY();
		dunTileX = newDungeon->getIniDTileX();
		dunTileY = newDungeon->getIniDTileY();

		EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, screenTileX, screenTileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon+1/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
		overworld->screenList->at((screenY*overworld->getWorldSizeW())+screenX)->getEntities()->push_back(e);

		//PARA QUE QUEDE BONITO PONEMOS SU ENTRADA:
		tileX = screenX*SCREEN_WIDTH + screenTileX;
		tileY = screenY*SCREEN_HEIGHT + screenTileY;
		tile = (tileY * overworld->getTileWorldSizeW()) + tileX;
		placeEntrance(tile);

	}
	overworld->dungeonTilesPoints.push_back(tile);
	//////////////////////////////////////////////////// DEBUG!!
	// Aparecemos en la última mazmorra creada por el generador
	//overworld->screenList->at(screenNumber)->setPosIni(tileX + tilesPerRow, tileY);
	//overworld->setStartLocation(screenX, screenY);
}

int GenFieldZone::getTileOfScreen(int& screenNumber){
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

bool GenFieldZone::isFrontierNear(int iniT, int range){

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
void GenFieldZone::placeSafeZone(int idZone,GPoint* pos)
{
	//cout << "Ejecutando funcion <>Zone::placeSafeZone()>" << endl;
}

void GenFieldZone::placeBlockades()
{  //FALTA SABER QUE idDMG HAY QUE PASARLE AL BLOCKADE. Y FALTA PEDIRLE A LA BD LOS BLOCKADES.

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

void GenFieldZone::placeEntrance(int entrance)
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
			overworld->getMapTile(pos+i)->setSolid(5);
	
	pos = pos+tilesPerRow;

	for(int i = 0; i < 5; i++)
		if( i % 2 == 0)
			overworld->getMapTile(pos+i)->setSolid(0);
		else
			overworld->getMapTile(pos+i)->setSolid(5);

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

//Vamos a crear bosques
void GenFieldZone::genGeoDetail()
{
	int numScreens = screenList->size();
	sowSeeds(numScreens); //Plantamos semillas
	int numSolids = (int)floor((numScreens*SCREEN_HEIGHT*SCREEN_WIDTH)*0.10);
	waterSeeds(numSolids);  //regamos las semillas para que se reproduzcan
	makeARiver(350);
}

//plantamos semillas de las cuales aparecerá un grupo de árboles.
bool GenFieldZone::sowSeeds(int numSeeds)
{
	int sowed = 0;  //semillas plantadas
	int posSeed;  //donde se va a encontrar nuestra semilla dentro de la matriz de pantalla
	int screenN; //actual screen number
	int screenX, screenY;  //coordenadas X Y de la screen Actual
	int tileX, tileY;  //coordenadas X Y sobre el mapa mundi del tile izq-arriba de la matriz de la pantalla
	int tileInic; // tile inicial de la matriz de la screen sobre el mapa mundi

	//plantamos una semilla por pantalla
	int i = 0;
	while (i < (int)screenList->size() && sowed < numSeeds)
	{
		screenN = screenList->at(rand()%screenList->size())->getScreenNumber();  //cogemos una screen

		posSeed = ((rand()%SCREEN_HEIGHT) * overworld->getTileWorldSizeW()) + rand()%SCREEN_WIDTH; //donde se va a ubicar la semilla (offSet)

		//coordenadas de la screenN dentro del mundo.
		screenX = screenN % overworld->getWorldSizeW();
		screenY = screenN / overworld->getWorldSizeW();

		// coordenada X e Y del tile inicial de pantalla
		tileY = screenY * SCREEN_HEIGHT;
		tileX = screenX * SCREEN_WIDTH;
	
		// el tile dentro del mapa de tiles grande.
		tileInic = (tileY * overworld->getTileWorldSizeW()) + tileX;

		seeds->push_back(tileInic + posSeed);  //guardamos la posición de la semilla dentro del mapa mundi
		overworld->getMapTile(tileInic+posSeed)->setTileId(222); //para debugueo <-------------------------------- Quitar
		sowed++;
		i++;
	}

	//plantamos semillas en las esquinas de las pantalla (que queda más cool ^^)
	while( sowed < numSeeds)
	{
		if ((sowed % 4) == 0)
			posSeed = 0;
		else
			posSeed = (SCREEN_WIDTH-1);

		screenN = screenList->at(rand() % screenList->size())->getScreenNumber();
		//coordenadas de la screenN dentro del mundo.
		screenX = screenN % overworld->getWorldSizeW();
		screenY = screenN / overworld->getWorldSizeW();

		// coordenada X e Y del tile inicial de pantalla
		tileY = screenY * SCREEN_HEIGHT;
		tileX = screenX * SCREEN_WIDTH;
	
		// el tile dentro del mapa de tiles grande.
		tileInic = (tileY * overworld->getTileWorldSizeW()) + tileX;
		seeds->push_back(tileInic + posSeed);
		sowed++;
	}

	return true;
}

bool GenFieldZone::waterSeeds(int numSolids)
{
	int growFactor;
	int actualSeed = 0;
	int actualSolids = 0;
	while(actualSeed < (int)seeds->size() && actualSolids < numSolids)
	{
		growFactor = rand()%51 + 40;  //Factor que indica si se crea un nueva semilla con cada expansión
		actualSolids = actualSolids + growSeed(seeds->at(actualSeed), growFactor);
		actualSeed++;
	}
	return true;
}

int GenFieldZone::growSeed(int posSeed, int growFactor)
{
	int tilesPerRow = overworld->getTileWorldSizeW(); //nos ahorramos muchos getters ^^
	int solidsMade = 0;

	if((posSeed+1)%tilesPerRow != 0) //se puede a la derecha? no nos salimos de la columna?
	{
		if(overworld->getMapTile(posSeed+1)->getZoneNumber() == zoneNumber)  // y estamos en la misma zona?
		{
			if(overworld->getMapTile(posSeed+1)->getSolid() == 0)  //era ya un sólido?
			{
				solidsMade++;
				overworld->getMapTile(posSeed+1)->setSolid(1);
				if(rand()%101 < growFactor)//la semilla consigue crecer?? (a mayor factor de crecimiento más posibilidades)
					seeds->push_back(posSeed+1); //añadimos la nueva semilla
			}
			//else ya hay un arbol en la posición.
		}
		//else no ha conseguido sembrarse la semilla.
	}

	if((posSeed+tilesPerRow) < (tilesPerRow * overworld->getTileWorldSizeH())) //se puede hacia abajo? no nos salimos de la matriz?
	{
		if(overworld->getMapTile(posSeed+tilesPerRow)->getZoneNumber() == zoneNumber)
		{
			if(overworld->getMapTile(posSeed+tilesPerRow)->getSolid() == 0)  //era ya un sólido?
			{
				solidsMade++;
				overworld->getMapTile(posSeed+tilesPerRow)->setSolid(1);
				if(rand()%101 < growFactor)//la semilla consigue crecer?? (a mayor factor de crecimiento más posibilidades)
					seeds->push_back(posSeed+tilesPerRow); //añadimos la nueva semilla
			}
			//else ya hay un arbol en la posición.
		}
		//else no ha conseguido sembrarse la semilla.
	}

	if((posSeed-1) > 0 && ((posSeed-1)%tilesPerRow) != (tilesPerRow-1)) //no nos vamos a otra columna(atravesamos la matriz)
	{
		if(overworld->getMapTile(posSeed-1)->getZoneNumber() == zoneNumber)
		{
			if(overworld->getMapTile(posSeed-1)->getSolid() == 0)  //era ya un sólido?
			{
				solidsMade++;
				overworld->getMapTile(posSeed-1)->setSolid(1);
				if(rand()%101 < growFactor)//la semilla consigue crecer?? (a mayor factor de crecimiento más posibilidades)
					seeds->push_back(posSeed-1); //añadimos la nueva semilla
			}
			//else ya hay un arbol en la posición.
		}
		//else no ha conseguido sembrarse la semilla.
	}

	if((posSeed-tilesPerRow) > 0) //se puede hacia arriba? no nos salimos de la matriz?
	{
		if(overworld->getMapTile(posSeed-tilesPerRow)->getZoneNumber() == zoneNumber)
		{
			if(overworld->getMapTile(posSeed-tilesPerRow)->getSolid() == 0)  //era ya un sólido?
			{
				solidsMade++;
				overworld->getMapTile(posSeed-tilesPerRow)->setSolid(1);
				if(rand()%101 < growFactor) //la semilla consigue crecer?? (a mayor factor de crecimiento más posibilidades)
					seeds->push_back(posSeed-tilesPerRow); //añadimos la nueva semilla
			}
			//else ya hay un arbol en la posición.
		}
		//else no ha conseguido sembrarse la semilla.
	}

	return solidsMade;

}

int GenFieldZone::makeARiver(int sizeLong)
{
	int iniPos;
	int pos;
	int actualLong = 0;
	int tilesPerRow = overworld->getTileWorldSizeW();

	int iniScreen = screenList->at(rand()%screenList->size())->getScreenNumber();

	//coordenadas de la screenN dentro del mundo.
	int screenX = iniScreen % overworld->getWorldSizeW();
	int screenY = iniScreen / overworld->getWorldSizeW();

	// coordenada X e Y del tile inicial de pantalla
	int tileY = screenY * SCREEN_HEIGHT;
	int tileX = screenX * SCREEN_WIDTH;
	
	// el tile dentro del mapa de tiles grande.
	int tileInic = (tileY * overworld->getTileWorldSizeW()) + tileX;

	iniPos = tileInic + rand()%SCREEN_WIDTH;  //cogemos un tile de la parte de arriba de la pantalla
	pos = iniPos;

	actualLong++;
	overworld->getMapTile(pos)->setSolid(2);

	int percent = 50;
	bool canMoveR = true, canMoveL = true;
	//Primero nos desplazamos a derecha y abajo o izquierda y abajo
	//bool direc = (bool)(rand()%2); //con esto decidimos si empiza moviendose a izq o a der.
	bool direc;
	if(rand()%2)
		direc = true;
	else
		direc = false;
	while (actualLong < sizeLong && (canMoveR || canMoveL))
	{
		if(direc)
		{
			if(rand()%101 < percent)
			{
				canMoveR = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber
							&& percent>0  && !(borderScreen(pos) && borderScreen(pos+tilesPerRow) && borderScreen(pos+(2*tilesPerRow)));
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					pos = pos+tilesPerRow;
					//relleno del rio(2 tiles de gordo)
					if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
						overworld->getMapTile(pos+1)->setSolid(2);
					else
						overworld->getMapTile(pos-1)->setSolid(2);
					percent = percent-10;
				}
				else
				{
					canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100 
								&& !(borderScreen(pos) && borderScreen(pos+1) && borderScreen(pos+2));
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos+1)->setSolid(2);
						pos = pos+1;
						//relleno del rio(2 tiles de gordo)
						if((pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber)
							overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						else
							overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						percent = percent+10;
					}
				}
			}
			else
			{
				canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100 
							&& !(borderScreen(pos) && borderScreen(pos+1) && borderScreen(pos+2));
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos+1)->setSolid(2);
					pos = pos+1;
					//relleno del rio(2 tiles de gordo)
					if((pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber)
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					else
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					percent = percent+10;
				}
				else
				{
					canMoveR = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber
								&& percent>0 && !(borderScreen(pos) && borderScreen(pos+tilesPerRow) && borderScreen(pos+(2*tilesPerRow)));
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						pos = pos+tilesPerRow;
						//relleno del rio(2 tiles de gordo)
						if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
							overworld->getMapTile(pos+1)->setSolid(2);
						else
							overworld->getMapTile(pos-1)->setSolid(2);
						percent = percent-10;
					}
				}
			}
			if(canMoveR)
				direc = !((actualLong%20) == 0);
			else
				direc = false;
		}
		else
		{
			if(rand()%101 < percent)
			{
				canMoveL = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber 
							&& percent>0 && !(borderScreen(pos) && borderScreen(pos+tilesPerRow) && borderScreen(pos+(2*tilesPerRow)));
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					pos = pos+tilesPerRow;
					//relleno del rio(2 tiles de gordo)
					if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
						overworld->getMapTile(pos+1)->setSolid(2);
					else
						overworld->getMapTile(pos-1)->setSolid(2);
					percent = percent-10;
				}
				else
				{
					canMoveL = ((pos-1)%tilesPerRow) != (tilesPerRow-1) && (pos-1) >= 0 && overworld->getMapTile(pos-1)->getZoneNumber() == zoneNumber && percent<100
								&& !(borderScreen(pos) && borderScreen(pos-1) && borderScreen(pos-2));
					if(canMoveL)
					{
						actualLong++;
						overworld->getMapTile(pos-1)->setSolid(2);
						pos = pos-1;
						//relleno del rio(2 tiles de gordo)
						if((pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber)
							overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						else
							overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						percent = percent+10;
					}
				}
			}
			else
			{
				canMoveL = ((pos-1)%tilesPerRow) != (tilesPerRow-1) && (pos-1) >= 0 && overworld->getMapTile(pos-1)->getZoneNumber() == zoneNumber && percent<100
							&& !(borderScreen(pos) && borderScreen(pos-1) && borderScreen(pos-2));
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos-1)->setSolid(2);
					pos = pos-1;
					//relleno del rio(2 tiles de gordo)
					if((pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber)
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					else
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					percent = percent+10;
				}
				else
				{
					canMoveL = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber 
								&& percent>0 && !(borderScreen(pos) && borderScreen(pos+tilesPerRow) && borderScreen(pos+(2*tilesPerRow)));
					if(canMoveL)
					{
						actualLong++;
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						pos = pos+tilesPerRow;
						//relleno del rio(2 tiles de gordo)
						if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
							overworld->getMapTile(pos+1)->setSolid(2);
						else
							overworld->getMapTile(pos-1)->setSolid(2);
						percent = percent-10;
					}
				}
			}
			if(canMoveL)
				direc = (actualLong%20) == 0;
			else
				direc = true;
		}
	}

	percent = 50;
	canMoveL = true; canMoveR = true;
	pos = iniPos;  //ahora cogemos el otro extremo e intentamos extenderlo
	//Ahora probamos a desplazarnos a arriba, izquierda y derecha
	if(rand()%2 == 0)//con esto decidimos si empiza moviendose a izq o a der.
		direc = false;
	else
		direc = true;
	while (actualLong < sizeLong && (canMoveL || canMoveR))
	{
		if(direc)
		{
			if(rand()%101 < percent)
			{
				canMoveR = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0
							&& !(borderScreen(pos) && borderScreen(pos-tilesPerRow) && borderScreen(pos-(2*tilesPerRow)));
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					pos = pos-tilesPerRow;
					//relleno del rio(2 tiles de gordo)
					if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
						overworld->getMapTile(pos+1)->setSolid(2);
					else
						overworld->getMapTile(pos-1)->setSolid(2);
					percent = percent-10;
				}
				else
				{
					canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100 
								&& !(borderScreen(pos) && borderScreen(pos+1) && borderScreen(pos+2));
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos+1)->setSolid(2);
						pos = pos+1;
						//relleno del rio(2 tiles de gordo)
						if((pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber )
							overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						else
							overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						percent = percent+10;
					}
				}
			}
			else
			{
				canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100 
							&& !(borderScreen(pos) && borderScreen(pos+1) && borderScreen(pos+2));
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos+1)->setSolid(2);
					pos = pos+1;
					//relleno del rio(2 tiles de gordo)
					if((pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber )
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					else
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					percent = percent+10;
				}
				else
				{
					canMoveR = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0 
								&& !(borderScreen(pos) && borderScreen(pos-tilesPerRow) && borderScreen(pos-(2*tilesPerRow)));
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						pos = pos-tilesPerRow;
						//relleno del rio(2 tiles de gordo)
						if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
							overworld->getMapTile(pos+1)->setSolid(2);
						else
							overworld->getMapTile(pos-1)->setSolid(2);
						percent = percent-10;
					}
				}
			}
			if(canMoveR)
				direc = !((actualLong%20) == 0);
			else
				direc = false;
		}
		else
		{
			if(rand()%101 < percent)
			{
				canMoveL = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0 
							&& !(borderScreen(pos) && borderScreen(pos-tilesPerRow) && borderScreen(pos-(2*tilesPerRow)));
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					pos = pos-tilesPerRow;
					//relleno del rio(2 tiles de gordo)
					if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
						overworld->getMapTile(pos+1)->setSolid(2);
					else
						overworld->getMapTile(pos-1)->setSolid(2);
					percent = percent-10;
				}
				else
				{
					canMoveL = ((pos-1)%tilesPerRow) != (tilesPerRow-1) && (pos-1) >= 0 && overworld->getMapTile(pos-1)->getZoneNumber() == zoneNumber && percent<100 
								&& !(borderScreen(pos) && borderScreen(pos-1) && borderScreen(pos-2));
					if(canMoveL)
					{
						actualLong++;
						overworld->getMapTile(pos-1)->setSolid(2);
						pos = pos-1;
						//relleno del rio(2 tiles de gordo)
						if((pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber )
							overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						else
							overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						percent = percent+10;
					}
				}
			}
			else
			{
				canMoveL = ((pos-1)%tilesPerRow) != (tilesPerRow-1) && (pos-1) >= 0 && overworld->getMapTile(pos-1)->getZoneNumber() == zoneNumber && percent<100
							&& !(borderScreen(pos) && borderScreen(pos-1) && borderScreen(pos-2));
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos-1)->setSolid(2);
					pos = pos-1;
					//relleno del rio(2 tiles de gordo)
					if((pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber )
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					else
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					percent = percent+10;
				}
				else
				{
					canMoveL = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0 
								&& !(borderScreen(pos) && borderScreen(pos-tilesPerRow) && borderScreen(pos-(2*tilesPerRow)));
					if(canMoveL)
					{
						actualLong++;
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						pos = pos-tilesPerRow;
						//relleno del rio(2 tiles de gordo)
						if(((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber)
							overworld->getMapTile(pos+1)->setSolid(2);
						else
							overworld->getMapTile(pos-1)->setSolid(2);
						percent = percent-10;
					}
				}
			}
			if(canMoveL)
				direc = (actualLong%20) == 0;
			else
				direc = true;
		}
	}
	/*	if(rand()%101 < percent)
		{
			canMoveL = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
			if(canMoveL)
			{
				actualLong++;
				overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
				pos = pos-tilesPerRow;
				percent = percent-10;
			}
			else
			{
				canMoveL = ((pos-1)%tilesPerRow) != (tilesPerRow-1) && (pos-1) >= 0 && overworld->getMapTile(pos-1)->getZoneNumber() == zoneNumber && percent<100;
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos-1)->setSolid(2);
					pos = pos-1;
					percent = percent+10;
				}
			}
		}
		else
		{
			canMoveL = ((pos-1)%tilesPerRow) != (tilesPerRow-1) && (pos-1) >= 0 && overworld->getMapTile(pos-1)->getZoneNumber() == zoneNumber && percent<100;
			if(canMoveL)
			{
				actualLong++;
				overworld->getMapTile(pos-1)->setSolid(2);
				pos = pos-1;
				percent = percent+10;
			}
			else
			{
				canMoveL = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					pos = pos-tilesPerRow;
					percent = percent-10;
				}
			}
		}
	}*/

	return actualLong;


/*	vector<OwScreen*>* initialScreens = new vector<OwScreen*>();



	vector<OwScreen*>::iterator it;
	for(it = initialScreens->begin(); it != initialScreens->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete initialScreens;
	initialScreens = NULL;*/
}

bool GenFieldZone::borderScreen(int pos)
{
	if(pos > overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH())
		return true;
	else
	{
		int screenPosX = (pos % overworld->getTileWorldSizeW()) % SCREEN_WIDTH;
		int screenPosY = (pos / overworld->getTileWorldSizeW()) / SCREEN_HEIGHT;
		if(screenPosY == 0 || screenPosY == (SCREEN_HEIGHT-1))
			int r = 0;
		return screenPosX == 0 || screenPosX == (SCREEN_WIDTH-1) || screenPosY == 0 || screenPosY == (SCREEN_HEIGHT-1);
	}
}

void GenFieldZone::genDetail()
{
	decorator->init(this->zone, idTileSet);
	for(vector<OwScreen*>::iterator it = screenList->begin(); it != screenList->end(); it++)
		(*it)->generate(), decorator->decorate(*(it));
}