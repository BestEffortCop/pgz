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

#include "HUDController.h"

HUDController::HUDController(Game* g, GameState* gs) : Entity(0, 0, g, gs)
{
	numHUDs = 0;
	collidable = false;
};

HUDController::~HUDController()
{
	for (int i = 0; i < numHUDs; i++)
		if (HUDS[i] != NULL) delete HUDS[i], HUDS[i] = NULL;
};

void HUDController::onStep()
{
	if (visible && enabled)
		for (int i = 0; i < numHUDs; i++)
			HUDS[i]->refresh();
};

void HUDController::onRender()
{
	if (visible && enabled)
		for (int i = 0; i < numHUDs; i++)
			HUDS[i]->onRender();
};

bool HUDController::addHud(Player* p)
{
	if (numHUDs > 4)
		return false;
	else
	{
		if (numHUDs == 0)
			HUDS[numHUDs] = new HUD(0, 0, p);
		else
			HUDS[numHUDs] = new HUD(0, 208, p);
		numHUDs++;
	}

	return true;
};

void HUDController::enableHUDs()
{
	this->enable();
};

void HUDController::disableHUDs()
{
	this->disable();
};

int HUDController::getNumHUDS()
{
	return numHUDs;
};

HUD* HUDController::getHUD(int num)
{
	if (num >= numHUDs)
		return NULL;
	else return HUDS[num];
};