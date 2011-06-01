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