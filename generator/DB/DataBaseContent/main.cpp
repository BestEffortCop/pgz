#include "DBAccess.h"

int main(int argc, char** argv) {
	DBAccess* db = new DBAccess();
	
	db->obtain_data();

	delete db; db = NULL;

	exit(0);
}