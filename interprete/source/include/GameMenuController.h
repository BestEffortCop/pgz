/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

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