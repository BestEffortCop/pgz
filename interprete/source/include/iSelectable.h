#pragma once
#ifndef __I_SELECTABLE_H__
#define __I_SELECTABLE_H__

#include "Graphic.h"

class iSelectable
{
public:

	bool enabled;
	int cursorPlaceX;
	int cursorPlaceY;
	Graphic* cursorDefaultImg;


	iSelectable();
	~iSelectable();

	void onSelected();
	void onDeselected();
	void onBeingDeselected();
	void onChosen();
	void onCancelled();
	void onIddle();
	void setSelected();

};

#endif

