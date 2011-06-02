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

#ifndef _DUNGEONMAPSTATE_H
#define _DUNGEONMAPSTATE_H

#include "MapStatus.h"

class DungeonMapStatus : public MapStatus 
{
private:
	// Boss derrotado?
	bool bossDefeated;

	// Llave de boss cogida?
	bool gotBossKey;

	// Compás cogido?
	bool gotCompass;

	// Mapa cogido?
	bool gotMap;

	// PowerUp cogido?
	bool gotPowerUp;


public:
	//Instancia el DungeonMapStatus
	DungeonMapStatus();

	//!Destruye el DungeonMapStatus
	~DungeonMapStatus();

	//!Inicializa los atributos de DungeonMapStatus
	//!
	//			\param bossDefeated flag de Boss derrotado.
	//			\param gotBossKey flag de llave del Boss cogida.
	//			\param gotCompass flag de compás cogido.
	//			\param gotMap flad de mapa cogido.
	//			\param gotPowerUp flag de PowerUp cogido.
	void init(/*std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles, std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey, bool gotCompass, bool gotMap, bool gotPowerUp*/);

	//!Getter del flag de boss derrotado
	//!
	//			\return Está el boss derrotado o no
	bool isBossDefeated();

	//!Setter del flag de boss derrotado
	//!
	//			\param bossDefeated nuevo flag que vamos a asignar
	void setBossDefeated(bool bossDefeated);

	//!Getter del flag de llave del boss
	//!
	//			\return Está cogida la llave del boss o no
	bool isBossKeyGot();

	//!Setter del flag de llave del boss
	//!
	//			\param gotBosskey nuevo flag que vamos a asignar
	void setBossKeyGot(bool gotBossKey);

	//!Getter del flag del compas
	//!
	//			\return Está cogido el compás o no
	bool isCompassGot();

	//!Setter del flag del compás
	//!
	//			\param gotBosskey nuevo flag que vamos a asignar
	void setCompassGot(bool gotCompass);

	//!Getter del flag del mapa
	//!
	//			\return Está el mapa cogido o no
	bool isMapGot();

	//!Setter del flag del mapa
	//!
	//			\param gotBosskey nuevo flag que vamos a asignar
	void setMapGot(bool gotMap);

	//!Getter del flag del powerup
	//!
	//			\return Está el powerup cogido o no
	bool isPowerUpGot();

	//!Setter del flag del powerup
	//!
	//			\param gotPowerUp nuevo flag que vamos a asignar
	void setPowerUpGot(bool gotPowerUp);

	void save(FILE* f);
	void load(FILE* f);

};

#endif
