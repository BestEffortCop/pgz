#include "DunScreen.h"

DunScreen::DunScreen(short posX, short posY, short puzzle, short n_enemies, short boss, short miniboss, short tool, string zone, string theme, DBManager* db, short mapNumber, GenPuzzle* genPuzzle) 
	: Screen(mapNumber, posX, posY, n_enemies, zone, db) {
	this->boss = boss;
	this->miniboss = miniboss;
	this->tool = tool;
	this->puzzle = puzzle;
	keyObj = -1;

	wall_size = 2;
	// Posición inicial del personaje en la pantalla
	posIniX = wall_size;
	posIniY = wall_size;

	// Id de la música de fondo
	idMusic = 0;

	key = false;
	boss_key = false;
	empty_room = false;
	initialRoom = false;

	// Inicializa puertas, bloqueos, tiles y sólidos
	for (int i = 0; i < 4; i++) {
		door[i] = false;
		lock[i] = false;
		boss_lock[i] = false;
		lockId[i] = -1;
	}

	this->genPuzzle = genPuzzle;
}

DunScreen::~DunScreen() {
	// Todo es estático de momento
}

void DunScreen::generate() {
	n_puzzles = puzzles->size();
	n_tilesFG = 0;		// Mientras no tengamos tiles de foreground
	n_entities = 0;		// Se irá incrementando según se vayan añadiendo

	decorate();			// Decora la mazmorra con sólidos
	placeEntities();	// Coloca las entidades de la pantalla
	placePuzzle();		// Coloca las entidades asociadas al puzzle de la pantalla (de haberlo)
	placeEnemies();		// Coloca los enemigos de la pantalla
}

void DunScreen::print_screen() {
	for (int j = 0; j < SCREEN_HEIGHT; j++) {
		for (int i = 0; i < SCREEN_WIDTH; i++) {
			if (solids[i][j] == 0) printf(".");
			if (solids[i][j] == 1) printf("#");
		}
		printf("\n");
	}
}

void DunScreen::setDoor(short i) {
	if (i >= 0 && i < 4)
		door[i] = true;
}

void DunScreen::setLock(short i) {
	if (i >= 0 && i < 4)
		lock[i] = true;
}

void DunScreen::setLock(short d, short id) {
	if (d >= 0 && d < 4) {
		lock[d] = true;
		lockId[d] = id;
	}
}

void DunScreen::unSetDoor(short i) {
	if (i >= 0 && i < 4)
		door[i] = false;
}

void DunScreen::unSetLock(short i) {
	if (i >= 0 && i < 4){
		lock[i] = false;
		lockId[i] = -1;
	}
}

void DunScreen::setBoss_lock(short d) {
	if (d >= 0 && d < 4)
		boss_lock[d] = true;
}

void DunScreen::setBoss_lock(short d, short id) {
	if (d >= 0 && d < 4) {
		boss_lock[d] = true;
		lockId[d] = id;
	}
}

bool DunScreen::has_lock() {
	return (lock[0] || lock[1] || lock[2] || lock[3]);
}

bool DunScreen::has_one_door() {
	return ((door[0] && !door[1] && !door[2] && !door[3]) ||
		(!door[0] && door[1] && !door[2] && !door[3]) ||
		(!door[0] && !door[1] && door[2] && !door[3]) ||
		(!door[0] && !door[1] && !door[2] && door[3]));
}

void DunScreen::placePuzzle() {
	for (vector<puzzle_t>::iterator it = puzzles->begin(); it < puzzles->end(); it++)
		genPuzzle->generate(this, it->id, it->type);
}

void DunScreen::placeWalls() {
	// De momento los tiles que coloca son 0 (suelo) o 1 (sólido)
	// Arriba
	for (int j = 0; j < SCREEN_WIDTH; j++)
		for (int k = 0; k < wall_size; k++)
			if (!(j == SCREEN_WIDTH / 2 || j == (SCREEN_WIDTH - 1) / 2) || !door[UP]) {
				solids[j][k] = 1;
				tiles[j][k] = 1;
			}

	// Abajo
	for (int j = 0; j < SCREEN_WIDTH; j++)
		for (int k = SCREEN_HEIGHT - wall_size; k < SCREEN_HEIGHT; k++)
			if (!(j == SCREEN_WIDTH / 2 || j == (SCREEN_WIDTH - 1) / 2) || !door[DOWN]) {
				solids[j][k] = 1;
				tiles[j][k] = 1;
			}

	// Izquierda
	for (int j = 0; j < wall_size; j++)
		for (int k = 0; k < SCREEN_HEIGHT; k++)
			if (!(k == SCREEN_HEIGHT / 2 || k == (SCREEN_HEIGHT - 1) / 2) || !door[LEFT]) {
				solids[j][k] = 1;
				tiles[j][k] = 1;
			}
			
	// Derecha
	for (int j = SCREEN_WIDTH - wall_size; j < SCREEN_WIDTH; j++)
		for (int k = 0; k < SCREEN_HEIGHT; k++)
			if (!(k == SCREEN_HEIGHT / 2 || k == (SCREEN_HEIGHT - 1) / 2) || !door[RIGHT]) {
				solids[j][k] = 1;
				tiles[j][k] = 1;
			}

}

void DunScreen::decorate() {
	// Construye las paredes y puertas de la mazmorra
	placeWalls();
	if (initialRoom) empty_room = true;
	// Si la habitación es vacía no hacemos nada más
	if (!empty_room) {
		// Primero elige un tipo de simetría
		sym_type = rand() % 3 + 1;	// No queremos sin simetría, que queda muy feo
		// Coloca elementos en los cuadrantes apropiados
		genQuadrants();
		genSymmetry();
	}

	// Hacemos una segunda pasada para cambiar sólidos aislados por cosas para decorator
	modify_isolated_solids();
	// Hacemos una tercera pasada para arreglar los sólidos en forma de cruz
	modify_isolated_solids();
}

void DunScreen::modify_isolated_solids() {
	for (int i = wall_size; i < SCREEN_WIDTH - wall_size; i++)
		for (int j = wall_size; j < SCREEN_HEIGHT - wall_size; j++) {
			if (solids[i][j] == 1 && 
				((solids[i-1][j] != 1 && solids[i+1][j] != 1) ||
				(solids[i][j-1] != 1 && solids[i][j+1] != 1)))
				solids[i][j] = 2;
		}
}

void DunScreen::genQuadrants() {
    switch (sym_type) {
        case NO_SYM:
            genQuadrant(0);
            genQuadrant(1);
            genQuadrant(2);
            genQuadrant(3);
            break;
        case HOR_SYM:
            genQuadrant(0);
            genQuadrant(1);
            break;
        case VER_SYM:
            genQuadrant(0);
            genQuadrant(2);
            break;
        case TOT_SYM:
            genQuadrant(0);
            break;
    }
}

void DunScreen::genQuadrant(short q) {
    // Cuadrantes:
    // 0 - superior izquierda
    // 1 - superior derecha
    // 2 - inferior izquierda
    // 3 - inferior derecha
    short qW = (SCREEN_WIDTH - wall_size*2) / 2;    // Ancho del cuadrante
    short qH = (SCREEN_HEIGHT - wall_size*2) / 2;   // Alto del cuadrante
    short iniX = wall_size + qW * (q % 2);          // Posición en la que comienza el cuadrante q (X)
    short iniY = wall_size + qH * (q / 2);          // Posición en la que comienza el cuadrante q (Y)
    short total_tiles = qW * qH;                    // Area en tiles disponible en el cuadrante
    short n_solids = rand() % (total_tiles / 2);    // Cantidad de sólidos a colocar (de momento la cuarta parte de la superficie, máximo)
	short qWX = (qW-1) * (q % 2);					// Abscisa de la pared horizontal del cuadrante
	short qWY = (qH-1) * (q / 2);					// Ordenada de la pared vertical del cuadrante

    // Coloca los sólidos en el cuadrante
    for (int i = 0; i < n_solids; i++) {
        // Escoge una localización válida en el cuadrante
        int x, y, s;
        do {
			if (rand() % 2 == 0) x = rand() % qW;
			else x = qWX;
			if (rand() % 2 == 0) y = rand() % qH;
            else y = qWY;
            s = solids[iniX+x][iniY+y];
        } while (s != 0 || iniX+x == SCREEN_WIDTH / 2 || iniX+x == SCREEN_WIDTH / 2 - 1 ||
			     iniY+y == SCREEN_HEIGHT / 2 || iniY+y == SCREEN_HEIGHT / 2 - 1);

        // Coloca el sólido en dicha habitación
        solids[iniX+x][iniY+y] = 1;
		tiles[iniX+x][iniY+y] = 1;
    }
}

void DunScreen::genSymmetry() {
    switch (sym_type) {
        case HOR_SYM:
            genHorSymmetry();
            break;
        case VER_SYM:
            genVerSymmetry();
            break;
        case TOT_SYM:
            genHorSymmetry();
            genVerSymmetry();
            break;
    }
}

void DunScreen::genHorSymmetry() {
    int k = SCREEN_HEIGHT - wall_size - 1; // Índice simétrico a j

    for (int i = wall_size; i < (SCREEN_WIDTH - wall_size); i++) {
        for (int j = wall_size; j < (SCREEN_HEIGHT / 2); j++) {
            solids[i][k] = solids[i][j];
            tiles[i][k] = tiles[i][j];
            k--;    // k retrocede una posición a la vez que j avanza una
        }
        // Restaura el valor original de k en cada iteración
        k = SCREEN_HEIGHT - wall_size - 1;
    }
}

void DunScreen::genVerSymmetry() {
    int k = SCREEN_WIDTH - wall_size - 1; // Índice simétrico a i

    for (int i = wall_size; i < (SCREEN_WIDTH / 2); i++) {
        for (int j = wall_size; j < (SCREEN_HEIGHT - wall_size); j++) {
            solids[k][j] = solids[i][j];
            tiles[k][j] = tiles[i][j];
        }
        // k retrocede una posición a la vez que i avanza una
        k--;
    }
}

bool DunScreen::blocksDoor(short x, short y) {
    // ¿Bloquea la puerta de arriba?
    if ((x == SCREEN_WIDTH / 2 - 1 || x == SCREEN_WIDTH / 2) && y == wall_size && door[UP]) return true;
    // ¿Bloquea la puerta de abajo?
    if ((x == SCREEN_WIDTH / 2 - 1 || x == SCREEN_WIDTH / 2) && y == SCREEN_HEIGHT - wall_size - 1 && door[DOWN]) return true;
    // ¿Bloquea la puerta de la izquierda?
    if (x == wall_size && (y == SCREEN_HEIGHT / 2 - 1 || y == SCREEN_HEIGHT / 2) && door[LEFT]) return true;
    // ¿Bloquea la puerta de la derecha?
    if (x == SCREEN_WIDTH - wall_size - 1 && (y == SCREEN_HEIGHT / 2 - 1 || y == SCREEN_HEIGHT / 2) && door[RIGHT]) return true;

    return false;
}

void DunScreen::placeLocks() {
	int x, y, s;
	for (int d = 0; d < 4; d++) {
		switch (d) {
			case UP:
				x = SCREEN_WIDTH / 2 - 1;
				y = 0;
				break;
			case DOWN:
				x = SCREEN_WIDTH / 2 - 1;
				y = SCREEN_HEIGHT - wall_size;
				break;
			case LEFT:
				x = 0;
				y = SCREEN_HEIGHT / 2 - 1;
				break;
			case RIGHT:
				x = SCREEN_WIDTH - wall_size;
				y = SCREEN_HEIGHT / 2 - 1;
				break;
		}
		if (lock[d]) {
			EntityDoor* e = new EntityDoor(DOOR, x, y, lockId[d], -1, idTileSet);
			entities->push_back(e);	// Añadimos la nueva entidad al vector de entidades
			n_entities++;
		}
		if (boss_lock[d]) {
			EntityBossDoor* e = new EntityBossDoor(BOSSDOOR, x, y, lockId[d], -1, idTileSet);
			entities->push_back(e);
			n_entities++;
		}
	}
}

void DunScreen::placeEntrance() {
	// Buscamos el teletransporte de la pantalla inicial
	Entity* teleporter = NULL;
	bool found = false;
	vector<Entity*>::iterator it = entities->begin();
	while (!found && it < entities->end()) {
		found = ((*it)->type == TELEPORTATOR);
		if (found) teleporter = (*it);
		it++;
	}

	int x, y;
	int dir = rand() % 4;	// Elegimos una dirección al azar para la entrada
	// Comprobamos el número de puertas que tiene la pantalla
	if (getDoorNum() == 4) {
		switch(dir) {
			case UP:
				x = SCREEN_WIDTH / 4 - 1;
				y = 0;
				break;
			case DOWN:
				x = SCREEN_WIDTH / 4 - 1;
				y = SCREEN_HEIGHT - wall_size;
				break;
			case LEFT:
				x = 0;
				y = SCREEN_HEIGHT / 4 - 1;
				break;
			case RIGHT:
				x = SCREEN_WIDTH - wall_size;
				y = SCREEN_HEIGHT / 4 - 1;
				break;
		}
	}
	else {
		while (door[dir]) dir = rand() % 4;
		switch (dir) {
			case UP:
				x = SCREEN_WIDTH / 2 - 1;
				y = 0;
				break;
			case DOWN:
				x = SCREEN_WIDTH / 2 - 1;
				y = SCREEN_HEIGHT - wall_size;
				break;
			case LEFT:
				x = 0;
				y = SCREEN_HEIGHT / 2 - 1;
				break;
			case RIGHT:
				x = SCREEN_WIDTH - wall_size;
				y = SCREEN_HEIGHT / 2 - 1;
				break;
		}
	}

	// Reubicamos el teletransporte
	((EntityTeleporter*) teleporter)->x = x;
	((EntityTeleporter*) teleporter)->y = y;

	// Indicamos esta posición como posición inicial en la pantalla
	posIniX = x;
	posIniY = y;

	// Hacemos un agujero en la pared
	for (int i = x; i < x + wall_size; i++)
		for (int j = y; j < y + wall_size; j++) {
			solids[i][j] = 0;
		}
}

void DunScreen::placeKeys() {
	int x, y, s;
	if (key || boss_key) {
		EntityItem* e = new EntityItem(ITEM, -1, -1, -1, -1, -1, -1, 1);
		do {
			x = (rand() % (SCREEN_WIDTH - wall_size*2)) + wall_size;
			y = (rand() % (SCREEN_HEIGHT - wall_size*2)) + wall_size;
            s = solids[x][y];
        } while (s != 0 || blocksDoor(x, y));
		e->x = x; e->y = y;
		if (key) {
			e->effect = KEY;
			e->gfxId = db->getKeyGfxId();
		}
		if (boss_key) {
			e->effect = BOSSKEY;
			e->gfxId = db->getBossKeyGfxId();
		}
		entities->push_back(e);
		n_entities++;
	}
}

void DunScreen::placeEntities() {
	// Colocamos los bloqueos
	placeLocks();
	// Los idCollectables del resto de entidades se asignan a nivel de mazmorra
	// Colocamos la llave o la llave del jefe, si la hay
	placeKeys();

	// Colocamos la herramienta de la mazmorra
	int x, y, s;
	if (tool >= 0) {
		do {
			x = (rand() % (SCREEN_WIDTH - wall_size*2)) + wall_size;
			y = (rand() % (SCREEN_HEIGHT - wall_size*2)) + wall_size;
            s = solids[x][y];
        } while (s != 0 || blocksDoor(x, y));
		EntityTool* e = new EntityTool(TOOL, x, y, -1, -1, tool);
		entities->push_back(e);
		n_entities++;
	}

	// Colocamos el objeto clave y el power up (y un teletransporte a la entrada de la mazmorra?)
	if (keyObj >= 0) {

		EntityItem* e1 = new EntityItem(ITEM, SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT / 2 - 1, -1, -1, db->getGfxId("KeyItem", keyObj), KEYOBJ, 1); 
		entities->push_back(e1);
		n_entities++;

		short idPowUp = db->getPowUp();
		// Comprobamos que en la base de datos había algún power up válido
		if (idPowUp >= 0) {
			EntityItem* e2 = new EntityItem(ITEM, SCREEN_WIDTH / 2 + 1, SCREEN_HEIGHT / 2 - 1, -1, -1, db->getGfxId("PowUp", idPowUp), db->getPowUpEffect(idPowUp), 1);
			entities->push_back(e2);
			n_entities++;
		}
	}

	if (initialRoom) placeEntrance();
}

void DunScreen::placeEnemies() {
	// Coloca los sólidos en el cuadrante
	short e = 0;
    for (int i = 0; i < n_enemies; i++) {
		// Pide un enemigo válido a la interfaz con la base de datos
		e = db->getEnemy(zone);
        // Escoge una localización válida en la habitación
        short x, y, s;
        do {
			x = (rand() % (SCREEN_WIDTH - wall_size*2)) + wall_size;
			y = (rand() % (SCREEN_HEIGHT - wall_size*2)) + wall_size;
            s = solids[x][y];
        } while (s != 0 || blocksDoor(x, y));
		// Al salir del bucle, x e y representan una posición válida para el enemigo e
		enemy en;
		en.id = e;
		en.posX = x;
		en.posY = y;
		en.linkedTo = -1;
		// Guardamos el nuevo enemigo en el vector de enemigos
		enemies->push_back(en);
	}

	// Si no había ningún enemigo válido, deshacemos lo hecho
	if (e == -1) {
		delete enemies;
		enemies = new vector<enemy>();
		n_enemies = 0;
	}
}

void DunScreen::placeTeleporter(short idMap, short screenX, short screenY, short tileX, short tileY) {
	EntityTeleporter* e = new EntityTeleporter(TELEPORTATOR, -1, -1, -1, -1, idMap, screenX, screenY, tileX, tileY);
	// Buscamos una posición válida en la habitación
	short x, y, s;
    do {
		x = (rand() % (SCREEN_WIDTH - wall_size*2)) + wall_size;
		y = (rand() % (SCREEN_HEIGHT - wall_size*2)) + wall_size;
        s = solids[x][y];
	} while (s != 0 || blocksDoor(x, y));
	// Colocamos el teletransporte en dicha habitación
	e->x = x;
	e->y = y;
	// Añadimos el teletransporte al vector de entidades
	entities->push_back(e);
}

void DunScreen::get_valid_position(int& x, int& y) {  }

short DunScreen::getSym_type() { return sym_type; }
short DunScreen::getWall_size() { return wall_size; }
bool DunScreen::getDoor(short d) { return door[d]; }
bool DunScreen::getLock(short l) { return lock[l]; }
short DunScreen::getPuzzle() { return puzzle; }
short DunScreen::getBoss() { return boss; }
short DunScreen::getMiniBoss() { return miniboss; }
short DunScreen::getTool() { return tool; }
short DunScreen::getDoorNum() { return door[0] + door[1] + door[2] + door[3]; }
bool DunScreen::getInitialRoom() { return initialRoom; }

void DunScreen::setWall_size(short wall_size) { this->wall_size = wall_size; }
void DunScreen::setKey() { key = true; }
void DunScreen::setBoss_key() { boss_key = true; }
void DunScreen::setBoss(short boss) { this->boss = boss; }
void DunScreen::setTool(short tool) { this->tool = tool; }
void DunScreen::setEmpty_room(short empty_room) { this->empty_room = empty_room; }
void DunScreen::setKeyObj(short keyObj) { this->keyObj = keyObj; }
void DunScreen::setInitialRoom(bool initialRoom) { this->initialRoom = initialRoom; }
void DunScreen::setPuzzle(short puzzle) { this->puzzle = puzzle; }

int DunScreen::getFreePos(vector<int>* posUsed){return 0;};
