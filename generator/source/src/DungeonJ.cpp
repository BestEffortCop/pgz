#include "DungeonJ.h"

DungeonJ::DungeonJ(string zone, string theme, int gameDiff, int dungNumber, int ratio, short tool, DBManager* db) : Dungeon(zone,theme,gameDiff,dungNumber,ratio,tool,db) {
	/*	int miniboss; 
		int keyItem;	*/				

	// Calculamos el número de habitaciones
	n_puzzles = 2*dungNumber;
	n_puertas = 0;
	n_minibosses = 1;
	n_collectables = 1;

	nZones = gameDiff;//1 + n_puzzles + n_minibosses + n_collectables + 1 + 1;//nTools + nPuzzles + miniboss + inicio + final; 

	dist = new short[3];
}

DungeonJ::~DungeonJ() {

	//delete dist;

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

	// vamos con las pantallas
	// vector de zonas visitadas
	bool* visited = new bool[nZones];
	for(int i = 0; i < nZones; i++)
		visited[i] = false;
	// vector de conexiones entre zonas para  asegurar exista un enlace entre ellas
	bool* linked = new bool[nZones-1]; 
	for(int i = 0; i < nZones-1; i++)
		linked[i] = false;

	int* block = new int[(DUNGEON_SIZE(nZones))];
	for(int i = 0; i < (DUNGEON_SIZE(nZones)); i++)
			block[i] = -1;

	DunScreen* s; 
	for (int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++){

			if(layout[x][y] == 0){
					iniX = x;
					iniY = y;
			}
			if(layout[x][y] >= 0){
				// obtenemos el número de zona
				int zone = layout[x][y]/ZONE_SIZE;
				if((!visited[zone]) && (layout[x][y] >= 0)){
					// Instanciamos pantallas con elementos interesantes
					switch(dist[zone]){
						case 0: // entrada
							s = new DunScreen(x, y, -1, 3, -1, -1, -1, "Zona","Tema", db);
							break;
						case 1: // puzzle
							s = new DunScreen(x, y, 1, 3, -1, -1, -1, "Zona","Tema", db);
							break;
						case 2:// miniboss
							s = new DunScreen(x, y, -1, 3, -1, 1, -1, "Zona","Tema", db);
							break;
						case 3: // collectable
							s = new DunScreen(x, y, -1, 3, -1, -1, 1, "Zona","Tema", db);
							break;
						case 4: // boss
							s = new DunScreen(x, y, -1, 3, 1, -1, -1, "Zona","Tema", db);
							break;
					}
					visited[zone] = true;
					// Le ponemos puertas comprobamos si es de su misma zona el id en el layout o si le toca conexión con otra zona 
					if( (y - 1 >= 0) && (layout[x][y-1]/ZONE_SIZE == zone) && layout[x][y-1] >= 0)
						s->setDoor(UP);
						
					if((x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE == zone) && layout[x-1][y] >= 0)
						s->setDoor(LEFT);			
					
					if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == zone) && layout[x+1][y] >= 0)
						s->setDoor(RIGHT);

					if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == zone) && layout[x][y+1] >= 0)
						s->setDoor(DOWN);


					if( (x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE  == zone + 1) && !linked[zone]) {
						s->setDoor(LEFT);
						s->setLock(LEFT);
						linked[zone] = true;
						block[layout[x-1][y]] = RIGHT;
					}
					else
						if((y - 1 >= 0) && ( layout[x][y-1]/ZONE_SIZE == zone + 1) && !linked[zone]){
							s->setDoor(UP);
							s->setLock(UP);
							linked[zone] = true;
							block[layout[x][y-1]] = DOWN;
						}
						else 
							if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == zone + 1) && !linked[zone]){
								s->setDoor(DOWN);
								s->setLock(DOWN);
								linked[zone] = true;
								block[layout[x][y+1]] = UP;
							}
							else
								if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == zone + 1) && !linked[zone]){
									s->setDoor(RIGHT);
									s->setLock(RIGHT);
									linked[zone] = true;
									block[layout[x+1][y]] = LEFT;
								}
					// Generamos la pantalla
					s->generate();
					// Añadimos la pantalla al vector
					screenList->push_back(s);
					}
					else{
						// Instanciamos pantallas
						s = new DunScreen(x, y, -1, 3, -1, -1, -1, "Zona","Tema", db);
						// Le ponemos puertas comprobamos si es de su misma zona el id en el layout o si le toca conexión con otra zona 
						if( (y - 1 >= 0) && (layout[x][y-1]/ZONE_SIZE == zone) && layout[x][y-1] >= 0)
							s->setDoor(UP);
						
						if((x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE == zone) && layout[x-1][y] >= 0)
							s->setDoor(LEFT);			
					
						if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == zone) && layout[x+1][y] >= 0)
							s->setDoor(RIGHT);

						if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == zone) && layout[x][y+1] >= 0)
							s->setDoor(DOWN);


						if( (x - 1 >= 0) && (layout[x-1][y]/ZONE_SIZE  == zone + 1) && !linked[zone]) {
							s->setDoor(LEFT);
							s->setLock(LEFT);
							linked[zone] = true;
							block[layout[x-1][y]] = RIGHT;
						}
						else
							if((y - 1 >= 0) && ( layout[x][y-1]/ZONE_SIZE == zone + 1) && !linked[zone]){
								s->setDoor(UP);
								s->setLock(UP);
								linked[zone] = true;
								block[layout[x][y-1]] = DOWN;
							}
							else 
								if( (y + 1 < height) && (layout[x][y+1]/ZONE_SIZE == zone + 1) && !linked[zone]){
									s->setDoor(DOWN);
									s->setLock(DOWN);
									linked[zone] = true;
									block[layout[x][y+1]] = UP;
								}
								else
									if( (x + 1 < width) && (layout[x+1][y]/ZONE_SIZE == zone + 1) && !linked[zone]){
										s->setDoor(RIGHT);
										s->setLock(RIGHT);
										linked[zone] = true;
										block[layout[x+1][y]] = LEFT;
									}
					
						// Generamos la pantalla
						s->generate();
						// Añadimos la pantalla al vector
						screenList->push_back(s);
					}
				}
			}
		}

	for (int x = 0; x < width; x++) 
		for(int y = 0; y < height; y++)
			// Comprobamos si es pantalla inicial de zona y si lo es se crea la otra parte del bloqueo
			if(layout[x][y] != -1)
			if((block[layout[x][y]]) != -1){
						s = findScreen(x,y);
						if(s != NULL){
							s->setDoor(block[layout[x][y]]);
							s->setLock(block[layout[x][y]]);
						}
			}
	delete visited;
	delete linked;
	delete block;
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

void DungeonJ::genLayout() {
	// generamos el layout instanciando un objeto igraphcontrol que nos devuelve una matriz int** con el layout 
	// comprobamos si cumple el mínimo de un 70% de habitaciones exigido
	// sino generamos uno nuevo // valores de ZONE_SIZE = 5 y nZones 20 máximos o menos nZone y mas ZONE_SIZE en ese caso se pueden conseguir más salas
	size = 0; 
	IGraphControl* igraphControl = NULL;
	layout = NULL;
	while( size < DUNGEON_SIZE(nZones)*0.7){
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

	/*for(int i = 0; i<15; i++)
		delete layout[i];	
	delete layout;
	*/
	layout = layoutAux;
	layoutAux = NULL;
}

void DungeonJ::blockPath() {}

void DungeonJ::placeItems(){
	// Asigna a cada zona un elemento siguiendo el orden:
	// inicio
	// puzzles
	// miniboss o collectable
	// puzzles
	// miniboss o collectable
	// puzzles
	// boss
	int i;
	// Entrada = 0, puzzle = 1, miniboss = 2 collectable = 3 final = 4 
	int idZone = 0;
	dist[idZone] = ENTRANCE;
	idZone++;
	if(n_minibosses != 0){
		for(i = 0; i <n_puzzles/3; i++){
				dist[idZone] = PUZZLE; 
				idZone++;
		}

		if(i = rand()%2 == 0)
				dist[idZone] = MINIBOSS;
		else
				dist[idZone] = COLLECTABLE;

		for(i = 0; i <n_puzzles/3; i++){
				dist[idZone] = MINIBOSS; 
				idZone++;
		}	
	}else{
		for(i = 0; i <n_puzzles/2; i++){
				dist[idZone] = PUZZLE;
				idZone++;
		}
		if(i = rand()%2 == 0)
				dist[idZone] = MINIBOSS;
		else
				dist[idZone] = COLLECTABLE;

		for(i = 0; i <n_puzzles/2; i++){
				dist[idZone] = PUZZLE; 
				idZone++;
		}	
		dist[idZone] = BOSS;
	}
}













