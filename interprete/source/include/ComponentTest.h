#pragma once
#ifndef __CTESTER_H__
#define __CTESTER_H__

#include "ComponentTiledMovement.h"

class Enemy;

class ComponentTester : public Component
{
protected:
	ComponentTiledMovement* tiledMov;

	enum TestState { Stand, Move, Attack };
	TestState state;

public:
	ComponentTester(Game* game, Controller* cont);
	virtual ~ComponentTester();

	virtual void onCInit(Enemy* e);
	virtual void onCStep(Enemy* e);
	virtual void onCRender(Enemy* e){};
	virtual void onCTimer(Enemy* e, int timer);
	virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
	virtual void onCDestroy(Enemy* e){};
	virtual void onCCustomEvent(Enemy* e, int event){};
	virtual void onCInitStep(Enemy* e){};
	virtual void onCEndStep(Enemy* e){};
	virtual void onCEndWorld(Enemy* e){};

	void hitPlayer(Enemy* e, Player* p);
};

#endif