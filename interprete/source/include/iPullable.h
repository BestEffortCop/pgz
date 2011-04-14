#pragma once

#ifndef __I_PULLABLE_H__
#define __I_PULLABLE_H__

#include "HelperTypes.h"
#include "Entity.h"
#include "Controller.h"
#include <set>

using namespace std;

class iPullable
{
	private:
		bool locked;
		bool useConstraints;
		set<Direction> pullConstraints;
		std::pair<int, int> move(Entity *ent, Direction dir);
		
	public:
		// Distancia pullable en cada step
		int stepPullDist;
		
		// Por defecto será pullable
		iPullable();
		iPullable(int stepPullDist, bool useConstraints = false);
		virtual ~iPullable();

		void init(int stepPullDist, bool useConstraints = false);
		void lockPull();
		void unlockPull();
		bool isLockedPull();

		// Pullea y devuelve si ha sido pulled con éxito.
		// Param ent: nosotros (lo que va a ser pulled)
		// Param dir: dirección en la que nos pullean.
		virtual std::pair<int, int> onPull(Entity *ent, Direction dir);

		// Indicamos en qué direcciones puede pullearse (Activa los constraints)
		void setConstraints(set<Direction> pushConstrains);
};


#endif
