#pragma once
#ifndef __GAMEPLAYSTATE_H__
#define __GAMEPLAYSTATE_H__

#include <list>

#include "GameState.h"
#include "controller.h"
#include "TileTextLabel.h"
#include "ScreenMap.h"

class Controller;

class GamePlayState : public GameState
{
	friend class Controller;

	protected:

		list<Entity*>* localEntities;

        bool _add(Entity* e);
        bool _remove(Entity* e);

		int offsetX, offsetY;

		HUDController* hudController;

	public:

		// Constructora
		GamePlayState(int w, int h, Game* g);

		// Destructora
		~GamePlayState();

		// Método propio sobre lista eliminables
		bool add(Entity* e, bool local);
		// Sobrecarga del método del padre para utilizar la lista de eliminables
		// (Se da por hecho que quien use este add no sabe que GamePlayState es como es
		// y por tanto debe borrarse la entidad)
		bool add(Entity* e);

		// Sobrecarga del método del padre para utilizar la lista de eliminables
		bool remove(Entity* e);

		// Envoltorio del método del padre para utilizar la lista de eliminables
		// que comprueba automaticamente si la entidad está en deathRow
		bool removeLocals();

		// Temporal
		void renderBG();

		void renderFG();

		void onStep();

		void onRender();

		void setOffset(int x, int y);
		std::pair<int, int> getOffset();
};

#endif
