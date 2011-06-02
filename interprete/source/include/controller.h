/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "HelperTypes.h"

#include "HUDController.h"
#include "ToolController.h"
#include "MessageController.h"
#include "EventController.h"

#include "GamePlayState.h"
#include "ScreenMap.h"
#include "DataPersistence.h"
#include "DataBaseInterface.h"

#include "DungeonMapStatus.h"
#include <map>
#include <vector>
#include <deque>
#include "GamePuzzle.h"

#include "Component.h"
#include "ComponentAnim.h"

#include "Enemy.h"


class GamePlayState;
class ScreenMap;
class ScreenMapConstructor;
class ToolController;
class MessageController;
class EventController;
class GamePuzzle;
class Enemy;
class Component;
class ComponentAnim;

class Controller
{
	friend class PGZGame;
	friend class HUDController;
	friend class ToolController;
	friend class EventController;
	friend class MessageController;

	public:
		enum State {NORMAL, TRANSITION};

		enum GameScreens { LOGO, TITLE, INTRO, GAMEPLAY, ENDING };

		Game* game;
		InputConfig mainInputConfig;

		Controller(Game* g);
		~Controller();

		bool loadInputConfig(InputConfig& ic, std::string path);
		// Carga el saveslot de ruta path en Data, o la inicia con la BD si path es nulo
		bool initData(std::string path /*, players info*/);
		// Carga rápida de valores básicos del saveslot de ruta path
		bool shortInitData(std::string path);
		// Inicia la información necesaria para comenzar la ejecución del juego.
		bool initGamePlayState(GamePlayState* gpst);

		// Cambio al mapa m con transición te solicitado por P, de forma bruta (no espera al resto de compañeros) o no
		bool teleportTo(MapLocation m, Player* p, TransitionEffect te, bool brute = false);
		// Desplaza el mapa a la pantalla contigua en dirección dir
		bool moveScreen(Direction dir);

		// Cambia efectivamente el mapa, llamado por los anteriores
		bool changeLocation(MapLocation target);

		State getState();
		void setState(State st);

		int getNumPlayers();
		TransitionEffect getTransitionEffect();
		ScreenMap* getScreenMap();
		Player* getPlayer(int i);

		DataBaseInterface* getDataBaseInterface();
		HUDController* getHUDController();
		ToolController* getToolController();
		MessageController* getMessageController();
		EventController* getEventController();

		bool addPlayer(/*params?*/);
		bool removePlayer(Player* p);
		bool removePlayer(int i);

		DataPersistence* getData();

		void save();

		void changeGameStateTo(GameScreens target);
		int getMaxSaves();
		void setMaxLife(int life);

	private:

		struct PortInfo{
			MapLocation mapLocation;
			Player* p;
			TransitionEffect te;
		};

		bool readMainInfo(int & numMaps, int & numKeyItems, int & initLife, int & initMoney, vector<int> * tools, int & numPigeons);

		deque<ScreenMapConstructor*>* screenMapList;

		int width;
		int height;

		Player* players[4];
		int numPlayers;
		int maxSaves;  // Número máximo de partidas guardadas
		int gameId; // Id de la partida que se está jugando

		HUDController* hudController;
		ToolController* toolController;
		MessageController* messageController;
		EventController* eventController;

		DataBaseInterface* dbi;

		DataPersistence* data;
		ScreenMap* screenMap;
		GamePlayState* gamePlayState;

		// Estado del controlador
		State state;


		/* --------------
			   LOAD
		 -------------- */

		// loadMap(MapLocation int, (bloque de info a devolver ));
		bool loadScreen(MapLocation location);

		bool readEntities(FILE* file, map<int, Entity*>* screenEntities, map<int, GamePuzzle*>* screenPuzzles);
		bool readEnemies(FILE* file, vector<Enemy*>* screenEnemies, map<int, Entity*>* screenEntities);

		//! Construye el nombre de archivo a cargar a partir de una localización
		std::string getMapScreenFileName(MapLocation map);

		/* --------------
			TRANSITION
		 -------------- */
		// Efecto de la transición
		TransitionEffect transitionEffect;
		// Imágenes para la transición de mapas
		Image* currentRoom;
		Image* nextRoom;
		// Velocidad de la transición
		int speed;
		// Coordenadas origen de la transición
		int mx, my;
		// Coordenadas destino de la transición
		int tx, ty;
		// Dirección de la transición
		int xdir, ydir;

		// Listado dinámico de los portales y la cantidad de players en cada uno <idport, cont>
		map<PortInfo, int>* active_teleports;

		void endTransition();

		enum EntityTypes { entDoor, entBossDoor, Item,  entTiledEntity, DmgBlockade, entTiledPushable, entFloorButton, entInstantiator, entAbreCierraDoors, entArena, entTeleporter, PickableTool, entDoorCloser, entNoKeyDoor, entFinalDoor, entFinalElement, entNPC };

		GameScreens currentScreen;

		ComponentAnim* readComponents(int idEnemy, Enemy* enemy, std::vector<Component*>* comps);

		MapLocation teleportFromLocation;
};


#endif
