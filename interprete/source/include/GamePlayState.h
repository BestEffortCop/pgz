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

#pragma once
#ifndef __GAMEPLAYSTATE_H__
#define __GAMEPLAYSTATE_H__

#include <list>

#include "GameState.h"
#include "controller.h"
#include "TileTextLabel.h"
#include "ScreenMap.h"

class Controller;

class GamePlayState : public GameState
{
	friend class Controller;

	protected:

		list<Entity*>* localEntities;

        bool _add(Entity* e);
        bool _remove(Entity* e);

		int offsetX, offsetY;

		HUDController* hudController;

	public:

		// Constructora
		GamePlayState(int w, int h, Game* g);

		// Destructora
		~GamePlayState();

		// Método propio sobre lista eliminables
		bool add(Entity* e, bool local);
		// Sobrecarga del método del padre para utilizar la lista de eliminables
		// (Se da por hecho que quien use este add no sabe que GamePlayState es como es
		// y por tanto debe borrarse la entidad)
		bool add(Entity* e);

		// Añade la entidad al buffer de locales
		bool addLocal(Entity* e);

		// Sobrecarga del método del padre para utilizar la lista de eliminables
		bool remove(Entity* e);

		// Envoltorio del método del padre para utilizar la lista de eliminables
		// que comprueba automaticamente si la entidad está en deathRow
		bool removeLocals();

		void hideLocals();

		// Temporal
		void renderBG();

		void renderFG();

		void onStep();

		void onRender();

		void setOffset(int x, int y);
		std::pair<int, int> getOffset();

		void pauseGameEntities();
		void unpauseGameEntities();

		Map* getMap();
};

#endif
