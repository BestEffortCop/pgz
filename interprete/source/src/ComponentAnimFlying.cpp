/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "ComponentAnimFlying.h"


ComponentAnimFlying::ComponentAnimFlying(Game* game, Enemy* e, std::string gfxPath) : ComponentAnim(game, e, gfxPath)
{
	height = 0;
	period = 1;
	amplitude = 0;
	phase = 1;
}


ComponentAnimFlying::~ComponentAnimFlying()
{
}

void ComponentAnimFlying::init(int height, float period, int amplitude, int phase)
{
	this->height = height;
	this->period = period;
	this->amplitude = amplitude;
	this->phase = phase;
}

void ComponentAnimFlying::onCInit()
{
	e->cAnim->setHeight(height);
	e->setTimer(1, rand()%phase);
	ComponentAnim::onCInit();
}

void ComponentAnimFlying::onCStep()
{
	e->cAnim->setHeight(height + (int) (sin((float) e->getTimer(1)*period)*amplitude));
	ComponentAnim::onCStep();
}

void ComponentAnimFlying::onCRender()
{
	ComponentAnim::onCRender();
}

void ComponentAnimFlying::onCTimer(int timer)
{
	if (timer == 1)
			e->setTimer(1, 359);
	ComponentAnim::onCTimer(timer);
}
