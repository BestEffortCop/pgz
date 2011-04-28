#pragma once
#ifndef _INOTIFICABLE_H_
#define _INOTIFICABLE_H_

#include "Entity.h"

class iNotificable
{
	public:
		iNotificable(){};
		~iNotificable(){};

		virtual void onNotified(Entity* e){};
};

#endif