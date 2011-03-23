#pragma once
#ifndef __HUDCONTROLLER_H__
#define __HUDCONTROLLER_H__

#include "Entity.h"
#include "Player.h"
#include "HUD.h"



class HUDController : public Entity {


		// CONSTRUCORES Y DESTRUCTORES
		HUDController(Game* g, GameState* gs);
		~HUDController();
		
		// MÉTODOS PERTENECIENTES A ENTITY
		void onStep();
		void onRender();

		// Añade un hud al sistema linkado al Player p (true) o nada si el hud correspondiente al player ya existía.
		bool addHud(Player* p);

};


#endif