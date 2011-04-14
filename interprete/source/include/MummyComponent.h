#pragma once

#ifndef __MUMMYCOMPONENT_H__
#define __MUMMYCOMPONENT_H__

#include "Enemy.h"
#include "Stamp.h"
#include "HelperTypes.h"

class Enemy;

class MummyComponent : public Component
{
	private:
		Direction dir;
		int xtemp, ytemp;
	public:
		MummyComponent(Game* game,Controller* cont);
		~MummyComponent(){};
		
		void onCInit(Enemy* e);
		void onCStep(Enemy* e);
		void onCRender(Enemy* e);
		virtual void onCTimer(Enemy* e, int timer){};
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
		virtual void onCDestroy(Enemy* e){};
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};
};
#endif __MUMMYCOMPONENT_H__
