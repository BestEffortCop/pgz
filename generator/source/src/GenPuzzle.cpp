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

GenPuzzle::GenPuzzle(short item, DBManager* db) {
	if(genPuzzle == NULL){
		genPuzzle = this;
		this->item = item;
		this->db = db;
	}
};

GenPuzzle::~GenPuzzle() {};

void GenPuzzle::setItem(short item) {this->item = item;}

void GenPuzzle::generate(DunScreen* ds, short id, short type) {
	// Entidad que se obtiene tras resolver el puzzle.
	
	entities = new vector<Entity*>();
	this->item = item;
	
	puzzle_t puzzle;

	puzzle.id = id;
	
	switch(type){
		case(pARENA): // Arena de enemigos básica.
			enemyArena(ds,id,false,false);
			break;
		case(pARENALINKED): // Arena de enemigos enlazada a otro puzzle al azar previo (raro pero bleh~ pones la piedra en el botón y... enemigos!!)
			enemyArena(ds,id,true,false);
			break;
		case(2): // Bloque movible + botón
			button(ds,id,true,false);
			break;
	}
	puzzle.entities = entities;
	
	ds->setPuzzle(puzzle);
}

void GenPuzzle::enemyArena(DunScreen* ds, int id, bool linked, bool persistent) {
	short e = -1;
	short n = rand() % 5 + 5;
	// Pide un enemigo válido a la interfaz con la base de datos
	e = db->getEnemy(zone);
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
	short order = ds->getEntitiesSize();
	int x = -1;
	int y = -1;
	/* type - x y<--sin sentido en este contexto - idCollectable - linkedto - espacio_variable */	
	if(linked && item != -1){	// hay enlace a otro conjunto de entidades de puzzle y recompensa
			if(persistent){ // recompensa en cada enlace
				ds->addEntity(new EntityArena(ARENA,x,y,order,order+3,...));
				ds->addEntity(new EntityDoorCloser(DOOR_CLOSER,x,y,order+1,order,...));
				ds->addEntity(new EntityItem(ITEM,x,y,order+2,order,...));
				n = rand() % NPUZZLES;
				this->generate(ds,id+1,n);
			}
			else{
				ds->addEntity(new EntityArena(ARENA,x,y,order,order+2,...));
				ds->addEntity(new EntityDoorCloser(DOOR_CLOSER,x,y,order+1,order,...));
				n = rand() % NPUZZLES;
				this->generate(ds,id+1,n);
			}
	}
	else{
		if(item != -1){ // hay recompensa pero no enlace
			ds->addEntity(new EntityArena(ARENA,x,y,order,-1,...));
			ds->addEntity(new EntityDoorCloser(DOOR_CLOSER,x,y,order+1,order,...));
			ds->addEntity(new EntityDoorOpener(DOOR_OPENER,x,y,order+2,order,...));
			ds->addEntity(new EntityItem(ITEM,x,y,order+3,order,...));
		}
		else
			if(linked){ // no hay recompensa pero si enlace a otro conjunto de entidades de puzzle
				ds->addEntity(new EntityArena(ARENA,x,y,order,order+2,...));
				ds->addEntity(new EntityDoorCloser(DOOR_CLOSER,x,y,order+1,order,...));
				n = rand() % NPUZZLES;
				this->generate(ds,id+1,n);
			}
	}
}
/*	
void GenPuzzle::button(DunScreen* ds, int id, bool linked, bool persistent){
		/* type - x - y - idCollectable - linkedto - espacio_variable */	
	/*if(linked && item != -1){	// hay enlace a otro conjunto de entidades de puzzle y recompensa
			if(persistent){ // recompensa en cada enlace
				ds->addEntity(new EntityFloorButton(BOTON,x,y,id,id+4,...));
				ds->addEntity(new EntityBLOQUEEMPUJABLE(BLOQUEEMPUJABLE,x,y,id,id,...));
				ds->addEntity(new EntityItem(ITEM,x,y,id,id,...));
				n = rand() % NPUZZLES;
				this->generate(ds,id,n);
			}
			else{
				ds->addEntity(new EntityFloorButton(BOTON,x,y,id,id+4,...));
				ds->addEntity(new EntityBLOQUEEMPUJABLE(BLOQUEEMPUJABLE,x,y,id,id,...));
				short n = rand() % NPUZZLES;
				this->generate(ds,id,n);
			}
	}
	else{
		if(item != -1){ // hay recompensa pero no enlace
				ds->addEntity(new EntityFloorButton(BOTON,x,y,id,-1,...));
				ds->addEntity(new EntityCosoEmpujable(COSOEMPUJABLE,x,y,id+1,id,...));
				ds->addEntity(new DoorOpener(DOOR_OPENER,x,y,id+2,id,...));
				ds->addEntity(new EntityItem(ITEM,x,y,id+3,id,...));
		}
		else
			if(linkedto){ // no hay recompensa pero si enlace a otro conjunto de entidades de puzzle
				ds->addEntity(new EntityFloorButton(BOTON,x,y,id,id+3,...));
				ds->addEntity(new EntityBLOQUEEMPUJABLE(BLOQUEEMPUJABLE,x,y,id+1,id,...));
				short n = rand() % NPUZZLES;
				this->generate(ds,id,n);
			}
	}
}
*/
