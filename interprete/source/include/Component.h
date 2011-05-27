#pragma once

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Controller.h"
#include "Enemy.h"

class Enemy;

class Component
{
	protected:
		Controller* cont;
		Game* game;
	public:
		Component(){};
		virtual ~Component(){};
		
		virtual void onCInit(Enemy* e){};
		virtual void onCStep(Enemy* e){};
		virtual void onCRender(Enemy* e){};
		virtual void onCTimer(Enemy* e, int timer){};
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e){};
		virtual void onCDestroy(Enemy* e){};
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};

		enum ComponentType { CompDummy, CompAnim, CompAnimFlying, CompTiledMovement, CompBat, CompMelee, CompMeleeSimple, CompTackle, CompRanged, CompDivide };
};
#endif __COMPONENT_H__
