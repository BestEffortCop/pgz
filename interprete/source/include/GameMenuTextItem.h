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
#ifndef __GAME_MENUTEXTITEM_H__
#define __GAME_MENUTEXTITEM_H__

#include "GameMenuItem.h"
#include "TileTextLabel.h"

class GameMenuTextItem : public GameMenuItem
{
protected:

	TileFont* font;
	TileTextLabel* textLabel;

	std::string text;

public:
	// Constructora si el texto es un TileTextLabel
	GameMenuTextItem(std::string text, TileFont* font, int x, int y, Game* game, GameState* gstate);

	~GameMenuTextItem();

	void setPos(int x, int y);
	void setText(std::string s);

	TileTextLabel* getText();

	// Cambia el texto a TileTextLabel con la nueva fuente
	void setFont(TileFont* font);
};

#endif