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

#include "TiledPushable.h"

TiledPushable::TiledPushable(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), iPushable()
{
	tileset = new FriendlyTileMap(16,16,game->getGfxEngine());
	mask = new MaskBox(x, y, tileset->getTileWidth(), tileset->getTileHeight(), "semisolid");
	tileId = NULL;

	iPushable::init(1);
};

void TiledPushable::init(std::string tset, int tile, bool foreground)
{
	//Asigno el tileset
	tileset->setTileSet(tset);
	tileId = tile;
	
	//Creo el mapa del tileset
	int**map = (int**) malloc(sizeof(int*));
	map[0] = (int*) malloc(sizeof(int));
	map[0][0] = tile;
	tileset->setMap(map, 1, 1);

	//Asigno el tipo a la mascara
	mask->type = "pushable";

	//Asigno los valores a las distintas propiedades
	type = "pushable";
	collidable = true;
	solid = true;
	depth = y;
};

TiledPushable::~TiledPushable()
{
	delete tileset;
	Entity::~Entity();
}

void TiledPushable::onStep()
{
	depth = y;
}

void TiledPushable::onRender()
{
	if (visible && enabled)
	{
		if (tileset == NULL)
			return;

		tileset->render(x,y);
	}
};