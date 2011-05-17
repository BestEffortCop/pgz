#include "DBAccess.h"

DBAccess::DBAccess() {
	if (sqlite3_open(DB_PATH, &db)) {
		fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	db_status = true;
}

DBAccess::~DBAccess() {
	sqlite3_close(db);
}

void DBAccess::obtain_data() {
	FILE* file = fopen("./dbdata", "w");

	char query[MAX_STR_LENGTH];
	sqlite3_stmt* statement;

	if (db_status) {
		// Players
		sprintf(query, "select id, name from Player");
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement))
				fprintf(file, "%d,%s;", sqlite3_column_int(statement, 0), sqlite3_column_text(statement, 1));
		}
		else db_status = false;
		fprintf(file, "\n");

		// Enemigos
		sprintf(query, "select id, name from Enemy");
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement))
				fprintf(file, "%d,%s;", sqlite3_column_int(statement, 0), sqlite3_column_text(statement, 1));
		}
		else db_status = false;
		fprintf(file, "\n");

		// Zonas
		sprintf(query, "select id, name from Zone");
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement))
				fprintf(file, "%d,%s;", sqlite3_column_int(statement, 0), sqlite3_column_text(statement, 1));
		}
		else db_status = false;
		fprintf(file, "\n");

		// Tools
		sprintf(query, "select id, name from Tool");
		if (SQLITE_OK == sqlite3_prepare(db, query, MAX_STR_LENGTH, &statement, NULL)) {
			while (SQLITE_ROW == sqlite3_step(statement))
				fprintf(file, "%d,%s;", sqlite3_column_int(statement, 0), sqlite3_column_text(statement, 1));
		}
		else db_status = false;
		fprintf(file, "\n");

		// Themes
	}

	fclose(file);
}
