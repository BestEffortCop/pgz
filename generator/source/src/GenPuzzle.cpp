#include "GenPuzzle.h"

const void* GenPuzzle::genPuzzle = NULL;

void* GenPuzzle::operator new (size_t size){
	if(genPuzzle == NULL){
		void* p = malloc(size);
		return p;
	}
	else
		return (void*)genPuzzle;
}

GenPuzzle::GenPuzzle(short item, string zone, DBManager* db) {
	if(genPuzzle == NULL){
		genPuzzle = this;
		this->item = item;
		this->zone = zone;
		this->db = db;
	}
};

GenPuzzle::~GenPuzzle() {};

void GenPuzzle::generate(DunScreen* ds, short id, short type) {

	switch(type){
		case(0):
			enemyArena(ds);
			break;
	}
}

void GenPuzzle::enemyArena(DunScreen* ds, int id) {
	short e = -1;
	short n = rand() % 5 + 5;
	// Pide un enemigo válido a la interfaz con la base de datos
	e = db->getEnemy(zone, theme);
    if(e != -1)
		for (int i = 0; i < n; i++) {
			// Escoge una localización válida en la habitación
			short x, y, s;
			do {
				x = (rand() % (SCREEN_WIDTH - ds->getWall_size()*2)) + ds->getWall_size();
				y = (rand() % (SCREEN_HEIGHT - ds->getWall_size()*2)) + ds->getWall_size();
				s = ds->getSolid(x,y);
			} while (s != 0 || ds->place_free(x, y));
			// Al salir del bucle, x e y representan una posición válida para el enemigo e
			enemy en;
			en.id = e;
			en.posX = x;
			en.posY = y;

			ds->addEnemy(en);
		}
	/* type x y<--sin sentido en este contexto idCollectable linkedto variable */
	ds->addEntity(new doorCloser(DOOR_CLOSER,x,y,id+1,id,-1));

	ds->addEntity(new EntityArena(ARENA,x,y,id,-1));

	if(item != -1)
		entities->push_back(new EntityItem(ITEM,x,y,id+2,id,-1,-1,-1));

	ds->addEntity(new doorOpener(DOOR_OPENER,-1,id,-1,));
}

