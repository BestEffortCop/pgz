#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


#include "Entity.h"
#include "iInteractable.h"

class iInteractable {
	void onInteract();
}

enum State {NORMAL, TRANSITION};
enum TransitionEffect {SCROLL, FADE};

class Controller : public Entity {

	private:
	
		// Estado del controlador
		State state;
		
		// Alto y ancho del juego
		int width;
		int height;
		
		Player* player;
		int numPlayers;
		
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
		
	public:
		// CONSTRUCORES Y DESTRUCTORES
		Controller();
		~Controller();
		
		// MÉTODOS PERTENECIENTES A ENTITY
		void onStep();
		void onRender();

		// MÉTODOS PROPIOS
		void change_screen(Dir dir);
		void change_map();
		void attack(int idtool, objPlayer* player);
		
		void setState();
		void setTransitionEffect(TransitionEffect te);
};


#endif