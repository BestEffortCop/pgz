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

#include "iPushable.h"

iPushable::iPushable(){
	init(stepPushDist, useConstraints);
}

iPushable::iPushable(int stepPushDist, bool useConstraints){
	init(stepPushDist, useConstraints);
}

void iPushable::init(int stepPushDist, bool useConstraints){
	this->stepPushDist = stepPushDist;
	this->useConstraints = useConstraints;
	locked = false;
}

iPushable::~iPushable(){
}

std::pair<int, int> iPushable::onPush(Entity *ent, Direction dir){
	// mover en base al stepPushDist si no estamos locked
	if(!locked){
		// Mover en las direcciones aceptadas por los constraints
		if(useConstraints) 
			if(pushConstraints.find(dir) != pushConstraints.end()){
				return move(ent, dir);
			}
			else 
				return make_pair(0, 0);

		// Mover sin restricciones
		return move(ent, dir);
	}
	return make_pair(0, 0);
}

void iPushable::lockPush(){
	locked = true;
}

void iPushable::unlockPush(){
	locked = false;
}

bool iPushable::isLockedPush(){
	return locked;
}

void iPushable::setConstraints(set<Direction> pushConstrains){
	this->pushConstraints = pushConstrains;
	useConstraints = true;
}

std::pair<int, int> iPushable::move(Entity *ent, Direction dir){
	int xtemp, ytemp;
	int xorig, yorig;

	xorig = ent->x;
	yorig = ent->y;

	switch (dir) {
		case UP:
			xtemp = ent->x;
			ytemp = ent->y-stepPushDist;
			break;
		case DOWN:
			xtemp = ent->x;
			ytemp = ent->y+stepPushDist;
			break;
		case LEFT:
			xtemp = ent->x-stepPushDist;
			ytemp = ent->y;
			break;
		case RIGHT:
			xtemp = ent->x+stepPushDist;
			ytemp = ent->y;
			break;
	}

	if (xtemp == ent->x && ytemp == ent->y)
		return make_pair(0, 0);

	/*if (ent->world->place_free(ent->x, ytemp, ent)){    
			ent->y = ytemp; 
		}
		else{   
			ent->world->moveToContact(ent->x,ytemp, ent);
		}

	if (ent->world->place_free(xtemp, ent->y, ent)){    
		ent->x = xtemp; 
	}
	else{   
		ent->world->moveToContact(xtemp,ent->y, ent); 
	}*/

	if (!ent->world->place_free(xtemp, ytemp, ent))
		ent->world->moveToContact(xtemp, ytemp, ent);
	else
		ent->x = xtemp, ent->y = ytemp;

	return make_pair(abs(ent->x - xorig), abs(ent-> y - yorig));
}