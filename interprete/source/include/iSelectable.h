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
#ifndef __I_SELECTABLE_H__
#define __I_SELECTABLE_H__

#include "Graphic.h"
#include "MaskBox.h"

#include "HelperTypes.h"

#include "GameMenuController.h"

class GameMenuController;

class iSelectable
{

	friend class GameMenuController;

protected:
	GameMenuController* menuController;

	MaskBox* mask;
	Direction cursorLocation;

	void setCursorPlace(Direction dir);

public:

	bool enabled;
	int cursorPlaceX;
	int cursorPlaceY;

	int cursorH, cursorW;
	Graphic* cursorDefaultImg;

	iSelectable(int x = 0, int y = 0, int w = 0, int h = 0);
	virtual ~iSelectable();

	void setCursorLocation(Direction dir);
	void setMenuController(GameMenuController* menuController);
	void setDimension(int x, int y, int w, int h);

	virtual void onSelected();
	virtual void onDeselected();
	virtual void onBeingDeselected();
	virtual void onChosen();
	virtual void onCancelled();
	virtual void onIddle();
	virtual void onStartPressed();
	virtual void onSelectPressed();


	void setSelected();
	bool isSelected();
};

#endif