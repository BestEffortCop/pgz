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

short GenPuzzle::generate(DunScreen* ds, short id, short type) {
	// EntidadItem que se obtiene tras resolver el puzzle.
	this->item = item;
	
	puzzle_t puzzle;
	
	// Asigno el identificador
	puzzle.id = id;
	
	switch (type) {
		case pARENA: // Arena de enemigos básica.
			enemyArena(ds,false,false,id);
			puzzle.type = ARENA;
			break;
		case pLINKEDARENA: // Arena de enemigos enlazada no se pero la precedencia temporal entre puzzles debe estar implicita en su posición en el vector de puzzles.
			enemyArena(ds,true,false,id);
			puzzle.type = ARENA;
			break;
		case pBUTTON:
			button(ds, false, true, id);
			puzzle.type = FLOORBUTTON;
			break;
	}
	// Añado el puzzle a la lista
	ds->addPuzzle(puzzle);

	return id+1;
}

void GenPuzzle::enemyArena(DunScreen* ds, bool linked, bool persistent, short& id) {
	short n;
	short order = ds->getEntities()->size();

	// Coloco los enemigos linkedto order = idarena
	placeEnemies(ds,order);

	int x = -1;
	int y = -1;
	/* type - x y<--sin sentido en este contexto - idCollectable - linkedto - espacio_variable */	
	if(linked && item != -1){	// hay enlace a otro conjunto de entidades de puzzle y recompensa
			if(persistent){ // recompensa en cada enlace
				ds->addEntity(new EntityPuzzleElement(ARENA,x,y,order,id));
				ds->addEntity(new EntityPuzzleElement(DOOR_CLOSER,x,y,order+1,id));
				ds->addEntity(placeItem(ds,order+2,order));
				n = rand() % NPUZZLES;
				id++;
				this->generate(ds,id,n);
			}
			else{ // hay enlace y no item luego nuevo puzzle.
				ds->addEntity(new EntityPuzzleElement(ARENA,x,y,order,id));
				ds->addEntity(new EntityPuzzleElement(DOOR_CLOSER,x,y,order+1,id));
				n = rand() % NPUZZLES;
				id++;
				this->generate(ds,id,n);
			}
	}
	else{
		if(item != -1){ // hay recompensa pero no enlace
			ds->addEntity(new EntityPuzzleElement(ARENA,x,y,order,id));
			ds->addEntity(new EntityPuzzleElement(DOOR_CLOSER,x,y,order+1,id));
			ds->addEntity(new EntityPuzzleElement(DOOR_OPENER,x,y,order+2,id));
			ds->addEntity(placeItem(ds,order+3,order));
		}
		else
			if(linked){ // no hay recompensa pero si enlace 
				ds->addEntity(new EntityPuzzleElement(ARENA,x,y,order,id));
				ds->addEntity(new EntityPuzzleElement(DOOR_CLOSER,x,y,order+1,id));
				n = rand() % NPUZZLES;
				id++;
				this->generate(ds,id+1,n);
			}
			else{ // Caso ni item ni enlace
				ds->addEntity(new EntityPuzzleElement(ARENA,x,y,order,id));
				ds->addEntity(new EntityPuzzleElement(DOOR_CLOSER,x,y,order+1,id));
				ds->addEntity(new EntityPuzzleElement(DOOR_OPENER,x,y,order+2,id));
			}
	}
}

void GenPuzzle::button(DunScreen* ds, bool linked, bool persistent, short& id) {
	short first_entity = ds->getEntities()->size();
	if (linked) {
	}
	else {
		if (persistent) {
			// Colocamos un botón
			int x = 0, y = 0;
			get_valid_position(ds, &x, &y);
			ds->addEntity(new EntityPuzzleElement(FLOORBUTTON, x, y,-1, id));		// pos = first_entity
			// Colocamos un bloque empujable (que no esté pegado a la pared)
			do { get_valid_position(ds, &x, &y); }
			while (x == ds->getWall_size() || y == ds->getWall_size() ||
				   x == SCREEN_WIDTH - ds->getWall_size() - 1 ||
				   y == SCREEN_HEIGHT - ds->getWall_size() - 1);
			ds->addEntity(new EntityPuzzleElement(TILEDPUSHABLE, x, y, -1, id));	// pos = first_entity+1
			// Colocamos un instanciador para la recompensa
			ds->addEntity(new EntityPuzzleElement(INSTANTIATOR, -1, -1, -1, id));	// pos = first_entity+2
			// Colocamos la recompensa
			ds->addEntity(placeItem(ds, -1, first_entity + 2));
		}
		else {
		}
	}
}

EntityItem* GenPuzzle::placeItem(DunScreen* ds, short id, short linkedTo){
	EntityItem* e = new EntityItem(ITEM, -1, -1, -1, -1, -1, -1, 1);

	int x = 0, y = 0;
	get_valid_position(ds, &x, &y);
	
	e->x = x; e->y = y;
	
	switch(item){
		case(KEY):{
				e->idCollectable = -1;
				e->effect = KEY;
				e->gfxId = db->getKeyGfxId();
				e->linkedTo = linkedTo;
				}
				break;
	};

	return e;
}

void GenPuzzle::placeEnemies(DunScreen* ds, short linkedTo){
	short e = -1;
	short n = rand() % 5 + 5;
	// Pide un enemigo válido a la interfaz con la base de datos
	e = db->getEnemy(ds->getZone());
    if(e != -1)
		for (int i = 0; i < n; i++) {
			// Escoge una localización válida en la habitación
			int x = 0, y = 0;
			get_valid_position(ds, &x, &y);
			// Al salir del bucle, x e y representan una posición válida para el enemigo e
			enemy en;
			// LinkedTo arena
			en.id = e;
			en.linkedTo = linkedTo;
			en.posX = x;
			en.posY = y;

			ds->addEnemy(en);
		}
}

void GenPuzzle::get_valid_position(DunScreen* ds, int* x, int* y) {
	int s;
	do {
		*x = rand() % (SCREEN_WIDTH - ds->getWall_size()*2) + ds->getWall_size();
		*y = rand() % (SCREEN_HEIGHT - ds->getWall_size()*2) + ds->getWall_size();
		s = ds->getSolid(*x, *y);
	}
	while (s != 0 || ds->blocksDoor(*x, *y));
}