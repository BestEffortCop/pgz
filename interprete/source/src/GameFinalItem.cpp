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

#include "GameFinalItem.h"


GameFinalItem::GameFinalItem(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world), iInteractable()
{
	solid = true;
	type = "finalItem";
}

GameFinalItem::~GameFinalItem() 
{

}

void GameFinalItem::init(string graphicpath, Controller* c) {
	controller = c;

	graphic = new Stamp(graphicpath, game->getGfxEngine());
	mask = new MaskBox(x, y, graphic->getWidth(), graphic->getHeight(), "npc", 0, 0); 
}

void GameFinalItem::onEndInteract(){
	controller->changeGameStateTo(Controller::ENDING);
}

void GameFinalItem::onInteract(Player* p) {
	this->controller->getMessageController()->showMessage("Your quest is at end. Congratulations!", this);
}
