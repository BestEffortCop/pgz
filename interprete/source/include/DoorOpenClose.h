#pragma once
#ifndef __DOOROPENERCLOSE_H__
#define __DOOROPENERCLOSE_H__

#include "DoorOpener.h"
class DoorOpenClose : public DoorOpener
{
public:
	DoorOpenClose(Game* g, GameState* gs);
	~DoorOpenClose();

	void onUnsolve();
	void onSolve();
};

#endif