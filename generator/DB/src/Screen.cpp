#include "Screen.h"

Screen::Screen(short posX, short posY, short puzzle, short n_enemies, short boss, short miniboss, short tool, string zone, DBManager* db) {
	this->posX = posX;
	this->posY = posY;
	this->puzzle = puzzle;
	this->n_enemies = n_enemies;
	this->boss = boss;
	this->miniboss = miniboss;
	this->tool = tool;
	this->db = db;

	key = false;
	boss_key = false;

	// Instancia los vectores de la pantalla
	entities = new vector<entity>();
	enemies = new vector<enemy>();
	fgTiles = new vector<tileFG>();
	puzzles = new vector<puzzle_t>();

	// Inicializa puertas, bloqueos, tiles y sólidos
	for (int i = 0; i < 4; i++) {
		door[i] = false;
		lock[i] = false;
	}

	for (int i = 0; i < SCREEN_WIDTH; i++)
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			tiles[i][j] = 0;
			solids[i][j] = 0;
		}
}

Screen::~Screen() {
	// Libera la memoria de los vectores que ha usado la Screen
	delete fgTiles; fgTiles = NULL;
	delete puzzles; puzzles = NULL;
    delete enemies; enemies = NULL;
    delete entities; entities = NULL;
}

void Screen::generate() {
	// Caution! Para generar la pantalla vacía
	n_entities = 0;
	n_puzzles = 0;
	n_tilesFG = 0;
	wall_size = 2;
	// End caution!

	decorate();			// Decora la mazmorra con sólidos
	placePuzzle();		// Coloca las entidades asociadas al puzzle de la pantalla (de haberlo)
	placeEntities();	// Coloca las entidades de la pantalla
	placeEnemies();		// Coloca los enemigos de la pantalla

	// DEBUG
	// print_screen();
}

void Screen::print_screen() {
	for (int j = 0; j < SCREEN_HEIGHT; j++) {
		for (int i = 0; i < SCREEN_WIDTH; i++) {
			if (solids[i][j] == 0) printf(".");
			if (solids[i][j] == 1) printf("#");
		}
		printf("\n");
	}
}

void Screen::saveFGTiles(FILE* file) {
	short* buffer = new short[1];
	fwrite(buffer, sizeof(buffer), 1, file);

	// Lista de tiles en foreground
	delete buffer; buffer = new short[3];
	vector<tileFG>::iterator itFG;
	for (itFG = fgTiles->begin(); itFG < fgTiles->end(); itFG++) {
		buffer[0] = itFG->id;
		buffer[1] = itFG->posX;
		buffer[2] = itFG->posY;
		fwrite(buffer, sizeof(buffer), 1, file);
	}

	delete buffer; buffer = NULL;
}

void Screen::saveEntities(FILE* file) {
	// Guarda el número de entidades
	short* buffer = new short[1];
	buffer[0] = n_entities;
	fwrite(buffer, sizeof(buffer), 1, file);

	// Guarda la info de las entidades
	vector<entity>::iterator it;
	for (it = entities->begin(); it < entities->end(); it++) {
		delete buffer; buffer = new short[3];
		buffer[0] = it->id;
		buffer[1] = it->posX;
		buffer[2] = it->posY;
		fwrite(buffer, sizeof(buffer), 1, file);
	}

	delete buffer; buffer = NULL;
}

void Screen::saveEnemies(FILE* file) {
	// Guarda el número de enemigos
	short* buffer = new short[1];
	buffer[0] = n_enemies;
	fwrite(buffer, sizeof(buffer), 1, file);

	// Guarda la info de los enemigos
	vector<enemy>::iterator it;
	for (it = enemies->begin(); it < enemies->end(); it++) {
		// Método propio de cada EnemyGen
		delete buffer; buffer = new short[3];
		buffer[0] = it->id;
		buffer[1] = it->posX;
		buffer[2] = it->posY;
		fwrite(buffer, sizeof(buffer), 1, file);
	}

	delete buffer; buffer = NULL;
}

void Screen::savePuzzles(FILE* file) {
	// Guarda el número de puzzles
	short* buffer = new short[1];
	buffer[0] = n_puzzles;
	fwrite(buffer, sizeof(buffer), 1, file);

	// Guarda la info de los puzzles
	delete buffer; buffer = new short[2];
	vector<puzzle_t>::iterator it;
	for (it = puzzles->begin(); it < puzzles->end(); it++) {
		buffer[0] = it->type;
		buffer[1] = it->id;
	}

	delete buffer; buffer = NULL;
}

bool Screen::save() {
	char fname[MAX_STR_LENGTH];
	// Nombre del archivo: m<ID>r<X>_<Y>
	sprintf(fname, "map\\m%dr%d_%d", 0, posX, posY);
	FILE* file = fopen(fname, "w");
	if (file != NULL) {
		// id del tileset e id del gráfico de foreground
		short* buffer = new short[2];
		buffer[0] = 0;
		buffer[1] = 0;
		fwrite(buffer, sizeof(buffer), 1, file);
		// Matriz de tiles de la pantalla
		for (int i = 0; i < SCREEN_WIDTH; i++)
			fwrite(tiles[i], sizeof(tiles[i]), 1, file);
		// Matriz de sólidos de la pantalla
		for (int i = 0; i < SCREEN_WIDTH; i++)
			fwrite(solids[i], sizeof(solids[i]), 1, file);

		// Info de tiles en foreground
		saveFGTiles(file);

		// Número de puzzles de la pantalla y lista de puzzles
		savePuzzles(file);

		// Info de las entidades de la pantalla
		saveEntities(file);

		// Info de los enemigos de la pantalla
		saveEnemies(file);

		// Posición inicial del personaje en la pantalla
		delete buffer; buffer = new short[2];
		buffer[0] = posIniX;
		buffer[1] = posIniY;
		fwrite(buffer, sizeof(buffer), 1, file);

		// Id de la música que suena en la pantalla
		delete buffer; buffer = new short[1];
		buffer[0] = idMusic;
		fwrite(buffer, sizeof(buffer), 1, file);

		delete buffer; buffer = NULL;

		fclose(file);
		return true;
	}

	return false;
}

void Screen::setDoor(short i) {
	if (i >= 0 && i < 4)
		door[i] = true;
}

void Screen::setLock(short i) {
	if (i >= 0 && i < 4)
		lock[i] = true;
}

void Screen::placePuzzle() {}

void Screen::placeWalls() {
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

void Screen::decorate() {
	// Construye las paredes y puertas de la mazmorra
	placeWalls();
    // Primero elige un tipo de simetría
    sym_type = rand() % 4;
    // Coloca elementos en los cuadrantes apropiados
    genQuadrants();
    genSymmetry();
}

void Screen::genQuadrants() {
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

void Screen::genQuadrant(short q) {
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

        // Coloca el sólido en dicha posición (en realidad debería obtener un tile de sólido y cambiar también el tile)
        solids[iniX+x][iniY+y] = 1;
    }
}

void Screen::genSymmetry() {
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

void Screen::genHorSymmetry() {
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

void Screen::genVerSymmetry() {
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

bool Screen::blocksDoor(short x, short y) {
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

void Screen::placeEntities() {}

void Screen::placeEnemies() {
	// Coloca los sólidos en el cuadrante
    for (int i = 0; i < n_enemies; i++) {
		// Pide un enemigo válido a la interfaz con la base de datos
		short e = db->getEnemy(zone);
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

short Screen::getPosX() { return posX; }
short Screen::getPosY() { return posY; }
short Screen::getSolid(short x, short y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        return solids[x][y];
    return -1;
}
short Screen::getSym_type() { return sym_type; }
short Screen::getWall_size() { return wall_size; }
bool Screen::getDoor(short d) { return door[d]; }
bool Screen::getLock(short l) { return lock[l]; }

void Screen::setWall_size(short wall_size) { this->wall_size = wall_size; }
void Screen::setKey() { key = true; }
void Screen::setBoss_key() { boss_key = true; }
void Screen::setBoss(short boss) { this->boss = boss; }
void Screen::setTool(short tool) { this->tool = tool; }
