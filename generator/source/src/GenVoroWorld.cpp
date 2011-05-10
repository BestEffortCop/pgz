#include "GenVoroWorld.h"

GenVoroWorld::GenVoroWorld(Overworld* overworld, vector<GenZone*>* genZones, DBManager* mydb) : GenOverworld(overworld, genZones, mydb)
{
	blockadeVerts = new vector<set<GPoint> >();
	mainRoadVerts = new vector<GPoint>();
	interestingPoints = new vector<GPoint>();
	mainRoadTiles = new vector<int>();
}

GenVoroWorld::~GenVoroWorld()
{
	delete blockadeVerts;
	blockadeVerts = NULL;
	
	delete mainRoadVerts;
	mainRoadVerts = NULL;

	delete interestingPoints;
	interestingPoints = NULL;

	delete mainRoadTiles;
	mainRoadTiles = NULL;
}

void GenVoroWorld::genFrontiers(){
	//cout << "Ejecutando funcion <GenOverworld::genFrontiers()>" << endl;
	float x1,y1,x2,y2;
	GLine l;
	GenVoronoi vdg;

	ptList = genPoints(overworld->getNumZones(), overworld->getTileWorldSizeH(), overworld->getTileWorldSizeW(), 
				overworld->getNumZones());

	//voronoi
	float* xPts = getPoints(ptList, 0);
	float* yPts = getPoints(ptList, 1);
	vdg.generateVoronoi(xPts, yPts, ptList.size(), 
		0, overworld->getTileWorldSizeW(), 0, overworld->getTileWorldSizeH(), 1, false);
	delete xPts;
	delete yPts;
	vdg.resetIterator();
	while(vdg.getNext(x1,y1,x2,y2)){
		l.a.x = x1;
		l.a.y = y1;
		l.b.x = x2;
		l.b.y = y2;
		// Añadimos la frontera 
		voronoiPoly.addLine(l);
	}
	// Los bordes tambien son fronteras 
	for (int  i = 0; i< overworld->getTileWorldSizeW(); i++){
		overworld->getMapTile(i, 0)->setZoneNumber(0);
		overworld->getMapTile(i, overworld->getTileWorldSizeH()-1)->setZoneNumber(0);
	}
	for (int  i = 0; i< overworld->getTileWorldSizeH(); i++){
		overworld->getMapTile(0, i)->setZoneNumber(0);
		overworld->getMapTile(overworld->getTileWorldSizeW()-1, i)->setZoneNumber(0);
	}
}

void GenVoroWorld::genShape(){
	//cout << "Ejecutando funcion <GenOverworld::genShape()>" << endl;
	vector<GPoint> bresenPoints;
	for(int i=0; i<voronoiPoly.getLines().size(); i++){
		// !!!!!!!!!!! Aquí a veces se sale de rango de la matriz. Revisar y quitar comments !!!!!!!!!!!!!! FIXME
		bresenPoints = getMatrixLine(voronoiPoly.getLines()[i].a.x, voronoiPoly.getLines()[i].a.y, voronoiPoly.getLines()[i].b.x, voronoiPoly.getLines()[i].b.y);
		for (int j=0; j < bresenPoints.size(); j++)
			if(bresenPoints[j].x >= 0 && bresenPoints[j].x < overworld->getTileWorldSizeW() && bresenPoints[j].y >= 0 && bresenPoints[j].y < overworld->getTileWorldSizeH() )
				overworld->getMapTile(bresenPoints[j].x, bresenPoints[j].y)->setZoneNumber(0);
	}
}

void GenVoroWorld::assignTilesAndScreens(){
	//cout << "Ejecutando funcion <GenOverworld::assignTilesScreens()>" << endl;
	for ( unsigned int i = 0; i<overworld->getNumZones(); i++)
		floodFillScanlineStack(ptList[i].x, ptList[i].y, i+1);

	int screensPerCol = overworld->getTileWorldSizeH() / SCREEN_HEIGHT;
	int screensPerRow = overworld->getTileWorldSizeW() / SCREEN_WIDTH;

	int screenNumber = 0;
    int iniTileRow;
    int iniTile;
	int zoneNum;

    for (int row = 0; row < screensPerCol; row++){
        iniTileRow = SCREEN_WIDTH*SCREEN_HEIGHT*screenNumber;
        for (int col = 0; col < screensPerRow; col++){
            iniTile = col*SCREEN_WIDTH + iniTileRow;
			OwScreen* screen = makeNewScreen(iniTile,screenNumber);  //creamos el screen
			zoneNum = screen->getZoneNum();  //número de zona a la que pertenece la screen
			overworld->addScreen(screen);  //añadimos la referencia a mundo
			genZones->at(zoneNum-1)->addScreen(screen);  //añadimos la referencia al generador de Zona
			screenNumber++;
        }
    }

	int erased = 0;
	//Borrado de zonas vacias
	for (int i = 0; i < genZones->size(); i++){
		if ( genZones->at(i)->getNumScreens() == 0 ){
			cout << "ZONA" << genZones->at(i)->getZoneNumber() << " VACÍA!!!" << endl;
			genZones->erase(genZones->begin() + i - erased);
			erased++;
		}		
	}

	//ReGenFrontiers
	
	//cout << "------> DONE! <-------" << endl;
}

OwScreen* GenVoroWorld::makeNewScreen(int iniT, int screenNumber){
	int screensPerRow = overworld->getWorldSizeW();
	int iniTile;
	MapTile* t;
	int zoneNum; //número de zona
	int* candidates = new int[overworld->getNumZones()];
	for (int i=0; i<overworld->getNumZones(); i++) {
		candidates[i] = 0;
	}

	vector<MapTile*>* screenMatrix = new vector<MapTile*>();  //es una matriz que tiene punteros a tiles.

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		iniTile = iniT + SCREEN_WIDTH*screensPerRow*i;
		for (int j = 0; j < SCREEN_WIDTH; j++){
			t = overworld->mapTileMatrix->at(iniTile + j); // pillamos el mapTile que toque. Cogemos el tile.
			zoneNum = checkTileinZone(t); // este nos dice en que zona esta el mapTile(tile).
			if (zoneNum > 0){
				t->setZoneNumber(zoneNum); // se lo ponemos al mapTile
				candidates[zoneNum-1]++; // incrementamos el numero de tiles de una zona dentro de una pantalla
			}
			screenMatrix->push_back(overworld->mapTileMatrix->at(iniTile + j));  //vamos añadiendo tiles a la pantalla.
		}
	}

	int maxNumber = 0;
	zoneNum = 0;
	for ( int i = 0; i < overworld->getNumZones(); i++){
		if (candidates[i] > maxNumber){  //La zona i es la que más candidatos tiene?
			maxNumber = candidates[i];
			zoneNum = i;	//en zoneNum se guarda el número de zona a la que pertenece.
		}
	}
	zoneNum ++; //sumamos uno porque las zonas empiezan por el número 1 y no por 0

	delete candidates;
	candidates = NULL;

	short posX = screenNumber % screensPerRow;
	short posY = screenNumber / screensPerRow;

	//Con esto dejamos que haya solo haya tiles de la misma zona en una pantalla.
	for(int i = 0; i < screenMatrix->size(); i++)
		screenMatrix->at(i)->setZoneNumber(zoneNum);
	
	//Si, mega-llamada porque necesita muchas cosas para poder hacer el guardado. El primer argumento '0' es el mapNumber. Que pertenece al OW inicial.
	return new OwScreen(0, screenNumber, screenMatrix, zoneNum, posX, posY, 0/*(Sino no va el cargado del interprete porque trata de leer enemigos que todavia no están)genZones->at(zoneNum-1)->getNumEnemies()*/, genZones->at(zoneNum-1)->getZone(), genZones->at(zoneNum-1)->getTheme(), myDB);
}

//Devuelve el número de la zona en el q está el tile
int GenVoroWorld::checkTileinZone(MapTile* mTile){
	if(mTile->getZoneNumber() == -1) return 1;
	return mTile->getZoneNumber();
	//return 0;
}

void GenVoroWorld::genGeoDetail(){
	//cout << "Ejecutando funcion <GenOverworld::genGeoDetail()>" << endl;

	for (unsigned int i = 0; i<genZones->size(); i++){
		GenZone* genZone = genZones->at(i);
		genZone->genGeoDetail();
	}
	overworld->guardameSolids("Solids1.txt");
	filterTilesDim1();
	filterScreenFrontiers(false);
	overworld->guardameSolids("Solids2.txt");
	//cout << "------> DONE! <-------" << endl;
}

//Se encarga de que no aparezcan tiles sueltos rodeados de sólidos y además repasa que las fronteras estén bien.
void GenVoroWorld::filterTilesDim1()
{
	short up, down, left, right;
	for (int i = 0; i < overworld->getTileWorldSizeW(); i++)
	{
		for (int j = 0; j < overworld->getTileWorldSizeH(); j++)
		{
			if (j == 0 || i == 0 || j == (overworld->getTileWorldSizeH()-1) || i == (overworld->getTileWorldSizeW()-1)) //Los bordes del mapa a solidos
			{
				overworld->getMapTile(i,j)->setSolid(4);
			}
			else
			{
				up = overworld->getMapTile(i,j-1)->getSolid();
				down = overworld->getMapTile(i,j+1)->getSolid();
				right = overworld->getMapTile(i+1,j)->getSolid();
				left = overworld->getMapTile(i-1,j)->getSolid();
				if( up != 0 && down != 0 && right != 0 && left != 0 && overworld->getMapTile(i,j)->getSolid() == 0)
					overworld->getMapTile(i,j)->setSolid(1);
			}
		}
	}
}

void GenVoroWorld::filterScreenFrontiers(bool open)
{

	OwScreen* screen;  //pantalla actual
	OwScreen* rightScreen;  //pantalla a la derecha de la actual
	OwScreen* downScreen; //pantalla debajo de la actual
	int solid1, solid2, solid3, solid4;
	bool atLeastOneSolid, atLeastOneFree;

	for (int k = 0; k < overworld->screenList->size()-1; k++) //-1 porque la última pantalla no tiene sentido mirarla.
	{
		if ( k < ((overworld->getWorldSizeW()) * ((overworld->getWorldSizeH())-1))) //NO Estamos en la última fila. Se puede revisar la de debajo
		{
			screen = overworld->screenList->at(k);
			downScreen = overworld->screenList->at(k+(overworld->getWorldSizeW())); //cogemos la pantalla de justo debajo de nosotros
		
			//Vamos a arreglar la frontera de abajo o.O!
			for (int i = 0; i < SCREEN_WIDTH; i++) 
			{													 //Situación de los tiles:
				solid1 = screen->getSolid(i,SCREEN_HEIGHT-2);    // 1 
				solid2 = screen->getSolid(i,SCREEN_HEIGHT-1);    // 2
				solid3 = downScreen->getSolid(i,0);				 // -
				solid4 = downScreen->getSolid(i,1);				 // 3
																 // 4
				atLeastOneSolid = (solid3 == 1 || solid3 == 2) || (solid2 == 1 || solid2 == 2);
				atLeastOneFree = (solid3 == 0 || solid3 == 3) || (solid2 == 0 || solid2 == 3);
				if( atLeastOneFree && atLeastOneSolid ) //si alguno de los dos son solidos...
				{
					if(!open & atLeastOneFree)
					{
						if(solid2 == 1 || solid2 == 2)
							if(solid3 != 2)
								downScreen->setSolid(i,0, 1);
						else if(solid3 == 1 || solid3 == 2)
							screen->setSolid(i,SCREEN_HEIGHT-1, 1);
					}
					else if(atLeastOneSolid)//plan open
					{	
						if(solid3 != 3)
							downScreen->setSolid(i,0, 0);
						if(solid2 != 3)
							screen->setSolid(i,SCREEN_HEIGHT-1, 0);
						if(screen->getSolid(i, SCREEN_HEIGHT-2) != 3) 
							screen->setSolid(i,SCREEN_HEIGHT-2, 0); //la pantalla que está justo encima de solid1
					}

				}

				//Caso especial los dos son no solidos
				else if((solid1 == 0 || solid1 == 3) && (solid2 == 0 || solid2 == 3)) //dado que hacia arriba tiene que caber el personaje, es caso especial
				{
					if(screen->getSolid(i, SCREEN_HEIGHT-2) != 3) 
						screen->setSolid(i,SCREEN_HEIGHT-2, 0); //la pantalla que está justo encima de solid1
					if(downScreen->getSolid(i, 1) != 3) 
						downScreen->setSolid(i, 1, 0); //la pantalla que está justo encima de solid1
				}
			}
		}
		if(!( k+1 % (overworld->getWorldSizeW()) == 0))// (k+1 % screensPerRow) Si no estamos en la columna de más a la derecha. Podemos comprobar frontera derecha ^^
		{
			screen = overworld->screenList->at(k);
			rightScreen = overworld->screenList->at(k+1);
			//Vamos a arreglar la frontera de la derecha o.O!
			for (int i = 0; i < SCREEN_HEIGHT; i++) 
			{
				solid1 = screen->getSolid(SCREEN_WIDTH-1,i);
				solid2 = rightScreen->getSolid(0,i);
				atLeastOneSolid = (solid1 == 1 || solid1 == 2) || (solid2 == 1 || solid2 == 2);
				atLeastOneFree = (solid1 == 0 || solid1 == 3) || (solid2 == 0 || solid2 == 3);
				if( atLeastOneSolid && atLeastOneFree ) //si alguno de los dos son solidos...
				{
					if(!open && atLeastOneFree)
					{
						if(solid1 == 1 || solid1 == 2)
							if(solid2 != 2)
								rightScreen->setSolid(0,i, 1);
						else if(solid2 == 1 || solid2 == 2)
								screen->setSolid(SCREEN_WIDTH-1,i, 1);
					}
					else if(atLeastOneSolid)//plan open
					{	
						if(solid2 != 3)
							rightScreen->setSolid(0,i, 0);
						if(solid1 != 3)
							screen->setSolid(SCREEN_WIDTH-1,i, 0);
					}
				}
			}
		}
	} //for de las fronteras entre 2 pantallas

	// Tiles de esta forma en las	1|2
	//								3|4
	//								-·-
	// esquinas de las pantallas	5|6

	int solid5, solid6;
	for (int i = 1; i < (overworld->getTileWorldSizeW()/SCREEN_WIDTH); i++)  // 1..ScreensPerRow-1
		for(int j = 1; j < (overworld->getTileWorldSizeH()/SCREEN_HEIGHT); j++)  // 1..ScreensPerColum-1
		{
			solid1 = overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT)-2)->getSolid();
			solid3 = overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT)-1)->getSolid();
			solid2 = overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT)-2)->getSolid();
			solid4 = overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT)-1)->getSolid();
			solid5 = overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT))->getSolid();
			solid6 = overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT))->getSolid();

			atLeastOneSolid = (solid3 == 1 || solid3 == 2) || (solid4 == 1 || solid4 == 2) ||
							  (solid5 == 1 || solid5 == 2) || (solid6 == 1 || solid6 == 2);

			atLeastOneFree =  (solid3 == 0 || solid3 == 3) || (solid4 == 0 || solid4 == 3) ||
							  (solid5 == 0 || solid5 == 3) || (solid6 == 0 || solid6 == 3);
			
			if(atLeastOneFree && atLeastOneSolid) //si no están los 4 iguales, hay problemas
			{
				if(!open)
				{
					if(solid3 != 2)
						overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT)-1)->setSolid(1); //la esquina 1º
					if(solid4 != 2)
						overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT)-1)->setSolid(1);
					if(solid5 != 2)
						overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT))->setSolid(1);
					if(solid6 != 2)
						overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT))->setSolid(1);
				}
				else //modo open
				{
					if(solid1 != 3)
						overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT)-2)->setSolid(0);
					if(solid2 != 3)
						overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT)-2)->setSolid(0);
					if(solid3 != 3)
						overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT)-1)->setSolid(0);
					if(solid4 != 3)
						overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT)-1)->setSolid(0);
					if(solid5 != 3)
						overworld->getMapTile((i*SCREEN_WIDTH)-1, (j*SCREEN_HEIGHT))->setSolid(0);
					if(solid6 != 3)
						overworld->getMapTile((i*SCREEN_WIDTH), (j*SCREEN_HEIGHT))->setSolid(0);
				}
			}
		}
}

void GenVoroWorld::genDecoration(DBManager* myDB)
{
	//cout << "Ejecutando funcion <GenOverworld::genDecoration()>" << endl;

	for (int i = 0; i<genZones->size(); i++){
		genZones->at(i)->genDetail();
	}
	//cout << "------> DONE! <-------" << endl;
}

void GenVoroWorld::placeDungeons(){
	//cout << "Ejecutando funcion <GenOverworld::placeDungeons()>" << endl;
	for (unsigned int i = 0; i< genZones->size();i++){
		
		GenZone* z = genZones->at(i);
		z->placeDungeon();
	}
}

void GenVoroWorld::placeSafeZones(){
	//cout << "Ejecutando funcion <GenOverworld::placeSafeZones()>" << endl;
}

void GenVoroWorld::genMainRoad()
{
	int tilesPerRow = overworld->getTileWorldSizeW();

	vector<int>* choosed = new vector<int>();
	
	int actZoneIni = 0;
	int actZoneEnd = 0;
	GenZone* zIni = NULL;
	GenZone* zEnd = NULL;
	int iniTile = 0;
	int endTile = 0;

	for (int i = 0; i < genZones->size(); i++){
		
		
		if (i == 0){ //Principio del camino
			zIni = genZones->at(0);
			
			int screenN;
			iniTile = zIni->getTileOfScreen(screenN);
			actZoneEnd = 0;
			overworld->setStartLocation(screenN%overworld->getWorldSizeW(), 
										screenN/overworld->getWorldSizeW());
		}
		else{ //Cualquier otro camino
			zIni = genZones->at(actZoneIni);
			iniTile = zIni->getDungEntranceTile();

			choosed->push_back(actZoneIni);
			actZoneEnd = findNearestZone(actZoneIni, zIni, choosed);
		}

		cout << "Zona inicial:" << zIni->getZoneNumber() << endl;
		
		if (actZoneEnd != -1 ){
			zEnd = genZones->at(actZoneEnd);
			endTile = zEnd->getDungEntranceTile();

					int iniTileRow = iniTile / tilesPerRow;
					int endTileRow = endTile / tilesPerRow;
					int tile = iniTile;
					int row = iniTileRow;
					int lastRowTurned = row;

					

					if( iniTile - endTile > 0 ){ //La otra entrada está hacia arriba
						//Hacemos camino hacia arriba hasta llegar a la misma fila
						/*if (isEdgeInDirection(tile,2,LEFTDIR))
							tile++;
						if (isEdgeInDirection(tile,2,RIGHTDIR))
							tile--;*/
						while ( row > endTileRow){
							overworld->mapTileMatrix->at(tile)->setSolid(3);
							mainRoadTiles->push_back(tile);

							if( (rand() % 3 == 0 ) && ( lastRowTurned - row > 3 ) && (row - endTileRow > 8)){ //Hacemos giro por ahí
								drawLateralTurn(tile, row, true, endTileRow);
								lastRowTurned = row;
							}
							else{
								tile -= tilesPerRow;
								row--;
							}
						}
						row = endTileRow;
						tile = row*overworld->getTileWorldSizeW() + tile%overworld->getTileWorldSizeW();
					}
					else{ //La otra entrada está por debajo
						//Hacemos camino hacia abajo hasta llegar a la misma fila
						/*if (isEdgeInDirection(tile,2,LEFTDIR))
							tile++;
						if (isEdgeInDirection(tile,2,RIGHTDIR))
							tile--;*/
						while ( row < endTileRow){
							overworld->mapTileMatrix->at(tile)->setSolid(3);
							mainRoadTiles->push_back(tile);

							if( (rand() % 3 == 0 ) && (row - lastRowTurned > 3) && (endTileRow - row > 8) ){ //Hacemos giro por ahí
								drawLateralTurn(tile, row, false,  endTileRow);
								lastRowTurned = row;
							}
							else{
								tile += tilesPerRow;
								row++;
							}
						}
						row = endTileRow;
						tile = row*overworld->getTileWorldSizeW() + tile%overworld->getTileWorldSizeW();
					}

					int col = tile % tilesPerRow;
					int endCol = endTile % tilesPerRow;
					int lastColTurned = col;

					if ( col - endCol > 0 ){ //La otra entrada está hacia la izquierda
						//Hacemos camino hacia la izquierda hasta llegar al mismo tile
						/*if (isEdgeInDirection(tile,2,UPDIR))
							tile += overworld->getTileWorldSizeW();
						if (isEdgeInDirection(tile,2,DOWNDIR))
							tile -= overworld->getTileWorldSizeW();*/
						while (col > endCol){
							overworld->mapTileMatrix->at(tile)->setSolid(3);

							mainRoadTiles->push_back(tile);

							if ( (rand() % 3 == 0) && (lastColTurned  - col > 3) && (col - endCol > 8)){
								drawVerticalTurn(tile, col, false, endCol);
								lastColTurned = col;
							}
							else{
								tile --;
								col--;
							}
						}
					}
					else{ //La otra entrada está hacia la derecha
						//Hacemos camino hacia la derecha hasta llegar al mismo tile
						/*if (isEdgeInDirection(tile,2,UPDIR))
							tile += overworld->getTileWorldSizeW();
						if (isEdgeInDirection(tile,2,DOWNDIR))
							tile -= overworld->getTileWorldSizeW();*/
						while ( col < endCol){
							
							overworld->mapTileMatrix->at(tile)->setSolid(3);
							mainRoadTiles->push_back(tile);

							if ( (rand() % 3 == 0) && (col - lastColTurned > 3) && (endCol - col > 8)){
								drawVerticalTurn(tile, col, true, endCol);
								lastColTurned = col;
							}
							else{
								tile++;
								col++;
							}
						}
					}
					actZoneIni = actZoneEnd;
					actZoneEnd = -1;
		}	
	}

	delete choosed; choosed = NULL;
}

void GenVoroWorld::drawVerticalTurn(int& tile, int& col, bool right, int maxCol){
	string direction = ( rand()%2==0? "up":"down");

	int iniRow = tile/overworld->getTileWorldSizeW();
	int endRow = -1;
	int colsCovered = 0;
	int rowsCovered = 0;
	int iniCol = col;
	int endCol = -1;
	bool doubleLoop = (rand()%2 > 0? true:false);

	int totalRows;

	if (direction == "down"){
		endRow = iniRow + (rand()%5 + 10 );
		totalRows = endRow - iniRow;
	}
	else{
		endRow = iniRow - (rand()%5 + 10 );
		totalRows = iniRow - endRow;
	}

	for (int i = 0; i<totalRows; i++){
		if ( ! isFrontierNear(tile, 3) &&
			 ! isRoadInDirection(tile, 4, direction=="down"? DOWNDIR:UPDIR)
			 //&& ! isRoadInDirection(tile+1, 3, RIGHTDIR)
			 //&& ! isRoadInDirection(tile-1, 3, LEFTDIR)
			 ){
			overworld->mapTileMatrix->at(tile)->setSolid(3);
			mainRoadTiles->push_back(tile);
			rowsCovered++;
			direction=="down"? tile += overworld->getTileWorldSizeW() : tile -= overworld->getTileWorldSizeW();
		}
	}

	if ( right ){ //Tenemos que ir a la derecha
		endCol = iniCol + (rand()%6 + 10 );
		for (int i = 0; i< endCol - iniCol; i++){
			if ( col + 2 < maxCol &&
				! isFrontierNear(tile, 3) &&
				! isRoadInDirection(tile, 4, RIGHTDIR)
				//&& ! isRoadInDirection(tile+overworld->getTileWorldSizeW(), 3, UPDIR)
				//&&! isRoadInDirection(tile-overworld->getTileWorldSizeW(), 3, DOWNDIR)
				){
					overworld->mapTileMatrix->at(tile)->setSolid(3);
					mainRoadTiles->push_back(tile);

					col++;
					tile++;
					if (rand()%4==0 && doubleLoop && i>1 && i< endCol-iniCol-2){
						if ( col + 6 < maxCol)
							drawVerticalTurn(tile,col,right,maxCol);

						doubleLoop = false;
					}
			}
		}
	}
	else{ //Tenemos que ir a la izquierda
		endCol = iniCol - (rand()%6 + 10 );
		for (int i = 0; i<iniCol-endCol; i++){
			if ( col - 2 > maxCol &&
				!isFrontierNear(tile, 3) &&
				! isRoadInDirection(tile, 4, LEFTDIR)
				//&& ! isRoadInDirection(tile+overworld->getTileWorldSizeW(), 3, UPDIR)
			    //&& ! isRoadInDirection(tile-overworld->getTileWorldSizeW(), 3, DOWNDIR)
				){
					overworld->mapTileMatrix->at(tile)->setSolid(3);
					mainRoadTiles->push_back(tile);

					col--;
					tile--;
					if (rand()%4==0 && doubleLoop && i>1 && i< endCol-iniCol-2){
						if ( col - 6 > maxCol)
							drawVerticalTurn(tile,col,right,maxCol);

						doubleLoop = false;
					}

			}

		}
	}

	for (int i = 0 ; i<rowsCovered; i++){
		overworld->mapTileMatrix->at(tile)->setSolid(3);
		
		mainRoadTiles->push_back(tile);
		
		direction=="down"? tile -= overworld->getTileWorldSizeW() : tile += overworld->getTileWorldSizeW();
	}
}

void GenVoroWorld::drawLateralTurn(int& tile, int& row, bool up, int maxEndRow){
	
	string direction = ( (rand() % 2) == 0) ? "right" : "left"; 

	int iniCol = tile % overworld->getTileWorldSizeW();
	int endCol = -1;
	int colsCovered = 0;
	int rowsCovered = 0;
	int iniRow = row;
	int endRow = -1;
	bool doubleLoop = (((rand()%3) > 0)? true:false);
	
		
		int totalCols;

		if (direction == "right"){
			endCol = iniCol  + (rand()%5 + 10 );
			totalCols = endCol - iniCol;
		}
		else{
			endCol = iniCol  - (rand()%5 + 10 );
			totalCols = iniCol - endCol;
		}

		for (int i = 0; i<totalCols; i++){
			if ( //((tile + 3) / overworld->getTileWorldSizeW() == iniRow || 
				 // (tile - 3) / overworld->getTileWorldSizeW() == iniRow   ) && 
				 !isFrontierNear(tile, 3) &&
				 !isRoadInDirection(tile, 4, direction=="right"? 2:4) 
				 //&& !isRoadInDirection(tile+overworld->getTileWorldSizeW(), 3, DOWNDIR)
				 //&& !isRoadInDirection(tile-overworld->getTileWorldSizeW(), 3, UPDIR)
				 ){
				overworld->mapTileMatrix->at(tile)->setSolid(3);
				mainRoadTiles->push_back(tile);

				colsCovered++;
				
				(direction=="right"? tile++ : tile--);
			}
		}

		if ( up ){ //Tenemos que subir filas
			endRow = iniRow - (rand()%6+10);
			for (int i = 0; i < (iniRow-endRow); i++){
				if (row - 2 > maxEndRow &&
					!isFrontierNear(tile, 3) &&
					! isRoadInDirection(tile, 4, UPDIR)
					// &&! isRoadInDirection(tile+1, 3, RIGHTDIR)
					// && ! isRoadInDirection(tile-1, 3, LEFTDIR)
					){
						overworld->mapTileMatrix->at(tile)->setSolid(3);
						mainRoadTiles->push_back(tile);

						row--;
						tile -= overworld->getTileWorldSizeW();
						if (doubleLoop && i>1 && i<iniRow-endRow-2 && rand()%4 == 0){
							if (row - 6 > maxEndRow)
								 drawLateralTurn(tile,row,up,maxEndRow);
							
							doubleLoop = false;
						}	
				}
			}
		}
		else{ //Tenemos que bajar filas
			endRow = iniRow + (rand()%6+10);
			for (int i = 0; i< (endRow - iniRow); i++){
				if (row + 2 < maxEndRow &&
					!isFrontierNear(tile, 3) &&
				    ! isRoadInDirection(tile, 4, DOWNDIR) 
					//&& ! isRoadInDirection(tile+1, 3, RIGHTDIR)
					//&& ! isRoadInDirection(tile-1, 3, LEFTDIR)
					){
						overworld->mapTileMatrix->at(tile)->setSolid(3);
						mainRoadTiles->push_back(tile);

						row++;
						tile += overworld->getTileWorldSizeW();
						if(doubleLoop && i>1 && i<endRow-iniRow-2&& rand()%4 == 0){
							if (row + 6 < maxEndRow)
								drawLateralTurn(tile,row,up,maxEndRow);
							
							doubleLoop = false;
						}
				}
			}
		}

		for (int i = 0; i<colsCovered; i++){ //Volvemos hacia la izquierda tantos como hemso ido a la drecha
			overworld->mapTileMatrix->at(tile)->setSolid(3);
			mainRoadTiles->push_back(tile);

			(direction=="right"? tile-- : tile++);
		}
}

int GenVoroWorld::findNearestZone(int actZone, GenZone* zIni, vector<int>* choosed){
	
	int tilesPerRow = overworld->getTileWorldSizeW();

	bool alreadyChoosed = false;
	int minDistance = 2147483647;
	int minDistanceZone = -1;
	int iniTile = zIni->getDungEntranceTile();
	int endTile = -1;

	GenZone* zEnd;
	for (int i = 0; i < genZones->size(); i++){
		if ( !contains(i,choosed) ){
			zEnd = genZones->at(i);
			endTile = zEnd->getDungEntranceTile();
			int tilesHeight = abs( (iniTile / tilesPerRow) - (endTile / tilesPerRow) );
			int tilesWidth = abs( (iniTile % tilesPerRow) - (endTile % tilesPerRow) );
			int absDistance = tilesHeight + tilesWidth;
			if (absDistance < minDistance){
				minDistance = absDistance;
				minDistanceZone = i;
			}
		}
	}
	return minDistanceZone;
}

bool GenVoroWorld::isRoadNear(int iniT, int range){
	int iniTile = iniT - range - (range*overworld->getTileWorldSizeW());

	int roadsFound = 0;
	int tile;
	for (int i = 0; i < range*2+1; i++){
		tile = iniTile + i*overworld->getTileWorldSizeW();
		for (int j = 0; j < range*2+1; j++){
			if ( roadsFound <= range+2 &&  overworld->mapTileMatrix->at(tile)->getTileId() == 666)
				roadsFound++;
			tile++;
		}	
	}

	if (roadsFound > (range+2))
		return true;
	else
		return false;
}

bool GenVoroWorld::isRoadInDirection(int iniT, int range, int direction){
	

	int tile = iniT;
	bool roadFound = false;
	for (int i = 0; i<range; i++){
		if (!roadFound){
			switch (direction){
				case UPDIR: // Arriba
					tile -= overworld->getTileWorldSizeW();
					break;
				case RIGHTDIR: // Dcha
					tile++;
					break;
				case DOWNDIR: // Abajo
					tile += overworld->getTileWorldSizeW();
					break;
				case LEFTDIR: // Izqda
					tile--;
					break;
				default :
					break;
			}
			if (tile < 0 || tile >= overworld->mapTileMatrix->size() || overworld->mapTileMatrix->at(tile)->getSolid() == 3 )
				roadFound = true;
		}
	}
	return roadFound;
}

bool GenVoroWorld::isFrontierNear(int iniT, int range){
	int iniTile = iniT - range - (range*overworld->getTileWorldSizeW());
	if (iniTile < 0) 
		return true;

	bool frontierFound = false;
	int tile = 0;
	for (int i = 0; i < (range*2+1); i++){
		tile = iniTile + i*overworld->getTileWorldSizeW();
		for (int j = 0; j < (range*2+1); j++){
			if ( !frontierFound) 
				if (tile >= overworld->mapTileMatrix->size() || overworld->mapTileMatrix->at(tile)->getSolid() == 4 )
					frontierFound = true;
			tile++;
		}	
	}

	if (frontierFound)
		return true;
	else
		return false;
}

bool GenVoroWorld::isEdgeInDirection(int iniT, int range, int direction){
	int tile = iniT;
	bool frontierFound = false;
	for (int i = 0; i<range; i++){
		if (!frontierFound){
			switch (direction){
				case UPDIR: // Arriba
					tile -= overworld->getTileWorldSizeW();
					break;
				case RIGHTDIR: // Dcha
					tile++;
					break;
				case DOWNDIR: // Abajo
					tile += overworld->getTileWorldSizeW();
					break;
				case LEFTDIR: // Izqda
					tile--;
					break;
				default :
					break;
			}
			if (tile < 0 || tile >= overworld->mapTileMatrix->size() || overworld->mapTileMatrix->at(tile)->getSolid() == 4 )
				frontierFound = true;
		}
	}
	return frontierFound;
}


bool GenVoroWorld::contains(int elem, vector<int>* collect){
	for (int i = 0; i < collect->size(); i++)
		if (collect->at(i) == elem)
			return true;

	return false;
}

void GenVoroWorld::genRoadRamifications(){
	overworld->guardameSolids("Solids3.txt");
	int actTile;
	int nextTile;

	//overworld->guardameZonas("zonasDebug.txt");
	unsigned int i;
	for (i = 0; i < mainRoadTiles->size() - 1; i++){
		
		actTile = mainRoadTiles->at(i);
		nextTile = mainRoadTiles->at(i+1);

		bool canDoRamification = rand()%5 == 0;

		if ( actTile - nextTile == overworld->getTileWorldSizeW() ){ //Hacia arriba
				if ( canDoRamification )
					doRamification (actTile, rand()%2==0? RIGHTDIR : LEFTDIR );
		}
		else if (actTile - nextTile == -1){  //Hacia la Derecha
				if ( canDoRamification )
					doRamification (actTile, rand()%2==0? UPDIR : DOWNDIR );
		}
		else if ( actTile - nextTile == -(overworld->getTileWorldSizeW()) ){ //Hacia abajo
				if ( canDoRamification )
					doRamification (actTile, rand()%2==0? RIGHTDIR : LEFTDIR );
		}	
		else if ( actTile - nextTile == 1 ){ //Hacia izquierda
				if ( canDoRamification )
					doRamification (actTile, rand()%2==0? UPDIR : DOWNDIR );
		}
	}
	

	extendsMainRoad();	
	/////////////////////////////////////////////////AQUI SE HACE FILTROS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	overworld->guardameSolids("Solids4.txt");
	filterUnreachableAreas();
	filterScreenFrontiers(true);

	
	
	// Debug -------------
	fstream file;

	file.open("OW.dat", ios::out |ios::binary | ios::trunc);
	
	//Número tiles
	int aux = overworld->mapTileMatrix->size();
	file.write((char *)& aux,sizeof(int));
	//World width
	aux = overworld->getTileWorldSizeW();
	file.write((char *)& aux,sizeof(int));
	//Tile info
	for (int i=0; i<overworld->mapTileMatrix->size(); i++){
		aux = overworld->mapTileMatrix->at(i)->getTileId();
		file.write((char *)&aux,sizeof(int));
	}
	file.close();
}


void GenVoroWorld::doRamification(int iniTile, short firstDir){

	queue<short>* directions = new queue<short>();
	directions->push(firstDir);

	short numDirections = (rand()%8) + 15;
	short nextDir;

	int tile = iniTile;
	int probTile;
	

	short i = 0;
	
	while (i<numDirections){
		short newDir = rand()%4 + 1;
	
		if (firstDir == UPDIR && newDir == DOWNDIR)
			i--;
		else if (firstDir == RIGHTDIR && newDir == LEFTDIR)
			i--;
		else if (firstDir == DOWNDIR && newDir == UPDIR)
			i--;
		else if (firstDir == LEFTDIR && newDir == RIGHTDIR)
			i--;
		else
			directions->push( newDir );
		
		i++;
	}
	/*for (short i = 0; i < numDirections; i++)
		short newDir = rand()%4 + 1;

		if (firstDir == 1){ //Arriba
			while ( newDir == 3 ) //Abajo
				newDir = rand()%4 + 1;
		}
		
		directions->push( (rand()%4) + 1 );

	*/
	short movesDone = 0;
	while (!directions->empty()){
		nextDir = directions->front();
		directions->pop();

		short numMoves = rand()%4 + 4;
		for (short i = 0; i<numMoves; i++){

			//overworld->guardameZonas("zonasDebug.txt");

			if (nextDir == UPDIR){ //Arriba
				probTile = tile - overworld->getTileWorldSizeW();
				if ( probTile >= 0 && !isEdgeInDirection(probTile,2,nextDir) && 
					!isRoadInDirection(tile,8,nextDir) &&
					!isRoadInDirection(probTile,5,RIGHTDIR) && 
					!isRoadInDirection(probTile,5,LEFTDIR)){
					tile = probTile;
					overworld->mapTileMatrix->at(tile)->setSolid(3);
					drillSolids(tile, 1, false);
					movesDone++;
				}
			}
			else if (nextDir == RIGHTDIR){ //Dcha
				probTile = tile + 1;
				if ( tile < overworld->mapTileMatrix->size() && !isEdgeInDirection(probTile,2,nextDir) && 
					 !isRoadInDirection(tile,8,nextDir) &&
					 !isRoadInDirection(probTile,5,UPDIR) &&
					 !isRoadInDirection(probTile,5,DOWNDIR)){
					tile = probTile;
					overworld->mapTileMatrix->at(tile)->setSolid(3);
					drillSolids(tile, 1, false);
					movesDone++;
				}
			}
			else if (nextDir == DOWNDIR){ //Abajo
				probTile = tile + overworld->getTileWorldSizeW();
				if ( tile < overworld->mapTileMatrix->size() && !isEdgeInDirection(probTile,2,nextDir) && 
					 !isRoadInDirection(tile,8,nextDir) &&
					 !isRoadInDirection(probTile,5,RIGHTDIR) &&
					 !isRoadInDirection(probTile,5,LEFTDIR)){
					tile = probTile;
					overworld->mapTileMatrix->at(tile)->setSolid(3);
					drillSolids(tile, 1, false);
					movesDone++;
				}
			}
			else if (nextDir == LEFTDIR){ //Izqu
				probTile = tile - 1;
				if ( tile >= 0 && !isEdgeInDirection(probTile,2,nextDir) && 
					!isRoadInDirection(tile,8,nextDir)&&
					!isRoadInDirection(probTile,5,UPDIR) &&
					!isRoadInDirection(probTile,5,DOWNDIR)){
					tile = probTile;
					overworld->mapTileMatrix->at(tile)->setSolid(3);
					drillSolids(tile, 1, false);
					movesDone++;
				}
			}	
		}


		//INFINITE RAMIFICATIONS!

		/*if (!isFrontierNear(tile,6)){
			bool canGoDirection = false;
			while ( !canGoDirection  ){
			
				short newDir = rand()%4 + 1;

				if (firstDir == 1 && newDir == 3)
					canGoDirection = false;
				else if (firstDir == 2 && newDir == 4)
					canGoDirection = false;
				else if (firstDir == 3 && newDir == 1)
					canGoDirection = false;
				else if (firstDir == 4 && newDir == 2)
					canGoDirection = false;
				else{
					directions->push( newDir );
					canGoDirection = true;
				}
			}
		}*/

	}

	if (movesDone > 20){
		GPoint p;
		p.x = tile % overworld->getTileWorldSizeW();
		p.y = tile / overworld->getTileWorldSizeW();
		interestingPoints->push_back(p);
	}
	//overworld->guardameZonas("zonasDebug.txt");

	// INSERTAR INTERESTING POINT

	delete directions; directions = NULL;
}

void GenVoroWorld::extendsMainRoad(){
	
	int actTile;
	for (unsigned int i = 0; i < mainRoadTiles->size(); i++){
		actTile = mainRoadTiles->at(i);

		if (actTile + 1 < overworld->mapTileMatrix->size() && overworld->mapTileMatrix->at(actTile + 1)->getSolid() != 4 )
			overworld->mapTileMatrix->at(actTile + 1)->setSolid(3);
		if (actTile + overworld->getTileWorldSizeW() < overworld->mapTileMatrix->size() 
			&& overworld->mapTileMatrix->at(actTile + overworld->getTileWorldSizeW())->getSolid() != 4)
			overworld->mapTileMatrix->at(actTile + overworld->getTileWorldSizeW() )->setSolid(3);
		if (actTile + overworld->getTileWorldSizeW() + 1 < overworld->mapTileMatrix->size() 
			&& overworld->mapTileMatrix->at(actTile + overworld->getTileWorldSizeW() + 1)->getSolid() != 4)
			overworld->mapTileMatrix->at(actTile + overworld->getTileWorldSizeW() + 1 )->setSolid(3);

		drillSolids(actTile,3,false);
	}
}

void GenVoroWorld::drillSolids(int iniT, int range, bool mainRoad){
	
	int iniTile = iniT - range - (range*overworld->getTileWorldSizeW());
	
	int plusOne;
	int tile;
	
	mainRoad? plusOne = 1 : plusOne = 0;

	if ( overworld->mapTileMatrix->at(iniT)->getSolid() != 2 ){
		for (int i = 0; i < (range*2+1+plusOne); i++){
			tile = iniTile + i*overworld->getTileWorldSizeW();
			for (int j = 0; j < (range*2+1); j++){
				if (tile >= 0 && tile < overworld->mapTileMatrix->size() && overworld->mapTileMatrix->at(tile)->getSolid() == 2)
					int r = 0;
				if ( tile >= 0 && tile < overworld->mapTileMatrix->size() 
					&& overworld->mapTileMatrix->at(tile)->getSolid() == 1)
					overworld->mapTileMatrix->at(tile)->setSolid(0);
				tile++;
			}	
		}
	}

}

void GenVoroWorld::genBlockades(){
	//cout << "Ejecutando funcion <GenOverworld::genBlockades()>" << endl;
	for (unsigned int zones = 0; zones < genZones->size(); zones++){
		GenZone* gen = genZones->at(zones);
		gen->placeBlockades();
	}
}

//Generar un screen para cada Zona
void GenVoroWorld::genScreens(){
	for (unsigned int i = 0; i < genZones->size(); i++){
		GenZone* gen = genZones->at(i);
		gen->genScreens();
	}

    //DE COÑA
	cout<< overworld->mapTileMatrix->size() << " tiles de mapa" << endl;
}

void GenVoroWorld::floodFillScanlineStack(int x, int y, int zoneNum)
{
    if(overworld->getMapTile(x,y)->getZoneNumber() != -1) return;
      
    int y1,h,w;
    
	h = overworld->getTileWorldSizeH();
	w = overworld->getTileWorldSizeW();
    //draw current scanline from start position to the top
    y1 = y;
    while(y1 < h && overworld->getMapTile(x,y1)->getZoneNumber() == -1)
    {
        overworld->getMapTile(x,y1)->setZoneNumber(zoneNum);
        y1++;
    }    
    
    //draw current scanline from start position to the bottom
    y1 = y - 1;
    while(y1 >= 0 && overworld->getMapTile(x,y1)->getZoneNumber() == -1)
    {
        overworld->getMapTile(x,y1)->setZoneNumber(zoneNum);
        y1--;
    }
    
    //test for new scanlines to the left
    y1 = y;
    while(y1 < h && overworld->getMapTile(x,y1)->getZoneNumber() == zoneNum)
    {
        if(x > 0 && overworld->getMapTile(x - 1,y1)->getZoneNumber() == -1) 
        {
            floodFillScanlineStack(x - 1, y1, zoneNum);
        } 
        y1++;
    }
    y1 = y - 1;
    while(y1 >= 0 && overworld->getMapTile(x,y1)->getZoneNumber() == zoneNum)
    {
        if(x > 0 && overworld->getMapTile(x - 1,y1)->getZoneNumber() == -1) 
        {
            floodFillScanlineStack(x - 1, y1, zoneNum);
        }
        y1--;
    } 
    
    //test for new scanlines to the right 
    y1 = y;
    while(y1 < h && overworld->getMapTile(x,y1)->getZoneNumber() == zoneNum)
    {
        if(x < w - 1 && overworld->getMapTile(x + 1,y1)->getZoneNumber() == -1) 
        {           
            floodFillScanlineStack(x + 1, y1, zoneNum);
        } 
        y1++;
    }
    y1 = y - 1;
    while(y1 >= 0 && overworld->getMapTile(x,y1)->getZoneNumber() == zoneNum)
    {
        if(x < w - 1 && overworld->getMapTile(x + 1,y1)->getZoneNumber() == -1) 
        {
            floodFillScanlineStack(x + 1, y1, zoneNum);
        }
        y1--;
    }
}

void GenVoroWorld::filterUnreachableAreas()
{
    int tilesPerRow = overworld->getTileWorldSizeW();
    vector<MapTile*>* matrix = overworld->mapTileMatrix;
	vector<bool>* connectMatrix = new vector<bool>(overworld->getTileWorldSizeH()*tilesPerRow, false);
    vector<bool>* checkedMatrix = new vector<bool>(overworld->getTileWorldSizeH()*tilesPerRow, false);

    for(int i = 0; i < checkedMatrix->size(); i++)
    {
		if(!checkedMatrix->at(i))  //Todavía no se ha comprobado este tile
        {
            if(matrix->at(i)->getSolid() == 0 || matrix->at(i)->getSolid() == 3)
			{
                if(!floodSearch(i, matrix, checkedMatrix, connectMatrix))
				{
					connectWithRoad(i, matrix, checkedMatrix, connectMatrix);
					floodSearch(i, matrix, checkedMatrix, connectMatrix);
				}
			}
			else // estamos sobre un sólido o agua o algo no pasable
			{
				checkedMatrix->at(i) = true;
				connectMatrix->at(i) = false;
			}
		}
	}

	delete checkedMatrix;
	checkedMatrix = NULL;
	delete connectMatrix;
	connectMatrix = NULL;
	matrix = NULL;
}

bool GenVoroWorld::floodSearch(int posIni, vector<MapTile*>* matrix, vector<bool>* checkedMatrix, vector<bool>* connectMatrix)
{
	stack<int> * pendientes = new stack<int>();
	stack<int> * recorridos = new stack<int>(); //Si al final NO hemos conseguido conectar con el camino ya sea por
	//un camino directamente o por una zona que está conectada con el camino entonces tenemos que deshacer lo checkeado
	pendientes->push(posIni);
	int pos;
	bool conectado = false;
	int tilesPerRow = overworld->getTileWorldSizeW();
	while(!pendientes->empty())
	{
		//la posición que estamos mirando
		pos = pendientes->top();
		recorridos->push(pos);
		pendientes->pop();

		//chekeamos el tile actual de ya visitado
		checkedMatrix->at(pos) = true;

		//miramos a los lados si es pasable
		// y si lo es, entonces lo añadimos a pendientes

		if((pos+1)%tilesPerRow != 0) //miramos a la derecha
		{
			if(!conectado) //nos hemos conectado con un camino o una ruta/area ya explorada y conectada?
				conectado = matrix->at(pos+1)->getSolid() == 3 || connectMatrix->at(pos+1);

			if(!checkedMatrix->at(pos+1)) //es un tile ya recorrido?
			{
				if(matrix->at(pos+1)->getSolid() == 0 || matrix->at(pos+1)->getSolid() == 3) // es un camino por explorar?
					pendientes->push(pos+1);
				//else es un sólido no pasable, podemos checkearlo sin problemas
				checkedMatrix->at(pos+1) = true;
			}
		}

		if((pos+tilesPerRow) < (tilesPerRow * overworld->getTileWorldSizeH())) //miramos hacia abajo
		{
			if(!conectado) //nos hemos conectado con un camino o una ruta/area ya explorada y conectada?
				conectado = matrix->at(pos+tilesPerRow)->getSolid() == 3 || connectMatrix->at(pos+tilesPerRow);

			if(!checkedMatrix->at(pos+tilesPerRow)) //es un tile ya buscado?
			{
				if(matrix->at(pos+tilesPerRow)->getSolid() == 0 || matrix->at(pos+tilesPerRow)->getSolid() == 3) // es un camino por explorar?
					pendientes->push(pos+tilesPerRow);
				//else es un sólido no pasable
				checkedMatrix->at(pos+tilesPerRow) = true;
			}
		}

		if((pos-1) > 0 && ((pos-1)%tilesPerRow) != (tilesPerRow-1)) //miramos a la izquierda
		{
			if(!conectado) //nos hemos conectado con un camino o una ruta/area ya explorada y conectada?
				conectado = matrix->at(pos-1)->getSolid() == 3 || connectMatrix->at(pos-1);

			if(!checkedMatrix->at(pos-1)) //es un tile ya buscado?
			{
				if(matrix->at(pos-1)->getSolid() == 0 || matrix->at(pos-1)->getSolid() == 3) // es un camino por explorar?
					pendientes->push(pos-1);
				//else es un sólido no pasable
				checkedMatrix->at(pos-1) = true;
			}
		}

		if((pos-tilesPerRow) > 0) //miramos hacia arriba
		{
			if(!conectado) //nos hemos conectado con un camino o una ruta/area ya explorada y conectada?
				conectado = matrix->at(pos-tilesPerRow)->getSolid() == 3 || connectMatrix->at(pos-tilesPerRow);

			if(!checkedMatrix->at(pos-tilesPerRow)) //es un tile ya buscado?
			{
				if(matrix->at(pos-tilesPerRow)->getSolid() == 0 || matrix->at(pos-tilesPerRow)->getSolid() == 3) // es un camino por explorar?
					pendientes->push(pos-tilesPerRow);
				//else es un sólido no pasable
				checkedMatrix->at(pos-tilesPerRow) = true;
			}
		}
	}

	if(!conectado) //esta area NO está conectada por lo que la descheckeamos
		while(!recorridos->empty())
		{
			pos = recorridos->top();
			recorridos->pop();
			checkedMatrix->at(pos) = false;
		}
	else //esta area está conectada por lo que la marcamos como connect
		while(!recorridos->empty())
		{
			pos = recorridos->top();
			recorridos->pop();
			connectMatrix->at(pos) = true;
		}
	

	delete pendientes;
	pendientes = NULL;
	delete recorridos;
	recorridos = NULL;

	return conectado; //devolvemos si el área explorado está conectado o no

}

int GenVoroWorld::connectWithRoad(int pos, vector<MapTile*>* matrix, vector<bool>* checkedMatrix, vector<bool>* connectMatrix)
{
	bool connect = false, connectR = false, connectL = false, connectU = false, connectD = false; //nos hemos conectado en esa direccion?
	bool canMoveR = false, canMoveD = false, canMoveL = false, canMoveU = false; // podemos movernos en esa dirección?
	bool frontR = false, frontD = false, frontL = false, frontU = false;  // hemos tocado frontera?
	bool moveDown = true; int moves = 0;  //cosas para el rumbo de a donde nos movemos.
	int tilesPerRow = overworld->getTileWorldSizeW();
	int iniPos = pos; int lastPos = pos;  // posiciones que guardamos para el movimiento y cambio de rumbo.
	stack<int> * recorridos = new stack<int>(); //para luego poner que están conectados
	while(!connect)
	{

	//COMPROBACIÓN DE SI ESTAMOS YA CONECTADOS
		if((pos+1)%tilesPerRow != 0 && !(matrix->at(pos+1)->getSolid() == 4)) //miramos a la derecha
		{
			connectR = matrix->at(pos+1)->getSolid() == 3 || connectMatrix->at(pos+1);
			canMoveR = !frontR;// && !(checkedMatrix->at(pos+1)); //una vez hemos tocado frontera, ya no tiene sentido moverse en esa dirección
		}
		else
		{
			canMoveR = false;
			frontR = true;
		}

		if((pos+tilesPerRow) < (tilesPerRow * overworld->getTileWorldSizeH()) && !(matrix->at(pos+tilesPerRow)->getSolid() == 4)) //miramos hacia abajo
		{
			connectD = matrix->at(pos+tilesPerRow)->getSolid() == 3 || connectMatrix->at(pos+tilesPerRow);
			canMoveD = !frontD;// && !(checkedMatrix->at(pos+tilesPerRow)); //una vez hemos tocado frontera, ya no tiene sentido moverse en esa dirección
		}
		else
		{
			canMoveD = false;
			frontD = true;
		}

		if((pos-1) > 0 && ((pos-1)%tilesPerRow) != (tilesPerRow-1) && !(matrix->at(pos-1)->getSolid() == 4)) //miramos a la izquierda
		{
			connectL = matrix->at(pos-1)->getSolid() == 3 || connectMatrix->at(pos-1);
			canMoveL = !frontL;// && !(checkedMatrix->at(pos-1));
		}
		else
		{
			canMoveL = false;
			frontL = true;
		}

		if((pos-tilesPerRow) > 0 && !(matrix->at(pos-tilesPerRow)->getSolid() == 4)) //miramos hacia arriba
		{
			connectU = matrix->at(pos-tilesPerRow)->getSolid() == 3 || connectMatrix->at(pos-tilesPerRow);
			canMoveU = !frontU;// && !(checkedMatrix->at(pos-tilesPerRow));
		}
		else
		{
			canMoveU = false;
			frontU = true;
		}

		connect = connectU || connectR || connectD || connectL;

		if(!connect) //tenemos que taladrar hacia algún sentido
		{

		//MOVIMIENTO, TALADRO Y CHECKEO DE LA NUEVA CASILLA
			if(moveDown) // nos movemos a la derecha o hacia abajo
			{
				if(canMoveD && rand()%2)
				{//hacia abajo
					lastPos = pos;
					pos = pos+tilesPerRow;
					matrix->at(pos)->setSolid(0);
					checkedMatrix->at(pos) = true;
					recorridos->push(pos);
				}
				else if(canMoveR && lastPos != (pos+1))
				{//hacia la derecha
					lastPos = pos;
					pos = pos+1;
					matrix->at(pos)->setSolid(0);
					checkedMatrix->at(pos) = true;
					recorridos->push(pos);
				}
				else if(canMoveL && lastPos != (pos-1))
				{//hacia la izq
					lastPos = pos;
					pos = pos-1;
					matrix->at(pos)->setSolid(0);
					checkedMatrix->at(pos) = true;
					recorridos->push(pos);
				}
			}
			else
			{
				if(canMoveU && rand()%2)
				{//hacia arriba
					lastPos = pos;
					pos = pos-tilesPerRow;
					matrix->at(pos)->setSolid(0);
					checkedMatrix->at(pos) = true;
					recorridos->push(pos);
				}
				else if(canMoveL && lastPos != (pos-1))
				{//hacia la izq
					lastPos = pos;
					pos = pos-1;
					matrix->at(pos)->setSolid(0);
					checkedMatrix->at(pos) = true;
					recorridos->push(pos);
				}
				else if(canMoveR && lastPos != (pos+1))
				{//hacia la derecha
					lastPos = pos;
					pos = pos+1;
					matrix->at(pos)->setSolid(0);
					checkedMatrix->at(pos) = true;
					recorridos->push(pos);
				}
			}
			moves++;

			//CAMBIO DE MODO DE EXPLORACIÓN (HACIA ARRIBA O HACIA ABAJO)

			if(moveDown)
			{
				moveDown = canMoveD && (moves % 20) != 0;  //si llevo 20 movimientos sin exito llendo hacia abajo cambio estrategia
				if(!moveDown)
				{//intercambiamos la búsqueda, volvemos a donde estábamos
					lastPos = pos;
					pos = iniPos;
					iniPos = lastPos; // ini pos para el siguiente cambio de rumbo
					frontR = false; frontL = false;  //frontera derecha e izquierda las reiniciamos.
				}
			}
			else
			{
				moveDown = !canMoveU || (moves % 20) == 0;  //menos mal que me acuerdo de lógica, lo mismo que el otro pero con negación
				if(moveDown)
				{
					lastPos = pos;
					pos = iniPos;
					iniPos = lastPos;  //ini pos para el siguiente cambio de rumbo
					frontR = false; frontL = false;
				}
			}


		}
		//else de if(!connect) --> nos hemos conectado ya a algo
	}

	while(!recorridos->empty())
	{
		pos = recorridos->top();
		recorridos->pop();
		connectMatrix->at(pos) = true;
	}
	
	return moves;
}
