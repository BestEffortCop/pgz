#pragma once

#ifndef __I_PUSHABLE_H__
#define __I_PUSHABLE_H__

#include "HelperTypes.h"
#include "Entity.h"
#include "Controller.h"
#include <set>

using namespace std;

class Controller;

class iPushable
{
	private:
		bool locked;
		bool useConstraints;
		set<Direction> pushConstraints;
		std::pair<int, int> move(Entity *ent, Direction dir);
		
	public:
		// Distancia empujable en cada step
		int stepPushDist;
		
		// Por defecto será empujable
		iPushable();
		iPushable(int stepPushDist, bool useConstraints = false);
		virtual ~iPushable();

		void init(int stepPushDist, bool useConstraints = false);
		void lockPush();
		void unlockPush();
		bool isLockedPush();

		// Empuja y devuelve si ha sido empujado con éxito.
		// Param ent: nosotros (lo que va a ser empujado)
		// Param dir: dirección en la que nos empujan.
		virtual std::pair<int, int> onPush(Entity *ent, Direction dir);

		// Indicamos en qué direcciones puede empujarse (Activa los constraints)
		void setConstraints(set<Direction> pushConstrains);
};

#endif
