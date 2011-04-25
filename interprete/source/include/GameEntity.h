#pragma once

#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__

#include "Entity.h"
#include "Stamp.h"


class GameEntity : public Entity
{
	public: 
		enum Size { sNone, sSmall, sMedium, sBig };
	protected:
		Size size;
		Graphic* gfxShadow;
		bool paused;

	public:
		GameEntity(int x, int y, Game* game, GameState* world);
		~GameEntity();

		void initShadow(GameEntity::Size size = sNone);

		virtual void onRender();

		virtual void pause();
		virtual void unpause();
		virtual bool isPaused();
};

#endif
