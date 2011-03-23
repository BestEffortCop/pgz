#pragma once

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
//#define D_INTERACT 3;

#include "Player.h"
#include "GameData.h"
#include "ScreenMap.h"
#include "HelperTypes.h"
#include "HUDController.h"
#include "ToolController.h"

#include <map>

class Controller : public Entity {

		enum State {NORMAL, TRANSITION};
		enum TransitionEffect {SCROLL, FADE};

		struct PortInfo{
			MapId mapId;
			Player* p;
			TransitionEffect te;
		};

	private:
		
		// DATOS EXTERNOS

		// Alto y ancho del juego
		int width;
		int height;
		
		(Player*)* players;
		int numPlayers;

		Entity* hud;

		GameData* data;

		// mapa actual
		ScreenMap* screenMap;


		// DATOS PROPIOS

		HUDController* hudController;
		ToolController* toolController;



		// Estado del controlador
		State state;
		

		/* --------------
			   LOAD
		 -------------- */

		// Carga una partida guardada, actualizando DATA
		bool load_slot(std::string slotpath);

		// loadMap(mapId int, (bloque de info a devolver ));
		// loadScreen(int id o cosa, (bloque de info a devolver)); <- o lo mete directamente en gamestate y screenmap




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
		
	public:
		// CONSTRUCORES Y DESTRUCTORES
		Controller(std::string path, Game* g, GameState* gs);
		~Controller();
		
		// MÉTODOS PERTENECIENTES A ENTITY
		void onStep();
		void onRender();

		void onTimer(int timer);

		// MÉTODOS PROPIOS
		// Iniliza lo necesario para el funcionamiento del gameplay
		bool init(std::string path);

		// Cambio de pantalla dentro del mismo mapa
		bool move_to_screen(Dir dir);

		// El player p solicita un cambio al mapa m con una transición te
		bool change_map(MapId m, Player* p, TransitionEffect te, bool brute = false);
		
		void setState(State st);
		void setTransitionEffect(TransitionEffect te);
};


#endif