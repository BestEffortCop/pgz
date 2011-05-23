#include "Dungeon.h"

Dungeon::Dungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db) {
	screenList = new vector<DunScreen*>(); // Instancia el vector de Screens
	decorator = new DunDecorator(db);		// Instancia el objeto decorador
	this->zone = zone;
	this->theme = theme;
	this->tool = tool;
	this->keyObj = keyObj;
	numDungeon = dungNumber;
	this->db = db;
	this->difficulty = gameDiff;
	this->ratio = ratio;

	wScreenX = dungeonPos.screenX;
	wScreenY = dungeonPos.screenY;
	wTileX = dungeonPos.tileX;
	wTileY = dungeonPos.tileY;
}

Dungeon::~Dungeon() {
	for (vector<DunScreen*>::iterator it = screenList->begin(); it < screenList->end(); it++)
		delete (*it);
    delete screenList; screenList = NULL;
	delete decorator; decorator = NULL;
}

bool Dungeon::save(std::string path) {
	// Abrimos el archivo de mazmorra m<ID>h
	char fname[MAX_STR_LENGTH];
	sprintf_s(fname, "%s%s%s/m%dh", path.c_str(), DATA_PATH, MAPS_PATH, numDungeon);
	FILE* file = fopen (fname, "wb");
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

		// Guardamos el layout no mirar x.o
		saveLayout(file);

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
		
		vector<DunScreen*>::iterator it;
		// información de las pantallas
		for (it = screenList->begin(); it < screenList->end(); it++)
			(*it)->save(path);
		return true;
	}
	return false;
}

void Dungeon::index_collectables() {
	int idC = 0;
	// Recorremos las pantallas de la mazmorra
	for (int i = 0; i < (int)screenList->size(); i++) {
		// Recorremos sus vectores de entidades
		for (int j = 0; j < (int)screenList->at(i)->getEntities()->size(); j++) {
			// Comprobamos si cada entidad es un cerrojo o un collectable
			if (screenList->at(i)->getEntities()->at(j)->type == DOOR ||
				screenList->at(i)->getEntities()->at(j)->type == BOSSDOOR ||
				screenList->at(i)->getEntities()->at(j)->type == FINAL_DOOR) { // por aclarar final door
				n_puertas++; // Contamos una puerta más (mitades de puerta, en realidad, que son las entidades que colocamos)
				// No hacemos nada más, pues los ids de las puertas fueron asignados previamente (véase placeEntities de DunScreen)
			} else if (screenList->at(i)->getEntities()->at(j)->type != TELEPORTATOR && // habría que pensar en encapsular esta condición 
					   screenList->at(i)->getEntities()->at(j)->type != DOOR_OPEN_CLOSE &&
				       screenList->at(i)->getEntities()->at(j)->type != ARENA &&
				       screenList->at(i)->getEntities()->at(j)->type != INSTANCIATOR &&
				       screenList->at(i)->getEntities()->at(j)->type != FLOORBUTTON &&
				       screenList->at(i)->getEntities()->at(j)->type != TILEDPUSHABLE && 
					   screenList->at(i)->getEntities()->at(j)->type != TILEDENTITY) {
				n_collectables++;
				screenList->at(i)->getEntities()->at(j)->idCollectable = idC;
				idC++;
			}
		}
	}
}

DunScreen* Dungeon::findScreen(int x, int y){
	DunScreen* s;
	int i = 0;
	bool found = false;
	while(i < (int)screenList->size() && !found){
		s = (DunScreen*)screenList->at(i);
		found = (s->getPosX() == x) && (s->getPosY() == y);
		i++;
	}
	if(found) 
		return s;
	else 
		return NULL;
}

short Dungeon::getWScreenX() { return wScreenX; }
short Dungeon::getWScreenY() { return wScreenY; }
short Dungeon::getWTileX() { return wTileX; }
short Dungeon::getWTileY() { return wTileY; }

short Dungeon::getIniDScreenX() { return iniX; }
short Dungeon::getIniDScreenY() { return iniY; }

short Dungeon::getIniDTileX() {
	DunScreen* s;
	if((s = findScreen(iniX,iniY)) == NULL)
		return -1;
	else
		return s->getPosIniX();
}

short Dungeon::getIniDTileY() { 
	DunScreen* s;
	if((s = findScreen(iniX,iniY)) == NULL)
		return -1;
	else
		return s->getPosIniY();
}

void Dungeon::saveLayout(FILE* file){
		// layout
		// inicializamos el layout a 0
		char** layout = new char*[width];
		for (int i = 0; i < width; i++) {
			layout[i] = new char[height];
			for (int j = 0; j < height; j++)
				layout[i][j] = 0;
		}

		// comprobamos qué pantallas están ocupadas
		vector<DunScreen*>::iterator it;
		for (it = screenList->begin(); it < screenList->end(); it++){

			// case horrible 
			switch((*it)->getDoorNum()){
			
				case 0: // cero habitaciones adyacentes
					layout[(*it)->getPosX()][(*it)->getPosY()] = 1;
					break;
				case 1: // una habitación
					if((*it)->getDoor(UP))
						layout[(*it)->getPosX()][(*it)->getPosY()] = 2;
					else
						if((*it)->getDoor(DOWN))
							layout[(*it)->getPosX()][(*it)->getPosY()] = 3;
						else
							if((*it)->getDoor(LEFT))
								layout[(*it)->getPosX()][(*it)->getPosY()] = 4;
							else
								if((*it)->getDoor(RIGHT))
									layout[(*it)->getPosX()][(*it)->getPosY()] = 5;
					break;
				case 2: // dos habitaciones
					if((*it)->getDoor(LEFT) && (*it)->getDoor(RIGHT))
						layout[(*it)->getPosX()][(*it)->getPosY()] = 6;
					else
						if((*it)->getDoor(LEFT) && (*it)->getDoor(UP))
							layout[(*it)->getPosX()][(*it)->getPosY()] = 7;
						else
							if((*it)->getDoor(LEFT) && (*it)->getDoor(DOWN))
								layout[(*it)->getPosX()][(*it)->getPosY()] = 8;
							else
								if((*it)->getDoor(RIGHT) && (*it)->getDoor(DOWN))
									layout[(*it)->getPosX()][(*it)->getPosY()] = 9;
								else
									if((*it)->getDoor(RIGHT) && (*it)->getDoor(UP))
											layout[(*it)->getPosX()][(*it)->getPosY()] = 10;
									else
										if((*it)->getDoor(UP) && (*it)->getDoor(DOWN))
											 layout[(*it)->getPosX()][(*it)->getPosY()] = 11;
					break;
				case 3: // tres habitaciones
					if((*it)->getDoor(LEFT) && (*it)->getDoor(RIGHT) && (*it)->getDoor(UP))
						layout[(*it)->getPosX()][(*it)->getPosY()] = 12;
					else
						if((*it)->getDoor(UP) && (*it)->getDoor(RIGHT) && (*it)->getDoor(DOWN))
							layout[(*it)->getPosX()][(*it)->getPosY()] = 13;
						else
							if((*it)->getDoor(LEFT) && (*it)->getDoor(UP) && (*it)->getDoor(DOWN))
								layout[(*it)->getPosX()][(*it)->getPosY()] = 15;
							else
								if((*it)->getDoor(LEFT) && (*it)->getDoor(RIGHT) && (*it)->getDoor(DOWN))
									layout[(*it)->getPosX()][(*it)->getPosY()] = 16;
					break;
				case 4:
					layout[(*it)->getPosX()][(*it)->getPosY()] = 17;
					break;
			}				

			// si es habitación inicial o de boss se asigna 
			if((*it)->getBoss() != -1){
				layout[(*it)->getPosX()][(*it)->getPosY()] = 18;
			}
			else
				if((*it)->getInitialRoom())
					layout[(*it)->getPosX()][(*it)->getPosY()] = 19;

		}
		// guardamos el layout
		for (int i = 0; i < width; i++)
			fwrite(layout[i], sizeof(char), height, file);

        // nos deshacemos de la memoria que hemos usado para guardar el layout
		for (int i = 0; i < width; i++) {
			delete layout[i];
			layout[i] = NULL;
		}
		delete layout; layout = NULL;

} 