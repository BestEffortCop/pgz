#pragma once
#ifndef __MAPSTATE_H__
#define __MAPSTATE_H__

#include <map>

class MapState
{
	private:
		std::map<int, bool> collectables;
		std::map<int, bool> doors;
		std::map<int, bool> puzzles;
		std::map<int, bool> minibosses;
	
	public:

		//!Instancia el MapState
		MapState(std::map<int, bool> collectables,	std::map<int, bool> doors, std::map<int, bool> puzzles,	
						  std::map<int, bool> minibosses);

		//!Destruye la instancia del MapState
		~MapState();

		//!Inicializa los atributos de MapState
		/*!
			\param collectables lista con el estado de los collectables del mapa del mundo.
			\param doors lista con el estado de las puertas del mapa del mundo.
			\param puzzles lista con el estado de puzzles del mapa del mundo.
			\param miniBosses lista con el estado (vivo o muerto) de los minibosses del mapa del mundo.
		*/
		void init(std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles, std::map<int, bool> miniBosses);

		std::map<int, bool>* getCollectables();
		void setCollectables(std::map<int, bool>* collectables);

		bool getCollectableState(int idCollectable);
		void setCollectableState(int idCollectable, bool picked);

		std::map<int, bool>* getDoors();
		void setDoors(std::map<int, bool>* doors);

		bool getDoorState(int idDoor);
		void setDoorState(int idDoor, bool open);

		std::map<int, bool>* getPuzzles();
		void setPuzzles(std::map<int, bool>* puzzles);

		bool getPuzzleState(int idPuzzle);
		void setPuzzleState(int idPuzzle, bool solved);

		std::map<int,bool>* getMinibosses();
		void setMinibosses(std::map<int,bool>* minibosses);

		bool getMinibossState(int idMiniboss);
		void setMinibossState(int idMiniboss, bool killed);
};

#endif