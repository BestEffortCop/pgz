/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "GameMenuTextItem.h"


GameMenuTextItem::GameMenuTextItem(std::string text, TileFont* font, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	this->text = text;
	//font = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());
	this->font = font;
	graphic = new TileTextLabel(text,font,game->getGfxEngine());
	textLabel = (TileTextLabel*) graphic;
}

GameMenuTextItem::~GameMenuTextItem()
{
}

void GameMenuTextItem::setPos(int x, int y)
{
	GameMenuItem::setPos(x, y);
}

void GameMenuTextItem::setText(std::string s)
{
	this->text = s;
	textLabel->setText(s);
}

TileTextLabel* GameMenuTextItem::getText()
{
	return textLabel;
}

void GameMenuTextItem::setFont(TileFont* font)
{
	if (graphic != NULL)
		delete graphic;

	this->font = font;
	graphic = new TileTextLabel(text,font,game->getGfxEngine());
	textLabel = (TileTextLabel*) graphic;
}