#include "Screen.h"

Screen::Screen(short mapNumber, short posX, short posY, short n_enemies, string zone, string theme, DBManager* db) {
	this->mapNumber = mapNumber;
	this->posX = posX;
	this->posY = posY;
	this->n_enemies = n_enemies;
	this->zone = zone;
	this->theme = theme;
	this->db = db;
	
	// Instancia los vectores de la pantalla
	entities = new vector<entity>();
	enemies = new vector<enemy>();
	fgTiles = new vector<tileFG>();
	puzzles = new vector<puzzle_t>();
	
	// Inicializa las matrices de sólidos y tiles
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

void Screen::saveFGTiles(FILE* file) {
	short* buffer = new short[1];
	buffer[0] = n_tilesFG;
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
		delete buffer; buffer = new short[6];
		buffer[0] = it->posX;
		buffer[1] = it->posY;
		buffer[2] = it->type;
		buffer[3] = it->id;
		buffer[4] = it->idCollectable;
		buffer[5] = it->linkedTo;
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
	sprintf(fname, "map\\m%dr%d_%d", mapNumber, posX, posY);
	FILE* file = fopen(fname, "w");
	if (file != NULL) {
		// Ancho y alto de la pantalla en tiles

		short* buffer = new short[2];

		buffer[0] = SCREEN_WIDTH;
		buffer[1] = SCREEN_HEIGHT;
		fwrite(buffer, sizeof(buffer), 1, file);
		// Ancho y alto del tile en píxeles
		buffer[0] = TILE_WIDTH;
		buffer[1] = TILE_HEIGHT;
		fwrite(buffer, sizeof(buffer), 1, file);
		// id del tileset e id del gráfico de foreground

		delete buffer; buffer = new short[2];

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

short Screen::getPosX() { return posX; }
short Screen::getPosY() { return posY; }
short Screen::getSolid(short x, short y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        return solids[x][y];
    return -1;
}
short Screen::getNEnemies(){return n_enemies;}