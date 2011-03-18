#pragma once
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Player.h"
#include "GameData.h"
#include "ScreenMap.h"
#include "HelperTypes.h"
//#include "iInteractable.h"

// HERE THERE BE SHIT

#define D_INTERACT 3;

class iInteractable {
	public:
		void onInteract(Player* p){};
};



// STOP (HAMMERTIME!)

class Controller : public Entity {

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
		enum State {NORMAL, TRANSITION};
		enum TransitionEffect {SCROLL, FADE};

		// Estado del controlador
		State state;
		

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
		
	public:
		// CONSTRUCORES Y DESTRUCTORES
		Controller(std::string path, Game* g, GameState* gs);
		~Controller();
		
		// MÉTODOS PERTENECIENTES A ENTITY
		void onStep();
		void onRender();

		// MÉTODOS PROPIOS
		// Iniliza lo necesario para el funcionamiento del gameplay
		bool init(std::string path);

		// Cambio de pantalla dentro del mismo mapa
		bool change_screen(Dir dir);

		// El player p solicita un cambio al mapa m con una transición te
		bool change_map(GameData::MapId m, Player* p, TransitionEffect te);
		void attack(int idtool, Player* player);
		
		void setState(State st);
		void setTransitionEffect(TransitionEffect te);

		/*
		// métodos de análisis
		// Avisan al HUD controller de que deben cambiar el correspondiente datos
		void hud_modLife(player, life);
		void hud_modMagic(player, magic);
		void hud_modMoney(player, money);
		void hud_modSelectedTool(player, tool, ammo?);
		void hud_modPlayers();

		*/
};


#endif