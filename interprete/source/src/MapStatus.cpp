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
	std::pair<int,bool> aux;	//Creamos un par auxiliar
	aux.first = idCollectable;	//Almacenamos el valor que queremos añadir
	aux.second = picked;
	collectables.insert(aux);	//Lo añadimos al mapa
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
	std::pair<int,bool> aux;	//Creamos un par auxiliar
	aux.first = idDoor;			//Almacenamos el valor que queremos añadir
	aux.second = open;
	doors.insert(aux);			//Lo añadimos al mapa
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
	std::pair<int,bool> aux;	//Creamos un par auxiliar
	aux.first = idPuzzle;		//Almacenamos el valor que queremos añadir
	aux.second = solved;
	puzzles.insert(aux);		//Lo añadimos al mapa
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
	std::pair<int,bool> aux;	//Creamos un par auxiliar
	aux.first = idMiniboss;		//Almacenamos el valor que queremos añadir
	aux.second = killed;
	minibosses.insert(aux);		//Lo añadimos al mapa
}