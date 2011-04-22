#include "EntityReader.h"

#include "CollectableGameItem.h"
#include "TiledEntity.h"


EntityReader::EntityReader(Game* g, GameState* gs, DataBaseInterface* dbi)
{
	game = g;
	gamestate = gs;
	this->dbi = dbi;
};

EntityReader::~EntityReader()
{
};

bool EntityReader::readEntities(FILE* file, vector<Entity*>* screenEntities)
{
	short nentBuf[1];
	if (fread(nentBuf, sizeof(short), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nentities = nentBuf[0];

	std::list<Entity*> specialEntities;

	short entitiesBuf[6];
	short entId;
	short entType;
	short entX, entY, entIdCol, entLinked2;
	Entity* ent = NULL;
	for (int i = 0; i < nentities; i++)
	{
		if (fread(entitiesBuf, sizeof(short), 5, file) < 1)
			return false;

		ent = NULL;
		entId = i;
		entType = entitiesBuf[0];
		entX = entitiesBuf[1];
		entY = entitiesBuf[2];
		entIdCol = entitiesBuf[3];
		entLinked2 = entitiesBuf[4];
	}

	return true;
};