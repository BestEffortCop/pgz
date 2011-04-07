#include "EntityReader.h"


EntityReader::EntityReader()
{
}

EntityReader::~EntityReader()
{
}

bool EntityReader::readEntities(FILE* file, vector<Entity*>* screenEntities)
{
	short nentBuf[1];
	if (fread(nentBuf, sizeof(nentBuf), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nentities = nentBuf[0];


	short entitiesBuf[6];
	for (int i = 0; i < nentities; i++)
	{
		if (fread(entitiesBuf, sizeof(entitiesBuf), 1, file) < 1)
			return false;

		// Use them if needed, add them to screenEntities
	}

	return true;
}