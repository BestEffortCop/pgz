#pragma once
#ifndef __TILEDENTITY_H__
#define __TILEDENTITY_H__

#include "Entity.h"
#include "Tileset.h"

class TiledEntity : public Entity
{
private:
	TileSet* tileset;
	int tileId;
public:
	TiledEntity(int x, int y, Game* g, GameState* gs);

	void init(TileSet* tset, int tile, bool foreground = false);

	void onRender();
};

#endif