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

	last_exchange = -1;		// Al principio la cadena de intercambio está vacía.
}

DBManager::~DBManager() {
	// Al terminar la generación, debemos volcar todos los datos de la "cache" en la BDJ y copiar los recursos físicos
	// (gráficos, sonidos) a la carpeta de juego (habrá que hacer la consulta apropiada y las llamadas al sistema que se requieran.
	saveToBDJ();	// Se supone que ya debe haber un archivo abierto por Decidator/GenWorld en el que se han escrito cosas necesarias (como la cantidad de piezas de corazón por corazón o la pantalla inicial del juego).
	
	// Liberamos la memoria de las estructuras de datos empleadas
	delete enemies; enemies = NULL;
	delete npcs; npcs = NULL;
	delete items; items = NULL;
	delete powUps; powUps = NULL;
	delete exchange; exchange = NULL;
	delete bosses; bosses = NULL;

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

short DBManager::getEnemy(string zone) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_enemies = 0;						// Número de enemigos que aparecen en la consulta
	enemy_t e;								// Struct con los datos del enemigo seleccionado
	short id = 0;							// Id del enemigo, valor a devolver

	// Seleccionamos los enemigos que pertenezcan a la zona especificada
	sprintf(query, "select id, gfxId, hp, str, df, name from Enemies, EnemyZoneTags where id = enemyId and tag = '%s'", zone.c_str());
	// Además habría que consultar el path del archivo de configuración de los componentes

	if (db_status) {
		// Vemos la cantidad de enemigos que tenemos disponibles
		n_enemies = rowNumber(query);
		// Si la consulta no ha producido ningún enemigo válido, hemos terminado
		if (n_enemies == 0) return -1;
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
		delete query; query = NULL;

		// DEBUG
		// printf("id: %d, gfxId: %d, hp: %d, atk: %d, df: %d, name: %s\n", e.id, e.gfxId, e.hp, e.atk, e.df, e.name.c_str());
	}
	return e.id;
}

short DBManager::getExchange(string theme) {
	return 0;
}

/* Devuelve el registro de un NPC dada una zona */
npc_t DBManager::getNPCbyZone(string zone) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_npcs = 0;							// Número de NPCs que aparecen en la consulta
	npc_t npc;								// Struct con los datos del NPC seleccionado
	short id = 0;							// Id del NPC, valor a devolver

	// Seleccionamos los NPCs que pertenezcan a la zona especificada
	sprintf(query, "select id, gfxId, sfxId, name from NPCs, NPCZoneTags where id = npcId and tag = '%s'", zone.c_str());
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
			delete query; query = NULL;

			// DEBUG
			printf("id: %d, gfxId: %d, sfxId: %d, name: %s\n", npc.id, npc.gfxId, npc.sfxId, npc.name.c_str());
		}
	}
	return npc;
}

/* Devuelve el registro de un NPC dado un tema */
npc_t DBManager::getNPCbyTheme(string theme) {
	char* query = new char[MAX_STR_LENGTH];	// String en el que vamos a escribir la consulta
	sqlite3_stmt* statement;				// Puntero a una sentencia SQL, preparada para tratar
	int n_npcs = 0;							// Número de NPCs que aparecen en la consulta
	npc_t npc;								// Struct con los datos del NPC seleccionado
	short id = 0;							// Id del NPC, valor a devolver

	// Seleccionamos los NPCs que pertenezcan a la zona especificada
	sprintf(query, "select id, gfxId, sfxId, name from NPCs, NPCThemeTags where id = npcId and tag = '%s'", theme.c_str());
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
			delete query; query = NULL;

			// DEBUG
			printf("id: %d, gfxId: %d, sfxId: %d, name: %s\n", npc.id, npc.gfxId, npc.sfxId, npc.name.c_str());
		}
	}
	return npc;
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
		if (n_items == 0) return -1;
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

			// items es un conjunto, si i ya está contenido en él no hace nada
			items->insert(i);
		}
		else db_status = false;
		
		// Finalizamos la ejecución de la consulta
		sqlite3_finalize(statement);
		delete query; query = NULL;

		// DEBUG
		printf("id: %d, type: %d, effect:%d, gfxId: %d\n", i.id, i.type, i.effect, i.gfxId);
	}
	return i.id;
}

void DBManager::saveToBDJ() {}