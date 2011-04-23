#include "DungeonJ.h"

DungeonJ::DungeonJ(string zone, string theme, int gameDiff, int dungNumber, int ratio, short tool, short keyObj, DBManager* db) : Dungeon(zone,theme,gameDiff,dungNumber,ratio,tool,keyObj,db) {
	// A falta de conocer los datos concretos sobre los que oscilen los paramétros

	// gameDiff 0 fácil 1 medio 2 díficil
	// ratio [0-1] 0 ningún puzzle - 1 todo puzzle

	// Calculamos el número de pantallas.
	
	switch(gameDiff){
		case (0): // fácil
			n_puzzles = (dungNumber) * ratio/100; // n_puzzles en función de dungNumber 
			n_minibosses = (dungNumber/3) * (1 - ratio/100); // solo miniboss a partir de la tercera
			break;
		case (1): // medio
			n_puzzles = (2 + dungNumber) * ratio/100; // n_puzzles en función de dungNumber 
			n_minibosses = (dungNumber/3  + 2) * (1 - ratio/100); // solo miniboss a partir de la tercera
			break;
		case (2): // díficil
			n_puzzles = (4 + dungNumber) * ratio/100; // n_puzzles en función de dungNumber 
			n_minibosses = (dungNumber/3  + 4) * (1 - ratio/100); // solo miniboss a partir de la tercera
			break;
		default: // medio
			n_puzzles = (2 + dungNumber) * ratio/100; // n_puzzles en función de dungNumber 
			n_minibosses = (dungNumber/3  + 2) * (1 - ratio/100); // solo miniboss a partir de la tercera
			break;
	}

	n_puertas = 0; // contador
	
	if(tool != -1)
		 n_collectables = 1; // solo tool de momento
	else
		n_collectables = 0; 

	nZones = n_puzzles + n_minibosses + n_collectables + 1 + 1 + 1;// nPuzzles + minibosses + inicio + final + llave boss;

	// si hay algo raro en la parametrización se genera con caso extremo soportado por el generador
	if(nZones > 16){

		switch(gameDiff){
			case (0): // fácil
				n_puzzles = 8 * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (8/3) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
			case (1): // medio
				n_puzzles = (2 + 8) * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (8/3  + 2) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
			case (2): // díficil
				n_puzzles = (4 + 8) * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (8/3  + 4) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
			default: // medio
				n_puzzles = (2 + 8) * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (8/3  + 2) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
		}	

		nZones = n_puzzles + n_minibosses + n_collectables + 1 + 1 + 1;// nPuzzles + minibosses + inicio + final + llave boss;
	}
	switch(gameDiff){
		case (0):
			n_enemies = 2 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
			break;
		case (1):
			n_enemies = 3 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
			break;
		case (2):
			n_enemies = 4 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
			break;
		default:
			n_enemies = 3 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
			break;
	}

	enemies = new int[nZones];
	
	dist = new zoneType[nZones];

	idLock = 1;

}
// debug
void DungeonJ::genTable(int dungeonNumber,int gameDiff, double ratio){
	int n_puzzles,n_minibosses,n_enemies,n_collectables,nZones;
	
	n_collectables = 1; 
	printf("Dificultad:%d \nRatio:%d\n",gameDiff,ratio);
	printf("Puzzles Minibosses Enemies Collectables DungeonSize, \n");
	for (int i = 0; i < dungeonNumber; i++){
		switch(gameDiff){
			case (0):
				n_puzzles = i * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (i/3) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
			case (1):
				n_puzzles = (2 + i) * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (i/3  + 2) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
			case (2):
				n_puzzles = (4 + i) * ratio/100; // n_puzzles en función de dungNumber 
				n_minibosses = (i/3  + 4) * (1 - ratio/100); // solo miniboss a partir de la tercera
				break;
		}
		nZones = n_puzzles + n_minibosses + 1 + 1 + n_collectables;
		switch(gameDiff){
			case (0):
				n_enemies = 2 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
				break;
			case (1):
				n_enemies = 3 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
				break;
			case (2):
				n_enemies = 4 * (1-ratio/100) * (DUNGEON_SIZE(nZones));
				break;
		}
		printf("  %d       %d          %d         %d          %d\n",n_puzzles,n_minibosses,n_enemies,n_collectables,(DUNGEON_SIZE(nZones)));
	}
}

DungeonJ::~DungeonJ() {
	delete enemies; 
	delete dist;

	for(int x = 0; x < width; x++){
		delete layout[x];
	}
	delete layout;
}

DunScreen* DungeonJ::findScreen(int x, int y){
	DunScreen* s;
	int i = 0;
	bool found = false;
	while(i < screenList->size() && !found){
		s = (DunScreen*)screenList->at(i);
		found = (s->getPosX() == x) && (s->getPosY() == y);
		i++;
	}
	if(found) 
		return s;
	else 
		return NULL;
}

void DungeonJ::generate() {
	// generamos el layout
	genLayout();

	// asignamos a cada zona un elemento vease puzzle, miniboss, herramienta inicio y fin
	placeItems();
	
	for (vector<Screen*>::iterator it= screenList->begin(); it < screenList->end(); it++)
			(*it)->generate();

	n_collectables = 0;

	index_collectables();

	int placed_enemies = 0;
	for (vector<Screen*>::iterator it= screenList->begin(); it < screenList->end(); it++)
			placed_enemies += (*it)->getNEnemies();
		
	printf("\nDificultad:%d \nRatio:%d\n", difficulty,ratio);
	printf("Puzzles Minibosses Enemies Collectables Enemies placed\n");
	printf("  %d       %d          %d         %d         %d\n",n_puzzles,n_minibosses,n_enemies,n_collectables,placed_enemies);

	/*printf("Bloqueos: %d\n",n_puertas);
	for (vector<Screen*>::iterator it= screenList->begin(); it < screenList->end(); it++){
		DunScreen* d = (DunScreen*)(*(it));
		if(d->has_lock())
			printf("Posicion:(%d,%d)\n",d->getPosX(),d->getPosY());
	}*/
}

void DungeonJ::placeBoss(){
	DunScreen* bossScreen = NULL,*keyItemScreen = NULL;
	int bossX,bossY;
	int	keyItemY, keyItemX;
	int aux,block;
	for (vector<Screen*>::iterator it = screenList->begin(); it < screenList->end(); it++){
		DunScreen* d = (DunScreen*)(*(it));
		int x = (*it)->getPosX(); 
		int y = (*it)->getPosY();
		if(layout[x][y]/ZONE_SIZE == nZones-1 && d->has_lock() &&
			((x-1 >= 0 && (layout[x-1][y]/ZONE_SIZE) == nZones-1) ||
			(x+1 < width && (layout[x+1][y]/ZONE_SIZE) == nZones-1) ||
			(y-1 >= 0 && (layout[x][y-1]/ZONE_SIZE) == nZones-1) ||
			(y+1 < height && (layout[x][y+1]/ZONE_SIZE) == nZones-1))){	
				bossX = (*it)->getPosX(); 
				bossY = (*it)->getPosY();
				bossScreen = (DunScreen*)(*it);
		} 
	}
	// la muerte!!! y solo por 1 caso de 10000
	if(bossScreen == NULL){
		for (vector<Screen*>::iterator it = screenList->begin(); it < screenList->end(); it++){
			int x = (*it)->getPosX(); 
			int y = (*it)->getPosY();
			if(layout[x][y]/ZONE_SIZE == nZones-1
					&&			
				((x-1 >= 0 && (layout[x-1][y]/ZONE_SIZE) < nZones-1 && (layout[x-1][y]/ZONE_SIZE) >= nZones-3) ||
				(x+1 < width && (layout[x+1][y]/ZONE_SIZE) < nZones-1 && (layout[x+1][y]/ZONE_SIZE) >= nZones-3) ||
				(y-1 >= 0 && (layout[x][y-1]/ZONE_SIZE) < nZones-1 && (layout[x][y-1]/ZONE_SIZE) >= nZones-3) ||
				(y+1 < height && (layout[x][y+1]/ZONE_SIZE) < nZones-1 && (layout[x][y+1]/ZONE_SIZE) >= nZones-3))
					&&
				((x-1 >= 0 && (layout[x-1][y]/ZONE_SIZE) == nZones-1) ||
				(x+1 < width && (layout[x+1][y]/ZONE_SIZE) == nZones-1) ||
				(y-1 >= 0 && (layout[x][y-1]/ZONE_SIZE) == nZones-1) ||
				(y+1 < height && (layout[x][y+1]/ZONE_SIZE) == nZones-1))){	
					bossX = (*it)->getPosX(); 
					bossY = (*it)->getPosY();
					bossScreen = (DunScreen*)(*it);
					if(x-1 >= 0 && (layout[x-1][y]/ZONE_SIZE) < nZones-1&& (layout[x][y+1]/ZONE_SIZE) >= nZones-3)
						bossScreen->setLock(LEFT);
					else
						if(x+1 < width && (layout[x+1][y]/ZONE_SIZE) < nZones-1 && (layout[x][y+1]/ZONE_SIZE) >= nZones-3)
							bossScreen->setLock(RIGHT);
						else 
							if(y-1 >= 0 && (layout[x][y-1]/ZONE_SIZE) < nZones-1 && (layout[x][y+1]/ZONE_SIZE) >= nZones-3)
								bossScreen->setLock(DOWN);
							else 
								if(y+1 < height && (layout[x][y+1]/ZONE_SIZE) < nZones-1 && (layout[x][y+1]/ZONE_SIZE) >= nZones-3)
									bossScreen->setLock(UP);
			} 
		}
	}
	for (vector<Screen*>::iterator it = screenList->begin(); it < screenList->end(); it++){
		keyItemX = (*it)->getPosX(); 
		keyItemY = (*it)->getPosY();
		if(layout[(*it)->getPosX()][(*it)->getPosY()]/ZONE_SIZE == nZones-1 
			){	
			if(keyItemX == bossX+1 && keyItemY == bossY){
				keyItemScreen = (DunScreen*)(*it);
				aux = RIGHT; 
			}
			if(keyItemX == bossX-1 && keyItemY == bossY){
				keyItemScreen = (DunScreen*)(*it);
				aux = LEFT;
			}
			if(keyItemY == bossY+1  && keyItemX == bossX){
				keyItemScreen = (DunScreen*)(*it);
				aux = UP;
			}
			if(keyItemY == bossY-1 && keyItemX == bossX){
				keyItemScreen = (DunScreen*)(*it);
				aux = DOWN;
			}
		}
	}
	for(int i = 0; i < 4; i++){
		if(i != aux){
			keyItemScreen->unSetDoor(i); // fuera puertas en la habitación del objeto clave salvo la que conecte con boss
			keyItemScreen->unSetLock(i);
		}
		if(bossScreen->getLock(i)) // busco el sentido del  bloqueo del boss.
			block = i;
	}
	for(int i = 0; i < 4; i++){
		if(i != aux && i != block)
			bossScreen->unSetDoor(i); // fuera puertas en la habitación del boss
	}
	// ponemos la puerta, objeto clave y bloqueo de boss. Se quita el normal por si acaso da problemas
	bossScreen->unSetLock(block);
	bossScreen->setBoss_lock(block,0);
	bossScreen->setDoor(block);
	bossScreen->setBoss(1);
	keyItemScreen->setKeyObj(0);
	// coloco el bloqueo en la habitacion opuesta al boss
	DunScreen* s;
	switch(block){
		case(UP): 
			s = findScreen(bossX,bossY-1);
			s->setBoss_lock(DOWN);
			s->unSetLock(DOWN);
			break;
		case(DOWN):
			s = findScreen(bossX,bossY+1);
			s->setBoss_lock(UP);
			s->unSetLock(UP);
			break;
		case(LEFT):
			s = findScreen(bossX-1,bossY);
			s->setBoss_lock(RIGHT);
			s->unSetLock(RIGHT);
			break;
		case(RIGHT):
			s = findScreen(bossX+1,bossY);
			s->setBoss_lock(LEFT);
			s->unSetLock(LEFT);
			break;
	}	
}

void DungeonJ::placeKeys(int zone){
	int d = INT_MIN;
	DunScreen* auxScreen = NULL;
	int x = 0,y = 0;
	int block1X = -1,block1Y = -1;
	int block2X = -1,block2Y = -1;
	// se buscan las X e y del bloqueo de la zona anterior y posterior
	for (vector<Screen*>::iterator it = screenList->begin(); it < screenList->end(); it++){
			DunScreen* d = (DunScreen*)(*(it));
			if(layout[(*it)->getPosX()][(*it)->getPosY()]/ZONE_SIZE == zone && d->has_lock()
				|| (zone == 0 && (*it)->getPosX() == iniX && (*it)->getPosY() == iniY)){
				if((block1X == -1)){
					block1X = (*it)->getPosX();
					block1Y = (*it)->getPosY();
				}
				else
					if(block1X != 0 && block2X == -1){
						block2X = (*it)->getPosX();
						block2Y = (*it)->getPosY();
					}
			} 
	}
	// Recorremos el resto de pantallas de zona y escogemos aquella con mayor distancia a screen bloqueada que no 
	// tenga elemento relevante ( collectable puzzle miniboss etc) <-- si el puzzle da llave no se consideran "zonas puzzle"
	for (vector<Screen*>::iterator it = screenList->begin(); it < screenList->end(); it++){
			DunScreen* ds = (DunScreen*)(*(it));
			if(layout[(*it)->getPosX()][(*it)->getPosY()]/ZONE_SIZE == zone && !ds->has_lock() && !checkElement(*(it))){	
				if(block2X != -1){
					if((LONG(block1X,block1Y,(*it)->getPosX(),(*it)->getPosY()))+
						(LONG(block2X,block2Y,(*it)->getPosX(),(*it)->getPosY()))
						>
						d){
						x = (*it)->getPosX(); 
						y = (*it)->getPosY();
						auxScreen = (DunScreen*) (*it);
						d = (LONG(block1X,block1Y,(*it)->getPosX(),(*it)->getPosY()))+
							(LONG(block2X,block2Y,(*it)->getPosX(),(*it)->getPosY())); 
					}
				}else{
					if((LONG(block1X,block1Y,(*it)->getPosX(),(*it)->getPosY())) > d){
						x = (*it)->getPosX(); 
						y = (*it)->getPosY();
						auxScreen = (DunScreen*) (*it);
						d = LONG(block1X,block1Y,(*it)->getPosX(),(*it)->getPosY()); 
					}
				}
			} 
	}
	// sino la encuentra toma la primera de la zona.
	if (auxScreen == NULL)
		for (vector<Screen*>::iterator it = screenList->begin(); it < screenList->end(); it++){
				if(layout[(*it)->getPosX()][(*it)->getPosY()]/ZONE_SIZE == zone){	
					auxScreen = (DunScreen*)(*it);
				} 
		}

	auxScreen->setKey();
}

bool DungeonJ::checkElement(Screen* s){
	DunScreen* ds = (DunScreen*)s;
	return ds->getPuzzle() != -1 || ds->getMiniBoss() != -1 || ds->getTool() != -1;
}

int DungeonJ::getEnemies(int zone){
	int n = rand() % ENEMY_NUMBER; // 16
	int aux;
	if(enemies[zone] <= 0){
		return 0;
	}
	if(n == 0 || n == 1 || n == 2)
		aux = 1;
	else
		if(n == 3 || n == 4 || n == 5)
			aux = 2;
		else
			if(n == 6 || n == 7 ||n == 8)
				aux = 3;
			else
				if(n == 9 || n == 10)
					aux = 4;
				else
					if(n == 11 || n == 12)
						aux = 5;
					else
						if(n == 13 ||n == 14)
							aux = 0;
						else
							if(n == 15)
								aux = 6;
	enemies[zone] -= aux;
	return aux;
}

int DungeonJ::countRooms(int** layout){
	int n = 0;
	if(layout != NULL)
		for(int r = 0; r < DUNGEON_SIZE(nZones); r++)
			for(int c = 0; c < DUNGEON_SIZE(nZones); c++)
				if(layout[r][c] >= 0)
						n++;
	return n;
}

bool DungeonJ::checkDungeon(int** layout){
	bool err = false;
	if(layout != NULL){
		for(int r = 0; r < DUNGEON_SIZE(nZones); r++){
			for(int c = 0; c < DUNGEON_SIZE(nZones); c++){
				if(layout[r][c] >= 0){
					err = err || checkZone(layout,r,c);
				}
			}
		}
	}
	return err;
}

bool DungeonJ::checkZone(int** layout, int x, int y){
	bool err;

	err = (x-1 >=0 && layout[x-1][y] >= 0 && (layout[x-1][y]/ZONE_SIZE) == layout[x][y]/ZONE_SIZE );

	err = err || (x+1 < DUNGEON_SIZE(nZones)&& layout[x+1][y] >= 0 && (layout[x+1][y]/ZONE_SIZE) == layout[x][y]/ZONE_SIZE );

	err = err || (y-1 >=0 && layout[x][y-1] >= 0 && (layout[x][y-1]/ZONE_SIZE) == layout[x][y]/ZONE_SIZE);

	err = err || (y+1 < DUNGEON_SIZE(nZones)&& layout[x][y+1] >= 0 && (layout[x][y+1]/ZONE_SIZE) == layout[x][y]/ZONE_SIZE);

	return !err;
}

void DungeonJ::genLayout() {
	// generamos el layout instanciando un objeto igraphcontrol que nos devuelve una matriz int** con el layout 
	// comprobamos si cumple el mínimo de un 90% de habitaciones exigido
	// sino generamos uno nuevo // valores de ZONE_SIZE = 5 y nZones 20 máximos o menos nZone y mas ZONE_SIZE en ese caso se pueden conseguir más salas
	size = 0; 
	IGraphControl* igraphControl = NULL;
	layout = NULL;
	bool err = false;
	int n = 0;
	while((size < DUNGEON_SIZE(nZones)*0.9) || checkDungeon(layout)){
			if(igraphControl != NULL)
				delete igraphControl;
			igraphControl = new IGraphControl(IGraphControl::a,nZones);
			layout = igraphControl->toLayout();
			size = countRooms(layout);
	}
	// resize Layout a dimensiones que se ajusten al resultado
	int minY = INT_MAX;
	int maxY = 0;
	int minX = INT_MAX;
	int maxX = 0;
	for (int y = 0; y < DUNGEON_SIZE(nZones); y++)
		for (int x = 0; x < DUNGEON_SIZE(nZones); x++){
			if(layout[y][x] != -1){
				if(y < minY) 
					minY = y;
				if(y > maxY)
					maxY = y;
				if(x < minX)
					minX = x;
				if(x > maxX)
					maxX = x;
			}
		}
	width = maxX - minX + 1;
	height = maxY - minY + 1;

	// reservamos memoria para la redimensión
	int** layoutAux = new int*[width];
	for(int x = 0; x < width; x++){
		layoutAux[x] = new int[height];
	}
	// copiamos la submatriz
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
				layoutAux[x][y] = layout[minY+y][minX+x]; 
		
	// muestra resultados
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			if(layoutAux[x][y] == -1)
				printf(". ");
			else
				printf("%d ",layoutAux[x][y]);
		
		}
	printf("\n");
	}	
	printf("\n");
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			if(layoutAux[x][y] == -1)
				printf(". ");
			else
				printf("# ");
		
		}
	printf("\n");
	}		
	printf("\nNSalas: %d\nAlto: %d Ancho: %d",size,width,height);

	delete igraphControl;

	layout = layoutAux;
	layoutAux = NULL;
}

void DungeonJ::blockPath() {}

void DungeonJ::zoneAllocations(){
	// Asigna a cada zona un elemento siguiendo el orden:
	// inicio
	// puzzles
	// miniboss o collectable
	// puzzles
	// miniboss o collectable
	// puzzles
	// boss
	for(int i=0; i < nZones; i++)
		enemies[i] = n_enemies/nZones;

	// Entrada = 0, puzzle = 1, miniboss = 2 collectable = 3 final = 4 
	int idZone = 0;
	dist[idZone] = ENTRANCE;
	idZone++;
	int nc = n_collectables;
	int nm = n_minibosses;
	int np = n_puzzles;
	bool boss_key = false;
	int aux = 0;
	if(np >= nm + nc +1){
		
		while(aux < n_puzzles + n_collectables + n_minibosses + 1){
		
			if(np != 0){
				dist[idZone] = PUZZLE; 
				idZone++;
				np--;
			}
			if(nc == 0 && nm != 0){
				dist[idZone] = MINIBOSS;
				idZone++;
				nm--;
			}
			else{
				if(nm == 0 && nc != 0){
					dist[idZone] = COLLECTABLE;
					idZone++;
					nc--;
				}
				if(nm == 0 && nc == 0 && !boss_key){
					dist[idZone] = BOSSS_KEY;
					idZone++;
					boss_key = true;
				}
				else{
					if(nc != 0 && nm != 0){
						int n = rand()%3; 
						if(n== 0){
							dist[idZone] = MINIBOSS;
							idZone++;
							nm--;
						}
						else{
							if(n==1){
								dist[idZone] = COLLECTABLE;
								idZone++;
								nc--;
							}
							else{
								dist[idZone] = BOSSS_KEY;
								idZone++;
								boss_key = true;
							}
						}
					}
				}
			}
			aux++;
		}
	}
	else{
	
		while(aux <  n_minibosses + n_collectables + n_puzzles){
			if(np != 0){
				dist[idZone] = PUZZLE; 
				idZone++;
				np--;
			}
			if(nm != 0){
				dist[idZone] = MINIBOSS;
				idZone++;
				nm--;
			}
			if(nc != 0){
				dist[idZone] = COLLECTABLE;
				idZone++;
				nc--;
			}
			if(!boss_key){
				dist[idZone] = BOSSS_KEY;
				idZone++;
				boss_key = true;
			}
			aux++;
		}
	}
	dist[idZone] = BOSS;
}

void DungeonJ::placeItems(){
	zoneAllocations();
	// vamos con las pantallas
	// vector de zonas visitadas
	bool* visited = new bool[nZones];
	for(int i = 0; i < nZones; i++)
		visited[i] = false;
	// vector de conexiones entre zonas para  asegurar exista un bloqueo entre ellas de momento todas tienen aunque se
	// podrían eliminar bloqueos asignando 1's a este vector
	int* linked = new int[nZones-1]; 
	for(int i = 0; i < nZones-1; i++)
		linked[i] = 0;

	pair<int,int>* block = new pair<int,int>[(DUNGEON_SIZE(nZones))];
	for(int i = 0; i < (DUNGEON_SIZE(nZones)); i++)
			block[i] = make_pair(-1,-1);

	DunScreen* s; 
	for (int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++){

			if(layout[x][y] == 0){
					iniX = x;
					iniY = y;
			}
			if(layout[x][y] >= 0){
				// obtenemos el número de zona
				int nZone = layout[x][y]/ZONE_SIZE;
				if((!visited[nZone]) && (layout[x][y] >= 0) && (nZone != nZones - 1)){
					// Instanciamos pantallas con elementos interesantes
					switch(dist[nZone]){
						case ENTRANCE: // entrada 
							s = new DunScreen(x, y, -1, getEnemies(nZone), -1, -1, -1, zone, theme, db, numDungeon);
							break;
						case PUZZLE: // puzzle
							s = new DunScreen(x, y, 1, getEnemies(nZone), -1, -1, -1, zone, theme, db, numDungeon);
							break;
						case MINIBOSS:// miniboss
							s = new DunScreen(x, y, -1, getEnemies(nZone), -1, 1, -1, zone, theme, db, numDungeon);
							break;
						case COLLECTABLE: // collectable
							s = new DunScreen(x, y, -1, getEnemies(nZone), -1, -1, 1, zone, theme, db, numDungeon);
							break;
						case BOSSS_KEY: { // llave del boss
							s = new DunScreen(x, y, -1, getEnemies(nZone), -1, -1, -1, zone, theme, db, numDungeon);
							s->setBoss_key();
							}
							break;
					}
					visited[nZone] = true;
					// Le ponemos puertas comprobamos si es de su misma zona el id en el layout o si le toca conexión con otra zona 
					if( (y - 1 >= 0) && (layout[x][y-1]/ZONE_SIZE == nZone) && layout[x][y-1] >= 0)
						s->setDoor(UP);	
					if((x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE == nZone) && layout[x-1][y] >= 0)
						s->setDoor(LEFT);			
					
					if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == nZone) && layout[x+1][y] >= 0)
						s->setDoor(RIGHT);

					if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == nZone) && layout[x][y+1] >= 0)
						s->setDoor(DOWN);

					if( (x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE  == nZone + 1) && !linked[nZone]) {
						s->setDoor(LEFT);
						s->setLock(LEFT,idLock);
						linked[nZone] = true;
						block[layout[x-1][y]].first = RIGHT;
						block[layout[x-1][y]].second = idLock;
						idLock++;
					}
					else
						if((y - 1 >= 0) && ( layout[x][y-1]/ZONE_SIZE == nZone + 1) && !linked[nZone]){
							s->setDoor(UP);
							s->setLock(UP,idLock);
							linked[nZone] = true;
							block[layout[x][y-1]].first = DOWN;
							block[layout[x][y-1]].second = idLock;
							idLock++;
						}
						else 
							if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == nZone + 1) && !linked[nZone]){
								s->setDoor(DOWN);
								s->setLock(DOWN,idLock);
								linked[nZone] = true;
								block[layout[x][y+1]].first = UP;
								block[layout[x][y+1]].second = idLock;
								idLock++;
							}
							else
								if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == nZone + 1) && !linked[nZone]){
									s->setDoor(RIGHT);
									s->setLock(RIGHT,idLock);
									linked[nZone] = true;
									block[layout[x+1][y]].first = LEFT;
									block[layout[x+1][y]].second = idLock;
									idLock++;
								}
					// Añadimos la pantalla al vector
					screenList->push_back(s);
					}
					else{
						// Instanciamos pantallas
						s = new DunScreen(x, y, -1, getEnemies(nZone), -1, -1, -1, zone,theme, db, numDungeon);
						// Le ponemos puertas comprobamos si es de su misma zona el id en el layout o si le toca conexión con otra zona 
						if( (y - 1 >= 0) && (layout[x][y-1]/ZONE_SIZE == nZone) && layout[x][y-1] >= 0)
							s->setDoor(UP);
						
						if((x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE == nZone) && layout[x-1][y] >= 0)
							s->setDoor(LEFT);			
					
						if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == nZone) && layout[x+1][y] >= 0)
							s->setDoor(RIGHT);

						if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == nZone) && layout[x][y+1] >= 0)
							s->setDoor(DOWN);

						if( (x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE  == nZone + 1) && !linked[nZone]) {
							s->setDoor(LEFT);
							s->setLock(LEFT,idLock);
							linked[nZone] = true;
							block[layout[x-1][y]].first = RIGHT;
							block[layout[x-1][y]].second = idLock;
							idLock++;
						}
						else
							if((y - 1 >= 0) && ( layout[x][y-1]/ZONE_SIZE == nZone + 1) && !linked[nZone]){
								s->setDoor(UP);
								s->setLock(UP,idLock);
								linked[nZone] = true;
								block[layout[x][y-1]].first = DOWN;
								block[layout[x][y-1]].second = idLock;
								idLock++;
							}
							else 
								if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == nZone + 1) && !linked[nZone]){
									s->setDoor(DOWN);
									s->setLock(DOWN,idLock);
									linked[nZone] = true;
									block[layout[x][y+1]].first = UP;
									block[layout[x][y+1]].second = idLock;
									idLock++;
								}
								else
									if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == nZone + 1) && !linked[nZone]){
										s->setDoor(RIGHT);
										s->setLock(RIGHT,idLock);
										linked[nZone] = true;
										block[layout[x+1][y]].first = LEFT;
										block[layout[x+1][y]].second = idLock;
										idLock++;
									}
						// Añadimos la pantalla al vector
						screenList->push_back(s);
					}
				}
			}
		}

	for (int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			// Comprobamos si es pantalla inicial de zona y si lo es se crea la otra parte del bloqueo
			if(layout[x][y] != -1)
				if((block[layout[x][y]]).first != -1){
							s = findScreen(x,y);
							if(s != NULL){
								s->setDoor(block[layout[x][y]].first);
								s->setLock(block[layout[x][y]].first,block[layout[x][y]].second);
							}
				}
		}
	}
	// se coloca boss junto con puerta y habitación de keyItem
	placeBoss();
	// Coloco llaves si existe bloqueo en la zona
	for(int i = 0; i < nZones-1; i++){
		if(linked[i] == 1)
			placeKeys(i);
	}
	delete visited;
	delete linked;
	delete block;
}