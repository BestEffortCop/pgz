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

#ifndef __DAMAGEABLEBLOCKADE_H__
#define __DAMAGEABLEBLOCKADE_H__

#include "Entity.h"
#include "iDamageable.h"
#include "SpriteMap.h"

using namespace std;


class DamageableBlockade: public Entity, public iDamageable
{
private:
	bool dying;

public:
	enum BlockadeAnim { Stand, Death };

	DamageableBlockade(int x, int y, Game* game, GameState* gameState);
	//Indica la debilidad ante la cual el bloque caerá
	void init(short typeWeakness,string gfxPath, int xColision, int yColision);
	void onDeath();

	bool loadAnimations(string fname);
	bool loadAnimation(BlockadeAnim anim, string name, FILE* from);

	void onStep();

	//Metodo temporal, deberia avisar el arma a onDamage, no yo
	//void onCollision(CollisionPair other, Entity* e);
};
#endif __DAMAGEABLEBLOCKADE_H__