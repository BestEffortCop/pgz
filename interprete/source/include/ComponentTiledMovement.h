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
#ifndef __CTILEDMOV_H__
#define __CTILEDMOV_H__

#include "Component.h"

class Enemy;

class ComponentTiledMovement : public Component
{
protected:
	int tileW, tileH;
	bool locked;
	int targetX, targetY;
	int originX, originY;
	bool once;
	int sp;

public:
	ComponentTiledMovement(Game* game, Controller* cont);
	virtual ~ComponentTiledMovement();

	virtual void initSettings(int tileW, int tileH, int speed);

	virtual void onCInit(Enemy* e);
	virtual void onCStep(Enemy* e);
	virtual void onCRender(Enemy* e){};
	virtual void onCTimer(Enemy* e, int timer) {};
	virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e) {};
	virtual void onCDestroy(Enemy* e){};
	virtual void onCCustomEvent(Enemy* e, int event){};
	virtual void onCInitStep(Enemy* e){};
	virtual void onCEndStep(Enemy* e){};
	virtual void onCEndWorld(Enemy* e){};

	void lock();
	void unlock();
	bool isLocked();
	virtual void move(Direction dir, Enemy* e);
	virtual void goBack();
	void snapToGrid(Enemy* e);
	bool isSnapped(Enemy* e);

	int getSpeed();
	void setSpeed(int speed);
};

#endif