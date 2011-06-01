/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "GenForestZone.h"

// Constructora.
GenForestZone::GenForestZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies, short difficulty,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB, short keyObj)
			: GenZone(zone, zoneNumber, idTileSet, ow, numEnemies, difficulty, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, decorator, myDB, keyObj){
	seeds = new vector<int>();
}

// Destructora.
GenForestZone::~GenForestZone()
{ 
	seeds->clear();
	delete seeds;
	seeds = NULL;
}


void GenForestZone::genScreens()
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


void GenForestZone::placeDungeon(dungeonType type)
{	
	//int screensPerRow = overworld->getWorldSizeW();
	//bool goodScreen = false;
	//int screenN, screenNFirst;
	//screenNFirst = screenList->at(rand()%screenList->size())->getScreenNumber();
	//screenN = screenNFirst;
	//while(!goodScreen)
	//{
	//	goodScreen = true;
	//	if(((screenN+1)%screensPerRow) != 0)
	//		goodScreen = overworld->screenList->at(screenN+1)->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();
	//	if(goodScreen && (screenN+screensPerRow) < (screensPerRow*overworld->getWorldSizeH()))
	//		goodScreen = overworld->screenList->at(screenN+overworld->getWorldSizeW())->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();
	//	if(goodScreen && ((screenN-1)%screensPerRow) != (screensPerRow-1) && (screenN-1) >= 0)
	//		goodScreen = overworld->screenList->at(screenN-1)->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();
	//	if(goodScreen && (screenN-screensPerRow) >= 0)
	//		goodScreen = overworld->screenList->at(screenN-screensPerRow)->getZoneNum() == overworld->screenList->at(screenN)->getZoneNum();

	//	screenN = (screenN + 1)%(screenList->size());
	//	if(!goodScreen)
	//		goodScreen = screenN == screenNFirst;
	//}

	////coordenadas de la screenN dentro del mundo.
	//int screenX = screenN % overworld->getWorldSizeW();
	//int screenY = screenN / overworld->getWorldSizeW();

	//// coordenada X e Y del tile donde se encuentra la mazmorra
	//int screenTileY = (rand()%(SCREEN_HEIGHT-8))+4; //ponemos 4 tiles para que no salga en el borde de la pantalla
	//int screenTileX = (rand()%(SCREEN_WIDTH-8))+4;
	//
	//int tileY = (screenY * SCREEN_HEIGHT) + screenTileY; //ponemos 4 tiles para que no salga en el borde de la pantalla
	//int tileX = (screenX * SCREEN_WIDTH) + screenTileX;
	//
	//// el tile dentro del mapa de tiles grande.
	//int tile = (tileY * overworld->getTileWorldSizeW()) + tileX;

	//overworld->mapTileMatrix->at(tile)->setSolid(0);
	//dungEntranceTile = tile;
	//// POSICIÓN DE LA MAZMORRA HERE!!
	//DungeonPos dp;
	//dp.screenX = screenN%screensPerRow;
	//dp.screenY = screenN/screensPerRow;
	//dp.tileX = screenTileX;
	//dp.tileY = screenTileY;
	//Dungeon* newDungeon = genDungeon->createDungeon(zone, theme, gameDifficulty, numDungeon, ratioDungeon, idTool, keyObj, dp/*Posición de la mazmorra*/, myDB);
	//int dunScreenX = newDungeon->getIniDScreenX();
	//int dunScreenY = newDungeon->getIniDScreenY();
	//int dunTileX = newDungeon->getIniDTileX();
	//int dunTileY = newDungeon->getIniDTileY();
	//EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, tileX, tileY, -1/*idCollectable*/, -1/*linkedTo*/, numDungeon/*idMap*/, dunScreenX, dunScreenY, dunTileX, dunTileY);
	//overworld->screenList->at(screenN)->getEntities()->push_back(e);
	////crear espacio alrededor del teleporter
	//overworld->screenList->at(screenN)->setSolid(screenTileX+1,screenTileY,0);
	//overworld->screenList->at(screenN)->setSolid(screenTileX+1,screenTileY-1,0);  //esquina sup-der
	//overworld->screenList->at(screenN)->setSolid(screenTileX,screenTileY+1,0);
	//overworld->screenList->at(screenN)->setSolid(screenTileX+1,screenTileY+1,0);  //esquina inf-der
	//overworld->screenList->at(screenN)->setSolid(screenTileX-1,screenTileY,0);
	//overworld->screenList->at(screenN)->setSolid(screenTileX-1,screenTileY+1,0);  //esquina inf-izq
	//overworld->screenList->at(screenN)->setSolid(screenTileX,screenTileY-1,0);
	//overworld->screenList->at(screenN)->setSolid(screenTileX-1,screenTileY-1,0);  //esquina sup-izq

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
	//overworld->screenList->at(screenNumber)->setPosIni(tileX+1, tileY);
	//overworld->setStartLocation(screenX, screenY);

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

int GenForestZone::getTileOfScreen(int& screenNumber){
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

bool GenForestZone::isFrontierNear(int iniT, int range){

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
void GenForestZone::placeSafeZone(int idZone,GPoint* pos)
{
	//cout << "Ejecutando funcion <>Zone::placeSafeZone()>" << endl;
}

void GenForestZone::placeBlockades()
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

	/*int iniTile = entrance - overworld->getTileWorldSizeW() - 1;
	short screenTileX, screenTileY,tile;
	EntityDmgBlockade* blockade;
	for (int i=0; i<3; i++){
		tile = iniTile + overworld->getTileWorldSizeW()*i;
		for (int j=0; j<3; j++){
			if ( tile != entrance && overworld->mapTileMatrix->at(tile)->getSolid() == 1){
				screenTileX = (tile % overworld->getTileWorldSizeW()) % SCREEN_WIDTH;
				screenTileY = (tile / overworld->getTileWorldSizeW()) % SCREEN_HEIGHT;
				blockade = new EntityDmgBlockade(DMGBLOCKADE,screenTileX, screenTileY,-1,-1,0,0,0);
				overworld->screenList->at(dungEntranceScreenN)->addEntity(blockade);
			}
			tile++;
		}
	}*/
}

void GenForestZone::placeEntrance(int entrance)
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

	/*queue<short>* directions = new queue<short>();

	if ( overworld->mapTileMatrix->at(dungEntranceTile-1)->getSolid() == 3 //Hay camino a la izq y arriba
		&& overworld->mapTileMatrix->at(dungEntranceTile-overworld->getTileWorldSizeW())->getSolid() == 3){
			directions->push(DOWNDIR);
			directions->push(RIGHTDIR);
	}
	else if ( overworld->mapTileMatrix->at(dungEntranceTile+1)->getSolid() == 3 //Hay camino a la dcha y arriba
			&& overworld->mapTileMatrix->at(dungEntranceTile-overworld->getTileWorldSizeW())->getSolid() == 3){
			directions->push(DOWNDIR);
			directions->push(LEFTDIR); 
	}
	else if ( overworld->mapTileMatrix->at(dungEntranceTile+1)->getSolid() == 3 //Hay camino a la dcha y abajo
			&& overworld->mapTileMatrix->at(dungEntranceTile+overworld->getTileWorldSizeW())->getSolid() == 3){
				directions->push(UPDIR);
				directions->push(LEFTDIR);
	}
	else if ( overworld->mapTileMatrix->at(dungEntranceTile-1)->getSolid() == 3 //Hay camino a abajo y a la izq
			&& overworld->mapTileMatrix->at(dungEntranceTile+overworld->getTileWorldSizeW())->getSolid() == 3){
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
			iniT = dungEntranceTile - overworld->getTileWorldSizeW() + 1;
		else if ( direction == DOWNDIR)
			iniT = dungEntranceTile + overworld->getTileWorldSizeW() - 1;
		else if ( direction == LEFTDIR)
			iniT = dungEntranceTile - overworld->getTileWorldSizeW() - 2;

		short maxCols=0, maxRows=0;
		if (direction == UPDIR || direction == DOWNDIR){
			maxCols = 3; maxRows = 2;
		}
		else{
			maxCols = 2; maxRows = 3;
		}
	
		int tile = -1;
		for (short col = 0; col<maxCols; col++){
			tile = iniT + col*overworld->getTileWorldSizeW();
			for (short row = 0; row<maxRows; row++){
				if ( tile < (int)overworld->mapTileMatrix->size())
					overworld->mapTileMatrix->at(tile)->setSolid(1);
				tile++;
			}
		}
	}
	delete directions;
	directions = NULL;*/
}

//Vamos a crear bosques
void GenForestZone::genGeoDetail()
{
	int numScreens = screenList->size();
	sowSeeds(numScreens-numScreens/5); //Plantamos semillas
	int numSolids = (int)floor((numScreens*SCREEN_HEIGHT*SCREEN_WIDTH)*0.60);
	waterSeeds(numSolids);  //regamos las semillas para que se reproduzcan
}

//plantamos semillas de las cuales aparecerá un grupo de árboles.
bool GenForestZone::sowSeeds(int numSeeds)
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

bool GenForestZone::waterSeeds(int numSolids)
{
	int growFactor;
	int actualSeed = 0;
	int actualSolids = 0;
	while(actualSeed < (int)seeds->size() && actualSolids < numSolids)
	{
		growFactor = rand()%51 + 40;
		actualSolids = actualSolids + growSeed(seeds->at(actualSeed), growFactor);
		actualSeed++;
	}
	return true;
}

int GenForestZone::growSeed(int posSeed, int growFactor)
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

void GenForestZone::genDetail()
{
	decorator->init(this->zone, idTileSet);
	for(vector<OwScreen*>::iterator it = screenList->begin(); it != screenList->end(); it++)
	{
		(*(it))->generate();
		decorator->decorate(*(it));
	}
}