#include "DBManager.h"
#include <time.h>

DBManager::DBManager() {
	if (sqlite3_open(DB_PATH, &db)) {
		fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	db_status = true;

	// Instanciamos las estructuras de datos del posterior contenido de la BDJ
	enemies = new set<enemy_t>();
	npcs = new set<npc_t>();
	tools = new set<tool_t>();
	items = new set<item_t>();
	powUps = new set<item_t>();
	exchange = new set<exchange_t>();
	bosses = new set<boss_t>();
	blocks = new set<block_t>();
	graphics = new vector<gfx_t>();
	sounds = new vector<sfx_t>();
	essential_elems = new vector<essential_elem_t>();
	tileSets = new vector<gfx_t>();
	zones = new set<zone_t>;
	dungeons = new set<dungeon_t>();
	players = new set<player_t>;	

	tags = new vector<string>();

	last_exchange = -1;		// Al principio la cadena de intercambio está vacía.
	gather_essential_elements();	// Obtenemos de la BDD los elementos comunes a todos los juegos
	
	// Provisional
	read_tags();
}

DBManager::~DBManager() {
	// Al terminar la generación, debemos volcar todos los datos de la "cache" en la BDJ y copiar los recursos físicos
	// (gráficos, sonidos) a la carpeta de juego (habrá que hacer la consulta apropiada y las llamadas al sistema que se requieran.
	
	save();
	
	// Liberamos la memoria de las estructuras de datos empleadas (el contenido es estático)

	delete enemies; enemies = NULL;
	delete npcs; npcs = NULL;
	delete tools; tools = NULL;
	delete items; items = NULL;
	delete powUps; powUps = NULL;
	delete exchange; exchange = NULL;
	delete bosses; bosses = NULL;
	delete blocks; blocks = NULL;
	delete graphics; graphics = NULL;
	delete sounds; sounds = NULL;
	delete essential_elems; essential_elems = NULL;
	delete tileSets; tileSets = NULL;
	delete zones; zones = NULL;
	delete dungeons; dungeons = NULL;
	delete players; players = NULL;

	delete tags; tags = NULL;

	// Cerramos la base de datos
	sqlite3_close(db);
}

int DBManager::rowNumber(char* query) {
	int i = 0;
	sqlite3_stmt* statement;

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement)) i++;
			sqlite3_finalize(statement);
			return i;
		}
		else {
			db_status = false;
			return -1;
		}
	}
	else return -1;
}

short DBManager::getTileSet(string zone) {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	int id = -1;	// Id del tileset

	sprintf(query, "select tileSetId from Zones where '%s' = name", zone.c_str());

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				id = sqlite3_column_int(statement, 0);

			sqlite3_finalize(statement);
		}
		else db_status = false;
	}
	
	return id;
}

string DBManager::getPath(char* table, short id) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	string path = ""; // String a devolver
	
	sprintf(query, "select pathG from '%s' where id = %d", table, id);

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				path = (char*) sqlite3_column_text(statement, 0);
			
			sqlite3_finalize(statement);
			delete query; query = NULL;
			return path;
		}
		else db_status = false;
	}
	
	delete query; query = NULL;
	return NULL;
}

short DBManager::getGfxId(char* table, short id) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	short gfxId = -1; // Id a devolver
	
	sprintf(query, "select gfxId from '%s' where id = %d", table, id);

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				gfxId = (short) sqlite3_column_int(statement, 0);
			
			sqlite3_finalize(statement);
		}
		else db_status = false;
	}
	
	delete query; query = NULL;
	return gfxId;
}

short DBManager::getPowUpEffect(short id) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	short effect = -1;

	sprintf(query, "select effect from PowUp where id = %d", id);

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				effect = (short) sqlite3_column_int(statement, 0);
			
			sqlite3_finalize(statement);
		}
		else db_status = false;
	}
	
	delete query; query = NULL;
	return effect;
}

short DBManager::getKeyGfxId() {
	return keyGfxId;
}

short DBManager::getBossKeyGfxId() {
	return bossKeyGfxId;
}

void DBManager::getKey() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;	
	vector<short>* elems = get_valid_elems("Item");
	int n_players = elems->size();					

	if (n_players >= 0) {
		item_t i;
		sprintf(query, "select id, power, effect, gfxId, name from Item where effect = %d", KEY);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);
				i.id = (short) sqlite3_column_int(statement, 0);
				i.power = (short) sqlite3_column_int(statement, 1);
				i.effect = (short) sqlite3_column_int(statement, 2);
				i.gfxId = (short) sqlite3_column_int(statement, 3);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 4));
				i.name = name;

				items->insert(i);

				// Apuntamos el id del gráfico de llave que se usará en el juego
				keyGfxId = i.gfxId;
			}
			else db_status = false;
		}
	}
}

void DBManager::getBossKey() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;	
	vector<short>* elems = get_valid_elems("Item");
	int n_players = elems->size();					

	if (n_players >= 0) {
		item_t i;
		sprintf(query, "select id, power, effect, gfxId, name from Item where effect = %d", BOSSKEY);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);
				i.id = (short) sqlite3_column_int(statement, 0);
				i.power = (short) sqlite3_column_int(statement, 1);
				i.effect = (short) sqlite3_column_int(statement, 2);
				i.gfxId = (short) sqlite3_column_int(statement, 3);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 4));
				i.name = name;

				items->insert(i);

				// Apuntamos el id del gráfico de llave que se usará en el juego
				bossKeyGfxId = i.gfxId;
			}
			else db_status = false;
		}
	}
}

void DBManager::saveGfx() {
	gfx_t gfx;
	// Miramos los gráficos de los enemigos
	for (set<enemy_t>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		gfx.id = it->gfxId;					// Guardamos el id del gráfico
		gfx.path = getPath("Gfx", gfx.id);	// Consultamos el path del archivo de la tabla de gráficos
		graphics->push_back(gfx);			// Añadimos el gráfico al vector de gráficos de la BDJ
	}
	// Miramos los gráficos de los NPCs
	for (set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);	// Consultamos el path del archivo de la tabla de gráficos
		graphics->push_back(gfx);			// Añadimos el gráfico al vector de gráficos de la BDJ
	}
	// Miramos los gráficos de los power ups
	for (set<item_t>::iterator it = powUps->begin(); it != powUps->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}
	// Miramos los gráficos de los ítems
	for (set<item_t>::iterator it = items->begin(); it != items->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}

	// Miramos los gráficos de los objetos de intercambio
	for (set<exchange_t>::iterator it = exchange->begin(); it != exchange->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}
	// Miramos los gráficos de los players
	for (set<player_t>::iterator it = players->begin(); it != players->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}
	// Miramos los gráficos de los bloqueos
	for (set<block_t>::iterator it = blocks->begin(); it != blocks->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}

	// Abrimos el archivo de gráficos de la BDJ
	FILE* file = fopen("./data/GfxIndex", "w");
	// Escribimos el número de gráficos (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = graphics->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los gráficos
	for (vector<gfx_t>::iterator it = graphics->begin(); it < graphics->end(); it++) {
		buffer[0] = it->id;
		fwrite(buffer, sizeof(short), 1, file);
		buffer[0] = it->path.size();
		fwrite(buffer, sizeof(short), 1, file); // Escribimos el tamaño del string del path
		fwrite(it->path.c_str(), sizeof(char), buffer[0], file); // Escribimos el path
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);

	// Copiamos los gráficos al directorio correspondiente
	copyGfx();
}

void DBManager::saveTileSets() {
	FILE* file = fopen("./data/TileSets", "w");

	gfx_t gfx;

	// TileSets de las zonas del juego
	for (set<zone_t>::iterator it = zones->begin(); it != zones->end(); it++) {
		gfx.id = it->idTileSet;
		gfx.path = getPath("TileSet", gfx.id);
		tileSets->push_back(gfx);
	}

	// TileSets de las mazmorras del juego
	for (set<dungeon_t>::iterator it = dungeons->begin(); it != dungeons->end(); it++) {
		gfx.id = it->idTileSet;
		gfx.path = getPath("TileSet", gfx.id);
		tileSets->push_back(gfx);
	}

	short n_tileSetsBuf[1];
	n_tileSetsBuf[0] = tileSets->size();
	fwrite(n_tileSetsBuf, sizeof(short), 1, file);

	short buffer[2];
	for (vector<gfx_t>::iterator it = tileSets->begin(); it < tileSets->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->path.size();
		fwrite(buffer, sizeof(short), 2, file);
		fwrite(it->path.c_str(), sizeof(char), buffer[1], file);
	}

	fclose(file);

	copyTileSets();
}

void DBManager::saveEssentialElems() {
	FILE* file = fopen("./data/EssentialElems", "w");

	short n_essentialElemsBuf[1];
	n_essentialElemsBuf[0] = essential_elems->size();
	fwrite(n_essentialElemsBuf, sizeof(short), 1, file);

	short buffer[3];
	for (vector<essential_elem_t>::iterator it = essential_elems->begin(); it < essential_elems->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->type;
		buffer[2] = it->path.size();
		fwrite(buffer, sizeof(short), 3, file);
		fwrite(it->path.c_str(), sizeof(char), buffer[2], file);
		
	}

	fclose(file);

	copyEssentialElems();
}

void DBManager::copyGfx() {
	if (system(NULL)) system("mkdir .\\data\\Gfx");
	for (vector<gfx_t>::iterator it = graphics->begin(); it < graphics->end(); it++) {	// Recorremos todo el vector de gráficos que hemos preparado previamente
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
			sprintf(command, "copy \"%s.png\" \".\\data\\Gfx\"", it->path.c_str());
			system(command);	// Copiamos el .png
			sprintf(command, "copy \"%s.cfg\" \".\\data\\Gfx\"", it->path.c_str());
			system(command);	// Copiamos el .cfg
			delete command; command = NULL;	// Liberamos la memoria
		}
	}
}

void DBManager::copyTileSets() {
	for (vector<gfx_t>::iterator it = tileSets->begin(); it < tileSets->end(); it++) {
		if (system(NULL)) {
			char command[MAX_STR_LENGTH];
			sprintf(command, "copy \"%s.png\" \".\\data\\Gfx\"", it->path.c_str());
			system(command);
			sprintf(command, "copy \"%s.cfg\" \".\\data\\Gfx\"", it->path.c_str());
			system(command);
		}
	}
}

void DBManager::copyEssentialElems() {
	for (vector<essential_elem_t>::iterator it = essential_elems->begin(); it < essential_elems->end(); it++) {
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
			sprintf(command, "copy \"%s.png\" \".\\data\\Gfx\"", it->path.c_str());
			system(command);	// Copiamos el .png
			sprintf(command, "copy \"%s.cfg\" \".\\data\\Gfx\"", it->path.c_str());
			system(command);	// Copiamos el .cfg
			delete command; command = NULL;	// Liberamos la memoria
		}
	}
}


void DBManager::saveSfx(){
	string boffer;
	sfx_t aux;
	// recorremos la lista de npcs
	for(set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); ++it){
		boffer = getPath("sfx", it->sfxId); // obtiene el path del sonido

		// añade el sfx_t al vector de sonidos
		aux.id = it->sfxId;
		aux.path = boffer;
		sounds->push_back(aux);
	}

	// Posiblemente hay más sonidos que guardar

	// Abrimos el archivo de sonidos de la BDJ
	FILE* file = fopen("./data/SfxIndex", "w");
	// Escribimos el número de sonidos (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = sounds->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los sonidos
	delete buffer; buffer = new short[2];
	for (vector<gfx_t>::iterator it = graphics->begin(); it < graphics->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->path.size();
		fwrite(buffer, sizeof(short), 2, file);
		fwrite(it->path.c_str(), sizeof(char), it->path.size(), file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);

	copySfx();
}

void DBManager::copySfx(){
	char command[MAX_STR_LENGTH];

	for (vector<sfx_t>::iterator it = sounds->begin(); it < sounds->end(); it++) {
		if (system(NULL)) {
			sprintf(command, "copy \"%s\" \".data/Sfx\"", it->path);
			system(command);
		}
	}
}

void DBManager::gather_essential_elements() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;

	sprintf(query, "select id, type, pathG from EssentialElem");

	essential_elem_t e;
	char path[MAX_STR_LENGTH];

	if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement)) {
				e.id = (short) sqlite3_column_int(statement, 0);
				e.type = (short) sqlite3_column_int(statement, 1);
				sprintf(path, "%s", sqlite3_column_text(statement, 2));
				e.path = path;

				essential_elems->push_back(e);
			}
	}
	else db_status = false;

	sqlite3_finalize(statement);
}

void DBManager::read_tags() {
	// Según lo escriba Decidator
	// De momento, para que no pete
	tags->push_back("Zelda");
}

vector<short>* DBManager::get_valid_elems(char* elem) {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = new vector<short>();

	// Consigo los ids de la tabla
	sprintf(query, "select id from '%s'", elem);
	// Veo cuántos elementos tiene
	int n_elems = rowNumber(query);
	// Para cada elemento, recupero sus themeTags y las compruebo con las tags del juego
	for (int i = 0; i < n_elems; i++) {
		// Consigo las tags del elemento i
		sprintf(query, "select tag from %sThemeTags where %sId = %d", elem, elem, i);
		int n_tags = rowNumber(query);
		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			// Compruebo las tags del elemento i
			int j = 0;
			bool b = true;
			while (b && j <= n_tags) {
				if (SQLITE_ROW == sqlite3_step(statement)) {
					char tag[MAX_STR_LENGTH];
					sprintf(tag, "%s", sqlite3_column_text(statement, 0));
					// Una vez obtenida la etiqueta, comprobamos que se encuentra en el conjunto de tags de Decidator
					// Si no está, este elemento no nos vale
					bool found = false;
					vector<string>::iterator it = tags->begin();
					while (!found && it < tags->end()) {
						found = (strcmp(tag, it->c_str()) == 0);
						it++;
					}
					// Podemos continuar si hemos encontrado dicha tag
					b = found;
				}
				j++;
			}
			// Si hemos comprobado todas las tags del elemento, nos vale
			if (b) elems->push_back(i);
			
			sqlite3_finalize(statement);
		}
		else db_status = false;
	}

	return elems;
}

vector<short>* DBManager::filter_by_zone(char* elem, string zone, vector<short>* elems) {
	vector<short>* filtered_elems = new vector<short>();

	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;

	// Buscamos los elementos que tengan ese tag de zona
	sprintf(query, "select %sid from %sZoneTags where tag = '%s'", elem, elem, zone.c_str());

	short id = -1;
	if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
		while (SQLITE_ROW == sqlite3_step(statement)) {
			// Comprobamos si el id encontrado está en el vector de ids válidos por tema
			id = (short) sqlite3_column_int(statement, 0);
			
			vector<short>:: iterator it = elems->begin();
			bool found = false;
			while (!found && it < elems->end()) {
				found = (id == *it);
				it++;
			}
			if (found) filtered_elems->push_back(id);
		}

		sqlite3_finalize(statement);
	}
	else db_status = false;

	delete elems; elems = NULL;
	return filtered_elems;
}

short DBManager::getPlayer() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;	
	vector<short>* elems = get_valid_elems("Player");
	int n_players = elems->size();					
	short id = -1;

	if (n_players > 0) {
		player_t p;						
		id = elems->at(rand() % n_players);

		sprintf(query, "select id, gfxId, hp, mp, atk, def, name from Player where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				p.id = (short) sqlite3_column_int(statement, 0);
				p.gfxId = (short) sqlite3_column_int(statement, 1);
				p.hp = (short) sqlite3_column_int(statement, 2);
				p.mp = (short) sqlite3_column_int(statement, 3);
				p.atk = (short) sqlite3_column_int(statement, 4);
				p.def = (short) sqlite3_column_int(statement, 5);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 6));
				p.name = name;

				// enemies es un conjunto, si e ya está contenido en él no hace nada
				players->insert(p);
			}
			else db_status = false;
		}
	}

	sqlite3_finalize(statement);
	delete elems; elems = NULL;

	return id;
}

short DBManager::getEnemy(string zone) {
	char query[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;	// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("Enemy");	// Ids de los enemigos que nos valen
	vector<short>* filtered_elems = filter_by_zone("Enemy", zone, elems);
	int n_enemies = filtered_elems->size();						// Número de enemigos que aparecen en la consulta
	short id = -1;	// Id del enemigo a devolver

	if (n_enemies > 0) {
		enemy_t e;								// Struct con los datos del enemigo seleccionado
		id = filtered_elems->at(rand() % n_enemies);

		sprintf(query, "select id, gfxId, hp, str, df, name from Enemy where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				e.id = (short) sqlite3_column_int(statement, 0);
				e.gfxId = (short) sqlite3_column_int(statement, 1);
				e.hp = (short) sqlite3_column_int(statement, 2);
				e.atk = (short) sqlite3_column_int(statement, 3);
				e.df = (short) sqlite3_column_int(statement, 4);

				char name[MAX_STR_LENGTH], confPath[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 5));
				sprintf(confPath, "%s", sqlite3_column_text(statement, 6));
				e.name = name;
				e.confPath = confPath;

				// enemies es un conjunto, si e ya está contenido en él no hace nada
				enemies->insert(e);
			}
			else db_status = false;
		}
		
		sqlite3_finalize(statement);
	}

	delete filtered_elems; filtered_elems = NULL;

	return id;
}

short DBManager::getPowUp() {
	char query[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;	// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("PowUp");	
	int n_powups = elems->size();						
	short id = -1;

	if (n_powups > 0) {
		item_t pu;								
		id = elems->at(rand() % n_powups);

		sprintf(query, "select id, power, effect, gfxId, name from PowUp where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				pu.id = (short) sqlite3_column_int(statement, 0);
				pu.power = (short) sqlite3_column_text(statement, 1);
				pu.effect = (short) sqlite3_column_int(statement,2);
				pu.gfxId = (short) sqlite3_column_int(statement,3);
			
				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 4));
				pu.name = name;

				powUps->insert(pu);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete elems; elems = NULL;

	return id;
}

short DBManager::getExchange() {
	char query[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;	// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("Exchange");	
	int n_exchanges = elems->size();						
	short id = -1;

	if (n_exchanges > 0) {
		exchange_t e;								
		id = elems->at(rand() % n_exchanges);

		sprintf(query, "select id, gfxId, name from Exchange where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				e.id = (short) sqlite3_column_int(statement, 0);
				e.gfxId = (short) sqlite3_column_int(statement,1);
			
				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 2));
				e.name = name;

				// Le decimos cuál es el objeto anterior en la cadena y este lo colocamos como el último
				e.previous = last_exchange;
				last_exchange = e.id;

				exchange->insert(e);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete elems; elems = NULL;

	return id;
}

short DBManager::getBlock(string zone, short tool) {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("Blockade");
	vector<short>* filtered_elems = filter_by_zone("Blockade", zone, elems);
	int n_blockades = filtered_elems->size();				
	short id = -1;							

	if (n_blockades > 0) {
		block_t b;
		id = filtered_elems->at(rand() % n_blockades);

		sprintf(query, "select id, type, gfxId, dmgType from Blockade, BlockadeZoneTags where id = blockadeId and id = %d and tag = '%s'", id, zone.c_str());
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				b.id = (short) sqlite3_column_int(statement, 0);
				b.type = (short) sqlite3_column_int(statement, 1);
				b.gfxId = (short) sqlite3_column_int(statement, 2);
				b.dmgType = (short) sqlite3_column_int(statement, 3);

				blocks->insert(b);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete filtered_elems; filtered_elems = NULL;

	return id;
}

/* Devuelve el id de un NPC dada una zona y un tema */
short DBManager::getNPC(string zone) {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("NPC");
	vector<short>* filtered_elems = filter_by_zone("NPC", zone, elems);
	int n_npcs = filtered_elems->size();				// Número de NPCs que aparecen en la consulta
	short id = -1;							// Id del NPC, valor a devolver

	if (n_npcs > 0) {
		npc_t npc;
		id = filtered_elems->at(rand() % n_npcs);

		sprintf(query, "select id, gfxId, sfxId, name from NPC, NPCZoneTags where id = npcId and id = %d and tag = '%s'", id, zone.c_str());
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				npc.id = (short) sqlite3_column_int(statement, 0);
				npc.gfxId = (short) sqlite3_column_int(statement, 1);
				npc.sfxId = (short) sqlite3_column_int(statement, 2);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 3));
				npc.name = name;

				this->getNPCTexts(npc);

				npcs->insert(npc);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete filtered_elems; filtered_elems = NULL;

	return id;
}

/* Rellena el campo textos del NPC */
void DBManager::getNPCTexts(npc_t npc){
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;		// Puntero a una sentencia SQL, preparada para tratar

	sprintf(query, "select textId from NPCText where npcId = %d", npc.id);
	int n_texts = rowNumber(query);
	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			npc.texts = new vector<short>();

			for (int i = 0; i < n_texts; i++) {
				if (SQLITE_ROW == sqlite3_step(statement)) {
					npc.texts->push_back((short) sqlite3_column_int(statement, 0));
				}
			}
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}
}

short DBManager::getTool() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;			
	vector<short>* elems = get_valid_elems("Tool");
	int n_tools = elems->size();				
	short id = -1;

	if (n_tools > 0) {
		tool_t t;
		id = elems->at(rand() % n_tools);

		sprintf(query, "select id, gfxId, dmgType, ammoType, maxAmmo, strength, name from Tool where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				t.id = (short) sqlite3_column_int(statement, 0);
				t.gfxId = (short) sqlite3_column_int(statement, 1);
				t.dmgType = (short) sqlite3_column_int(statement, 2);
				t.ammoType = (short) sqlite3_column_int(statement, 3);
				t.maxAmmo = (short) sqlite3_column_int(statement, 4);
				t.strength = (short) sqlite3_column_int(statement, 5);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 6));
				t.name = name;

				tools->insert(t);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete elems; elems = NULL;

	return id;
}

/* Devuelve el id de un item dado un tema */
short DBManager::getItem() {
	char query[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;	// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("Item");	
	int n_items = elems->size();						
	short id = -1;

	if (n_items > 0) {
		item_t i;								
		id = elems->at(rand() % n_items);

		sprintf(query, "select id, power, effect, gfxId, name from Item where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				i.id = (short) sqlite3_column_int(statement, 0);
				i.power = (short) sqlite3_column_text(statement, 1);
				i.effect = (short) sqlite3_column_int(statement,2);
				i.gfxId = (short) sqlite3_column_int(statement,3);
			
				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 4));
				i.name = name;

				items->insert(i);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete elems; elems = NULL;

	return id;
}

short DBManager::getZone() {
	char query[MAX_STR_LENGTH];	
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("Zone");	
	int n_zones = elems->size();						
	short id = -1;

	if (n_zones > 0) {
		zone_t z;								
		id = elems->at(rand() % n_zones);

		sprintf(query, "select id, idTileSet, name from Zone where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				z.id = (short) sqlite3_column_int(statement, 0);
				z.idTileSet = (short) sqlite3_column_int(statement, 1);
			
				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 2));
				z.name = name;

				zones->insert(z);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete elems; elems = NULL;

	return id;
}

short DBManager::getDungeon(string zone) {
	// No consultamos el nombre de la mazmorra porque no nos es necesario
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("Dungeon");
	vector<short>* filtered_elems = filter_by_zone("Dungeon", zone, elems);
	int n_dungeons = filtered_elems->size();
	int idTileSet = -1;

	if (n_dungeons > 0) {
		int id = filtered_elems->at(rand() % n_dungeons);
		dungeon_t d;

		sprintf(query, "select id, idTileSet from Dungeon where id = %d", id);

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			sqlite3_step(statement);

			d.id = (short) sqlite3_column_int(statement, 0);
			d.idTileSet = (short) sqlite3_column_int(statement, 1);
			idTileSet = d.idTileSet;

			dungeons->insert(d);
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete filtered_elems; filtered_elems = NULL;

	// Devolvemos el idTileSet, que es lo que de verdad nos hace falta, no el id de la mazmorra
	return idTileSet;
}

void DBManager::save() {
	if (system(NULL))
		system("mkdir .\\data");

	savePlayers();
	saveEnemies();
	saveNPCs();
	saveTools();
	saveItems();
	savePowUps();
	saveExchange();
	saveBosses();
	saveBlocks();

	// Estos métodos además se encargan de copiar los respectivos archivos a la carpeta del juego
	saveGfx();
	saveEssentialElems();
	saveTileSets();
	saveSfx();
}

void DBManager::savePlayers() {
	// Abrimos el archivo de Players de la BDJ
	FILE* file = fopen("./data/Players", "w");
	// Escribimos el número de Players (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = players->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los players
	delete buffer; buffer = new short[7];
	for (set<player_t>::iterator it = players->begin(); it != players->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->hp;
		buffer[3] = it->mp;
		buffer[4] = it->atk;
		buffer[5] = it->def;
		buffer[6] = it->name.size();

		fwrite(buffer, sizeof(short), 7, file);
		fwrite(it->name.c_str(), sizeof(char), it->name.size(), file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveEnemies() {
	// Abrimos el archivo de enemigos de la BDJ
	FILE* file = fopen("./data/Enemies", "w");
	// Escribimos el número de enemigos que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = enemies->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los enemigos
	delete buffer; buffer = new short[7];
	for (set<enemy_t>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->hp;
		buffer[3] = it->atk;
		buffer[4] = it->df;
		buffer[5] = it->name.size();
		buffer[6] = it->confPath.size();
		fwrite(buffer, sizeof(short), 7, file);
		fwrite(it->name.c_str(), sizeof(char), it->name.size(), file);
		fwrite(it->confPath.c_str(), sizeof(char), it->confPath.size(), file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveNPCs() {
	// Abrimos el archivo de NPCs de la BDJ
	FILE* file = fopen("./data/NPCs", "w");
	// Escribimos el número de NPCs (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = npcs->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los npcs
	delete buffer; buffer = new short[6];
	for (set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->sfxId;
		buffer[3] = it->name.size();
		buffer[4] = it->confPath.size();
		fwrite(buffer, sizeof(short), 5, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[3], file);
		fwrite(it->confPath.c_str(), sizeof(char), buffer[4], file);
		// ------------------------------ nº de textos del npc
		buffer[0] = it->texts->size();
		fwrite(buffer, sizeof(short), 1, file);
		short* bufferText = new short[it->texts->size()];
		for (int i = 0; i < it->texts->size(); i++)
			bufferText[i] = it->texts->at(i);
		fwrite(bufferText, sizeof(short), it->texts->size(), file);
		delete bufferText; bufferText = NULL;
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveTools() {
	FILE* file = fopen("./data/Tools", "w");

	short* buffer = new short[1];
	buffer[0] = tools->size();
	fwrite(buffer, sizeof(short), 1, file);
	
	delete buffer; buffer = new short[7];
	for (set<tool_t>::iterator it = tools->begin(); it != tools->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->dmgType;
		buffer[3] = it->ammoType;
		buffer[4] = it->maxAmmo;
		buffer[5] = it->strength;
		buffer[6] = it->name.size();
		fwrite(buffer, sizeof(short), 7, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[6], file);
	}
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveItems() {
	// Abrimos el archivo de items de la BDJ
	FILE* file = fopen("./data/Items", "w");
	// Escribimos el número de items que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = items->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los items
	delete buffer; buffer = new short[5];
	for (set<item_t>::iterator it = items->begin(); it != items->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->power;
		buffer[2] = it->effect;
		buffer[3] = it->gfxId;
		buffer[4] = it->name.size();
		fwrite(buffer, sizeof(short), 5, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[4], file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::savePowUps() {
	// Abrimos el archivo de powUps de la BDJ
	FILE* file = fopen("./data/PowUps", "w");
	// Escribimos el número de porUps que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = powUps->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los power ups
	delete buffer; buffer = new short[5];
	for (set<item_t>::iterator it = powUps->begin(); it != powUps->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->power;
		buffer[2] = it->effect;
		buffer[3] = it->gfxId;
		buffer[4] = it->name.size();
		fwrite(buffer, sizeof(short), 5, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[4], file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveExchange() {
	// Abrimos el archivo de intercambios de la BDJ
	FILE* file = fopen("./data/Exchange", "w");
	// Escribimos el número de intercambios (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = exchange->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los intercambios
	delete buffer; buffer = new short[4];
	for (set<exchange_t>::iterator it = exchange->begin(); it != exchange->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->previous;
		buffer[3] = it->name.size();
		fwrite(buffer, sizeof(short), 4, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[3], file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveBosses() {
	// Abrimos el archivo de Bosses de la BDJ
	FILE* file = fopen("./data/Bosses", "w");
	// Escribimos el número de Bosses (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = bosses->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los bosses
	delete buffer; buffer = new short[2];
	for (set<boss_t>::iterator it = bosses->begin(); it != bosses->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->name.size();
		/* Más */
		fwrite(buffer, sizeof(short), 2, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[1], file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveBlocks() {
	// Abrimos el archivo de Blocks de la BDJ
	FILE* file = fopen("./data/Blocks", "w");
	// Escribimos el número de Blocks (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = blocks->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los blocks
	delete buffer; buffer = new short[4];
	for (set<block_t>::iterator it = blocks->begin(); it != blocks->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->type;
		buffer[2] = it->gfxId;
		buffer[3] = it->dmgType;	
		fwrite(buffer, sizeof(short), 4, file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}