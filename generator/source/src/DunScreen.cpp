#include "DunScreen.h"

DunScreen::DunScreen(short posX, short posY, short puzzle, short n_enemies, short boss, short miniboss, short tool, string zone, string theme, DBManager* db, short mapNumber) 
	: Screen(mapNumber, posX, posY, n_enemies, zone, theme, db) {
	this->boss = boss;
	this->miniboss = miniboss;
	this->tool = tool;
	this->puzzle = puzzle;

	key = false;
	boss_key = false;

	// Inicializa puertas, bloqueos, tiles y sólidos
	for (int i = 0; i < 4; i++) {
		door[i] = false;
		lock[i] = false;
	}
}

DunScreen::~DunScreen() {
}

void DunScreen::generate() {
	// Caution! Para generar la pantalla vacía
	n_entities = 0;
	n_puzzles = 0;
	n_tilesFG = 0;
	wall_size = 1;
	// End caution!

	decorate();			// Decora la mazmorra con sólidos
	placePuzzle();		// Coloca las entidades asociadas al puzzle de la pantalla (de haberlo)
	placeEntities();	// Coloca las entidades de la pantalla
	placeEnemies();		// Coloca los enemigos de la pantalla

	// DEBUG
	// print_screen();
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

void DunScreen::unSetDoor(short i) {
	if (i >= 0 && i < 4)
		door[i] = false;
}

void DunScreen::unSetLock(short i) {
	if (i >= 0 && i < 4)
		lock[i] = false;
}

void DunScreen::placePuzzle() {}

void DunScreen::placeWalls() {
	// De momento coloca paredes donde no hay puertas y donde hay bloqueos, habrá que mejorarlo (ask mma)
	// De momento los tiles que coloca son 0 (suelo) o 1 (sólido)
	for (int i = 0; i < 4; i++) {
		// if (!door[i] || (door[i] && lock[i])) {
		// Mejor solamente donde no haya ni puertas ni cerrojos, para que se pueda pasear libremente por toda la mazmorra
		if (!door[i] && !lock[i]) {
			switch (i) {
				case UP:
					for (int j = 0; j < SCREEN_WIDTH; j++)
						for (int k = 0; k < wall_size; k++) {
							solids[j][k] = 1;
							tiles[j][k] = 1;
						}
					break;
				case DOWN:
					for (int j = 0; j < SCREEN_WIDTH; j++)
						for (int k = SCREEN_HEIGHT - wall_size; k < SCREEN_HEIGHT; k++) {
							solids[j][k] = 1;
							tiles[j][k] = 1;
						}
						break;
				case LEFT:
					for (int j = 0; j < wall_size; j++)
						for (int k = 0; k < SCREEN_HEIGHT; k++) {
							solids[j][k] = 1;
							tiles[j][k] = 1;
						}
						break;
				case RIGHT:
					for (int j = SCREEN_WIDTH - wall_size; j < SCREEN_WIDTH; j++)
						for (int k = 0; k < SCREEN_HEIGHT; k++) {
							solids[j][k] = 1;
							tiles[j][k] = 1;
						}
						break;
			}
		}
	}
}

void DunScreen::decorate() {
	// Construye las paredes y puertas de la mazmorra
	placeWalls();
    // Primero elige un tipo de simetría
    sym_type = rand() % 4;
    // Coloca elementos en los cuadrantes apropiados
    genQuadrants();
    genSymmetry();
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
    short n_solids = rand() % (total_tiles / 4);    // Cantidad de sólidos a colocar (de momento la cuarta parte de la superficie, máximo)

    // Coloca los sólidos en el cuadrante
    for (int i = 0; i < n_solids; i++) {
        // Escoge una localización válida en el cuadrante
        int x, y, s;
        do {
            x = rand() % qW;
            y = rand() % qH;
            s = solids[iniX+x][iniY+y];
        } while (s != 0 || blocksDoor(iniX+x, iniY+y));

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
    if (x == SCREEN_WIDTH - wall_size - 1 && (y == SCREEN_HEIGHT / 2 - 1 || y == SCREEN_HEIGHT / 2) && door[LEFT]) return true;

    return false;
}

void DunScreen::placeEntities() {}

void DunScreen::placeEnemies() {
	// Coloca los sólidos en el cuadrante
    for (int i = 0; i < n_enemies; i++) {
		// Pide un enemigo válido a la interfaz con la base de datos
		short e = db->getEnemy(zone, theme);
        // Escoge una localización válida en el cuadrante
        short x, y, s;
        do {
			x = (rand() % SCREEN_WIDTH - wall_size*2) + wall_size;
			y = (rand() % SCREEN_HEIGHT - wall_size*2) + wall_size;
            s = solids[x][y];
        } while (s != 0 || blocksDoor(x, y));
		// Al salir del bucle, x e y representan una posición válida para el enemigo e
		enemy en;
		en.id = e;
		en.posX = x;
		en.posY = y;
		// Guardamos el nuevo enemigo en el vector de enemigos
		enemies->push_back(en);
	}
}

short DunScreen::getSym_type() { return sym_type; }
short DunScreen::getWall_size() { return wall_size; }
bool DunScreen::getDoor(short d) { return door[d]; }
bool DunScreen::getLock(short l) { return lock[l]; }
short DunScreen::getPuzzle(){ return puzzle; }
short DunScreen::getMiniBoss(){ return miniboss; }
short DunScreen::getTool(){ return tool; }

void DunScreen::setWall_size(short wall_size) { this->wall_size = wall_size; }
void DunScreen::setKey() { key = true; }
void DunScreen::setBoss_key() { boss_key = true; }
void DunScreen::setBoss(short boss) { this->boss = boss; }
void DunScreen::setTool(short tool) { this->tool = tool; }
