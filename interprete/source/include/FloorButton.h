#pragma once
#ifndef __FLOORBUTTON_H__
#define __FLOORBUTTON_H__

#include "Entity.h"
#include "GamePuzzleElement.h"
#include "Stamp.h"

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

	void FloorButton::init(GamePuzzle* puzzle);

	void onCollision(CollisionPair p, Entity* other);
};

#endif