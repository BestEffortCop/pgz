/*#include "iPullable.h"

iPullable::iPullable(){
	init(stepPullDist, useConstraints);
}

iPullable::iPullable(int stepPullDist, bool useConstraints){
	init(stepPullDist, useConstraints);
}

void iPullable::init(int stepPullDist, bool useConstraints){
	this->stepPullDist = stepPullDist;
	this->useConstraints = useConstraints;
	locked = false;
}

iPullable::~iPullable(){
}

std::pair<int, int> iPullable::onPull(Entity *ent, Direction dir){
	// mover en base al stepPullDist si no estamos locked
	if(!locked){
		// Mover en las direcciones aceptadas por los constraints
		if(useConstraints) 
			if(pullConstraints.find(dir) != pullConstraints.end()){
				return move(ent, dir);
			}
			else 
				return make_pair(0, 0);

		// Mover sin restricciones
		return move(ent, dir);
	}
	return make_pair(0, 0);
}

void iPullable::lockPull(){
	locked = true;
}

void iPullable::unlockPull(){
	locked = false;
}

bool iPullable::isLockedPull(){
	return locked;
}

void iPullable::setConstraints(set<Direction> pullConstrains){
	this->pullConstraints = pullConstrains;
	useConstraints = true;
}

std::pair<int, int> iPullable::move(Entity *ent, Direction dir){
	int xtemp, ytemp;
	int xorig, yorig;

	xorig = ent->x;
	yorig = ent->y;

	switch (dir) {
		case UP:
			xtemp = ent->x;
			ytemp = ent->y-stepPullDist;
			break;
		case DOWN:
			xtemp = ent->x;
			ytemp = ent->y+stepPullDist;
			break;
		case LEFT:
			xtemp = ent->x-stepPullDist;
			ytemp = ent->y;
			break;
		case RIGHT:
			xtemp = ent->x+stepPullDist;
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
}*/