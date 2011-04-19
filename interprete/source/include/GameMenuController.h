#pragma once
#ifndef __GAME_MENUCONTROLLER_H__
#define __GAME_MENUCONTROLLER_H__

#include "GameMenuItem.h"
#include "iSelectable.h"
#include <list>

class GameMenuController : public GameMenuItem
{
protected:
	list<iSelectable*>* selectableList;
	list<GameMenuItem*>* menuItemList;
public:

	int cursorPosX;
	int cursorPosY;
	Graphic* cursorImage;
	bool cursorEnable;
	iSelectable* selected;

	GameMenuController(int x, int y, Game* game, GameState* gstate);
	~GameMenuController();

	void onRender();
	void onStep();

	void launch();
	void quit();

	void setCursorPos(int x, int y);
	void setCursorImage(Graphic* g);

	void addSelectable(iSelectable* selectable);
	void addMenuItem(GameMenuItem* menuItem);

	iSelectable* getSelectable(Direction dir);

};


#endif