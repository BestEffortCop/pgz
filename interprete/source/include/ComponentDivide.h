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
