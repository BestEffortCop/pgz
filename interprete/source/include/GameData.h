#pragma once
#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include "DungeonMapState.h"
#include "OverWorldMapState.h"
#include "GameStatus.h"

#include <vector>

class GameData
{

private:

	std::vector<DungeonMapState*> dungeonMapStates;		// vector de estados de mazmorras
	std::vector<OverWorldMapState*> overWorldMapStates;	// vector de estados de overworlds
	GameStatus* gameStatus;								// estado del juego entre otras cosas

public:

	//!Instancia los atributos de GameData
	GameData(int numDungeons, int numOverWorlds);

	//!Elimina los atributos de GameData
	~GameData();

	//!Inicializa los atributos del dungeonMapState indicado
	/*!
		\param dungeonID identificador del dungeonMapState que se quiere iniciar
		\param collectables mapa de objetos coleccionables
		\param doors mapa de puertas de la mazmorra en cuestión.
		\param puzzles tabla de puzzles de la mazmorra en cuestión.
		\param minibosses tabla de minibosses de la mazmorra en cuestión.
		\param bossDefeated flag de Boss derrotado de la mazmorra en cuestión.
		\param gotBossKey flag de llave del Boss cogida de la mazmorra en cuestión.
		\param gotCompass flag de compás cogido de la mazmorra en cuestión.
		\param gotMap flad de mapa cogido de la mazmorra en cuestión.
		\param gotPowerUp flag de PowerUp cogido de la mazmorra en cuestión.
	*/
	void initDungeonMapState(int dungeonID, std::map<int, bool> collectables, std::map<int, bool> doors,
			std::map<int, bool> puzzles, std::map<int, bool> minibosses,	bool bossDefeated, bool gotBossKey,
			bool gotCompass, bool gotMap, bool gotPowerUp);

	//!Inicializa los atributos del dungeonMapState indicado
	/*!
		\param dungeonID identificador del overWorldMapState que se quiere iniciar
		\param collectables mapa de objetos coleccionables
		\param doors mapa de puertas del overworld en cuestión
		\param puzzles tabla de puzzles del overworld en cuestión.
		\param minibosses tabla de minibosses del overworld en cuestión.
	*/
	void initOverWorldMapState(int overWorldID, std::map<int, bool> collectables, std::map<int, bool> doors,
								std::map<int, bool> puzzles, std::map<int, bool> minibosses);

	//!Inicializa el gameStatus con los parámetros indicados
	void initGameStatus(int numKeyItems, int maxLife, std::map<int,ToolInfo> tools, int actualMoney,
					MapId actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPidgeons,
					int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress);

	//!Devuelve el dungeonMapState solicitado
	/*
		\param i identificador del dungeonMapState que se quiere conseguir
		\return Puntero al dungeonMapState solicitado
	*/
	DungeonMapState* getDungeonMapState(int i);

	//!Devuelve el overWorldMapState solicitado
	/*
		\param i identificador del dungeonMapState que se quiere conseguir
		\return Puntero al dungeonMapState solicitado
	*/
	OverWorldMapState* getOverWorldMapState(int i);

	//!Getter del gameStatus
	/*
		\return Puntero al gameStatus
	*/
	GameStatus* getGameStatus();

};


#endif