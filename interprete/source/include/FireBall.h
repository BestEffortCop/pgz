#pragma once
#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "Entity.h"
#include "HelperTypes.h"

class FireBall : public Entity {
	private:
		int sp;
		Direction dir;
	public:

		FireBall(Direction dir, int x, int y, Game* g, GameState* gs);
		~FireBall();

		void init(string graphicpath, int ncol, int nrow);
		void onStep();
		void onCollision(Entity* e);
		//void onTimer(int i);

};

#endif