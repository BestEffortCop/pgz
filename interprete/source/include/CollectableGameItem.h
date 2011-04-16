#pragma once
#ifndef __COLLECTABLE_H__
#define __COLLECTABLE_H__

#include "MapStatus.h"
#include "GameItem.h"

class CollectableGameItem : public GameItem
{
private:
	int idCollectable;
	MapStatus* myMapStatus;

	void applyEffect(Entity* target);
public:
	CollectableGameItem(int x, int y, Game* g, GameState* gs);

	void onInit();
	void init(int idCollectable, MapStatus* mapstatus, std::string gfxPath, ItemType t, int power);
};

#endif