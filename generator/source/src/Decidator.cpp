#include "Decidator.h"

Decidator::Decidator(DBManager* myDB, string path){
	db = myDB;
	ifstream file(path);
	if (!file) {
		cout<< "No pudo leerse el archivo " << path;
		cin.get();
		exit(1);
	}
	map<string, string> datos;
	string line, key, value; 
    while (getline (file, line)) // vamos leyendo lineas del fichero
    {
        istringstream iss(line);
		getline(iss, key, '=');
		getline(iss, value);
		datos.insert(pair<string, string>(key,value));
	}
	file.close();

	evaluateData(datos);
	completeData();	
	numPigeons = 10+rand()%30;
}

void Decidator::evaluateData(map<string, string> datos){
	string s;

	// Convertimos datos a su tipo
	consistency = atoi(datos.find("consistency")->second.c_str());
	ratio = atoi(datos.find("ratio")->second.c_str());
	numTools = atoi(datos.find("numTools")->second.c_str());
	numDungeons = atoi(datos.find("numDungeons")->second.c_str());
	numZones = atoi(datos.find("numZones")->second.c_str());
	numSafeZones = atoi(datos.find("numSafeZones")->second.c_str());
	worldSize = atoi(datos.find("worldSize")->second.c_str());
	difficulty = atoi(datos.find("difficulty")->second.c_str());
	playerName = atoi(datos.find("playerName")->second.c_str());
	player = atoi(datos.find("player")->second.c_str());
	thematic = atoi(datos.find("thematic")->second.c_str());
	worldName = atoi(datos.find("worldName")->second.c_str());
	numKeyObj = atoi(datos.find("numKeyObj")->second.c_str());

	// ToolSet
	toolsSet = loadShortCSV(datos.find("toolsSet")->second);

	// EnemiesSet
	enemiesSet = loadShortCSV(datos.find("enemiesSet")->second);

	// ZonesSet
	zonesSet = loadShortCSV(datos.find("zonesSet")->second);

	/*  NO SE USAN:
	worldSizeColumn = atoi(datos->back().c_str());
	worldSizeRow = atoi(datos->back().c_str());
	dungeonsSizeColumn = atoi(datos->back().c_str());
	dungeonsSizeRow = atoi(datos->back().c_str());*/
}

vector<short>* Decidator::loadShortCSV(string input){
	vector<short>* output = new vector<short>();
	string value;
	istringstream iss(input);
	while (getline(iss, value, ',')){
		output->push_back(atoi(value.c_str()));
	}
	return output;
}

/* Toma las decisiones oportunas para completar los parámetros restantes */
void Decidator::completeData(){
	/*
	Los parámetros siguientes se seleccionan en función de la dificultad:
		- initMaxLife
		- numPieces
		- numKeyObj
		- initialMoney
	
	*/
	initialMap = 0;
	switch (this->difficulty){
		case 0: // fácil
			initialMaxLife = 24; 
			numPieces = 3;
			numKeyObj = 4;
			initialMoney = 600;
			numEnemies = 2;
			break;
		case 1: // normal
			initialMaxLife = 20;
			numPieces = 4;
			numKeyObj = 5;
			initialMoney = 500;
			numEnemies = 3;
			break;
		case 2: // difícil
			initialMaxLife = 16;
			numPieces = 5;
			numKeyObj = 6;
			initialMoney = 400;
			numEnemies = 4;
			break;
		case 3: // muy difícil
			initialMaxLife = 12;
			numPieces = 6;
			numKeyObj = 7;
			initialMoney = 300;
			numEnemies = 5;
			break;
		case 4: // caótico
			initialMaxLife = 8;
			numPieces = 7;
			numKeyObj = 8;
			initialMoney = 200;
			numEnemies = 6;
			break;
		default: // para todo lo demás mastercard
			initialMaxLife = 4;
			numPieces = 8;
			numKeyObj = 9;
			initialMoney = 100;
			numEnemies = 7;
			break;
	}

	initialMap = 0;
	difficulty = 3;
	worldSize = 9;
}

ZoneInfo Decidator::getWorldGen(){
	//return db->getWorldGen(this->thematic);
	return db->getZone();
}

short Decidator::getDungeonGen(){
	// return db->getWorldGen(this->thematic);
	// Pongo esto para que no estalle
	return db->getDungeon("Zelda");
}

bool Decidator::save() {

	printMainInfo();

	// Abrimos el archivo de decidator
	char fname[100];
	sprintf_s(fname, "decidator", 0);
	FILE* file = fopen (fname, "w");
	// Guardamos la información de decidator para el intérprete
	if (file != NULL) {
		short* buffer = new short[7];
		buffer[0] = initialMaxLife;
		buffer[1] = initialMap;
		buffer[2] = numMaps;
		buffer[3] = numPieces;
		buffer[4] = initialMoney;
		buffer[5] = numKeyObj;
		buffer[6] = toolsSet->size();
		fwrite(buffer, sizeof(short), 7, file);	
		delete buffer; buffer = NULL;

		// guardamos el conjunto de herramientas
		vector<short>::iterator it;
		buffer = new short[toolsSet->size()];
		int i = 0;
		for (it = toolsSet->begin(); it < toolsSet->end(); it++){
			buffer[i] = *it;
			i++;
		}
		fwrite(buffer, sizeof(short), toolsSet->size(), file);
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

string Decidator::getThematic(){
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

short Decidator::getNumSafeZones(){
	return this->numSafeZones;
}

short Decidator::getNumZones(){
	return this->numZones;
}

vector<short>* Decidator::getZonesSet(){
	return this->zonesSet;
}

short Decidator::getNumEnemies(){
	return this->numEnemies;
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

/*short Decidator::getDungeonsSizeRow(){
	return this->dungeonsSizeRow;
}

short Decidator::getDungeonsSizeColumn(){
	return this->dungeonsSizeColumn;
}*/

short Decidator::getConsistency(){
	return this->consistency;
}

void Decidator::printMainInfo()
{
	// Carga el archivo y se lee
	FILE* f = std::fopen("./data/maininfo", "w");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
	{
		cout<< "No pudo leerse el archivo " << "main info";
		cin.get();
		exit(1);
	}

	std::fprintf(f, "%d\n", numMaps);
	std::fprintf(f, "%d\n", numKeyObj);

	std::fprintf(f, "%d\n", initialMaxLife);

	std::fprintf(f, "%d\n", initialMoney);

	std::fprintf(f, "%d\n", numTools);

	for (vector<short>::iterator it = toolsSet->begin(); it != toolsSet->end(); it++)
		std::fprintf(f, "%d ", (*it));

	std::fprintf(f, "\n%d", numPigeons);

	std::fclose(f);
}

void Decidator::addInitialTool(short idTool)
{
	toolsSet->push_back(idTool);
};

void Decidator::clearInitialTools()
{
	toolsSet->clear();
};