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