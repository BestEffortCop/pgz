/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

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
#include "GameOverMenu.h"

class Controller;
class ToolMenu;
class StateMenu;
class GameOverMenu;

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
		GameOverMenu* gameOver;

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
		void closeGameOverMenu();
};

#endif