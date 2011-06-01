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

#include "GameEntity.h"
#include "PGZGame.h"

GameEntity::GameEntity(int x, int y, Game* game, GameState* world):Entity(x,y,game,world)
{
	gfxShadow = NULL;
	size = sNone;
	paused = false;
};

GameEntity::~GameEntity()
{
	if (gfxShadow != NULL)
		delete gfxShadow, gfxShadow = NULL;
};

void GameEntity::initShadow(Size s)
{
	if (gfxShadow != NULL)
	{
		delete gfxShadow;
		gfxShadow = NULL;
	}

	// Si no nos pasan tamaño, suponemos que ya está puesto
	// y si no está puesto, es que no se quiere sombra
	if (s == sNone && size == sNone)
		return;
	else if (s == sNone && size != sNone)
		s = size;
	
	
	gfxShadow = new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getShadowGfxPath(s), game->getGfxEngine());

	/*switch (s)
	{
	case sNone:
		break;
	case sSmall:
		// Las rutas las dará dbi en algún momento
		gfxShadow = new Stamp("data/graphics/shadow-s.png", game->getGfxEngine());
		break;
	case sMedium:
		gfxShadow = new Stamp("data/graphics/shadow-m.png", game->getGfxEngine());
		break;
	default:
		break;
	}*/

	if (gfxShadow != NULL)
		gfxShadow->setAlpha(0.7f);
};

void GameEntity::onRender()
{
	if (gfxShadow != NULL && mask != NULL && visible && enabled)
	{
		gfxShadow->render(x + (mask->xoffset + mask->width / 2 - ((Stamp *)gfxShadow)->getWidth()/2), y + (mask->yoffset + mask->height - ((Stamp *)gfxShadow)->getHeight()/2 - 2));
	}

	if (visible && enabled)
		Entity::onRender();
};

void GameEntity::pause()
{
	paused = true;
};

void GameEntity::unpause()
{
	paused = false;
};

bool GameEntity::isPaused()
{
	return paused;
};