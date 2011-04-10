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
	items = new set<item_t>();
	powUps = new set<item_t>();
	exchange = new set<exchange_t>();
	bosses = new set<boss_t>();
	blocks = new set<block_t>();
	graphics = new vector<gfx_t>();
	sounds = new vector<sfx_t>();

	last_exchange = -1;		// Al principio la cadena de intercambio está vacía.
}

DBManager::~DBManager() {
	// Al terminar la generación, debemos volcar todos los datos de la "cache" en la BDJ y copiar los recursos físicos
	// (gráficos, sonidos) a la carpeta de juego (habrá que hacer la consulta apropiada y las llamadas al sistema que se requieran.
	save();
	
	// Liberamos la memoria de las estructuras de datos empleadas

	delete enemies; enemies = NULL;
	delete npcs; npcs = NULL;
	delete items; items = NULL;
	delete powUps; powUps = NULL;
	delete exchange; exchange = NULL;
	delete bosses; bosses = NULL;
	delete blocks; blocks = NULL;
	delete graphics; graphics = NULL;
	delete sounds; sounds = NULL;

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

char* DBManager::getPath(char* table, short id) {
	sqlite3_stmt* statement;
	char* query = new char[MAX_STR_LENGTH];
	char* path = NULL;	// String a devolver
	
	sprintf(query, "select path from %s where id = %d", table, id);

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


void DBManager::saveGfx() {
	int c = 0;							// Contador de los gráficos del juego (para dar los nuevos ids)

	// Miramos los gráficos de los enemigos
	for (set<enemy_t>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		gfx_t gfx;
		short id = it->gfxId;		// Recuperamos el identificador del gráfico que usa
		gfx.id = c;						// Le asignamos un nuevo id dentro de la BDJ
		gfx.path = getPath("Gfx", id);	// Consultamos el path del archivo de la tabla de gráficos
		graphics->push_back(gfx);		// Añadimos el gráfico al vector de gráficos de la BDJ
		c++;							// Aumentamos el contador de gráficos
	}
	// Miramos los gráficos de los NPCs
	for (set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); it++) {
		gfx_t gfx;
		short id = it->gfxId;		// Recuperamos el identificador del gráfico que usa
		gfx.id = c;						// Le asignamos un nuevo id dentro de la BDJ
		gfx.path = getPath("Gfx", id);	// Consultamos el path del archivo de la tabla de gráficos
		graphics->push_back(gfx);		// Añadimos el gráfico al vector de gráficos de la BDJ
		c++;							// Aumentamos el contador de gráficos
	}
	// Miramos los gráficos de los power ups
	for (set<item_t>::iterator it = powUps->begin(); it != powUps->end(); it++) {
		gfx_t gfx;
		short id = it->gfxId;
		gfx.id = c;
		gfx.path = getPath("Gfx", id);
		graphics->push_back(gfx);
		c++;
	}

	// Miramos los gráficos de los ítems
	for (set<item_t>::iterator it = items->begin(); it != items->end(); it++) {
		gfx_t gfx;
		short id = it->gfxId;
		gfx.id = c;
		gfx.path = getPath("Gfx", id);
		graphics->push_back(gfx);
		c++;
	}

	// Miramos los gráficos de los objetos de intercambio
	for (set<exchange_t>::iterator it = exchange->begin(); it != exchange->end(); it++) {
		gfx_t gfx;
		short id = it->gfxId;
		gfx.id = c;
		gfx.path = getPath("Gfx", id);
		graphics->push_back(gfx);
		c++;
	}

	// Puede que falten más gráficos por guardar

	// Copiamos los gráficos al directorio correspondiente
	copyGfx();
}

void DBManager::copyGfx() {
	vector<gfx_t>::iterator it;		// Iterador del vector de gráficos
	for (it = graphics->begin(); it < graphics->end(); it++) {	// Recorremos todo el vector de gráficos que hemos preparado previamente
		char* path = (char*) it->path.c_str();	// Obtenemos el path del gráfico
		if (system(NULL)) {						// Comprobamos que el sistema está disponible
			char* command = new char[MAX_STR_LENGTH];	// String con la orden de copia
			sprintf(command, "copy \"%s\" \".\\..\\..\\Roger en Katzaland\\Gfx\"", path);
			system(command);	// Mandamos ejecutar la orden de copia
			delete command; command = NULL;	// Liberamos la memoria
		}
	}
}


void DBManager::saveSfx(){
	FILE* f;
	char* buffer;
	sfx_t aux;
	// recorremos la lista de npcs
	for(set<npc_t>::iterator it = npcs->begin(); it!=npcs->end(); ++it){
		buffer = getPath("sfx", it->sfxId); // obtiene el path del sonido

		// si falla acaba
		if (buffer == NULL) return; 

		// añade el sfx_t a la lista 
		aux.id = it->sfxId;
		aux.path = buffer;
		sounds->push_back(aux);
	}
}

void DBManager::copySfx(){
	char dest[MAX_STR_LENGTH];
	char command[MAX_STR_LENGTH];

	for(vector<sfx_t>::iterator it = sounds->begin(); it!=sounds->end(); ++it){
		if(system(0)){
				sprintf(command, "copy %s \\Carpeta Juego\\sfx", it->path);
				system(command);
		}
	}
}

short DBManager::getEnemy(string zone, string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_enemies = 0;						// Número de enemigos que aparecen en la consulta
	enemy_t e;								// Struct con los datos del enemigo seleccionado
	short id = 0;							// Id del enemigo, valor a devolver

	// Seleccionamos los enemigos que pertenezcan a la zona especificada
	sprintf(query, "select id, gfxId, hp, str, df, name from Enemies, EnemyZoneTags ezt, EnemyThemeTags ett where id = ett.enemyId and id = ezt.enemyId and ett.tag = '%s' and ezt.tag = '%s'", theme.c_str(),zone.c_str());
	// Además habría que consultar el path del archivo de configuración de los componentes

	if (db_status) {
		// Vemos la cantidad de enemigos que tenemos disponibles
		n_enemies = rowNumber(query);
		// Si la consulta no ha producido ningún enemigo válido, hemos terminado
		if (n_enemies <= 0){delete query; query = NULL; return -1;};
		// Si hay 1 o más enemigos disponibles, elegimos uno al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int enemy = rand() % n_enemies;
			// Avanzamos hasta la fila del enemigo que queremos
			for (int i = 0; i <= enemy; i++) sqlite3_step(statement);

			// De esa fila consultamos el id del enemigo, el id del gráfico, los atributos del enemigo y su nombre
			e.id = (short) sqlite3_column_int(statement, 0);
			e.gfxId = (short) sqlite3_column_int(statement, 1);
			e.hp = (short) sqlite3_column_int(statement, 2);
			e.atk = (short) sqlite3_column_int(statement, 3);
			e.df = (short) sqlite3_column_int(statement, 4);

			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 5));
			e.name = name;
			// Además, habría que coger el confPath

			// enemies es un conjunto, si e ya está contenido en él no hace nada
			enemies->insert(e);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);

		// DEBUG
		// printf("id: %d, gfxId: %d, hp: %d, atk: %d, df: %d, name: %s\n", e.id, e.gfxId, e.hp, e.atk, e.df, e.name.c_str());
	}
	delete query; query = NULL;
	return e.id;
}

short DBManager::getPowUp(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_powerUp = 0;						// Número de items que aparecen en la consulta
	item_t pu;								// Struct con los datos del power up 

	// Seleccionamos los power ups que pertenezcan del tema indicado
	sprintf(query, "select id, name, type, effect, gfxId from PowUps, PowerUpThemeTags where id = pwUpId and tag = '%s'", theme.c_str());
	
	if (db_status) {
		// Vemos la cantidad de power up que tenemos disponibles
		n_powerUp = rowNumber(query);
		// Si la consulta no ha producido ningún item válido, acaba
		if (n_powerUp <= 0){delete query; query = NULL; return -1;};
		// Si hay 1 o más power ups disponibles, elegimos uno al azar y recogemos su información
		if (SQLITE_OK == sqlite3_prepare(db, query, 255, &statement, NULL)) {
			int item = rand() % n_powerUp;
			// Avanzamos hasta la fila del item que queremos
			for (int i = 0; i <= item; i++) sqlite3_step(statement);

			// De esa fila consultamos el id del power up, el id del gráfico, los atributos del power up y su nombre
			pu.id = (short) sqlite3_column_int(statement, 0);
			pu.type = (short) sqlite3_column_text(statement, 2);
			pu.effect = (short) sqlite3_column_int(statement,3);
			pu.gfxId = (short) sqlite3_column_int(statement,4);
			
			char name[MAX_STR_LENGTH];
			sprintf(name, "%s", sqlite3_column_text(statement, 5));
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

zone_t* DBManager::getZone(string theme) {
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
			// De esa fila consultamos nombre id del gráfico, id del sonido(?).
			sprintf(aux, "%s", sqlite3_column_text(statement, 0));
			zone.name = aux;
			
			zone.gfxId = sqlite3_column_int(statement, 1);
			zone.sfxId = sqlite3_column_int(statement, 2);
			
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
	}
	delete query; query = NULL;
	return &zone;
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

block_t DBManager::getBlock(string theme, string zone, short tool) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_block = 0;						// Número de bloqueos que aparecen en la consulta
	block_t e;								// Struct con los datos del objeto de intercambio seleccionado, a devolver

	sprintf(query, "select id, type, gfxId, dmgType from Blocks, BlocksThemeTags btt, BlocksZoneTags bzt where id = btt.blockId and id = bzt.blockId and btt.themeTag = '%s' and bzt.zoneTag = '%s'", theme.c_str(), zone.c_str());

	if (db_status) {
		n_block = rowNumber(query);

		if (n_block <= 0){delete query; query = NULL; return e;};

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
	return e;
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

			// DEBUG
			printf("id: %d, gfxId: %d, sfxId: %d, name: %s\n", npc.id, npc.gfxId, npc.sfxId, npc.name.c_str());
		}
	}
	delete query; query = NULL;
	return npc.id;
}

/* Devuelve el id de un item dado un tema */
short DBManager::getItem(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_items = 0;						// Número de Items que aparecen en la consulta
	item_t i;								// Struct con los datos del item seleccionado
	short id = 0;							// Id del item, valor a devolver

	// Seleccionamos los items que pertenezcan a la zona especificada
	sprintf(query, "select id, type, effect, gfxId from Items, ItemThemeTags where id = itemId and tag = '%s'", theme.c_str());

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
			i.type = (short) sqlite3_column_int(statement, 1);
			i.effect = (short) sqlite3_column_int(statement, 2);
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

		// DEBUG
		printf("id: %d, type: %d, effect:%d, gfxId: %d\n", i.id, i.type, i.effect, i.gfxId);
	}
	delete query; query = NULL;
	return i.id;
}

void DBManager::save() {
	saveEnemies();
	saveNPCs();
	saveItems();
	savePowUps();
	saveExchange();
	saveBosses();
	saveBlocks();

	saveGfx();
	saveSfx();
}

void DBManager::saveEnemies() {
	// Abrimos el archivo de enemigos de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Enemies", "w");
	// Escribimos el número de enemigos que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = enemies->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los enemigos
	delete buffer; buffer = new short[5];
	for (set<enemy_t>::iterator it = enemies->begin(); it != enemies->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->hp;
		buffer[3] = it->atk;
		buffer[4] = it->df;
		fwrite(buffer, sizeof(buffer), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
		fwrite(it->confPath.c_str(), sizeof(it->confPath.c_str()), 1, file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveNPCs() {
	// Abrimos el archivo de NPCs de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Enemies", "w");
	// Escribimos el número de NPCs (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = npcs->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los npcs
	delete buffer; buffer = new short[3];
	for (set<npc_t>::iterator it = npcs->begin(); it != npcs->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->sfxId;
		fwrite(buffer, sizeof(buffer), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
		fwrite(it->confPath.c_str(), sizeof(it->confPath.c_str()), 1, file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveItems() {
	// Abrimos el archivo de items de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Items", "w");
	// Escribimos el número de items que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = items->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los items
	delete buffer; buffer = new short[4];
	for (set<item_t>::iterator it = items->begin(); it != items->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->type;
		buffer[2] = it->effect;
		buffer[3] = it->gfxId;
		fwrite(buffer, sizeof(buffer), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::savePowUps() {
	// Abrimos el archivo de powUps de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\PowUps", "w");
	// Escribimos el número de porUps que aparecerán en el juego
	short* buffer = new short[1];		
	buffer[0] = powUps->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los power ups
	delete buffer; buffer = new short[4];
	for (set<item_t>::iterator it = powUps->begin(); it != powUps->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->type;
		buffer[2] = it->effect;
		buffer[3] = it->gfxId;
		fwrite(buffer, sizeof(buffer), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
	}
	// Liberamos los buffers utilizados y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveExchange() {
	// Abrimos el archivo de intercambios de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Exchange", "w");
	// Escribimos el número de intercambios (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = exchange->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los intercambios
	delete buffer; buffer = new short[3];
	for (set<exchange_t>::iterator it = exchange->begin(); it != exchange->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->gfxId;
		buffer[2] = it->previous;

		fwrite(buffer, sizeof(buffer), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);}

void DBManager::saveBosses() {
	// Abrimos el archivo de Bosses de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Bosses", "w");
	// Escribimos el número de Bosses (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = bosses->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los bosses
	delete buffer; buffer = new short[1];
	for (set<boss_t>::iterator it = bosses->begin(); it != bosses->end(); it++) {
		buffer[0] = it->id;
		/* Más */
		fwrite(buffer, sizeof(buffer), 1, file);
		fwrite(it->name.c_str(), sizeof(it->name.c_str()), 1, file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DBManager::saveBlocks() {
	// Abrimos el archivo de Blocks de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Blocks", "w");
	// Escribimos el número de Blocks (distintos) que aparecen en el juego
	short* buffer = new short[1];
	buffer[0] = blocks->size();
	fwrite(buffer, sizeof(buffer), 1, file);
	// Escribimos los datos de los blocks
	delete buffer; buffer = new short[4];
	for (set<block_t>::iterator it = blocks->begin(); it != blocks->end(); it++) {
		buffer[0] = it->id;
		buffer[1] = it->type;
		buffer[2] = it->gfxId;
		buffer[3] = it->dmgType;	
		fwrite(buffer, sizeof(buffer), 1, file);
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}