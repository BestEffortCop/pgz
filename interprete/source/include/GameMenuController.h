#pragma once
#ifndef __GAME_MENUCONTROLLER_H__
#define __GAME_MENUCONTROLLER_H__

#include "GameMenuItem.h"
#include "iSelectable.h"
//#include "PGZGame.h"

#include <list>

class iSelectable;

class GameMenuController : public GameMenuItem
{
protected:
	list<iSelectable*>* selectableList;
	list<GameMenuItem*>* menuItemList;

	Direction lastDir;	
	InputConfig inputConfig;

public:

	struct MenuInput 
	{
		float xAxis, yAxis;
		ButtonState buttonA, buttonB, buttonSTART, buttonSELECT;
	};

	MenuInput currentInput;

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
	void removeSelectable(iSelectable* selectable);
	void removeMenuItem(GameMenuItem* menuItem);

	iSelectable* getSelectable(Direction dir);
	virtual iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	virtual iSelectable* getAlternativeSelectable(iSelectable* slc, Direction dir);

	void setSelected(iSelectable* i);

	void GameMenuController::parseInput();

	// Todos los eventos de los items del menu pueden definirse en el menu controller si se desea
	virtual void onSelected(iSelectable* selectable = NULL);
	virtual void onDeselected(iSelectable* selectable = NULL);
	virtual void onBeingDeselected(iSelectable* selectable = NULL);
	virtual void onChosen(iSelectable* selectable = NULL);
	virtual void onCancelled(iSelectable* selectable = NULL);
	virtual void onIddle(iSelectable* selectable = NULL);
	virtual void onStartPressed(iSelectable* selectable = NULL);
	virtual void onSelectPressed(iSelectable* selectable = NULL);

	void setInputConfig(InputConfig ic);
	InputConfig getInputConfig();
};


#endif