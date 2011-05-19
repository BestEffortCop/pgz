#include "FinalDungeon.h"

FinalDungeon::FinalDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db) : Dungeon(zone,theme,gameDiff,dungNumber,ratio,tool,keyObj, dungeonPos, db) {
	// Obtener el tileSet apropiado y su path
	short idTileSet = db->getFinalDungeon(zone);
	decorator->init(zone, theme, idTileSet);

	// Pantalla inicial
	iniX = 0;
	iniY = 1;

	// Fijamos ancho y alto
	width = 1;
	height = 2;

	// Persistencia
	n_puzzles = 0;
	n_collectables = 0;
	n_puertas = 0;
	n_minibosses = 0;
}


FinalDungeon::~FinalDungeon() {}

void FinalDungeon::generate() {
	generateLockScreen();

	generateFinalScreen();

	for (vector<DunScreen*>::iterator it= screenList->begin(); it < screenList->end(); it++){
		decorator->decorate((*it));
	}

	index_collectables();
}

void FinalDungeon::generateLockScreen() {
	DunScreen* ds;
	
	// Instanciar la screen
	ds = new DunScreen(0, 1, -1, 0, -1, -1, -1, zone, theme, db, numDungeon, genPuzzle);

	// Pantalla inicial
	ds->setInitialRoom(true);

	// Colocamos puertas
	ds->setDoor(UP);

	// Teleporter hacia el mundo
	ds->addEntity(new EntityTeleporter(TELEPORTATOR, 6, 10, -1, -1, 0, getWScreenX(), getWScreenY(), getWTileX(), getWTileY()));

	// Bloqueo de objeto clave
	ds->addEntity(new Entity(FINAL_DOOR, SCREEN_WIDTH / 2 - 1, 0, -1, -1));

	// Coloca sólidos
	allocateSolids(ds,LOCK_SCREEN);

	screenList->push_back(ds);
}

void FinalDungeon::generateFinalScreen() {
	DunScreen* ds;

	// instanciamos la pantalla
	ds = new DunScreen(0, 0, -1, 0, -1, -1, -1, zone, theme, db, numDungeon, genPuzzle);

	// Añade el elemento final idCollectable = 1
	ds->addEntity(new EntityFinalElement(FINAL_ELEMENT,6,3,-1,-1,db->getFinalElem()));

	// Colocamos puertas
	ds->setDoor(DOWN);

	// Coloca sólidos
	allocateSolids(ds,FINAL_SCREEN);

	screenList->push_back(ds);
}

void FinalDungeon::allocateSolids(DunScreen* ds, int type) {

	placeWalls(ds);

	if(type == LOCK_SCREEN){
		for(int x = 0; x < 3; x++)
			for(int y = 0; y < 3; y++){
				ds->setSolid(x+3,y+4,2);
				ds->setSolid(x+8,y+4,2);
			}
		ds->setSolid(6,10,0);
		ds->setSolid(7,10,0);
	}

	if(type == FINAL_SCREEN){	
		// Columnas/estatuas
		for(int i = 0; i < 4; i++){
				ds->setSolid(5 - ((i%2)*2), 6+i,2);
				ds->setSolid((SCREEN_WIDTH -1) - (5-((i%2)*2)),6+i,2);
		}
		// Altar
		for(int x = 0; x < 2; x++)
			for(int y = 0; y < 4; y++){
				ds->setSolid(x+3,y+2,2);
				ds->setSolid((SCREEN_WIDTH -1) - (x + 3),y+2,2);
			}
		ds->setSolid(5,4,2);
		ds->setSolid(5,5,2);
		ds->setSolid((SCREEN_WIDTH-1) - 5,4,2);
		ds->setSolid((SCREEN_WIDTH-1) - 5,5,2);
	}

	/*for(int j = 0; j < SCREEN_HEIGHT; j++){
		for(int i = 0; i < SCREEN_WIDTH; i++)
			printf("%d ",ds->getSolid(i,j));
	printf("\n");
	}

	getchar();*/

}

void FinalDungeon::placeWalls(DunScreen* ds) {
	// Arriba
	for (int j = 0; j < SCREEN_WIDTH; j++)
		for (int k = 0; k < ds->getWall_size(); k++)
			if (!(j == SCREEN_WIDTH / 2 || j == (SCREEN_WIDTH - 1) / 2) || !ds->getDoor(UP)) {
				ds->setSolid(j,k,1);
				ds->setTile(j,k,1);
			}

	// Abajo
	for (int j = 0; j < SCREEN_WIDTH; j++)
		for (int k = SCREEN_HEIGHT - ds->getWall_size(); k < SCREEN_HEIGHT; k++)
			if (!(j == SCREEN_WIDTH / 2 || j == (SCREEN_WIDTH - 1) / 2) || !ds->getDoor(DOWN)) {
				ds->setSolid(j,k,1);
				ds->setTile(j,k,1);
			}

	// Izquierda
	for (int j = 0; j < ds->getWall_size(); j++)
		for (int k = 0; k < SCREEN_HEIGHT; k++)
			if (!(k == SCREEN_HEIGHT / 2 || k == (SCREEN_HEIGHT - 1) / 2) || !ds->getDoor(LEFT)) {
				ds->setSolid(j,k,1);
				ds->setTile(j,k,1);
			}
			
	// Derecha
	for (int j = SCREEN_WIDTH - ds->getWall_size(); j < SCREEN_WIDTH; j++)
		for (int k = 0; k < SCREEN_HEIGHT; k++)
			if (!(k == SCREEN_HEIGHT / 2 || k == (SCREEN_HEIGHT - 1) / 2) || !ds->getDoor(RIGHT)) {
				ds->setSolid(j,k,1);
				ds->setTile(j,k,1);
			}
}