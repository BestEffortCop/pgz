#pragma once
#ifndef __GAMEFINALITEM_H__
#define __GAMEFINALITEM_H__

#include "Player.h"
#include "iInteractable.h"
#include "Controller.h"


class GameEntity;
class iInteractable;

class GameFinalItem : public GameEntity, public iInteractable {
	private:

		Controller* controller;		/* Puntero a Controller */


	public:

		GameFinalItem(int x, int y, Game* game, GameState* world);
		~GameFinalItem();

		void init(string graphicpath, Controller* c);
		void onInteract(Player* p);
		void onEndInteract();
};

#endif