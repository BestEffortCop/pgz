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
	essential_elems = new vector<gfx_t>();
	worldGens = new set<worldGen_t>;
	players = new set<player_t>;	

	tags = new vector<string>();

	last_exchange = -1;		// Al principio la cadena de intercambio está vacía.
	gather_essential_elements();	// Obtenemos de la BDD los elementos comunes a todos los juegos
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
	delete worldGens; worldGens = NULL;
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

char* DBManager::getPath(char* table, short id) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	char* path = NULL;	// String a devolver
	
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

	sprintf(query, "select effect from PowUps where id = %d", id);

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

void DBManager::getKey(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	
	sprintf(query, "select id, power, effect, gfxId, name from Items, ItemThemeTags where effect = %d and id = itemId and tag = '%s'", KEY, theme.c_str());

	if (db_status) {
		// Comprobamos que haya una llave disponible
		if (rowNumber(query) <= 0) { delete query; query = NULL; }
		else {
			if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
				// Obtenemos la fila de la llave que queremos
				if (SQLITE_ROW == sqlite3_step(statement)) {
					// Guardamos la llave en el conjunto de items que aparecen en el juego
					item_t i;
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
			}
			else db_status = false;
		}
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
}

void DBManager::getBossKey(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	
	sprintf(query, "select id, power, effect, gfxId, name from Items, ItemThemeTags where effect = %d and id = itemId and tag = '%s'", BOSSKEY, theme.c_str());

	if (db_status) {
		// Comprobamos que haya una llave disponible
		if (rowNumber(query) <= 0) { delete query; query = NULL; }
		else {
			if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
				// Obtenemos la fila de la llave que queremos
				if (SQLITE_ROW == sqlite3_step(statement)) {
					// Guardamos la llave en el conjunto de items que aparecen en el juego
					item_t i;
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
			}
			else db_status = false;
		}
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
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

	// Puede que falten más gráficos por guardar

	// Abrimos el archivo de gráficos de la BDJ
	FILE* file = fopen("./data/GfxIndex", "w");
	// Escribimos el número de sonidos (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = graphics->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los sonidos
	for (vector<gfx_t>::iterator it = graphics->begin(); it < graphics->end(); it++) {
		buffer[0] = it->id;
		fwrite(buffer, sizeof(short), 1, file);
		buffer[0] = sizeof(it->path.c_str());
		fwrite(buffer, sizeof(short), 1, file); // Escribimos el tamaño del string del path
		fwrite(it->path.c_str(), sizeof(it->path.c_str()), 1, file); // Escribimos el path
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);

	// Copiamos los gráficos al directorio correspondiente
	copyGfx();
}

void DBManager::copyGfx() {
	for (vector<gfx_t>::iterator it = graphics->begin(); it < graphics->end(); it++) {	// Recorremos todo el vector de gráficos que hemos preparado previamente
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
			sprintf(command, "copy \"%s.png\" \".data/Gfx\"", it->path);
			system(command);	// Copiamos el .png
			sprintf(command, "copy \"%s.cfg\" \".data/Gfx\"", it->path);
			system(command);	// Copiamos el .cfg
			delete command; command = NULL;	// Liberamos la memoria
		}
	}

	// Y además, copiamos los gráficos de los elementos comunes a todos los juegos
	for (vector<gfx_t>::iterator it = essential_elems->begin(); it < essential_elems->end(); it++) {
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
			sprintf(command, "copy \"%s.png\" \".data/Gfx\"", it->path);
			system(command);	// Copiamos el .png
			sprintf(command, "copy \"%s.cfg\" \".data/Gfx\"", it->path);
			system(command);	// Copiamos el .cfg
			delete command; command = NULL;	// Liberamos la memoria
		}
	}
}


void DBManager::saveSfx(){
	char* boffer;
	sfx_t aux;
	// recorremos la lista de npcs
	for(set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); ++it){
		boffer = getPath("sfx", it->sfxId); // obtiene el path del sonido

		if (boffer != NULL) {
			// añade el sfx_t al vector de sonidos
			aux.id = it->sfxId;
			aux.path = boffer;
			sounds->push_back(aux);
		}
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
		buffer[1] = sizeof(it->path.c_str());
		fwrite(buffer, sizeof(short), 2, file);
		fwrite(it->path.c_str(), sizeof(it->path.c_str()), 1, file);
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
	char* query = new char[MAX_STR_LENGTH];
	sqlite3_stmt* statement;

	sprintf(query, "select id, pathG from EssentialElems");

	gfx_t g;
	char path[MAX_STR_LENGTH];
	if (db_status) {
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement)) {
				g.id = (short) sqlite3_column_int(statement, 0);
				sprintf(path, "%s", sqlite3_column_text(statement, 1));
				g.path = path;

				essential_elems->push_back(g);
			}
		}
		else db_status = false;

		sqlite3_finalize(statement);
	}

	delete query; query = NULL;
}

void DBManager::read_tags() {
	// Según lo escriba Decidator
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
		sprintf(query, "select tag from %sThemeTags where %sId = %d", elem, i);
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
		}
		else db_status = false;
	}

	return elems;
}

short DBManager::getPlayer(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_player = 0;						// Número de items que aparecen en la consulta
	player_t p;								// Struct con los datos del power up 

	sprintf(query, "select id, name, gfxId, hp, mp, atk, def from Players, PlayerThemeTags where id = playerId and tag = '%s'", theme.c_str());
	
	if (db_status) {
		n_player = rowNumber(query);
		if (n_player <= 0) { delete query; query = NULL; return -1; };
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int item = rand() % n_player;
			// Avanzamos hasta la fila del item que queremos
			for (int i = 0; i <= item; i++) sqlite3_step(statement);


			p.id = (short) sqlite3_column_int(statement, 0);
			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 1));
			p.name = name;
			p.gfxId = (short) sqlite3_column_int(statement, 2);
			p.hp = (short) sqlite3_column_int(statement, 3);
			p.mp = (short) sqlite3_column_int(statement, 4);
			p.atk = (short) sqlite3_column_int(statement, 5);
			p.def = (short) sqlite3_column_int(statement, 6);

			players->insert(p);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);

	}
	delete query; query = NULL;
	return p.id;
}

short DBManager::getEnemy(string zone) {
	char query[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;	// Puntero a una sentencia SQL, preparada para tratar
	vector<short>* elems = get_valid_elems("Enemy");	// Ids de los enemigos que nos valen
	int n_enemies = elems->size();						// Número de enemigos que aparecen en la consulta
	short id = -1;	// Id del enemigo a devolver

	if (n_enemies >= 0) {
		enemy_t e;								// Struct con los datos del enemigo seleccionado
		id = elems->at(rand() % n_enemies);

		sprintf(query, "select id, gfxId, hp, str, df, name from Enemy where id = %d", id);
		
		if (db_status) {
			if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
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
	}

	return id;
}

short DBManager::getPowUp(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_powerUp = 0;						// Número de items que aparecen en la consulta
	item_t pu;								// Struct con los datos del power up 

	// Seleccionamos los power ups que pertenezcan del tema indicado
	sprintf(query, "select id, power, effect, gfxId, name from PowUps, PowUpThemeTags where id = powUpId and tag = '%s'", theme.c_str());
	
	if (db_status) {
		// Vemos la cantidad de power up que tenemos disponibles
		n_powerUp = rowNumber(query);
		// Si la consulta no ha producido ningún item válido, acaba
		if (n_powerUp <= 0) { delete query; query = NULL; return -1; };
		// Si hay 1 o más power ups disponibles, elegimos uno al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int item = rand() % n_powerUp;
			// Avanzamos hasta la fila del item que queremos
			for (int i = 0; i <= item; i++) sqlite3_step(statement);

			// De esa fila consultamos el id del power up, el id del gráfico, los atributos del power up y su nombre
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
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);

	}
	delete query; query = NULL;
	return pu.id;
}

short DBManager::getZone(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_zones = 0;						// Número de zonas que aparecen en la consulta
	zone_t zone;							// informacion de la zona			

	// Seleccionamos los enemigos que pertenezcan a la zona especificada
	sprintf(query, "select name,gfxId,SfxId from Zone,zoneThemeTags where id = zoneId and tag = '%s'", theme.c_str());

	if (db_status) {
		// Vemos la cantidad de zonas disponibles
		n_zones = rowNumber(query);
		// Si la consulta no ha producido ninguna zona, acaba
		if (n_zones <= 0){delete query; query = NULL; return NULL;};
		// Si hay 1 o más zonas disponibles, elegimos una al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int zn = rand() % n_zones;
			// Avanzamos hasta la fila de la zona que queremos
			for (int i = 0; i <= zn; i++) sqlite3_step(statement);

			char aux[MAX_STR_LENGTH];	
			zone.id = sqlite3_column_int(statement, 0);
			// De esa fila consultamos nombre id del gráfico, id del sonido(?).
			sprintf(aux, "%s", sqlite3_column_text(statement, 1));
			zone.name = aux;
			
			zone.gfxId = sqlite3_column_int(statement, 2);
			zone.sfxId = sqlite3_column_int(statement, 3);
			
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return zone.id;
}

short DBManager::getExchange(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_exchange = 0;						// Número de objetos de intercambio que aparecen en la consulta
	exchange_t e;							// Struct con los datos del objeto de intercambio seleccionado
	short id = 0;							// Id del objeto, valor a devolver

	// Seleccionamos los objetos de intercambio que pertenezcan a la temática especificada
	sprintf(query, "select id, gfxId, name from Exchange, ExchangeThemeTags where id = exchangeId and tag = '%s'", theme.c_str());

	if (db_status) {
		// Vemos la cantidad de objetos de intercambio que tenemos disponibles
		n_exchange = rowNumber(query);
		// Si la consulta no ha producido ningún objeto válido, hemos terminado
		if (n_exchange <= 0){delete query; query = NULL; return NULL;};
		// Si hay 1 o más objetos disponibles, elegimos uno al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int aux = rand() % n_exchange;
			// Avanzamos hasta la fila del objeto que queremos
			for (int i = 0; i <= aux; i++) sqlite3_step(statement);

			// Consultamos id, id del gráfico y el nombre del objeto de intercambio
			e.id = (short) sqlite3_column_int(statement, 0);
			e.gfxId = (short) sqlite3_column_int(statement, 1);

			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 2));
			e.name = name;

			// Le decimos cuál es el objeto anterior en la cadena y este lo colocamos como el último
			e.previous = last_exchange;
			last_exchange = e.id;

			// exchange es un conjunto, si e ya está contenido en él no hace nada
			exchange->insert(e);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return e.id;
}

short DBManager::getBlock(string theme, string zone, short tool) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_block = 0;						// Número de bloqueos que aparecen en la consulta
	block_t e;								// Struct con los datos del objeto de intercambio seleccionado, a devolver

	sprintf(query, "select id, type, gfxId, dmgType from Blocks, BlocksThemeTags btt, BlocksZoneTags bzt where id = btt.blockId and id = bzt.blockId and btt.themeTag = '%s' and bzt.zoneTag = '%s'", theme.c_str(), zone.c_str());

	if (db_status) {
		n_block = rowNumber(query);

		if (n_block <= 0){delete query; query = NULL; return NULL;};

		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			int aux = rand() % n_block;
			for (int i = 0; i <= aux; i++) sqlite3_step(statement);

			e.id = (short) sqlite3_column_int(statement, 0);
			e.type = (short) sqlite3_column_int(statement, 1);
			e.gfxId = (short) sqlite3_column_int(statement, 2);
			e.dmgType = (short) sqlite3_column_int(statement, 3);

			blocks->insert(e);

			sqlite3_finalize(statement);
		}
	}
	delete query; query = NULL;
	return e.id;
}

/* Devuelve el id de un NPC dada una zona y un tema */
short DBManager::getNPC(string zone, string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_npcs = 0;							// Número de NPCs que aparecen en la consulta
	npc_t npc;								// Struct con los datos del NPC seleccionado
	short id = 0;							// Id del NPC, valor a devolver

	// Seleccionamos los NPCs que pertenezcan a la zona especificada
	sprintf(query, "select id, gfxId, sfxId, name from NPCs, NPCZoneTags, NPCThemeTags where id = NPCZoneTags.npcId and id = NPCThemeTags.npcId and NPCZoneTags.tag = '%s' and NPCThemeTags.tag = '%s'", zone.c_str(), theme.c_str());
	// Además habría que consultar el path del archivo de configuración de los componentes

	if (db_status) {
		// Vemos la cantidad de NPCs que tenemos disponibles
		n_npcs = rowNumber(query);
		// Si la consulta no ha producido ningún NPC válido, hemos terminado
		if (n_npcs != 0){
			// Si hay 1 o más NPCs disponibles, elegimos uno al azar y recogemos su información
			if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
				int npcInt = rand() % n_npcs;
				// Avanzamos hasta la fila del NPC que queremos
				for (int i = 0; i <= npcInt; i++) sqlite3_step(statement);

				// De esa fila consultamos el id del NPC, el id del gráfico, los atributos del NPC y su nombre
				npc.id = (short) sqlite3_column_int(statement, 0);
				npc.gfxId = (short) sqlite3_column_int(statement, 1);
				npc.sfxId = (short) sqlite3_column_int(statement, 2);

				char name[MAX_STR_LENGTH];
				sprintf(name, "%s", sqlite3_column_text(statement, 3));
				npc.name = name;
				// Además, habría que coger el confPath

				// npcs es un conjunto, si npc ya está contenido en él no hace nada
				npcs->insert(npc);
			}
			else db_status = false;
		
			// Finalizamos la ejecución de la consulta
			sqlite3_finalize(statement);
		}
	}
	delete query; query = NULL;
	return npc.id;
}

short DBManager::getTool(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_tools = 0;						// Número de Tools que aparecen en la consulta
	tool_t t;								// Struct con los datos de la herramienta seleccionada
	short id = 0;							// Id de la herramienta a devolver

	// Seleccionamos las tools que pertenezcan a la temática especificada
	sprintf(query, "select id, gfxId, dmgType, ammoType, maxAmmo, strength, name from Tools, ToolThemeTags where id = toolId and tag = '%s'", theme.c_str());

	if (db_status) {
		// Vemos la cantidad de herramientas que tenemos disponibles
		n_tools = rowNumber(query);
		// Si la consulta no ha producido ninguna herramienta válida, hemos terminado
		if (n_tools <= 0) { delete query; query = NULL; return -1; };
		// Si hay 1 o más items disponibles, elegimos uno al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int tool = rand() % n_tools;
			// Avanzamos hasta la fila del item que queremos
			for (int j = 0; j <= tool; j++) sqlite3_step(statement);

			// De esa fila consultamos el id de la herramienta, el id del gráfico y demás atributos
			t.id = (short) sqlite3_column_int(statement, 0);
			t.gfxId = (short) sqlite3_column_int(statement, 1);
			t.dmgType = (short) sqlite3_column_int(statement, 2);
			t.ammoType = (short) sqlite3_column_int(statement, 3);			
			t.maxAmmo = (short) sqlite3_column_int(statement, 4);
			t.strength = (short) sqlite3_column_int(statement, 5);

			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 6));
			t.name = name;

			// Añadimos la tool al conjunto de herramientas del juego
			tools->insert(t);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return t.id;
}

/* Devuelve el id de un item dado un tema */
short DBManager::getItem(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_items = 0;						// Número de Items que aparecen en la consulta
	item_t i;								// Struct con los datos del item seleccionado
	short id = 0;							// Id del item, valor a devolver

	// Seleccionamos los items que pertenezcan a la zona especificada
	sprintf(query, "select id, effect, power, gfxId, name from Items, ItemThemeTags where id = itemId and tag = '%s'", theme.c_str());

	if (db_status) {
		// Vemos la cantidad de items que tenemos disponibles
		n_items = rowNumber(query);
		// Si la consulta no ha producido ningún item válido, hemos terminado
		if (n_items <= 0){delete query; query = NULL; return -1;};
		// Si hay 1 o más items disponibles, elegimos uno al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int item = rand() % n_items;
			// Avanzamos hasta la fila del item que queremos
			for (int j = 0; j <= item; j++) sqlite3_step(statement);

			// De esa fila consultamos el id del item, el id del gráfico, los atributos del item y su nombre
			i.id = (short) sqlite3_column_int(statement, 0);
			i.effect = (short) sqlite3_column_int(statement, 1);
			i.power = (short) sqlite3_column_int(statement, 2);
			i.gfxId = (short) sqlite3_column_int(statement, 3);			

			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 4));
			i.name = name;

			// items es un conjunto, si i ya está contenido en él no hace nada
			items->insert(i);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return i.id;
}

short DBManager::getWorldGen(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_gen = 0;						// Número de zonas que aparecen en la consulta
	worldGen_t gen;							// informacion de la zona			

	// Seleccionamos los enemigos que pertenezcan a la zona especificada
	sprintf(query, "select id from WorldGenThemeTags where tag = '%s'", theme.c_str());

	if (db_status) {
		// Vemos la cantidad de zonas disponibles
		n_gen = rowNumber(query);
		// Si la consulta no ha producido ninguna zona, acaba
		if (n_gen <= 0){delete query; query = NULL; return NULL;};
		// Si hay 1 o más generadores disponibles, elegimos una al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int zn = rand() % n_gen;
			// Avanzamos hasta la fila del generador que queremos
			for (int i = 0; i <= zn; i++) sqlite3_step(statement);

			gen.id = (short) sqlite3_column_int(statement, 0);
			worldGens->insert(gen);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return gen.id;
}

/*short DBManager::getDungeonGen(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_gen = 0;						// Número de zonas que aparecen en la consulta
	dungeonGen_t gen;							// informacion de la zona			

	// Seleccionamos los enemigos que pertenezcan a la zona especificada
	sprintf(query, "select id from WorldGenThemeTags where tag = '%s'", theme.c_str());

	if (db_status) {
		// Vemos la cantidad de zonas disponibles
		n_gen = rowNumber(query);
		// Si la consulta no ha producido ninguna zona, acaba
		if (n_gen <= 0){delete query; query = NULL; return NULL;};
		// Si hay 1 o más generadores disponibles, elegimos una al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int zn = rand() % n_gen;
			// Avanzamos hasta la fila del generador que queremos
			for (int i = 0; i <= zn; i++) sqlite3_step(statement);

			gen.id = (short) sqlite3_column_int(statement, 0);
			dungeonGens->insert(gen);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return gen.id;
}*/

void DBManager::save() {
	savePlayers();
	saveEnemies();
	saveNPCs();
	saveTools();
	saveItems();
	savePowUps();
	saveExchange();
	saveBosses();
	saveBlocks();

	saveGfx();
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
		buffer[6] = sizeof(it->name.c_str());

		fwrite(buffer, sizeof(short), 7, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
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
		buffer[5] = sizeof(it->name.c_str());
		buffer[6] = sizeof(it->confPath.c_str());
		fwrite(buffer, sizeof(short), 7, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
		fwrite(it->confPath.c_str(), sizeof(it->confPath.c_str()), 1, file);
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
	delete buffer; buffer = new short[3];
	for (set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->sfxId;
		fwrite(buffer, sizeof(short), 3, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
		fwrite(it->confPath.c_str(), sizeof(it->confPath.c_str()), 1, file);
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
		buffer[6] = sizeof(it->name.c_str());
		fwrite(buffer, sizeof(short), 7, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
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
		buffer[4] = sizeof(it->name.c_str());
		fwrite(buffer, sizeof(short), 5, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
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
		buffer[4] = sizeof(it->name.c_str());
		fwrite(buffer, sizeof(short), 5, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
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
	delete buffer; buffer = new short[3];
	for (set<exchange_t>::iterator it = exchange->begin(); it != exchange->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->previous;
		fwrite(buffer, sizeof(short), 3, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);}

void DBManager::saveBosses() {
	// Abrimos el archivo de Bosses de la BDJ
	FILE* file = fopen("./data/Bosses", "w");
	// Escribimos el número de Bosses (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = bosses->size();
	fwrite(buffer, sizeof(short), 1, file);
	// Escribimos los datos de los bosses
	delete buffer; buffer = new short[1];
	for (set<boss_t>::iterator it = bosses->begin(); it != bosses->end(); it++) {
		buffer[0] = it->id;
		/* Más */
		fwrite(buffer, sizeof(short), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
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