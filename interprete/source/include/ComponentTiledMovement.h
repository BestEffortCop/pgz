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
};

#endif