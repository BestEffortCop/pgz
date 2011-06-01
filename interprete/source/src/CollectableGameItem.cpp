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

#include "CollectableGameItem.h"

#include "Player.h"

CollectableGameItem::CollectableGameItem(int x, int y, Game* g, GameState* gs) : GameItem(x, y, g, gs)
{
};

void CollectableGameItem::init(int idCollectable, MapStatus* mapstatus, std::string gfxPath, ItemType t, int power, Controller* c, string n)
{
	name = n;
	controller = c;
	myMapStatus = mapstatus;
	this->idCollectable = idCollectable;
	GameItem::init(gfxPath, t, power);
};

void CollectableGameItem::onInit()
{
	if (myMapStatus->getCollectableStatus(idCollectable))
		setVisible(false), instance_destroy();
};

void CollectableGameItem::applyEffect(Entity* target)
{
	// Una vez actuado, ya nunca más
	if (idCollectable >= 0)
		myMapStatus->setCollectableStatus(idCollectable, true);
	// Se hace al player reproducir animación de oh yeah!
	((Player*) target)->playGetItem(graphic, -1);
	// Pasándole el gráfico y quitándonoloslo para que lo borre player
	graphic = NULL;
	// Y se aplica el efecto
	GameItem::applyEffect(target);
	// Mensajito
	this->controller->getMessageController()->showItemMessage(name);
};