#include "MapStatus.h"

void MapStatus::mapCopy(std::map<int,bool>* m, char id)
{

	std::map< int, bool >::iterator it;	//Iterador para recorrer la lista de collectables entrante
	std::pair<int,bool> aux;			//Par para almacenar los valores que vamos recorriendo

	for(it = m->begin(); it != m->end(); it++)
	{
		aux.first = (*it).first;			//Copiamos la clave a un par auxiliar
		aux.second = (*it).second;			//Copiamos el valor a un par auxiliar
		
		//Insertamos el par auxiliar en el map que corresponde según id
		switch (id)
		{
		case 'c':
			collectables.insert(aux);
			break;
		case 'd':
			doors.insert(aux);
			break;
		case 'p':
			puzzles.insert(aux);
			break;
		case 'm':
			minibosses.insert(aux);
			break;
		default:
			break;
		}//end switch
	}//end for
}

//No hace nada
MapStatus::MapStatus()
{
}

//No hace nada
MapStatus::~MapStatus()
{
};

void MapStatus::init(/*std::map< int, bool > collectables, std::map< int, bool > doors, std::map< int, bool > puzzles, 
					std::map< int, bool > minibosses*/)
{
	/*mapCopy(&collectables,'c');	//Copiamos el mapa de collectables
	mapCopy(&doors,'d');		//Copiamos el mapa de doors
	mapCopy(&puzzles,'p');		//Copiamos el mapa de puzzles
	mapCopy(&minibosses, 'm');	//Copiamos el mapa de minibosses*/
	numKeys = 0;
}

std::map<int, bool> MapStatus::getCollectables()
{
	return collectables;
}

void MapStatus::setCollectables(std::map<int, bool> collectables)
{
	mapCopy(&collectables,'c');
}

bool MapStatus::getCollectableStatus(int idCollectable)
{
	return collectables[idCollectable];
}

//Consideramos que sobreescribe la información si existía el elemento NECESITA REVISIÓN
void MapStatus::setCollectableStatus(int idCollectable, bool picked)
{
	std::pair<std::map<int, bool>::iterator, bool> ret;

	// Tratamos de insertar el estado
	ret = collectables.insert(std::make_pair(idCollectable, picked));
	// Si no lo conseguimos, es que ya estaba
	if (!ret.second)
	{
		// Y lo modificamos
		std::map<int, bool>::iterator it = collectables.find(idCollectable);
		if (it != collectables.end())
			it->second = picked;
	};
}

std::map<int, bool> MapStatus::getDoors()
{
	return doors;
}

void MapStatus::setDoors(std::map<int, bool> doors)
{
	mapCopy(&doors,'d');
}

bool MapStatus::getDoorStatus(int idDoor)
{
	return doors[idDoor];
}

//Consideramos que sobreescribe la información si existía el elemento NECESITA REVISIÓN
void MapStatus::setDoorStatus(int idDoor, bool open)
{
	std::pair<std::map<int, bool>::iterator, bool> ret;

	// Tratamos de insertar el estado
	ret = doors.insert(std::make_pair(idDoor, open));
	// Si no lo conseguimos, es que ya estaba
	if (!ret.second)
	{
		// Y lo modificamos
		std::map<int, bool>::iterator it = doors.find(idDoor);
		if (it != doors.end())
			it->second = open;
	};
}

std::map<int, bool> MapStatus::getPuzzles()
{
	return puzzles;
}

void MapStatus::setPuzzles(std::map<int, bool> puzzles)
{
	mapCopy(&puzzles,'p');
}

bool MapStatus::getPuzzleStatus(int idPuzzle)
{
	return puzzles[idPuzzle];
}

//Consideramos que sobreescribe la información si existía el elemento NECESITA REVISIÓN
void MapStatus::setPuzzleStatus(int idPuzzle, bool solved)
{
	std::pair<std::map<int, bool>::iterator, bool> ret;

	// Tratamos de insertar el estado
	ret = puzzles.insert(std::make_pair(idPuzzle, solved));
	// Si no lo conseguimos, es que ya estaba
	if (!ret.second)
	{
		// Y lo modificamos
		std::map<int, bool>::iterator it = puzzles.find(idPuzzle);
		if (it != puzzles.end())
			it->second = solved;
	};
}

std::map<int, bool> MapStatus::getMinibosses()
{
	return minibosses;
}

void MapStatus::setMinibosses(std::map<int, bool> minibosses)
{
	mapCopy(&minibosses,'m');
}

bool MapStatus::getMinibossStatus(int idMiniboss)
{
	return minibosses[idMiniboss];
}

//Consideramos que sobreescribe la información si existía el elemento NECESITA REVISIÓN
void MapStatus::setMinibossStatus(int idMiniboss, bool killed)
{
	std::pair<std::map<int, bool>::iterator, bool> ret;

	// Tratamos de insertar el estado
	ret = minibosses.insert(std::make_pair(idMiniboss, killed));
	// Si no lo conseguimos, es que ya estaba
	if (!ret.second)
	{
		// Y lo modificamos
		std::map<int, bool>::iterator it = minibosses.find(idMiniboss);
		if (it != minibosses.end())
			it->second = killed;
	};
}

void MapStatus::addKeys(int ammount)
{
	numKeys += ammount;
};

int MapStatus::getKeys()
{
	return numKeys;
};

void MapStatus::save(FILE* f){
	std::map< int, bool >::iterator it;	//Iterador para recorrer la lista de collectables entrante

	// Número de collectables
	int* buffer = new int[5];
	buffer[0] = collectables.size();
	buffer[1] = doors.size();
	buffer[2] = puzzles.size();
	buffer[3] = minibosses.size();
	buffer[4] = numKeys;
	fwrite(buffer, sizeof(int), 5, f);
	delete buffer; buffer = new int[1];

	// NOTA: Los fwrite de aquí abajo los he añadido yo (carlos), porque si no no tenía mucho sentido. Si no es correcto quitadlo.


	bool buffer1;
	for (it = collectables.begin(); it != collectables.end(); it++)	{
		buffer[0] = (*it).first;			
		buffer1 = (*it).second;	

		if (buffer[0] == 26)
			buffer[0]--;

		fwrite(buffer, sizeof(int), 1, f);
		fwrite(&buffer1, sizeof(bool), 1, f);
	}

	for (it = doors.begin(); it != doors.end(); it++)	{
		buffer[0] = (*it).first;			
		buffer1 = (*it).second;		
				
		if (buffer[0] == 26)
			buffer[0]--;

		fwrite(buffer, sizeof(int), 1, f);
		fwrite(&buffer1, sizeof(bool), 1, f);		
	}

	for (it = puzzles.begin(); it != puzzles.end(); it++)	{
		buffer[0] = (*it).first;			
		buffer1 = (*it).second;		

		if (buffer[0] == 26)
			buffer[0]--;

		fwrite(buffer, sizeof(int), 1, f);
		fwrite(&buffer1, sizeof(bool), 1, f);	
	}

	for (it = minibosses.begin(); it != minibosses.end(); it++)	{
		buffer[0] = (*it).first;			
		buffer1 = (*it).second;			

		if (buffer[0] == 26)
			buffer[0]--;

		fwrite(buffer, sizeof(int), 1, f);
		fwrite(&buffer1, sizeof(bool), 1, f);	
	}

	delete buffer;
	//delete buffer1;
}

void MapStatus::load(FILE* f){
	std::map< int, bool >::iterator it;	//Iterador para recorrer la lista de collectables entrante
	std::pair<int,bool> aux;			//Par para almacenar los valores que vamos recorriendo

	// Número de collectables
	int buffer[5];
	fread(buffer, sizeof(int), 5, f);
	int numCollectables = buffer[0];
	int numDoors = buffer[1];
	int numPuzzles = buffer[2];
	int numMinibosses = buffer[3];
	numKeys = buffer[4];

	bool buffer1[1]; buffer[1];

	bool preparefor26 = false;

	for (int i = 0; i < numCollectables; i++) {
		fread(buffer, sizeof(int), 1, f);

		if (buffer[0] == 25) 
			if (preparefor26)
				buffer[0]++;
			else
				preparefor26 = true;

		aux.first = buffer[0];
		fread(buffer1, sizeof(bool), 1, f);
		aux.second = buffer1[0];
		collectables.insert(aux);
	}

	preparefor26 = false;

	for (int i = 0; i < numDoors; i++)	{
		fread(buffer, sizeof(int), 1, f);

		if (buffer[0] == 25) 
			if (preparefor26)
				buffer[0]++;
			else
				preparefor26 = true;

		aux.first = buffer[0];
		fread(buffer1, sizeof(bool), 1, f);
		aux.second = buffer1[0];
		doors.insert(aux);	
	}

	preparefor26 = false;

	for (int i = 0; i < numPuzzles; i++)	{
		fread(buffer, sizeof(int), 1, f);

		if (buffer[0] == 25) 
			if (preparefor26)
				buffer[0]++;
			else
				preparefor26 = true;

		aux.first = buffer[0];
		fread(buffer1, sizeof(bool), 1, f);
		aux.second = buffer1[0];
		puzzles.insert(aux);		
	}

	preparefor26 = false;

	for (int i = 0; i < numMinibosses; i++)	{
		fread(buffer, sizeof(int), 1, f);

		if (buffer[0] == 25) 
			if (preparefor26)
				buffer[0]++;
			else
				preparefor26 = true;

		aux.first = buffer[0];
		fread(buffer1, sizeof(bool), 1, f);
		aux.second = buffer1[0];
		minibosses.insert(aux);		
	}
}