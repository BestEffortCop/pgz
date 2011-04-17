#pragma once
#ifndef __NPC_H__
#define __NPC_H__

#include "Player.h"
#include "iInteractable.h"
#include "Stamp.h"

class NPC : public GameEntity, public iInteractable {
	private:

		enum State {move, idle};

		Direction dir;
		int ox, oy;
		int sp;
		State state;
	public:

		NPC(int x, int y, Game* game, GameState* world);
		~NPC();

		void init(string graphicpath, int ncol, int nrow);
		bool animFinished();
		void onTimer(int timer);
		void onInteract(Player* p);
		void onStep();

};
#endif