#include "GenOverworld.h"

GenOverworld::GenOverworld(Overworld* overworld)
{
	this->overworld = overworld;
	zones = new vector<Zone*>();
	blockadeVerts = new vector<set<GPoint> >();
	mainRoadVerts = new vector<GPoint>();
	interestingPoints = new vector<GPoint>();
}

GenOverworld::~GenOverworld()
{
	overworld = NULL;	// Se encargará de destruirlo el que lo crea

	vector<Zone*>::iterator it;
    for(it = zones->begin(); it != zones->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete zones;
	zones = NULL;

	delete blockadeVerts;
	blockadeVerts = NULL;
	
	delete mainRoadVerts;
	mainRoadVerts = NULL;

	delete interestingPoints;
	interestingPoints = NULL;
}

void GenOverworld::genFrontiers(){
	//cout << "Ejecutando funcion <GenOverworld::genFrontiers()>" << endl;
	float x1,y1,x2,y2;
	GLine l;
	GPolygon poly;
	GenVoronoi vdg;
	vector<GPoint> vP;

	PointList ptList = genPoints(overworld->getNumZones(), overworld->getWorldSizeH(), overworld->getWorldSizeW());

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
		poly.addLine(l);   
		vP = getMatrixLine(x1,y1,x2,y2);

		// Ponemos las fronteras
		for (int i = 0; i < vP.size(); i++){
			overworld->getMapTile(vP.at(i).x, vP.at(i).y)->setZoneNumber(0);
			overworld->getMapTile(vP.at(i).x, vP.at(i).y)->setSolid(1);
		}
		// Los bordes tambien son fronteras 
		for (int  i = 0; i< overworld->getWorldSizeW(); i++){
			overworld->getMapTile(i, 0)->setZoneNumber(0);
			overworld->getMapTile(i, 0)->setSolid(1);
			overworld->getMapTile(i, overworld->getWorldSizeH()-1)->setZoneNumber(0);
			overworld->getMapTile(i, overworld->getWorldSizeH()-1)->setSolid(1);
		}
		for (int  i = 0; i< overworld->getWorldSizeH(); i++){
			overworld->getMapTile(0, i)->setZoneNumber(0);
			overworld->getMapTile(0, i)->setSolid(1);
			overworld->getMapTile(overworld->getWorldSizeW()-1, i)->setZoneNumber(0);
			overworld->getMapTile(overworld->getWorldSizeW()-1, i)->setSolid(1);
		}
	}

	for ( unsigned int i = 0; i<overworld->getNumZones(); i++){
		Zone* z = new Zone(overworld->getZonesInfo()->at(i).themeId, &poly, overworld);
		z->setZoneNumber(i+1);
		zones->push_back(z);
		floodFillScanlineStack(ptList[i].x, ptList[i].y, i+1);
	}

	//cout << "------> DONE! <-------" << endl;
}

void GenOverworld::genShape(){
	//cout << "Ejecutando funcion <GenOverworld::genShape()>" << endl;
}

void GenOverworld::assignTilesAndScreens(){
	//cout << "Ejecutando funcion <GenOverworld::assignTilesScreens()>" << endl;

	int screensPerCol = overworld->getWorldSizeH() / screenHeight;
	int screensPerRow = overworld->getWorldSizeW() / screenWidth;

	int screenNumber = 0;
    int iniTileRow;
    int iniTile;

    for (int row = 0; row < screensPerCol; row++){
        iniTileRow = screenWidth*screenHeight*screenNumber;
        for (int col = 0; col < screensPerRow; col++){
            iniTile = col*screenWidth + iniTileRow;
			OwScreen* screen = makeNewScreen(iniTile,screenNumber);
			zones->at(screen->zoneId-1)->addScreen(screen);
			screenNumber++;
        }
    }

	int erased = 0;
	//Borrado de zonas vacias
	for (int i = 0; i < zones->size(); i++){
		if ( zones->at(i)->getNumScreens() == 0 ){
			cout << "ZONA" << zones->at(i)->getZoneNumber() << " VACÍA!!!" << endl;
			zones->erase(zones->begin() + i - erased);
			erased++;
		}		
	}

	//cout << "------> DONE! <-------" << endl;
}

OwScreen* GenOverworld::makeNewScreen(int iniT, int screenNumber){
	int screensPerRow = overworld->getWorldSizeW() / screenWidth;
	int iniTile;
	MapTile* t;
	int zoneNum;
	int* candidates = new int[overworld->getNumZones()];
	for (int i=0; i<overworld->getNumZones(); i++) {
		candidates[i] = 0;
	}

	vector<MapTile*>* screenMatrix = new vector<MapTile*>();

	for (int i = 0; i < screenHeight; i++)
	{
		iniTile = iniT + screenWidth*screensPerRow*i;
		for (int j = 0; j < screenWidth; j++){
			t = overworld->mapTileMatrix->at(iniTile + j); // pillamos el mapTile que toque
			zoneNum = checkTileinZone(t); // este nos dice en que zona esta el mapTile
			if (zoneNum > 0){
				t->setZoneNumber(zoneNum); // se lo ponemos al mapTile
				candidates[zoneNum-1]++; // incrementamos el numero de tiles de una zona dentro de una pantalla
				screenMatrix->push_back(overworld->mapTileMatrix->at(iniTile + j));
			}
		}
	}

	int maxNumber = 0;
	int maxPosition = 0;
	for ( int i = 0; i<overworld->getNumZones(); i++){
		if (candidates[i] > maxNumber){
			maxNumber = candidates[i];
			maxPosition = i;
		}
	}

	delete candidates;
	candidates = NULL;

	return new OwScreen(screenNumber, screenMatrix, maxPosition+1);
}

//Devuelve el número de la zona en el q está el tile
int GenOverworld::checkTileinZone(MapTile* mTile){
	if(mTile->getZoneNumber() == -1) return 1;
	return mTile->getZoneNumber();
	//return 0;
}

void GenOverworld::genGeoDetail(){
	//cout << "Ejecutando funcion <GenOverworld::genGeoDetail()>" << endl;

	for (unsigned int i = 0; i<zones->size(); i++){
		Zone* zone = zones->at(i);
		zone->genGeoDetail();
	}
	//cout << "------> DONE! <-------" << endl;
}

void GenOverworld::genDecoration(DBInterface* myDB)
{
	//cout << "Ejecutando funcion <GenOverworld::genDecoration()>" << endl;
    // Esto se cambiará en un futuro, de momento es para meter porqueria en la matriz
	
	// Pedir datos a DBInterface
	//vector<int>* candidatos = myDB->getTiles(1);

	for (int i = 0; i<zones->size(); i++){
		zones->at(i)->genDetail();
	}
	
	//delete candidatos;
	//candidatos = NULL;

	//cout << "------> DONE! <-------" << endl;
}

void GenOverworld::placeDungeons(){
	//cout << "Ejecutando funcion <GenOverworld::placeDungeons()>" << endl;
	if (zones->size()  < 5 )
		cout << "BreakIt" << endl;
	for (unsigned int i = 0; i< zones->size();i++){
		
		Zone* z = zones->at(i);
		z->placeDungeon(NULL, z->getDungeonNumber(), overworld->getWorldDiff(), z->getTypeId(), NULL, z->getNumScreens(), 2, NULL, NULL, NULL);
	}
}

void GenOverworld::placeSafeZones(){
	//cout << "Ejecutando funcion <GenOverworld::placeSafeZones()>" << endl;
}

void GenOverworld::genMainRoad(){
	
	//genMainRoad1();
	genMainRoad2();
}

void GenOverworld::genMainRoad1(){
	
	int tilesPerRow = overworld->getWorldSizeW();
	cout << "Número de Zonas:" << zones->size() << endl;
	for (int zone = 0; zone < zones->size() - 1 ; zone++){
		cout <<"Zona inicial:" << zones->at(zone)->getZoneNumber()<< endl;
		cout <<"Zona Final:" << zones->at(zone+1)->getZoneNumber()<< endl;

		int iniTile = zones->at(zone)->getDungEntranceTile();
		int endTile = zones->at(zone+1)->getDungEntranceTile();

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

void GenOverworld::genMainRoad2(){

	int tilesPerRow = overworld->getWorldSizeW();

	vector<int>* choosed = new vector<int>();
	
	int actZoneIni = 0;
	int actZoneEnd = 0;
	Zone* zIni = NULL;
	Zone* zEnd = NULL;
	int iniTile = 0;
	int endTile = 0;

	for (int i = 0; i< zones->size() - 1; i++){
		
		zIni = zones->at(actZoneIni);
		iniTile = zIni->getDungEntranceTile();

		cout << "Zona inicial:" << zIni->getZoneNumber() << endl;
		
		choosed->push_back(actZoneIni);
		
		actZoneEnd = findNearestZone(actZoneIni, zIni, choosed);
		
		if (actZoneEnd != -1 ){
			zEnd = zones->at(actZoneEnd);
			endTile = zEnd->getDungEntranceTile();

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

					actZoneIni = actZoneEnd;
					actZoneEnd = -1;

		}	
	}

	delete choosed; choosed = NULL;

	
}


int GenOverworld::findNearestZone(int actZone, Zone* zIni, vector<int>* choosed){
	
	int tilesPerRow = overworld->getWorldSizeW();

	bool alreadyChoosed = false;
	int minDistance = 2147483647;
	int minDistanceZone = -1;
	int iniTile = zIni->getDungEntranceTile();
	int endTile = -1;

	Zone* zEnd;
	for (int i = 0; i < zones->size(); i++){
		if ( !contains(i,choosed) ){
			zEnd = zones->at(i);
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

bool GenOverworld::contains(int elem, vector<int>* collect){
	for (int i = 0; i < collect->size(); i++)
		if (collect->at(i) == elem)
			return true;

	return false;
}

void GenOverworld::genRoadRamifications(){
	//cout << "Ejecutando funcion <GenOverworld::genRoadRamifications()>" << endl;


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
	// -------------
}

void GenOverworld::genBlockades(){
	//cout << "Ejecutando funcion <GenOverworld::genBlockades()>" << endl;
}

//Generar un screen para cada Zona
void GenOverworld::genScreens(){
	for (unsigned int i = 0; i < zones->size(); i++){
		Zone* zone = zones->at(i);
		zone->genScreens();
	}

    // Debuggin
	cout<< overworld->mapTileMatrix->size() << " tiles de mapa" << endl;
}

void GenOverworld::floodFillScanlineStack(int x, int y, int zoneNum)
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

/*******************************FUNCIONES AÑADIDAS PARA DEBUG*********************************************/
// Debuggin
void GenOverworld::guardameSolids(string path){

	string fichero (path);
	ofstream f_lista (fichero.c_str());
	if (!f_lista) {
		cout << "El fichero " << fichero << " no existe.";
		exit (0);
	}

	for(int i = 0; i < overworld->getWorldSizeH()*overworld->getWorldSizeW(); i++){
		if( overworld->mapTileMatrix->at(i)->getSolid() <= 0)
			f_lista << "·" << " ";
		else
			f_lista << "0" << " ";
		if((i+1) % overworld->getWorldSizeW() == 0)
			f_lista << endl;
	}

	f_lista.close();
}

// Debuggin
void GenOverworld::guardameZonas(string path){

	string fichero (path);
	ofstream f_lista (fichero.c_str());
	if (!f_lista) {
		cout << "El fichero " << fichero << " no existe.";
		exit (0);
	}

	for(int i = 0; i < overworld->getWorldSizeH()*overworld->getWorldSizeW(); i++){
		if ( overworld->mapTileMatrix->at(i)->getZoneNumber() == 0 )
			f_lista << "*" << " ";
		else if (overworld->mapTileMatrix->at(i)->getTileId() == 0 )
			f_lista << "·" << " ";
		else if (overworld->mapTileMatrix->at(i)->getTileId() == 666 )
			f_lista << "-" << " ";
		else 
			f_lista << overworld->mapTileMatrix->at(i)->getZoneNumber() << " ";

		if((i+1) % overworld->getWorldSizeW() == 0)
			f_lista << endl;
	}

	f_lista.close();
}

