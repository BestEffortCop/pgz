#include "GenFieldZone.h"

// Constructora.
GenFieldZone::GenFieldZone(string theme, string zone, int zoneNumber, GPolygon* zoneShape, Overworld* ow, short numEnemies,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB)
			: GenZone(theme, zone, zoneNumber, zoneShape, ow, numEnemies, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, decorator, myDB){
	seeds = new vector<int>();
}

// Destructora.
GenFieldZone::~GenFieldZone()
{ 
	seeds->clear();
	delete seeds;
	seeds = NULL;
}


void GenFieldZone::genScreens(){
   	for (unsigned int i=0; i< screenList->size(); i++){
		OwScreen* screen = screenList->at(i);
		screen->placeDetails();
		screen->placeEnemies();
	}
}


void GenFieldZone::placeDungeon()
{	
	/*int screensPerRow = overworld->getWorldSizeW();
	bool goodScreen = false;
	int screenN, screenNFirst;
	screenNFirst = screenList->at(rand()%screenList->size())->getScreenNumber();
	screenN = screenNFirst;
	while(!goodScreen)
	{
		goodScreen = true;
		if(((screenN+1)%screensPerRow) != 0)
			goodScreen = overworld->screenList->at(screenN+1)->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();
		if(goodScreen && (screenN+screensPerRow) < (screensPerRow*overworld->getWorldSizeH()))
			goodScreen = overworld->screenList->at(screenN+overworld->getWorldSizeW())->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();
		if(goodScreen && ((screenN-1)%screensPerRow) != (screensPerRow-1) && (screenN-1) >= 0)
			goodScreen = overworld->screenList->at(screenN-1)->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();
		if(goodScreen && (screenN-screensPerRow) >= 0)
			goodScreen = overworld->screenList->at(screenN-screensPerRow)->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();

		screenN = (screenN + 1)%(screenList->size());
		if(!goodScreen)
			goodScreen = screenN == screenNFirst;
	}

	//coordenadas de la screenN dentro del mundo.
	int screenX = screenN % overworld->getWorldSizeW();
	int screenY = screenN / overworld->getWorldSizeW();

	// coordenada X e Y del tile donde se encuentra la mazmorra
	int screenTileY = (rand()%(SCREEN_HEIGHT-8))+4; //ponemos 4 tiles para que no salga en el borde de la pantalla
	int screenTileX = (rand()%(SCREEN_WIDTH-8))+4;
	
	int tileY = (screenY * SCREEN_HEIGHT) + screenTileY; //ponemos 4 tiles para que no salga en el borde de la pantalla
	int tileX = (screenX * SCREEN_WIDTH) + screenTileX;
	
	// el tile dentro del mapa de tiles grande.
	int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

	overworld->mapTileMatrix->at(tile)->setSolid(0);
	dungEntranceTile = tile;
	// POSICIÓN DE LA MAZMORRA HERE!!
	DungeonPos dp;
	dp.screenX = screenN%screensPerRow;
	dp.screenY = screenN/screensPerRow;
	dp.tileX = screenTileX;
	dp.tileY = screenTileY;*/

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
				if (tile+1 < overworld->mapTileMatrix->size() &&
					overworld->mapTileMatrix->at(tile + 1)->getZoneNumber() == this->zoneNumber)
					tile++;
				else{
					iniTile = getTileOfScreen(screenNumber);
					tile = iniTile;
				}
			}
			tries++;

			if (tries == 10 || tries == 20 || tries == 30)
				range -=5;
			else if (tries == 40)
				range = 2;
		}
	}


	//coordenadas de la screenN dentro del mundo.
	int screenX = screenNumber % overworld->getWorldSizeW();
	int screenY = screenNumber / overworld->getWorldSizeW();

	int tileX = dungEntranceTile % SCREEN_WIDTH;
	int tileY = dungEntranceTile / SCREEN_HEIGHT;
	
	
	// el tile dentro del mapa de tiles grande.
	//int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

	DungeonPos dp;
	dp.screenX = screenNumber%screensPerRow;
	dp.screenY = screenNumber/screensPerRow;
	dp.tileX = tileX;
	dp.tileY = tileY;
	//genDungeon->createDungeon(zone, theme, gameDifficulty, numDungeon, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);

	Dungeon* newDungeon = genDungeon->createDungeon(zone, theme, gameDifficulty, numDungeon, ratioDungeon, idTool, 2/*keyObj*/, dp/*Posición de la mazmorra*/, myDB);
	int dunScreenX = newDungeon->getIniDScreenX();
	int dunScreenY = newDungeon->getIniDScreenY();
	int dunTileX = newDungeon->getIniDTileX();
	int dunTileY = newDungeon->getIniDTileY();
	EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, tileX, tileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
	overworld->screenList->at(screenNumber)->getEntities()->push_back(e);

	//crear espacio alrededor del teleporter
	/*overworld->screenList->at(screenN)->setSolid(screenTileX+1,screenTileY,0);
	overworld->screenList->at(screenN)->setSolid(screenTileX+1,screenTileY-1,0);  //esquina sup-der
	overworld->screenList->at(screenN)->setSolid(screenTileX,screenTileY+1,0);
	overworld->screenList->at(screenN)->setSolid(screenTileX+1,screenTileY+1,0);  //esquina inf-der
	overworld->screenList->at(screenN)->setSolid(screenTileX-1,screenTileY,0);
	overworld->screenList->at(screenN)->setSolid(screenTileX-1,screenTileY+1,0);  //esquina inf-izq
	overworld->screenList->at(screenN)->setSolid(screenTileX,screenTileY-1,0);
	overworld->screenList->at(screenN)->setSolid(screenTileX-1,screenTileY-1,0);  //esquina sup-izq*/
}

// Por decidir, de primeras coloca la entrada a una zona segura.
void GenFieldZone::placeSafeZone(int idZone,GPoint* pos)
{
	//cout << "Ejecutando funcion <>Zone::placeSafeZone()>" << endl;
}

//Vamos a crear bosques
void GenFieldZone::genGeoDetail()
{
	int numScreens = screenList->size();
	sowSeeds(numScreens); //Plantamos semillas
	int numSolids = floor((numScreens*SCREEN_HEIGHT*SCREEN_WIDTH)*0.10);
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
	while (i < screenList->size() && sowed < numSeeds)
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
	while(actualSeed < seeds->size() && actualSolids < numSolids)
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
	bool direc = rand()%1; //con esto decidimos si empiza moviendose a izq o a der.
	while (actualLong < sizeLong && (canMoveR || canMoveL))
	{
		if(direc)
		{
			if(rand()%101 < percent)
			{
				canMoveR = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					pos = pos+tilesPerRow;
					percent = percent-5;
				}
				else
				{
					canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100;
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos+1)->setSolid(2);
						pos = pos+1;
						percent = percent+10;
					}
				}
			}
			else
			{
				canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100;
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos+1)->setSolid(2);
					pos = pos+1;
					percent = percent+10;
				}
				else
				{
					canMoveR = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						pos = pos+tilesPerRow;
						percent = percent-5;
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
				canMoveL = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
					pos = pos+tilesPerRow;
					percent = percent-5;
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
					canMoveL = (pos+tilesPerRow) < (overworld->getTileWorldSizeW()*overworld->getTileWorldSizeH()) && overworld->getMapTile(pos+tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
					if(canMoveL)
					{
						actualLong++;
						overworld->getMapTile(pos+tilesPerRow)->setSolid(2);
						pos = pos+tilesPerRow;
						percent = percent-5;
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
	direc = rand()%1; //con esto decidimos si empiza moviendose a izq o a der.
	while (actualLong < sizeLong && (canMoveL || canMoveR))
	{
		if(direc)
		{
			if(rand()%101 < percent)
			{
				canMoveR = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					pos = pos-tilesPerRow;
					percent = percent-5;
				}
				else
				{
					canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100;
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos+1)->setSolid(2);
						pos = pos+1;
						percent = percent+10;
					}
				}
			}
			else
			{
				canMoveR = ((pos+1)%tilesPerRow) != 0 && overworld->getMapTile(pos+1)->getZoneNumber() == zoneNumber && percent<100;
				if(canMoveR)
				{
					actualLong++;
					overworld->getMapTile(pos+1)->setSolid(2);
					pos = pos+1;
					percent = percent+10;
				}
				else
				{
					canMoveR = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
					if(canMoveR)
					{
						actualLong++;
						overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
						pos = pos-tilesPerRow;
						percent = percent-5;
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
				canMoveL = (pos-tilesPerRow) >= 0 && overworld->getMapTile(pos-tilesPerRow)->getZoneNumber() == zoneNumber && percent>0;
				if(canMoveL)
				{
					actualLong++;
					overworld->getMapTile(pos-tilesPerRow)->setSolid(2);
					pos = pos-tilesPerRow;
					percent = percent-5;
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
						percent = percent-5;
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

void GenFieldZone::genDetail()
{

}