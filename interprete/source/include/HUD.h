#pragma once
#ifndef __HUD_H__
#define __HUD_H__

#include "TileTextLabel.h"
#include "Player.h"

class HUD
{
	Player* player;
	int x;
	int y;

	TileFont* font;
	FriendlyTileMap* ihp;
	FriendlyTileMap* iMoney;
	FriendlyTileMap* iKey;

	//El recuadro
	FriendlyTileMap* iWeapon1;
	FriendlyTileMap* iWeapon2;

	//Las armas en si
	Stamp* Weapon1;
	Stamp* Weapon2;

	//Falta dibujar una A encima de la primera arma y una B encima de la segunda

	TileTextLabel* moneyDisplay, *keyDisplay, *fpsDisplay;

	public:
		HUD(int x, int y, Player* player, int w = -1, int h = -1);
		~HUD();

		void setPosition(int x, int y);
		std::pair<int, int> getPosition();

		void refresh();

		void onRender();
};


#endif