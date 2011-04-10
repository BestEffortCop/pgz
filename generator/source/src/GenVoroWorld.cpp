#include "GenVoroWorld.h"

GenVoroWorld::GenVoroWorld(Overworld* overworld, vector<GenZone*>* genZones, DBManager* mydb) : GenOverworld(overworld, genZones, mydb)
{
	blockadeVerts = new vector<set<GPoint> >();
	mainRoadVerts = new vector<GPoint>();
	interestingPoints = new vector<GPoint>();
}

GenVoroWorld::~GenVoroWorld()
{
	delete blockadeVerts;
	blockadeVerts = NULL;
	
	delete mainRoadVerts;
	mainRoadVerts = NULL;

	delete interestingPoints;
	interestingPoints = NULL;
}

void GenVoroWorld::genFrontiers(){
	//cout << "Ejecutando funcion <GenOverworld::genFrontiers()>" << endl;
	float x1,y1,x2,y2;
	GLine l;
	GenVoronoi vdg;

	ptList = genPoints(overworld->getNumZones(), overworld->getWorldSizeH(), overworld->getWorldSizeW());

	//voronoi
	float* xPts = getPoints(ptList, 0);
	float* yPts = getPoints(ptList, 1);
	vdg.generateVoronoi(xPts, yPts, ptList.size(), 
		0, overworld->getWorldSizeW(), 0, overworld->getWorldSizeH(), 1, false);
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
	for (int  i = 0; i< overworld->getWorldSizeW(); i++){
		overworld->getMapTile(i, 0)->setZoneNumber(0);
		overworld->getMapTile(i, overworld->getWorldSizeH()-1)->setZoneNumber(0);
	}
	for (int  i = 0; i< overworld->getWorldSizeH(); i++){
		overworld->getMapTile(0, i)->setZoneNumber(0);
		overworld->getMapTile(overworld->getWorldSizeW()-1, i)->setZoneNumber(0);
	}
}

void GenVoroWorld::genShape(){
	//cout << "Ejecutando funcion <GenOverworld::genShape()>" << endl;
	Horses h;
	h.placeHorses(voronoiPoly, 50);
	h.run();

	// !!!!!!!!!!! Aquí a veces se sale de rango de la matriz. Revisar y quitar comments !!!!!!!!!!!!!! FIXME
	
	vector<GPoint> bresenPoints;
	for(int i=0; i<h.ropes.size(); i++){
		bresenPoints = getMatrixLine(h.ropes[i].a.x,h.ropes[i].a.y,h.ropes[i].b.x,h.ropes[i].b.y);
		voroniPointLines.insert(voroniPointLines.end(), bresenPoints.begin(), bresenPoints.end());
	}

	for (int i = 0; i < voroniPointLines.size(); i++)
		overworld->getMapTile(voroniPointLines.at(i).x, voroniPointLines.at(i).y)->setZoneNumber(0);
}

void GenVoroWorld::assignTilesAndScreens(){
	//cout << "Ejecutando funcion <GenOverworld::assignTilesScreens()>" << endl;
	for ( unsigned int i = 0; i<overworld->getNumZones(); i++)
		floodFillScanlineStack(ptList[i].x, ptList[i].y, i+1);

	int screensPerCol = overworld->getWorldSizeH() / screenHeight;
	int screensPerRow = overworld->getWorldSizeW() / screenWidth;

	int screenNumber = 0;
    int iniTileRow;
    int iniTile;
	int zoneNum;

    for (int row = 0; row < screensPerCol; row++){
        iniTileRow = screenWidth*screenHeight*screenNumber;
        for (int col = 0; col < screensPerRow; col++){
            iniTile = col*screenWidth + iniTileRow;
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
	//cout << "------> DONE! <-------" << endl;
}

OwScreen* GenVoroWorld::makeNewScreen(int iniT, int screenNumber){
	int screensPerRow = overworld->getWorldSizeW() / screenWidth;
	int iniTile;
	MapTile* t;
	int zoneNum; //número de zona
	int* candidates = new int[overworld->getNumZones()];
	for (int i=0; i<overworld->getNumZones(); i++) {
		candidates[i] = 0;
	}

	vector<MapTile*>* screenMatrix = new vector<MapTile*>();  //es una matriz que tiene punteros a tiles.

	for (int i = 0; i < screenHeight; i++)
	{
		iniTile = iniT + screenWidth*screensPerRow*i;
		for (int j = 0; j < screenWidth; j++){
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
	for ( int i = 0; i<overworld->getNumZones(); i++){
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
	
	//Si, mega-llamada porque necesita muchas cosas para poder hacer el guardado. El primer argumento '0' es el mapNumber. Que pertenece al OW inicial.
	return new OwScreen(0, screenNumber, screenMatrix, zoneNum, posX, posY, genZones->at(zoneNum-1)->getNumEnemies(), genZones->at(zoneNum-1)->getZone(), genZones->at(zoneNum-1)->getTheme(), myDB);
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
		genZone->genGeoDetail( overworld->getWorldSizeW() / screenWidth);
	}
	filterTiles();
	//cout << "------> DONE! <-------" << endl;
}

//Se encarga de que no aparezcan tiles sueltos rodeados de sólidos y además repasa que las fronteras estén bien.
void GenVoroWorld::filterTiles()
{/*
	short up, down, left, right;
	for (int i = 0; i < overworld->mapTileMatrix->size(); i++)
	{
		if (i < overworld->getWorldSizeW())
			up = 1; //decimos que es sólido
		else
			up = overworld->
		overworld->mapTileMatrix->at(i);
	}*/
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
	if (genZones->size()  < 5 )
		cout << "BreakIt" << endl;
	for (unsigned int i = 0; i< genZones->size();i++){
		
		GenZone* z = genZones->at(i);
		z->placeDungeon();
	}
}

void GenVoroWorld::placeSafeZones(){
	//cout << "Ejecutando funcion <GenOverworld::placeSafeZones()>" << endl;
}

void GenVoroWorld::genMainRoad(){
	genMainRoad1();
	//genMainRoad2();
}

void GenVoroWorld::genMainRoad1(){
	
	int tilesPerRow = overworld->getWorldSizeW();
	cout << "Número de Zonas:" << genZones->size() << endl;
	for (int zone = 0; zone < genZones->size() - 1 ; zone++){
		cout <<"Zona inicial:" << genZones->at(zone)->getZoneNumber()<< endl;
		cout <<"Zona Final:" << genZones->at(zone+1)->getZoneNumber()<< endl;

		int iniTile = genZones->at(zone)->getDungEntranceTile();
		int endTile = genZones->at(zone+1)->getDungEntranceTile();

		int iniTileRow = iniTile / tilesPerRow;
		int endTileRow = endTile / tilesPerRow;
		int tile = iniTile;

		//this->guardameZonas("zonesDebug.txt");

		if( iniTile - endTile > 0 ){ //La otra entrada está hacia arriba
			//Hacemos camino hacia arriba hasta llegar a la misma fila
			MapTile* actTile;
			for (int row = iniTileRow; row > endTileRow ; row--){ 
				actTile = overworld->mapTileMatrix->at(tile);
				if (actTile->getTileId() != 0 )
					actTile->setTileId(666);
				tile -= tilesPerRow;
			}
		}
		else{ //La otra entrada está por debajo
			//Hacemos camino hacia abajo hasta llegar a la misma fila
			MapTile* actTile;
			for (int row = iniTileRow; row < endTileRow ; row++){
				actTile = overworld->mapTileMatrix->at(tile);
				if ( actTile->getTileId() != 0 )
					actTile->setTileId(666);
				tile += tilesPerRow;
			}
		}

		//this->guardameZonas("zonesDebug.txt");
		if ( tile - endTile > 0 ){ //La otra entrada está hacia la izquierda
			//Hacemos camino hacia la izquierda hasta llegar al mismo tile
			MapTile* actTile;
			for (int col = tile; col > endTile; col--){
				actTile = overworld->mapTileMatrix->at(col);
				if ( actTile->getTileId() != 0 )
					actTile->setTileId(666);
			}
		}
		else{ //La otra entrada está hacia la derecha
			//Hacemos camino hacia la derecha hasta llegar al mismo tile
			MapTile* actTile;
			for (int col = tile; col < endTile; col++){
				actTile = overworld->mapTileMatrix->at(col);
				if ( actTile->getTileId() != 0 )
					actTile->setTileId(666);
			}
		}
		//this->guardameZonas("zonesDebug.txt");
	} //End for zone
}

void GenVoroWorld::genMainRoad2(){

	/*int i = 0;
	vector<int>* choosed = new vector<int>();
	while ( i < zones->size() ){
		Zone* zIni = zones->at(i);
		Zone* zEnd;
		
		cout <<"Zona inicial:" << zIni->getZoneNumber() << endl;
		int iniTile = zIni->getDungEntranceTile();
		for (int j = i; j < zones->size(); j++){
			if (! contains(j,choosed) )
				;

		}
			
	}

	delete choosed; choosed = NULL;*/

	
}

bool GenVoroWorld::contains(int elem, vector<int>* collect){
	for (int i = 0; i < collect->size(); i++)
		if (collect->at(i) == elem)
			return false;

	return true;
}

void GenVoroWorld::genRoadRamifications(){
	// Debug -------------
	fstream file;

	file.open("OW.dat", ios::out |ios::binary | ios::trunc);
	
	//Número tiles
	int aux = overworld->mapTileMatrix->size();
	file.write((char *)& aux,sizeof(int));
	//World width
	aux = overworld->getWorldSizeW();
	file.write((char *)& aux,sizeof(int));
	//Tile info
	for (int i=0; i<overworld->mapTileMatrix->size(); i++){
		aux = overworld->mapTileMatrix->at(i)->getTileId();
		file.write((char *)&aux,sizeof(int));
	}
	file.close();
}

void GenVoroWorld::genBlockades(){
	//cout << "Ejecutando funcion <GenOverworld::genBlockades()>" << endl;
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
    
	h = overworld->getWorldSizeH();
	w = overworld->getWorldSizeW();
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

