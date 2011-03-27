#pragma once
#ifndef __EVENTCONTROLLER_H__
#define __EVENTCONTROLLER_H__

#include "Entity.h"
#include "controller.h"

class Controller;

class EventController : public Entity{

	private:
	
		// Referencia a la clase padre creadora
		Controller* controller;


	public:

	// CONSTRUCORES Y DESTRUCTORES
		EventController(Game* g, GameState* gs, Controller* controller);
		~EventController();
		
		void onStep();
		void onRender();
		void onTimer(int timer);

};

#endif