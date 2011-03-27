#pragma once
#ifndef __HUDCONTROLLER_H__
#define __HUDCONTROLLER_H__

#include "Entity.h"
#include "Player.h"
#include "HUD.h"



class HUDController : public Entity {

	private:

		HUD* HUDS[4];
		int numHUDS;

	public:
		HUDController(Game* g, GameState* gs): Entity(0,0,g,gs){}
		~HUDController();
		
		void onStep(){}
		void onRender(){}

		// Añade un hud al sistema linkado al Player p (true) o nada si el hud correspondiente al player ya existía.
		bool addHud(Player* p);
		void disableHUDs();
		void enableHUDs(){}

		int getNumHUDS();
		HUD* getHUD(int i);
};


#endif