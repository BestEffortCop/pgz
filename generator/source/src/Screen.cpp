#include "Screen.h"

Screen::Screen(short mapNumber, short posX, short posY, short n_enemies, string zone, DBManager* db) {
	this->mapNumber = mapNumber;
	this->posX = posX;
	this->posY = posY;
	this->n_enemies = n_enemies;
	this->zone = zone;
	this->db = db;
	
	// Inicializa la info de la pantalla
	posIniX = 0;
	posIniY = 0;
	
	n_entities = 0;	
	n_tilesFG = 0; 		
	n_puzzles = 0;

	idMusic = 0;

	// Instancia los vectores de la pantalla
	entities = new vector<Entity*>();
	enemies = new vector<enemy>();
	fgTiles = new vector<tileFG>();
	puzzles = new vector<puzzle_t>();
	
	// Inicializa las matrices de sólidos y tiles
	for (int i = 0; i < SCREEN_WIDTH*AUTOTILE_DIVISION; i++)
		for (int j = 0; j < SCREEN_HEIGHT*AUTOTILE_DIVISION; j++) {
			tiles[i][j] = 0;
		}

	for (int i = 0; i < SCREEN_WIDTH; i++)
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			solids[i][j] = 0;
		}
}

Screen::~Screen() {
	// Libera la memoria de los vectores que ha usado la Screen
	delete fgTiles; fgTiles = NULL;
	delete puzzles; puzzles = NULL;
    delete enemies; enemies = NULL;
	for (vector<Entity*>::iterator it = entities->begin(); it < entities->end(); it++)
		delete (*it);
    delete entities; entities = NULL;
}

void Screen::saveFGTiles(FILE* file) {
	short n_fgtiles[1];
	n_fgtiles[0] = n_tilesFG;
	fwrite(n_fgtiles, sizeof(short), 1, file);

	// Lista de tiles en foreground
	short fgTilesBuf[3];
	vector<tileFG>::iterator itFG;
	for (itFG = fgTiles->begin(); itFG < fgTiles->end(); itFG++) {
		fgTilesBuf[0] = itFG->id;
		fgTilesBuf[1] = itFG->posX;
		fgTilesBuf[2] = itFG->posY;
		fwrite(fgTilesBuf, sizeof(short), 3, file);
	}
}

void Screen::saveEntities(FILE* file) {
	short n_ent[1];
	n_ent[0] = entities->size();
	fwrite(n_ent, sizeof(short), 1, file);

	for (vector<Entity*>::iterator it = entities->begin(); it < entities->end(); it++)
		bool b = (*it)->save(file);
}

void Screen::saveEnemies(FILE* file) {
	// Guarda el número de enemigos
	short nene[1];
	nene[0] = enemies->size();
	fwrite(nene, sizeof(short), 1, file);

	// Guarda la info de los enemigos
	short ene[4];
	vector<enemy>::iterator it;
	for (it = enemies->begin(); it < enemies->end(); it++) {
		ene[0] = it->id;
		ene[1] = it->posX;
		ene[2] = it->posY;
		ene[3] = it->linkedTo;
		fwrite(ene, sizeof(short), 4, file);
	}
}

void Screen::savePuzzles(FILE* file) {
	// Guarda el número de puzzles
	short npuz[1];
	npuz[0] = puzzles->size();
	fwrite(npuz, sizeof(short), 1, file);

	// Guarda la info de los puzzles
	short puz[2];
	vector<puzzle_t>::iterator it;
	for (it = puzzles->begin(); it < puzzles->end(); it++) {
		puz[0] = it->type;
		puz[1] = it->id;
		fwrite(puz, sizeof(short), 2, file);
	}
}

bool Screen::save() {
	char fname[MAX_STR_LENGTH];
	// Nombre del archivo: m<ID>r<X>_<Y>
	sprintf(fname, "map/m%dr%d_%d", mapNumber, posX, posY);
	FILE* file = fopen(fname, "w");
	if (file != NULL) {
		// Ancho y alto de la pantalla en tiles
		short whScreen[2];
		whScreen[0] = SCREEN_WIDTH;
		whScreen[1] = SCREEN_HEIGHT;
		fwrite(whScreen, sizeof(short), 2, file);
		// Ancho y alto del tile en píxeles
		short whTile[2];
		whTile[0] = TILE_WIDTH;
		whTile[1] = TILE_HEIGHT;
		fwrite(whTile, sizeof(short), 2, file);
		// id del tileset e id del gráfico de foreground
		short idTsetFG[2];
		idTsetFG[0] = 0;
		idTsetFG[1] = 0;
		fwrite(idTsetFG, sizeof(short), 2, file);

		// Matriz de tiles de la pantalla
		for (int i = 0; i < SCREEN_WIDTH*2; i++)
			for (int j = 0; j < SCREEN_HEIGHT*2; j++)
				fwrite(&(tiles[i][j]), sizeof(short), 1, file);

		// Matriz de sólidos de la pantalla
		for (int i = 0; i < SCREEN_WIDTH; i++)
			for (int j = 0; j < SCREEN_HEIGHT; j++)
				fwrite(&(solids[i][j]), sizeof(short), 1, file);

		// Info de tiles en foreground
		saveFGTiles(file);

		// Número de puzzles de la pantalla y lista de puzzles
		savePuzzles(file);

		// Info de las entidades de la pantalla
		saveEntities(file);

		// Info de los enemigos de la pantalla
		saveEnemies(file);

		// Posición inicial del personaje en la pantalla
		short initialPos[2];
		initialPos[0] = posIniX;
		initialPos[1] = posIniY;
		fwrite(initialPos, sizeof(short), 2, file);

		// Id de la música que suena en la pantalla
		short music[1];
		music[0] = idMusic;
		fwrite(music, sizeof(short), 1, file);

		fclose(file);

		return true;
	}

	return false;
}

short Screen::getPosX() { return posX; }
short Screen::getPosY() { return posY; }
short Screen::getPosIniX() { return posIniX; }
short Screen::getPosIniY() { return posIniY; }

short Screen::getSolid(short x, short y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        return solids[x][y];
    return -1;
}
short Screen::getNEnemies() {return n_enemies;}
vector<Entity*>* Screen::getEntities() { return entities; }

string Screen::getZone(){return zone;};

vector<puzzle_t>* Screen::getPuzzles() {return puzzles;};

void Screen::setPosIni(int x, int y)
{
	posIniX = x;
	posIniY = y;
}

void Screen::setTile(int x, int y, short idTile)
{
	// Los tiles trabajan a resolución 8x8
	if (x >= 0 && x < SCREEN_WIDTH*AUTOTILE_DIVISION && y >= 0 && y < SCREEN_HEIGHT*AUTOTILE_DIVISION)
	{
		tiles[x][y] = idTile;
	}
}

short Screen::getTile(int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH*AUTOTILE_DIVISION && y >= 0 && y < SCREEN_HEIGHT*AUTOTILE_DIVISION)
	{
		return tiles[x][y];
	}
}

void Screen::setSolid(int x, int y, short solid)
{
	// Los solids trabajan a resolución 8x8
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		solids[x][y] = solid;
	}
}

void Screen::addEntity(Entity* ent)
{
	entities->push_back(ent);
}

void Screen::addEnemy(enemy e) {
	enemies->push_back(e);
}

void Screen::addPuzzle(puzzle_t p) {
	puzzles->push_back(p);
}

bool Screen::contains(int elem, vector<int>* collect){
	for (int i = 0; i < collect->size(); i++)
		if (collect->at(i) == elem)
			return true;

	return false;
}