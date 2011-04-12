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

bool iPushable::onPush(Direction dir, int &x, int& y){
	// mover en base al peso si no estamos locked
	if(!locked){
		if(useConstraints)
		// Mover en las direcciones aceptadas por los constraints
		//TODO
		return true;
		// Mover sin restricciones
		//TODO
	}
	return false;
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

void iPushable::setConstraints(vector<Direction> pushConstrains){
	this->pushConstraints = pushConstrains;
	useConstraints = true;
}