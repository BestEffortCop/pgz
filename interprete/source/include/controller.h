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

#include "DungeonMapStatus.h"
#include <map>

class GamePlayState;
class EventToolController;

class Controller {

	friend class HUDController;
	friend class ToolController;
	friend class EventController;

	public:
		
		enum State {NORMAL, TRANSITION};
		enum TransitionEffect {SCROLL, FADE};
		
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
		bool change_map(MapLocation m, Player* p, TransitionEffect te, bool brute = false);
		// Desplaza el mapa a la pantalla contigua en dirección dir
		bool move_screen(Dir dir);
		
		State getState();
		void setState(State st);
		
		int getNumPlayers();
		TransitionEffect getTransitionEffect();
		ScreenMap* getScreenMap();
		Player* getPlayer(int i);

		HUDController* getHUDController();
		ToolController* getToolController();
		EventController* getEventController();
		
		bool addPlayer(/*params?*/);
		bool removePlayer(Player* p);
		bool removePlayer(int i);

	private:
		
		struct PortInfo{
			MapLocation MapLocation;
			Player* p;
			TransitionEffect te;
		};

		int width;
		int height;
		
		Player* players[4];
		int numPlayers;

		HUDController* hudController;
		ToolController* toolController;
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
		bool load_screen(MapLocation location);

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
};


#endif