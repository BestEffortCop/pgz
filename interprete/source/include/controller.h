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
		
		enum State {NORMAL, TRANSITION};
		enum TransitionEffect {SCROLL, FADE};

		// Estado del controlador
		State state;
		
		// Alto y ancho del juego
		int width;
		int height;
		
		(Player*)* players;
		Entity* hud;
		int numPlayers;

		GameData* data;
		// mapa actual
		ScreenMap* screenMap;
		
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
		Controller(Game* g, GameState* gs, int players);
		~Controller();
		
		// MÉTODOS PERTENECIENTES A ENTITY
		void onStep();
		void onRender();

		// MÉTODOS PROPIOS
		bool change_screen(Dir dir);
		bool change_map();
		void attack(int idtool, Player* player);
		
		void setState(State st);
		void setTransitionEffect(TransitionEffect te);
};


#endif