#pragma once
#ifndef __FLOORBUTTON_H__
#define __FLOORBUTTON_H__

#include "Entity.h"
#include "GamePuzzleElement.h"
#include "SpriteMap.h"

class FloorButton : public Entity, public GamePuzzleElement
{
protected:
	bool onceSolved;
	bool onceUnsolved;
public:
	FloorButton(int x, int y, Game* g, GameState* gs);
	~FloorButton();

	void onStep();
	void onRender();

	void FloorButton::init(GamePuzzle* puzzle, std::string gfxpath);

	void onCollision(CollisionPair p, Entity* other);
};

#endif