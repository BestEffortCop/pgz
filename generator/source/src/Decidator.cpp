#include "Decidator.h"

Decidator::Decidator(string path){
	// Abrimos el archivo de Decidator
	ifstream f(path,ifstream::in);
	/* Declaramos un array con suficiente tamaño para leer las líneas */
	char cadena[100], aux[100];
	for (int i = 0; i < 100; i++){
		aux[i] = ' '; 
	}

	if (!f) {
		printf("No pudo leerse el archivo");
		exit(1);   // parar
	}

	/* Hacemos una primera lectura */
	f >> cadena;
	strcpy(aux, cadena);
	while (!f.eof()){
		/* Leemos la siguiente línea */
		f >> cadena;	
		strcat(aux,cadena);
	}
	f.close();

	// DEBUG
	printf(aux);
	printf("\n");

	for (int i = 0; i < 100; i++){
		cadena[i] = ' ';
	}

	int i = 0; string s = "";
	vector<string>* datos = new vector<string>();

	while (i < strlen(aux)){
		if (aux[i] != ';'){
			s += aux[i];
		}
		else{
			datos->push_back(s);
			s = "";
		}
		i++;
	}

	fillDates(datos);
	completeDates();

	
}

void Decidator::fillDates(vector<string>* datos){
	string s = "";
	consistency = atoi(datos->back().c_str());
	datos->pop_back();

	dungeonsSizeColumn = atoi(datos->back().c_str());
	datos->pop_back();

	dungeonsSizeRow = atoi(datos->back().c_str());
	datos->pop_back();

	this->ratio = atoi(datos->back().c_str());
	datos->pop_back();

	this->numDungeons = atoi(datos->back().c_str());
	datos->pop_back();

	// ToolSet
	toolsSet = new vector<short>();
	for (int i = 0; i < strlen(datos->back().c_str()); i++){
		if (datos->back().c_str()[i] != ',')
			s += datos->back().c_str()[i];
		else{
			toolsSet->push_back(atoi(s.c_str()));
			s = "";
		}
	}
	toolsSet->push_back(atoi(s.c_str()));
	datos->pop_back();
	s = "";

	this->numTools = atoi(datos->back().c_str());
	datos->pop_back();

	// EnemiesSet
	enemiesSet = new vector<short>();
	for (int i = 0; i < strlen(datos->back().c_str()); i++){
		if (datos->back().c_str()[i] != ',')
			s += datos->back().c_str()[i];
		else{
			this->enemiesSet->push_back(atoi(s.c_str()));
			s = "";
		}
	}
	enemiesSet->push_back(atoi(s.c_str()));
	datos->pop_back();
	s = "";

	this->teleports = atoi(datos->back().c_str());
	datos->pop_back();

	// ZonesSet
	zonesSet = new vector<short>();
	for (int i = 0; i < strlen(datos->back().c_str()); i++){
		if (datos->back().c_str()[i] != ',')
			s += datos->back().c_str()[i];
		else{
			this->zonesSet->push_back(atoi(s.c_str()));
			s = "";
		}
	}
	zonesSet->push_back(atoi(s.c_str()));
	datos->pop_back();
	s = "";

	this->numZones = atoi(datos->back().c_str());
	datos->pop_back();

	this->worldSize = atoi(datos->back().c_str());
	datos->pop_back();

	/*this->worldSizeColumn = atoi(datos->back().c_str());
	datos->pop_back();

	this->worldSizeRow = atoi(datos->back().c_str());
	datos->pop_back();*/

	this->difficulty = atoi(datos->back().c_str());
	datos->pop_back();

	this->playerName = datos->back();
	datos->pop_back();

	this->player = atoi(datos->back().c_str());
	datos->pop_back();

	this->thematic = atoi(datos->back().c_str());
	datos->pop_back();

	this->worldName = datos->back();
	datos->pop_back();

	this->initialMoney = atoi(datos->back().c_str());
	datos->pop_back();

	this->numKeyObj = atoi(datos->back().c_str());
	datos->pop_back();

	this->numPieces = atoi(datos->back().c_str());
	datos->pop_back();

	this->initialMap = atoi(datos->back().c_str());
	datos->pop_back();

	this->initialMaxLife = atoi(datos->back().c_str());
	datos->pop_back();

	/* Ya no hace falta conservar datos porque se han leido */
	delete datos; datos = NULL;
}

void Decidator::completeDates(){
	/*
	Los parámetros siguientes se seleccionan en función de la dificultad:
		- initMaxLife
		- numPieces
		- numKeyObj
		- initialMoney
	
	*/
	switch (this->difficulty){
		case 0: 
			initialMaxLife = 24; 
			numPieces = 3;
			numKeyObj = 4;
			initialMoney = 600;
			break;
		case 1:
			initialMaxLife = 20;
			numPieces = 4;
			numKeyObj = 5;
			initialMoney = 500;
			break;
		case 2:
			initialMaxLife = 16;
			numPieces = 5;
			numKeyObj = 6;
			initialMoney = 400;
			break;
		case 3:
			initialMaxLife = 12;
			numPieces = 6;
			numKeyObj = 7;
			initialMoney = 300;
			break;
		case 4: 
			initialMaxLife = 8;
			numPieces = 7;
			numKeyObj = 8;
			initialMoney = 200;
			break;
		default:
			initialMaxLife = 4;
			numPieces = 8;
			numKeyObj = 9;
			initialMoney = 100;
			break;
	}

	initialMap = 0;
	numMaps = 3;
}

bool Decidator::save() {
	// Abrimos el archivo de decidator
	char fname[100];
	sprintf(fname, "decidator", 0);
	FILE* file = fopen (fname, "w");
	// Guardamos la información de decidator para el intérprete
	if (file != NULL) {
		short* buffer = new short[6];
		buffer[0] = initialMaxLife;
		buffer[1] = initialMap;
		buffer[2] = numMaps;
		buffer[3] = numPieces;
		buffer[4] = initialMoney;
		buffer[5] = numKeyObj;
		fwrite(buffer, sizeof(buffer), 1, file);	
		delete buffer; buffer = NULL;

		// guardamos el conjunto de herramientas
		vector<short>::iterator it;
		buffer = new short[toolsSet->size()];
		int i = 0;
		for (it = toolsSet->begin(); it < toolsSet->end(); it++){
			buffer[i] = *it;
			i++;
		}
		fwrite(buffer, sizeof(buffer), 1, file);
		delete buffer; buffer = NULL;

		fclose(file);

		return true;
	}
	return false;
}

Decidator::~Decidator(){
	delete zonesSet; zonesSet = NULL;
	delete enemiesSet; enemiesSet = NULL;
	delete toolsSet; toolsSet = NULL;
}

/**------------------------- GETTERS & SETTERS ------------------------------------*/

short Decidator::getInitialMaxLife(){
	return this->initialMaxLife;
}

short Decidator::getInitialMap(){
	return this->initialMap;
}		
short Decidator::getNumMaps(){
	return this->numMaps;
}		
short Decidator::getNumPieces(){
	return this->numPieces;
}

short Decidator::getNumKeyObj(){
	return this->numKeyObj;
}

short Decidator::getInitialMoney(){
	return this->initialMoney;
}

string Decidator::getWorldName(){
	return this->worldName;
}

short Decidator::getThematic(){
	return this->thematic;
}

short Decidator::getPlayer(){
	return this->player;
}

string Decidator::getPlayerName(){
	return this->playerName;
}

short Decidator::getDifficulty(){
	return this->difficulty;
}

short Decidator::getWorldSize(){
	return this->worldSize;
}

/*short Decidator::getWorldSizeRow(){
	return this->worldSizeRow;
}

short Decidator::getWorldSizeColumn(){
	return this->worldSizeColumn;
}*/

short Decidator::getNumZones(){
	return this->numZones;
}

vector<short>* Decidator::getZonesSet(){
	return this->zonesSet;
}

bool Decidator::getTeleports(){
	return this->teleports;
}

vector<short>* Decidator::getEnemiesSet(){
	return this->enemiesSet;
}

short Decidator::getNumTools(){
	return this->numTools;
}

vector<short>* Decidator::getToolsSet(){
	return this->toolsSet;
}

short Decidator::getNumDungeons(){
	return this->numDungeons;
}

short Decidator::getRatio(){
	return this->ratio;
}

short Decidator::getDungeonsSizeRow(){
	return this->dungeonsSizeRow;
}

short Decidator::getDungeonsSizeColumn(){
	return this->dungeonsSizeColumn;
}

short Decidator::getConsistency(){
	return this->consistency;
}