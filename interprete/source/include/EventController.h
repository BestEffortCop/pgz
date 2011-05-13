#pragma once
#ifndef __EVENTCONTROLLER_H__
#define __EVENTCONTROLLER_H__

#include "Entity.h"
#include "HelperTypes.h"
#include "TileTextLabel.h"
#include "Teleporter.h"
#include "Door.h"
#include "DoorOpenClose.h"
#include "ToolMenu.h"
#include "StateMenu.h"

class Controller;
class ToolMenu;
class StateMenu;

class EventController : public Entity{

	friend class Controller;

	private:

	private:

		// Referencia a la clase padre creadora
		Controller* controller;

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

		ToolMenu* toolMenu;
		StateMenu* stateMenu;

	public:

	// CONSTRUCORES Y DESTRUCTORES
		EventController(Game* g, GameState* gs, Controller* controller);
		~EventController();
		
		void onStep();
		void onRender();
		void onTimer(int timer);

		// Inicia el efecto de transición
		void initTransition(TransitionProperties effect, Image* oldRoom, Image* newRoom);

		void stepTest();

		void launchToolsMenu();
		void launchStatusMenu();
};

#endif