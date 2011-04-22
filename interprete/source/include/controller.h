#pragma once

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "HelperTypes.h"

#include "HUDController.h"
#include "ToolController.h"
#include "EventController.h"

#include "GamePlayState.h"
#include "ScreenMap.h"
#include "DataPersistence.h"
#include "DataBaseInterface.h"

#include "EntityReader.h"

#include "DungeonMapStatus.h"
#include <map>
#include <deque>

class GamePlayState;
class ScreenMap;
class ScreenMapConstructor;
class ToolController;

class Controller
{

	friend class HUDController;
	friend class ToolController;
	friend class EventController;

	public:

		enum State {NORMAL, TRANSITION};

		Game* game;

		Controller(Game* g);
		~Controller();

		// Carga el saveslot de ruta path en Data, o la inicia con la BD si path es nulo
		bool initData(std::string path/*, players info*/);
		// Carga rápida de valores básicos del saveslot de ruta path
		bool shortInitData(std::string path);
		// Inicia la información necesaria para comenzar la ejecución del juego.
		bool initGamePlayState(GamePlayState* gpst);

		// Cambio al mapa m con transición te solicitado por P, de forma bruta (no espera al resto de compañeros) o no
		bool teleportTo(MapLocation m, Player* p, EventController::TransitionEffect te, bool brute = false);
		// Desplaza el mapa a la pantalla contigua en dirección dir
		bool moveScreen(Direction dir);

		// Cambia efectivamente el mapa, llamado por los anteriores
		bool changeLocation(MapLocation target);

		State getState();
		void setState(State st);

		int getNumPlayers();
		EventController::TransitionEffect getTransitionEffect();
		ScreenMap* getScreenMap();
		Player* getPlayer(int i);

		HUDController* getHUDController();
		ToolController* getToolController();
		EventController* getEventController();

		bool addPlayer(/*params?*/);
		bool removePlayer(Player* p);
		bool removePlayer(int i);

		DataPersistence* getData();

	private:

		struct PortInfo{
			MapLocation mapLocation;
			Player* p;
			EventController::TransitionEffect te;
		};

		deque<ScreenMapConstructor*>* screenMapList;

		int width;
		int height;

		Player* players[4];
		int numPlayers;

		HUDController* hudController;
		ToolController* toolController;
		EventController* eventController;

		DataBaseInterface* dbi;
		EntityReader* entityReader;

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

		//! Construye el nombre de archivo a cargar a partir de una localización
		std::string getMapScreenFileName(MapLocation map);

		/* --------------
			TRANSITION
		 -------------- */
		// Efecto de la transición
		EventController::TransitionEffect transitionEffect;
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
};


#endif
