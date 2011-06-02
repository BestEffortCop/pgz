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

#ifndef __SCREENMAP_H__
#define __SCREENMAP_H__

#include "HelperTypes.h"

#include "Map.h"
#include "Enemy.h"
#include "ScreenMapConstructor.h"
#include <vector>

using namespace std;

class ScreenMap;
class Enemy;

class ScreenMap: public Map
{

	friend class ScreenMapConstructor;

protected:

	std::list< EnemySpawnData * > enemies;
	MapLocation screenLocation;

	//map<int,bool>* enemies;		//Mapa de id de enemigos de la pantalla y si han de ser creados o no cuando se cargue la pantalla
	int width;					//Ancho de la pantalla
	int height;					//Alto de la pantalla
	int x;						//Coordenada x absoluta del ScreenMap
	int y;						//Coordenada y absoluta del ScreenMap

public:

	// Tipos de cambio sobre las entidades de la pantalla
	enum ChangeType { eNONE, eMODIFY, eCREATE, eDESTROY };

	//Constructora parametrizada
	ScreenMap(int width, int height, int tileW, int tileH, int x, int y, GfxEngine* gfxEngine);
	
	//Destructora por defecto
	~ScreenMap();

	//Comprueba si la entidad que le pasan colisiona con su solidGrid
	vector<CollisionPair>* checkColision(Entity* e);

	//Comprueba si la entidad que le han pasado está dentro de los limites del mapa
	bool isInBounds(Entity* e);  

	// Notifica al mapa de un cambio sobre una de sus entidades
	void notify(ChangeType change, Entity* e);

	//Función de actualización
	void update();

	//Función de pintado
	void render();

	//Devuelve la dirección del mapa por la que se está saliendo el player en caso
	//de que esté aún dentro de la pantalla devuelve NONE
	Direction relative_position(Entity* p, bool & out);

	void setRows(int row);

	void setCols(int col);

	void setScreenLocation(MapLocation screenLocation);
	MapLocation getScreenLocation();

	ScreenMapConstructor* getConstructor();

	//Actualiza su lista de entidades con el vector de IDs de enemigo que le pasan
/*	void setEnemies(vector<int>* enemies);
	 
	//Decvuelve el map de enemigos y si han de ser o no creados
	map<int,bool>* getEnemies();*/
};

#endif __SCREENMAP_H__