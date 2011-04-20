#include "Dungeon.h"

Dungeon::Dungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, DBManager* db) {
    // Instancia el vector de Screens
	screenList = new vector<Screen*>();
	this->zone = zone;
	this->theme = theme;
	this->tool = tool;
	numDungeon = dungNumber;
	this->db = db;
	this->difficulty = gameDiff;
	this->ratio = ratio;
	
	srand(time(NULL));
}

Dungeon::~Dungeon() {
	for (vector<Screen*>::iterator it= screenList->begin(); it < screenList->end(); it++)
			delete(*it);
    delete screenList; screenList = NULL;
}

bool Dungeon::save() {
	// Abrimos el archivo de mazmorra m<ID>h
	char fname[MAX_STR_LENGTH];
	sprintf(fname, "map\\m%dh", numDungeon);
	FILE* file = fopen (fname, "w");
	// Guardamos la información de la mazmorra (ahora mismo no me sé el orden)
	if (file != NULL) {
		// Guardamos el tipo de mapa del que se trata
		short mapType[1];
		mapType[0] = 1;	// Tipo mazmorra
		fwrite(mapType, sizeof(short), 1, file);
		// Guardamos la información de la mazmorra
		short wh[2];
		wh[0] = width;
		wh[1] = height;
		fwrite(wh, sizeof(short), 2, file);	// ancho y alto de la mazmorra en pantallas

		// layout
		// inicializamos el layout a 0
		bool** layout = new bool*[width];
		for (int i = 0; i < width; i++) {
			layout[i] = new bool[height];
			for (int j = 0; j < height; j++)
				layout[i][j] = false;
		}

		// comprobamos qué pantallas están ocupadas
		vector<Screen*>::iterator it;
		for (it = screenList->begin(); it < screenList->end(); it++)
			layout[(*it)->getPosX()][(*it)->getPosY()] = true;

		// guardamos el layout
		for (int i = 0; i < width; i++)
			fwrite(layout[i], sizeof(bool), height, file);

        // nos deshacemos de la memoria que hemos usado para guardar el layout
		for (int i = 0; i < width; i++) {
			delete layout[i];
			layout[i] = NULL;
		}
		delete layout; layout = NULL;

		// guardamos la pantalla inicial de la mazmorra
		short initialScreen[2];
		initialScreen[0] = iniX;
		initialScreen[1] = iniY;
		fwrite(initialScreen, sizeof(short), 2, file);

		// información general de la mazmorra

		short persistence[4];
		persistence[0] = n_puzzles;
		persistence[1] = n_collectables;
		persistence[2] = n_puertas;
		persistence[3] = n_minibosses;
		fwrite(persistence, sizeof(short), 4, file);

		fclose(file);

		// información de las pantallas
		for (it = screenList->begin(); it < screenList->end(); it++)
			(*it)->save();
		return true;
	}
	return false;
}

void Dungeon::index_collectables() {
	int idC = 0;
	// Recorremos las pantallas de la mazmorra
	for (int i = 0; i < screenList->size(); i++) {
		// Recorremos sus vectores de entidades
		for (int j = 0; j < screenList->at(i)->getEntities()->size(); j++) {
			// Comprobamos si cada entidad es un cerrojo o un collectable
			if (screenList->at(i)->getEntities()->at(j).type == LOCK ||
				screenList->at(i)->getEntities()->at(j).type == BOSS_LOCK) {
				n_puertas++; // Contamos una puerta más (mitades de puerta, en realidad, que son las entidades que colocamos)
				// No hacemos nada más, pues los ids de las puertas fueron asignados previamente (véase placeEntities de DunScreen)
			} else {
				n_collectables++;
				screenList->at(i)->getEntities()->at(j).idCollectable = idC;
				idC++;
			}
		}
	}
}