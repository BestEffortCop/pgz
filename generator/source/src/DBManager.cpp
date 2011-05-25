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
	bosses = new set<boss_t>();
	blocks = new set<block_t>();
	graphics = new vector<gfx_t>();
	sounds = new vector<sfx_t>();
	essential_elems = new vector<essential_elem_t>();
	tileSets = new vector<gfx_t>();
	zones = new set<zone_t>;
	dungeons = new set<dungeon_t>();
	players = new set<player_t>;	
	puzzle_elems = new set<puzzle_elem_t>();

	tags = new vector<string>();

	gather_essential_elements();	// Obtenemos de la BDD los elementos comunes a todos los juegos
	
	read_tags();					// Leemos las tags que ha seleccionado Decidator
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
	delete bosses; bosses = NULL;
	delete blocks; blocks = NULL;
	delete graphics; graphics = NULL;
	delete sounds; sounds = NULL;
	delete essential_elems; essential_elems = NULL;
	delete tileSets; tileSets = NULL;
	delete zones; zones = NULL;
	delete dungeons; dungeons = NULL;
	delete players; players = NULL;
	delete puzzle_elems; puzzle_elems = NULL;

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

	sprintf(query, "select tileSetId from Zones where '%s' = gen", zone.c_str());

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
	char query[MAX_STR_LENGTH];
	string path = ""; // String a devolver
	
	sprintf(query, "select pathG from '%s' where id = %d", table, id);

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				path = (char*) sqlite3_column_text(statement, 0);
			
			sqlite3_finalize(statement);
			return path;
		}
		else db_status = false;
	}

	return "";
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
	
	delete [] query; query = NULL;
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
	
	delete [] query; query = NULL;
	return effect;
}

short DBManager::getPower(char* table, short id) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	short power = -1;
	
	sprintf(query, "select power from '%s' where id = %d", table, id);

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				power = (short) sqlite3_column_int(statement, 0);
			
			sqlite3_finalize(statement);
		}
		else db_status = false;
	}
	
	delete [] query; query = NULL;
	return power;
}

short DBManager::getDmgType(short idBlockade) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	short dmgType = -1;

	sprintf(query, "select dmgType from Blockade where id = %d", idBlockade);

	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			if (SQLITE_ROW == sqlite3_step(statement))
				dmgType = (short) sqlite3_column_int(statement, 0);
			
			sqlite3_finalize(statement);
		}
		else db_status = false;
	}
	
	delete [] query; query = NULL;
	return dmgType;
}

short DBManager::getKeyGfxId() {
	return keyGfxId;
}

short DBManager::getBossKeyGfxId() {
	return bossKeyGfxId;
}

short DBManager::getKeyId() {
	return keyId;
}

short DBManager::getBossKeyId() {
	return bossKeyId;
}

void DBManager::getKey() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;	
	vector<short>* elems = get_valid_elems("Item");
	int n_keys = elems->size();					

	if (n_keys >= 0) {
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
				keyId = i.id;
			}
			else db_status = false;
		}
	}
	delete elems; elems = NULL;
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
				bossKeyId = i.id;
			}
			else db_status = false;
		}
	}
	delete elems; elems = NULL;
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
	// Miramos los gráficos de las tools
	for (set<tool_t>::iterator it = tools->begin(); it != tools->end(); it++) {
		// Gráfico de la tool
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
		// Gráfico de la munición
		gfx.id = it->gfxAmmo;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}
	// Miramos los gráficos de los puzzleElems
	for (set<puzzle_elem_t>::iterator it = puzzle_elems->begin(); it != puzzle_elems->end(); it++) {
		gfx.id = it->gfxId;
		gfx.path = getPath("Gfx", gfx.id);
		graphics->push_back(gfx);
	}

	// Abrimos el archivo de gráficos de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sGfxIndex", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);

	// Copiamos los gráficos al directorio correspondiente
	copyGfx();
}

void DBManager::saveTileSets() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sTileSets", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

	gfx_t gfx;

	// TileSets de las zonas del juego
	for (set<zone_t>::iterator it = zones->begin(); it != zones->end(); it++) {
		gfx.id = it->idTileSet;
		gfx.path = getPath("TileSet", gfx.id);
		tileSets->push_back(gfx);
	}

	// TileSets de las mazmorras del juego (ya se encarga del de la mazmorra final)
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
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sEssentialElems", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

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
	char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
	sprintf(command, "mkdir .\\%s%s", DATA_PATH, RES_PATH);
	if (system(NULL)) system(command);
	for (vector<gfx_t>::iterator it = graphics->begin(); it < graphics->end(); it++) {	// Recorremos todo el vector de gráficos que hemos preparado previamente
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			sprintf(command, "copy \"%s.png\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);	// Copiamos el .png
			sprintf(command, "copy \"%s.cfg\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);	// Copiamos el .cfg
			sprintf(command, "copy \"%s.mnu\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);	// Copiamos el .mnu
		}
	}
	delete [] command; command = NULL;	// Liberamos la memoria
}

void DBManager::copyTileSets() {
	for (vector<gfx_t>::iterator it = tileSets->begin(); it < tileSets->end(); it++) {
		if (system(NULL)) {
			char command[MAX_STR_LENGTH];
			sprintf(command, "copy \"%s.png\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);
			sprintf(command, "copy \"%s.cfg\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);
		}
	}
}

void DBManager::copyEssentialElems() {
	for (vector<essential_elem_t>::iterator it = essential_elems->begin(); it < essential_elems->end(); it++) {
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
			sprintf(command, "copy \"%s.png\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);	// Copiamos el .png
			sprintf(command, "copy \"%s.cfg\" \".\\%s%s\" >> \".\\%sLog\"", it->path.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
			system(command);	// Copiamos el .cfg
			delete [] command; command = NULL;	// Liberamos la memoria
		}
	}
}

void DBManager::copyEnemyComponents() {
	for (set<enemy_t>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		if (system(NULL)) {
			char command[MAX_STR_LENGTH];
			sprintf(command, "mkdir .\\%s%s  >> \".\\%sLog\"", DATA_PATH, COMPS_PATH, DATA_PATH);
			system(command);
			sprintf(command, "copy \".\\%s%s.nmy\" \".\\%s%s\" >> \".\\%sLog\"", COMPS_PATH, it->name.c_str(), DATA_PATH, COMPS_PATH, DATA_PATH);
			system(command);
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
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sSfxIndex", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);

	//copySfx();
}

void DBManager::copySfx(){
	char command[MAX_STR_LENGTH];

	for (vector<sfx_t>::iterator it = sounds->begin(); it < sounds->end(); it++) {
		if (system(NULL)) {
			sprintf(command, "copy \"%s\" \".\\%sSfx\" >> \".\\%sLog\"", it->path, DATA_PATH, DATA_PATH);
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

short DBManager::getFloorButton() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("PuzzleElem");
	short gfxId = -1;

	if (elems->size() > 0) {
		sprintf(query, "select id, type, gfxId from PuzzleElem where type = %d", 0);

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			puzzle_elem_t p;
			int id = -1;
			while (!belongsTo(id, elems) && SQLITE_ROW == sqlite3_step(statement))
				id = (short) sqlite3_column_int(statement, 0);

			p.id = id;
			p.type = (short) sqlite3_column_int(statement, 1);
			p.gfxId = (short) sqlite3_column_int(statement, 2);
			gfxId = p.gfxId;

			puzzle_elems->insert(p);
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete elems; elems = NULL;

	return gfxId;
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

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 5));
				e.name = name;

				// enemies es un conjunto, si e ya está contenido en él no hace nada
				enemies->insert(e);
			}
			else db_status = false;
		}
		
		sqlite3_finalize(statement);
	}

	delete filtered_elems; filtered_elems = NULL;
	delete elems; elems = NULL;
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
				pu.power = (short) sqlite3_column_int(statement, 1);
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
	delete elems; elems = NULL;

	return id;
}

/* Devuelve el id de un NPC dada una zona y un tema */
NPCInfo DBManager::getNPC(string zone) {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("NPC");
	vector<short>* filtered_elems = filter_by_zone("NPC", zone, elems);
	int n_npcs = filtered_elems->size();				// Número de NPCs que aparecen en la consulta
	NPCInfo n;

	if (n_npcs > 0) {
		npc_t npc;
		short id = filtered_elems->at(rand() % n_npcs);

		sprintf(query, "select id, gfxId, sfxId, name, movComp from NPC, NPCZoneTags where id = npcId and id = %d and tag = '%s'", id, zone.c_str());
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				npc.id = (short) sqlite3_column_int(statement, 0);
				npc.gfxId = (short) sqlite3_column_int(statement, 1);
				npc.sfxId = (short) sqlite3_column_int(statement, 2);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 3));
				npc.name = name;

				npc.movComp = (short) sqlite3_column_int(statement, 4);

				n.gfxId = npc.gfxId;
				n.npcType = npc.movComp;

				npcs->insert(npc);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete filtered_elems; filtered_elems = NULL;
	delete elems; elems = NULL;

	return n;
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

		sprintf(query, "select id, gfxId, dmgType, gfxAmmo, maxAmmo, strength, name, type from Tool where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				t.id = (short) sqlite3_column_int(statement, 0);
				t.gfxId = (short) sqlite3_column_int(statement, 1);
				t.dmgType = (short) sqlite3_column_int(statement, 2);
				t.gfxAmmo = (short) sqlite3_column_int(statement, 3);
				t.maxAmmo = (short) sqlite3_column_int(statement, 4);
				t.strength = (short) sqlite3_column_int(statement, 5);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 6));
				t.name = name;

				t.type = (short) sqlite3_column_int(statement, 7);

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
				i.power = (short) sqlite3_column_int(statement, 1);
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

ZoneInfo DBManager::getZone() {
	char query[MAX_STR_LENGTH];	
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("Zone");	
	int n_zones = elems->size();						
	ZoneInfo zI;

	if (n_zones > 0) {
		zone_t z;								
		short id = elems->at(rand() % n_zones);

		sprintf(query, "select id, tileSetId, name, gen from Zone where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
				sqlite3_step(statement);

				z.id = (short) sqlite3_column_int(statement, 0);
				z.idTileSet = (short) sqlite3_column_int(statement, 1);
			
				char name[MAX_STR_LENGTH], gen[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 2));
				sprintf(gen, "%s", sqlite3_column_text(statement, 3));
				z.gen = gen;
				z.name = name;

				zI.tileSetId = z.id;
				zI.gen = z.gen;

				zones->insert(z);
			}
			else db_status = false;

			sqlite3_finalize(statement);
		}
	}

	delete elems; elems = NULL;

	return zI;
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
	delete elems; elems = NULL;

	// Devolvemos el idTileSet, que es lo que de verdad nos hace falta, no el id de la mazmorra
	return idTileSet;
}

short DBManager::getFinalDungeon(string zone) {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("FinalDungeon");
	vector<short>* filtered_elems = filter_by_zone("FinalDungeon", zone, elems);
	int n_dungeons = filtered_elems->size();
	int idTileSet = -1;

	if (n_dungeons > 0) {
		int id = filtered_elems->at(rand() % n_dungeons);
		dungeon_t d;

		sprintf(query, "select id, idTileSet from FinalDungeon where id = %d", id);

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
	delete elems; elems = NULL;

	// Devolvemos el idTileSet, que es lo que de verdad nos hace falta, no el id de la mazmorra
	return idTileSet;
}

short DBManager::getFinalElem() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("FinalElem");
	int gfxId = -1;
	
	if (elems->size() > 0) {
		sprintf(query, "select id, gfxId, name from FinalElem where id = %d", rand() % elems->size());

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			sqlite3_step(statement);

			gfxId = (short) sqlite3_column_int(statement, 1);
			// Como sólo se va a usar uno, se encarga él mismo de guardar el gráfico
			gfx_t gfx;
			gfx.id = gfxId;
			gfx.path = getPath("Gfx", gfxId);
			graphics->push_back(gfx);

			finalElem.id = (short) sqlite3_column_int(statement, 0);
			finalElem.gfxId = gfx.id;
			
			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 2));
			finalElem.name = name;
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete elems; elems = NULL;

	return gfxId;
}

short DBManager::getPigeon() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("Pigeon");
	int id = -1;
	
	if (elems->size() > 0) {
		sprintf(query, "select id, gfxId, name from Pigeon where id = %d", elems->at(rand() % elems->size()));

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			sqlite3_step(statement);

			pigeon.id = (short) sqlite3_column_int(statement, 0);
			pigeon.gfxId = (short) sqlite3_column_int(statement, 1);

			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 2));
			pigeon.name = name;

			// Como sólo se va a usar uno, se encarga él mismo de guardar el gráfico
			gfx_t gfx;
			gfx.id = pigeon.gfxId;
			gfx.path = getPath("Gfx", pigeon.gfxId);
			graphics->push_back(gfx);

			id = pigeon.id;
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete elems; elems = NULL;

	return id;
}

short DBManager::getKeyObj() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("KeyObj");
	int id = -1;
	
	if (elems->size() > 0) {
		sprintf(query, "select id, gfxId, name from KeyObj where id = %d", elems->at(rand() % elems->size()));

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			sqlite3_step(statement);

			keyObj.id = (short) sqlite3_column_int(statement, 0);
			keyObj.gfxId = (short) sqlite3_column_int(statement, 1);

			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 2));
			keyObj.name = name;

			// Como sólo se va a usar uno, se encarga él mismo de guardar el gráfico
			gfx_t gfx;
			gfx.id = keyObj.gfxId;
			gfx.path = getPath("Gfx", keyObj.gfxId);
			graphics->push_back(gfx);

			id = keyObj.id;
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete elems; elems = NULL;

	return id;
}

bool DBManager::belongsTo(int id, vector<short>* elems) {
	bool b = false;
	vector<short>::iterator it = elems->begin();
	while (!b && it < elems->end()) {
		b = (id == *it);
		it++;
	}
	return b;
}

void DBManager::getDoors() {
	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;
	vector<short>* elems = get_valid_elems("Door");
	int n_doors = elems->size();

	if (n_doors > 0) {
		sprintf(query, "select id, pathG from Door where type = 0");

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			int id = -1;
			while (!belongsTo(id, elems) && SQLITE_ROW == sqlite3_step(statement))
				id = (short) sqlite3_column_int(statement, 0);

			char aux[MAX_STR_LENGTH];
			sprintf(aux, "%s", sqlite3_column_text(statement, 1));
			doorPath = aux;
		}
		else db_status = false;

		sprintf(query, "select id, pathG from Door where type = 1");

		if (db_status && SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			int id = -1;
			while (!belongsTo(id, elems) && SQLITE_ROW == sqlite3_step(statement))
				id = (short) sqlite3_column_int(statement, 0);

			char aux[MAX_STR_LENGTH];
			sprintf(aux, "%s", sqlite3_column_text(statement, 1));
			bossDoorPath = aux;
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete elems; elems = NULL;
}

void DBManager::save() {
	char command[MAX_STR_LENGTH];
	sprintf(command, "mkdir .\\%s", DATA_PATH);
	if (system(NULL))
		system(command);

	savePlayers();
	saveEnemies();
	saveNPCs();
	saveTools();
	saveItems();
	savePowUps();
	saveBosses();
	saveBlocks();
	savePigeon();
	saveKeyObj();
	saveFinalElem(),
	savePuzzleElems();

	// Creamos el archivo de Log
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sLog", DATA_PATH);
	FILE* file =fopen(file_path, "wb");
	fclose(file);

	// Estos métodos además se encargan de copiar los respectivos archivos a la carpeta del juego
	saveGfx();
	saveEssentialElems();
	saveTileSets();
	saveSfx();
	saveDoors();

	sprintf(command, "del \".\\%sLog\"", DATA_PATH);
	if (system(NULL))
		system(command);
}

void DBManager::savePlayers() {
	// Abrimos el archivo de Players de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sPlayers", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveEnemies() {
	// Abrimos el archivo de enemigos de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sEnemies", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
	// Escribimos el número de enemigos que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = enemies->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los enemigos
	delete buffer; buffer = new short[6];
	for (set<enemy_t>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->hp;
		buffer[3] = it->atk;
		buffer[4] = it->df;
		buffer[5] = it->name.size();
		fwrite(buffer, sizeof(short), 6, file);
		fwrite(it->name.c_str(), sizeof(char), it->name.size(), file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete [] buffer; buffer = NULL;
	fclose(file);

	// Copiamos los componentes de los enemigos
	copyEnemyComponents();
}

void DBManager::saveNPCs() {
	// Abrimos el archivo de NPCs de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sNPCs", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
	// Escribimos el número de NPCs (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = npcs->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los npcs
	delete buffer; buffer = new short[5];
	for (set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->sfxId;
		buffer[3] = it->name.size();
		buffer[4] = it->movComp;
		fwrite(buffer, sizeof(short), 5, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[3], file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveTools() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sTools", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

	short* buffer = new short[1];
	buffer[0] = tools->size();
	fwrite(buffer, sizeof(short), 1, file);
	
	delete buffer; buffer = new short[8];
	for (set<tool_t>::iterator it = tools->begin(); it != tools->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->dmgType;
		buffer[3] = it->gfxAmmo;
		buffer[4] = it->maxAmmo;
		buffer[5] = it->strength;
		buffer[6] = it->type;
		buffer[7] = it->name.size();
		fwrite(buffer, sizeof(short), 8, file);
		fwrite(it->name.c_str(), sizeof(char), buffer[7], file);
	}
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveItems() {
	// Abrimos el archivo de items de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sItems", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::savePowUps() {
	// Abrimos el archivo de powUps de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sPowUps", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveBosses() {
	// Abrimos el archivo de Bosses de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sBosses", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveBlocks() {
	// Abrimos el archivo de Blocks de la BDJ
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sBlocks", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
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
	delete [] buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveDoors() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sDoors", DATA_PATH);
	FILE* file = fopen(file_path, "wb");
	
	short buffer[2];
	buffer[0] = doorPath.size();
	buffer[1] = bossDoorPath.size();
	
	fwrite(buffer, sizeof(short), 2, file);
	fwrite(doorPath.c_str(), sizeof(char), buffer[0], file);
	fwrite(doorPath.c_str(), sizeof(char), buffer[1], file);

	fclose(file);

	copyDoors();
}

void DBManager::savePigeon() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sPigeon", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

	short buffer[3];
	buffer[0] = pigeon.id;
	buffer[1] = pigeon.gfxId;
	buffer[2] = pigeon.name.size();
	fwrite(buffer, sizeof(short), 3, file);
	fwrite(pigeon.name.c_str(), sizeof(char), buffer[2], file);

	fclose(file);
}

void DBManager::saveKeyObj() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sKeyObj", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

	short buffer[3];
	buffer[0] = keyObj.id;
	buffer[1] = keyObj.gfxId;
	buffer[2] = keyObj.name.size();
	fwrite(buffer, sizeof(short), 3, file);
	fwrite(keyObj.name.c_str(), sizeof(char), buffer[2], file);

	fclose(file);
}

void DBManager::saveFinalElem() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sFinalElem", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

	short buffer[3];
	buffer[0] = finalElem.id;
	buffer[1] = finalElem.gfxId;
	buffer[2] = finalElem.name.size();
	fwrite(buffer, sizeof(short), 3, file);
	fwrite(finalElem.name.c_str(), sizeof(char), buffer[2], file);

	fclose(file);
}

void DBManager::savePuzzleElems() {
	char file_path[MAX_STR_LENGTH];
	sprintf(file_path, ".\\%sPuzzleElems", DATA_PATH);
	FILE* file = fopen(file_path, "wb");

	short n_puzzleElemsBuf[1];
	n_puzzleElemsBuf[0] = puzzle_elems->size();
	fwrite(n_puzzleElemsBuf, sizeof(short), 1, file);

	short buffer[3];
	for (set<puzzle_elem_t>::iterator it = puzzle_elems->begin(); it != puzzle_elems->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->type;
		buffer[2] = it->gfxId;
		fwrite(buffer, sizeof(short), 3, file);
	}

	fclose(file);
}

void DBManager::copyDoors() {
	if (system(NULL)) {						// Comprobamos que el sistema está disponible
		char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
		sprintf(command, "copy \"%s.png\" \".\\%s%s\" >> \".\\%sLog\"", doorPath.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
		system(command);	// Copiamos el .png
		sprintf(command, "copy \"%s.cfg\" \".\\%s%s\" >> \".\\%sLog\"", doorPath.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
		system(command);	// Copiamos el .cfg
		
		sprintf(command, "copy \"%s.png\" \".\\%s%s\" >> \".\\%sLog\"", bossDoorPath.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
		system(command);	// Copiamos el .png
		sprintf(command, "copy \"%s.cfg\" \".\\%s%s\" >> \".\\%sLog\"", bossDoorPath.c_str(), DATA_PATH, RES_PATH, DATA_PATH);
		system(command);	// Copiamos el .cfg

		delete command; command = NULL;	// Liberamos la memoria
	}
}