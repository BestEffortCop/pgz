#ifndef _MAPSTATUS_H
#define _MAPSTATUS_H

#include <map>

class MapStatus 
{
private:
	std::map<int, bool> collectables;

	std::map<int, bool> doors;

	std::map<int, bool> puzzles;

	std::map<int, bool> minibosses;

	//Copia un mapa
	//
	//			\param m mapa que tenemos que copiar
	//			\param id identificador del atributo al que lo vamos a copiar
	void mapCopy(std::map<int,bool> * m, char id);

	// Número de llaves obtenidas en el mapa actual
	int numKeys;

public:
	//!Instancia el MapStatus
	MapStatus();
	
	//!Destruye la instancia del MapStatus
	~MapStatus();

	//!Inicializa los atributos de MapStatus
	//!
	//			\param collectables mapa con el estado de los collectables del mapa del mundo.
	//			\param doors mapa con el estado de las puertas del mapa del mundo.
	//			\param puzzles mapa con el estado de puzzles del mapa del mundo.
	//			\param miniBosses mapa con el estado (vivo o muerto) de los minibosses del mapa del mundo.
	void init(/*std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles, std::map<int, bool> miniBosses*/);

	//!Getter del mapa de collectables
	//!
	//			\return mapa de collectables
	std::map<int, bool> getCollectables();

	//!Setter del mapa de collectables
	//!
	//			\param collectables mapa que vamos a asignar al atributo
	void setCollectables(std::map<int, bool> collectables);

	//!Devuelve el estado de un collectable
	//!
	//			\param idCollectable identificador del collectable que nos interesa
	bool getCollectableStatus(int idCollectable);

	//!Añade un elemento al mapa de collectables
	//!
	//			\param idCollectable identificador del collectable que vamos a añadir
	//			\param picked estado del collectable
	void setCollectableStatus(int idCollectable, bool picked);

	//!Getter del mapa de doors
	//!
	//			\return mapa de doors
	std::map<int, bool> getDoors();

	//!Setter del mapa de doors
	//!
	//			\param doors mapa que vamos a asignar al atributo
	void setDoors(std::map<int, bool> doors);

	//!Devuelve el estado de una Door
	//!
	//			\param idDoor identificador de la puerta que vamos a coseguier
	bool getDoorStatus(int idDoor);

	//!Añade un elemento al mapa de Doors
	//!
	//			\param idDoor identificador de la puerta que vamos a añadir
	//			\param open estado de la puerta
	void setDoorStatus(int idDoor, bool open);

	//!Getter del mapa de puzzles
	//!
	//			\return mapa de puzzles
	std::map<int, bool> getPuzzles();

	//!Setter del mapa de puzzles
	//!
	//			\param puzzles mapa que vamos a asignar al atributo
	void setPuzzles(std::map<int, bool> puzzles);

	//!Devuelve el estado de un puzzle
	//!
	//			\param idPuzzle identificador del puzzle que vamos a coseguier
	bool getPuzzleStatus(int idPuzzle);

	//!Añade un elemento a la lista de Puzzles
	//!
	//			\param idPuzzle identificador del puzzle que vamos a añadir
	//			\param solved estado del puzzle
	void setPuzzleStatus(int idPuzzle, bool solved);

	//!Getter del mapa de minibosses
	//!
	//			\return mapa de minibosses
	std::map<int,bool> getMinibosses();

	//!Setter del mapa de minibosses
	//!
	//			\param minibosses mapa que vamos a asignar al atributo
	void setMinibosses(std::map<int,bool> minibosses);

	//!Devuelve el estado de un miniboss
	//!
	//			\param idMiniboss identificador del miniboss que vamos a coseguier
	bool getMinibossStatus(int idMiniboss);

	//!Añade un elemento a la lista de Minibosses
	//!
	//			\param idMiniboss identificador del miniboss que vamos a añadir
	//			\param killed estado del miniboss
	void setMinibossStatus(int idMiniboss, bool killed);

	// Obtiene el nº de llaves conseguidas en el mapa
	int getKeys();
	// Añade ammount (puede ser negativo) al número de llaves obtenidas
	void addKeys(int ammount);
};

#endif
