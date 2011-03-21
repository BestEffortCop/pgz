#include "Zone.h"

// Constructora.
Zone::Zone(int zoneTypeId, vector<GPoint>* zoneShape, vector<MapTile*>* mapTileM){
	// Asignamos parametros a los atributos.
	typeId = zoneTypeId;
	shape = zoneShape;
	mapTileMatrix = mapTileM;
	screenList = new vector<OwScreen*>();
}

// Destructora.
Zone::~Zone(){
	vector<OwScreen*>::iterator it;
    for(it = screenList->begin(); it != screenList->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete screenList;
	screenList = NULL;
}

// Devuelve el tipo de zona en forma de int.
int Zone::getTypeId(){
	return typeId;
}

// Permite modificar el tipo asociado a una zona.
void Zone::setTypeId(int tId){
	typeId = tId;
}

// Devuelve el conjunto de puntos delimitador de zona.
vector<GPoint>* Zone::getShape(){
	return shape;
}

// Permite modificar el delimitador de zona.
void Zone::setShape(vector<GPoint>* s){
	shape = s;
}

// Coloca una mazmorra. Ricky: al final no recuerdo qu decidimos si les pasabamos tanta informacion o no.
void Zone::placeDungeon(vector<int>* idTools,int dungNumber, int gameDiff,int typeId, vector<int>* keyObjects, int dungSize, int ratio,
										vector<int>* idBosses, vector<int>* idEnemies, GPoint pos, vector<int>* idMiniBosses)
{
	cout << "Ejecutando funcion <>Zone::placeDungeon()>" << endl;
}

// Por decidir, de primeras coloca la entrada a una zona segura. (Ricky: esto tendra tela)
void Zone::placeSafeZone(int idZone,GPoint* pos){
	cout << "Ejecutando funcion <>Zone::placeSafeZone()>" << endl;
}

void Zone::genScreens(){
   	for (unsigned int i=0; i< screenList->size(); i++){
		OwScreen* screen = screenList->at(i);
		screen->placeDetails();
		screen->placeEnemies();
		string screenpath = screen->createScreenFiles();
	}
}


// Devuelve el número de orden de la mazmorra que se encuentra en la zona
int Zone::getDungeonNumber(){
	return dungeonNumber;
}

// Establece un nuevo número de orden de la mazmorra de la zona
void Zone::setDungeonNumber(int dunNum){
	dungeonNumber = dunNum;
}

void Zone::addScreen(OwScreen* ows){
	screenList->push_back(ows);
}

void Zone::genGeoDetail(int screensPerRow){
	
	//una posible aproximación de movimientos de gusanos
	//por ahora vamos a hacer 5 moves por pantalla aprox
	int moves = 10*( rand()%(screenList->size()) + screenList->size()/2); // 1/2 + ~1 = rango(1/2, 3/2) movimientos de gusano por pantalla
	int movesDone = 0;
	while ( movesDone < moves )
	{
		movesDone = movesDone + genWormDetail(screensPerRow);
	}

	/*int times = rand()%(screenList->size()/2) + screenList->size()/3; 
	for (int i=0; i<times; i++)
		genWormDetail(screensPerRow);*/
}

int Zone::genWormDetail(int screensPerRow){
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

void Zone::iniBrush(int tile, int brush[BRUSHW][BRUSHH], int tilesPerRow){

	for (int i = 0; i<BRUSHW; i++)
		for (int j=0; j<BRUSHH; j++)
			brush[i][j] = tile + (j*tilesPerRow) + i;
		
}

queue<int>* Zone::genVectorDirections(){
	
	queue<int>* q = new queue<int>();

	//Hacer según tamaño de brocha (ej: screenWidth*screenHeight y comparar con BRUSHW*BRUSHH)
	int maxMovs = rand() % 10 + 5;
	//En vez de poner la dirección aleatoria, se podrían tener movimientos deseados según la zona
	for (int i = 0; i< maxMovs; i++){ 
		q->push(rand() % 4); 
	}
	return q;
}

void Zone::placeSolids(int brush[BRUSHW][BRUSHH]){

	int halfHeight = BRUSHH/2;
	int halfWidth = BRUSHW/2;

	int percent = 50; //porcentaje de q ponga un sólido
	for (int i = 0; i<BRUSHW;i++){
		for (int j=0; j<BRUSHH; j++){
			if ((i >= halfWidth -1 && i < halfWidth +1 ) && (j >= halfHeight -1 && j < halfHeight +1))
				//Cuadrado 2x2 en el centro de la brocha
				mapTileMatrix->at(brush[i][j])->setSolid(1); //Aquí iría el tipo de sólido que sea
			else{
				if (rand()%101 < percent){ // Ponemos a solido o no los opcionalesb
					mapTileMatrix->at(brush[i][j])->setSolid(1);
					percent -= 10;
				}
				else
					percent += 10;
			}
		}
	}

	return;
}

bool Zone::canMoveDirection(int direction, int brush[BRUSHW][BRUSHH], int tilesPerRow){

	bool canMove = false;
	
	if (direction== 0){ //Queremos ir a la derecha
		if ( brush[BRUSHW-1][BRUSHH-1] + BRUSHW < mapTileMatrix->size()){ //no nos salimos de la matriz grande
			if( brush[0][0] / tilesPerRow  == (brush[BRUSHW-1][0]+1) / tilesPerRow){ //si estamos en la misma fila
				canMove = true;
				for (int i = 0; i<BRUSHH; i++){
					if ( canMove )
						// la primera columna de la siguiente brocha son de la misma zona
						canMove = mapTileMatrix->at(brush[0][i] + BRUSHW)->getZoneNumber() == this->zoneNumber;
				}
			}
		}
	}
	else if(direction==1){ //Queremos ir hacia abajo
		if ( brush[BRUSHW-1][BRUSHH-1] + BRUSHH*tilesPerRow < mapTileMatrix->size()){ //no nos salimos de la matriz grande
			canMove = true;
			for (int i = 0; i<BRUSHW;i++){
				if (canMove)
					//la primera fila de la siguiente brocha es de la misma zona
					canMove = mapTileMatrix->at(brush[i][BRUSHH-1] + tilesPerRow)->getZoneNumber() == this->zoneNumber;
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
						canMove = mapTileMatrix->at(brush[0][i] -1)->getZoneNumber() == this->zoneNumber;
			}
		}
	}
	else{
		if ( (brush[0][0] - tilesPerRow*BRUSHH) >= 0 ){
			canMove = true;
			for (int i=0;i<BRUSHW;i++)
				if(canMove)
					//La última fila de la nueva brocha es de nuestra zona
					canMove = mapTileMatrix->at(brush[i][0] - tilesPerRow)->getZoneNumber() == this->zoneNumber;
		}

	}

	return canMove;

}

void Zone::moveBrush(int nextDir, int brush[BRUSHW][BRUSHH], int tilesPerRow){
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