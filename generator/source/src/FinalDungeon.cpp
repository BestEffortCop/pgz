#include "FinalDungeon.h"

FinalDungeon::FinalDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db) : Dungeon(zone,theme,gameDiff,dungNumber,ratio,tool,keyObj, dungeonPos, db) {
	// Obtener el tileSet apropiado y su path
	short idTileSet = db->getFinalDungeon(zone);
	decorator->init(zone, theme, idTileSet);

	iniX = 0;
	iniY = 0;

	n_puzzles = 0;
	n_collectables = 0;
	n_puertas = 0;
	n_minibosses = 0;
}


FinalDungeon::~FinalDungeon() {}

void FinalDungeon::generate() {
	generateLockScreen();

	generateFinalScreen();

	index_collectables();
}

void FinalDungeon::generateLockScreen() {
	DunScreen* ds;
	
	// Instanciar la screen
	ds = new DunScreen(0, 1, -1, 0, -1, -1, -1, zone, theme, db, numDungeon, genPuzzle);

	// Colocar la puerta aunque realmente no hace nada pero bleh
	ds->setDoor(UP);

	// Teleporter hacia el mundo
	ds->placeTeleporter(0, getWScreenX(), getWScreenY(), getWTileX(), getWTileY());

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

	// Forma de comprobar posición libre de  siempre
	int x,y,s;
	do {
		x = rand() % (SCREEN_WIDTH - ds->getWall_size()*2) + ds->getWall_size();
		y = rand() % (SCREEN_HEIGHT - ds->getWall_size()*2) + ds->getWall_size();
		s = ds->getSolid(x, y);
	}
	while (s != 0 || ds->blocksDoor(x, y));

	// Añade el elemento final idCollectable = 1
	ds->addEntity(new EntityFinalElement(FINAL_ELEMENT,-1,-1, 1,-1,db->getFinalElem()));

	// Colocar la puerta aunque realmente no hace nada pero bleh
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
				ds->setSolid(x+3,y+6,1);
				ds->setSolid(x+10,y+6,1);
			}
	}

	if(type == FINAL_SCREEN){	
		// Columnas/estatuas
		ds->setSolid(5,8,1);
		ds->setSolid(10,8,1);
		ds->setSolid(5,10,1);
		ds->setSolid(10,10,1);

		// Altar
		for(int x = 0; x < 2; x++)
			for(int y = 0; y < 5; y++){
				ds->setSolid(x+4,y+2,1);
				ds->setSolid(SCREEN_WIDTH - (x + 4),y+2,1);
			}
		ds->setSolid(6,5,1);
		ds->setSolid(6,6,1);
		ds->setSolid(SCREEN_WIDTH - 6,5,1);
		ds->setSolid(SCREEN_WIDTH - 6,6,1);
	}
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