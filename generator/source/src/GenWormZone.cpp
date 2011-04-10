#include "GenWormZone.h"

// Constructora.
GenWormZone::GenWormZone(string theme, string zone, int zoneNumber, GPolygon* zoneShape, Overworld* ow, short numEnemies,
						 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, DBManager* myDB)
			: GenZone(theme, zone, zoneNumber, zoneShape, ow, numEnemies, genDungeon, numDungeon, idTool, ratioDungeon, safeZones, myDB){
	// Asignamos parametros a los atributos
}

// Destructora.
GenWormZone::~GenWormZone()
{ //No se crea nada, asique no destruimos nada
}


void GenWormZone::genScreens(){
   	for (unsigned int i=0; i< screenList->size(); i++){
		OwScreen* screen = screenList->at(i);
		screen->placeDetails();
		screen->placeEnemies();
	}
}


// Coloca una mazmorra. Ricky: al final no recuerdo qu decidimos si les pasabamos tanta informacion o no.
void GenWormZone::placeDungeon()
{
	//cout << "Ejecutando funcion <>Zone::placeDungeon()>" << endl;

	int screensPerRow = overworld->getWorldSizeW() / screenWidth;
	int tilesPerRow = screensPerRow*screenWidth;
	// Pantalla de comienzo del gusano
	// por ahora se elige una al azar y creo que se va a quedar así
	if ( screenList->size() != 0 ){
		int startScreenN = screenList->at(rand() % screenList->size())->getScreenNumber();

		//coordenadas dentro de la matriz de screens de startScreenN
		int screenX = startScreenN % screensPerRow;
		int screenY = startScreenN / screensPerRow;

		// coordenada X e Y del tile incial de pantalla
		int tileY = screenY * screenHeight;
		int tileX = screenX * screenWidth;
	
		// el tile dentro del mapa de tiles grande.
		int iniTile = (tileY * tilesPerRow) + tileX;

		bool placed = false;

		int tile = iniTile;

		while (!placed){
			if (overworld->mapTileMatrix->at(tile)->getZoneNumber() == this->zoneNumber && overworld->mapTileMatrix->at(tile)->getSolid() > 0)
			{
				placed = true;
				overworld->mapTileMatrix->at(tile)->setTileId(0);
				dungEntranceTile = tile;
				// Aqui se hara el new Dungeon tal tal
				// new Dungeon (bla bla); 
				genDungeon->createDungeon(zone, theme, gameDifficulty, numDungeon, ratioDungeon, idTool, myDB);
			}
			else{
				if (overworld->mapTileMatrix->at(tile + 1)->getZoneNumber() == this->zoneNumber)
					tile++;
				else{
					iniTile += tilesPerRow;
					tile = iniTile;
				}
			}
		}
	}
}

// Por decidir, de primeras coloca la entrada a una zona segura. (Ricky: esto tendra tela)
void GenWormZone::placeSafeZone(int idZone,GPoint* pos){
	//cout << "Ejecutando funcion <>Zone::placeSafeZone()>" << endl;
}

void GenWormZone::genGeoDetail(int screensPerRow){
	
	//una posible aproximación de movimientos de gusanos
	//por ahora vamos a hacer 7 moves por pantalla aprox
	if (screenList->size() != 0){
		int moves = 7*(rand()%(screenList->size()) + screenList->size()/2); // 1/2 + ~1 = rango(1/2, 3/2) movimientos de gusano por pantalla
		int movesDone = 0;
		while (movesDone < moves)
		{
			movesDone = movesDone + genWormDetail(screensPerRow);
		}
	}
	/*int times = rand()%(screenList->size()/2) + screenList->size()/3; 
	for (int i=0; i<times; i++)
		genWormDetail(screensPerRow);*/
}

int GenWormZone::genWormDetail(int screensPerRow){
	//tiles por fila del mapa de tiles
	int tilesPerRow = screensPerRow*screenWidth;
	// Pantalla de comienzo del gusano
	// por ahora se elige una al azar y creo que se va a quedar asi
	int startScreenN = screenList->at(rand() % screenList->size())->getScreenNumber();

	//coordenadas dentro de la matriz de screens de startScreenN
	int screenX = startScreenN % screensPerRow;
	int screenY = startScreenN / screensPerRow;

	// coordenada X e Y del tile incial de pantalla
	int tileY = screenY * screenHeight;
	int tileX = screenX * screenWidth;
	
	// el tile dentro del mapa de tiles grande.
	int tile = (tileY * tilesPerRow) + tileX;

	//crear una brocha(brocheta)

	int brush[BRUSHW][BRUSHH];

	//colocamos la brocha en el primer tile:
	iniBrush(tile, brush, tilesPerRow);

	int movsDone = 0;

	queue<int>* directs = genVectorDirections();

	while( !directs->empty() ){
		placeSolids(brush);
		int nextDir = directs->front();
		directs->pop();

		if ( canMoveDirection(nextDir, brush, tilesPerRow) )
		{
			moveBrush(nextDir, brush, tilesPerRow);	
			movsDone++;
		}
	}

	delete directs;
	directs = NULL;

	return movsDone;

}

void GenWormZone::iniBrush(int tile, int brush[BRUSHW][BRUSHH], int tilesPerRow){

	for (int i = 0; i<BRUSHW; i++)
		for (int j=0; j<BRUSHH; j++)
			brush[i][j] = tile + (j*tilesPerRow) + i;
		
}

queue<int>* GenWormZone::genVectorDirections(){
	
	queue<int>* q = new queue<int>();

	//Hacer según tamaño de brocha (ej: screenWidth*screenHeight y comparar con BRUSHW*BRUSHH)
	int maxMovs = rand() % 15 + 10;
	//En vez de poner la dirección aleatoria, se podrían tener movimientos deseados según la zona
	for (int i = 0; i< maxMovs; i++){ 
		q->push(rand() % 4); 
	}
	return q;
}

void GenWormZone::placeSolids(int brush[BRUSHW][BRUSHH]){

	int halfHeight = BRUSHH/2;
	int halfWidth = BRUSHW/2;

	int percent = 50; //porcentaje de q ponga un sólido
	for (int i = 0; i<BRUSHW;i++){
		for (int j=0; j<BRUSHH; j++){
			if ((i >= halfWidth -1 && i < halfWidth +1 ) && (j >= halfHeight -1 && j < halfHeight +1))
				//Cuadrado 2x2 en el centro de la brocha
				overworld->mapTileMatrix->at(brush[i][j])->setSolid(1); //Aquí iría el tipo de sólido que sea
			else{
				if (rand()%101 < percent){ // Ponemos a solido o no los opcionalesb
					overworld->mapTileMatrix->at(brush[i][j])->setSolid(1);
					percent -= 10;
				}
				else
					percent += 10;
			}
		}
	}

	return;
}

bool GenWormZone::canMoveDirection(int direction, int brush[BRUSHW][BRUSHH], int tilesPerRow){

	bool canMove = false;
	
	if (direction== 0){ //Queremos ir a la derecha
		if ( brush[BRUSHW-1][BRUSHH-1] + BRUSHW < overworld->mapTileMatrix->size()){ //no nos salimos de la matriz grande
			if( brush[0][0] / tilesPerRow  == (brush[BRUSHW-1][0]+1) / tilesPerRow){ //si estamos en la misma fila
				canMove = true;
				for (int i = 0; i<BRUSHH; i++){
					if ( canMove )
						// la primera columna de la siguiente brocha son de la misma zona
						canMove = overworld->mapTileMatrix->at(brush[0][i] + BRUSHW)->getZoneNumber() == this->zoneNumber;
					//canMove = true;
				}
			}
		}
	}
	else if(direction==1){ //Queremos ir hacia abajo
		if ( brush[BRUSHW-1][BRUSHH-1] + BRUSHH*tilesPerRow < overworld->mapTileMatrix->size()){ //no nos salimos de la matriz grande
			canMove = true;
			for (int i = 0; i<BRUSHW;i++){
				if (canMove)
					//la primera fila de la siguiente brocha es de la misma zona
					canMove = overworld->mapTileMatrix->at(brush[i][BRUSHH-1] + tilesPerRow)->getZoneNumber() == this->zoneNumber;
				//canMove = true;
			}
		}
	}
	else if(direction==2){//Queremos ir hacia la izquierda
		if ( (brush[0][0] - BRUSHW) >= 0 ){ // no nos salimos de la matriz grande
			if( brush[0][0] / tilesPerRow  == (brush[0][0] - 1) / tilesPerRow){ //si estamos en la misma fila
				canMove = true;
				for(int i = 0; i<BRUSHH; i++)
					if(canMove)
						//la ultima columna de la nueva brocha es de la misma zona
						canMove = overworld->mapTileMatrix->at(brush[0][i] -1)->getZoneNumber() == this->zoneNumber;
				//canMove = true;
			}
		}
	}
	else{
		if ( (brush[0][0] - tilesPerRow*BRUSHH) >= 0 ){
			canMove = true;
			for (int i=0;i<BRUSHW;i++)
				if(canMove)
					//La última fila de la nueva brocha es de nuestra zona
					canMove = overworld->mapTileMatrix->at(brush[i][0] - tilesPerRow)->getZoneNumber() == this->zoneNumber;
			//canMove = true;
		}

	}

	return canMove;

}

void GenWormZone::moveBrush(int nextDir, int brush[BRUSHW][BRUSHH], int tilesPerRow){
	if (nextDir==0){ //Vamos hacia la derecha
		for(int i=0;i<BRUSHW;i++)
			for(int j=0;j<BRUSHH;j++)
				brush[i][j] += BRUSHW;
	}
	else if (nextDir==1){ //Vamos hacia abajo
		for(int i=0;i<BRUSHW;i++)
			for(int j=0;j<BRUSHH;j++)
				brush[i][j] += tilesPerRow*BRUSHH;
	}
	else if (nextDir==2){ //Vamos hacia izquierda
		for(int i=0;i<BRUSHW;i++)
			for(int j=0;j<BRUSHH;j++)
				brush[i][j] -= BRUSHW;
	}
	else{
		for(int i=0;i<BRUSHW;i++)
			for(int j=0;j<BRUSHH;j++)
				brush[i][j] -= tilesPerRow*BRUSHH;
	}
}

void GenWormZone::genDetail(){
	//Aplicamos una capa base
	MapTile* aTile;
	OwScreen* s;
	int i, j;
	for (i=0; i< screenList->size(); i++){
		s = screenList->at(i);
		//Aplicamos una capa base
		for (j=0; j<s->getMatrix()->size(); j++){
			aTile = s->getMatrix()->at(j);
			if (aTile->getZoneNumber() == (zoneNumber || 0)){	// Si esta en nuestra zona o en una frontera
				// si no es un solido, pintamos capa base
				if(aTile->getSolid() < 0){
					aTile->setTileId(1); // aqui deberiamos hacer una query a la base de datos
				} // si es un solido rodeamos con otra capa base 
				else {
					sorrundTile(j, s, 2); // Otra query aqui para el id
				}
			}
		}
	}
}

void GenWormZone::sorrundTile(int pos, OwScreen* s, int id){
	int limits =screenWidth*screenHeight;
	// Solo cambiamos si no es un solido
	// Der
	if(pos+1<screenWidth*screenHeight && s->getMatrix()->at(pos+1)->getSolid()<1)
		s->getMatrix()->at(pos+1)->setTileId(id);
	// Izq
	if(pos-1>=0 && s->getMatrix()->at(pos-1)->getSolid()<1)
		s->getMatrix()->at(pos-1)->setTileId(id);
	// Arriba
	if(pos-screenWidth>=0 && s->getMatrix()->at(pos-screenWidth)->getSolid()<1)
		s->getMatrix()->at(pos-screenWidth)->setTileId(id);
	// Abajo
	if(pos+screenWidth<limits && s->getMatrix()->at(pos+screenWidth)->getSolid()<1)
		s->getMatrix()->at(pos+screenWidth)->setTileId(id);

	//faltan diagonales

}