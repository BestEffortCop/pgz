#pragma once
#ifndef __PTLIGHT_H__
#define __PTLIGHT_H__

#include "Entity.h"
#include "GamePuzzleListener.h";

class PuzzleTesterLight : public Entity, public GamePuzzleListener
{
protected:
	Color* c;
public:
	PuzzleTesterLight(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleListener()
	{
		c = new Color(255, 255, 255);
		collidable = false;
	};

	~PuzzleTesterLight()
	{
		delete c;
	};

	void onSolve()
	{
		c->r = 0; c->g = 255; c->b = 50;
	};

	void onUnsolve()
	{
		c->r = 255; c->g = 255; c->b = 255;
	};

	void onRender()
	{
		game->getGfxEngine()->renderRectangle(x, y, 8, 8, *c);
	};
};

#endif