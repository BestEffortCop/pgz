#pragma once

#ifndef __ENTITY_READER_H__
#define __ENTITY_READER_H__

#include <stdio.h>
#include <vector>
#include "Entity.h"

class EntityReader 
{
	public:
		EntityReader();
		~EntityReader();

		bool readEntities(FILE* file, vector<Entity*>* screenEntities);

};


#endif