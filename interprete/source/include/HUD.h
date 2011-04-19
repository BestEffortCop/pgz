#pragma once
#ifndef __HUD_H__
#define __HUD_H__

#include "TileTextLabel.h"
#include "Player.h"

class HUD
{
	Player* player;
	int x, y;
	int width, height;

	TileFont* font;
	TileTextLabel* hpDisplay, *mpDisplay, *moneyDisplay, *keyDisplay, *fpsDisplay;

	public:
		HUD(int x, int y, Player* player, int w = -1, int h = -1);
		~HUD();

		void setPosition(int x, int y);
		std::pair<int, int> getPosition();

		void refresh();

		void onRender();
};


#endif