#pragma once
#ifndef __GAME_MENUCONTROLLER_H__
#define __GAME_MENUCONTROLLER_H__

#include "GameMenuItem.h"

class GameMenuController : public GameMenuItem
{
public:

	int cursorPosX;
	int cursorPosY;
	Graphic* cursorImage;

	GameMenuController(int x, int y, Game* game, GameState* gstate);
	~GameMenuController();

	void onRender();
	void onUpdate();
	void setCursorPos(int x, int y);
	void setCursorImage(Graphic* g);
	//void getMenuItem()
};


#endif