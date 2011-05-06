#include "Decoration.h"

Decoration::Decoration(DecorationData data)
{
	this->data = data;
};

Decoration::~Decoration()
{
	this->x = -1;
	this->y = -1;
};

void Decoration::init(int x, int y)
{
	this->x = x;
	this->y = y;
};

std::vector<Decoration::TiledEntity> Decoration::toEntities()
{
	std::vector<TiledEntity> v;
	std::vector<int>::iterator itTile, itSolid;

	if (data.solids.size() != data.tiles.size())
		return v;

	itTile = data.tiles.begin();
	itSolid = data.solids.begin();
	while (itTile != data.tiles.end())
	{
		TiledEntity e;
		e.idTile = (*itTile);
		e.solid = (*itSolid);
		e.x = x;
		e.y = y;
		v.push_back(e);

		itTile++;
		itSolid++;
	}

	return v;
};

Decoration::DecorationData Decoration::getDecorationData()
{
	return data;
};