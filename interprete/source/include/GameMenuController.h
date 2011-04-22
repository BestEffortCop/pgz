#pragma once
#ifndef __GAME_MENUCONTROLLER_H__
#define __GAME_MENUCONTROLLER_H__

#include "GameMenuItem.h"
#include "iSelectable.h"
#include <list>

class iSelectable;

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
	virtual ~GameMenuController();

	virtual void onRender();
	virtual void onStep();

	virtual void launch();
	virtual void quit();

	void setCursorPos(int x, int y);
	void setCursorImage(Graphic* g);

	void addSelectable(iSelectable* selectable);
	void addMenuItem(GameMenuItem* menuItem);

	iSelectable* getSelectable(Direction dir);

	void setSelected(iSelectable* i);


	// Todos los eventos de los items del menu pueden definirse en el menu controller si se desea
	virtual void onSelected(iSelectable* selectable);
	virtual void onDeselected(iSelectable* selectable);
	virtual void onBeingDeselected(iSelectable* selectable);
	virtual void onChosen(iSelectable* selectable);
	virtual void onCancelled(iSelectable* selectable);
	virtual void onIddle(iSelectable* selectable);
};


#endif