#pragma once
#ifndef __EVENTCONTROLLER_H__
#define __EVENTCONTROLLER_H__

#include "Entity.h"
#include "HelperTypes.h"
#include "MenuTest.h"
#include "MainMenuTest.h"
#include "TileTextLabel.h"

class Controller;

class EventController : public Entity{

	friend class Controller;

	private:

		// Referencia a la clase padre creadora
		Controller* controller;

		enum TransitionEffect {SCROLL, FADE};

		struct TransitionProperties
		{
			TransitionEffect effect;
			int speed;
			Direction direction;
		};

		/* Transition thingies */
		int width, height;
		int mx, my, tx, ty;
		int xdir, ydir;
		int xpos, ypos;
		int speed;
		TransitionProperties currentTrans;
		Image* currentRoom;
		Image* nextRoom;

		/* Test */
		bool fadeOut;
		int maxCounter;
		float falpha;

	public:

	// CONSTRUCORES Y DESTRUCTORES
		EventController(Game* g, GameState* gs, Controller* controller);
		~EventController();
		
		void onStep();
		void onRender();
		void onTimer(int timer);

		// Inicia el efecto de transición
		void initTransition(TransitionProperties effect, Image* oldRoom, Image* newRoom);
};

#endif