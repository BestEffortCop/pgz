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
	// mover en base al peso si no estamos locked
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

	if (ent->world->place_free(ent->x, ytemp, ent)){    
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
	}

	return make_pair(abs(ent->x - xorig), abs(ent-> y - yorig));
}