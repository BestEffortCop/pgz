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

#pragma once

#ifndef __COMPONENTDIVIDE_H__
#define __COMPONENTDIVIDE_H__

#include "Component.h"
#include "ComponentTiledMovement.h"

class Enemy;

class ComponentDivide : public Component
{
	protected:

		int minions;

		bool father;
		bool chasing;

		float offspringScale;

		int chaseDistance;
		int speed;
		int standTime;

		enum DivideState { Stand, Move, ReceivingDamage, Divide, Dead};

		DivideState state;

		ComponentTiledMovement* mov;
	public:
		ComponentDivide(Game* game, Controller* cont, bool father = true);
		~ComponentDivide();
		
		void onCInit(Enemy* e);
		void onCStep(Enemy* e);
		void onCRender(Enemy* e);
		virtual void onCTimer(Enemy* e, int timer);
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
		virtual void onCDestroy(Enemy* e);
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};

		void setMinions(int n);
};
#endif __COMPONENTDIVIDE_H__
