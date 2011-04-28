#pragma once
#ifndef _TILEDPUSHABLE_H_
#define _TILEDPUSHABLE_H_

#include "Entity.h"
#include "Stamp.h"
#include "Player.h"
#include "iPushable.h"
#include "HelperTypes.h"
#include <set>

class TiledPushable : public iPushable, public Entity
{
private:
	FriendlyTileMap* tileset;
	int tileId;
public:

	TiledPushable(int x, int y, Game* g, GameState* gs);
	~TiledPushable();

	void init(std::string tset, int tile, bool foreground = false);
	void onStep();
	void onRender();
};

#endif