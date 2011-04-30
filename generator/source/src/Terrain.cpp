#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::init(int idTerrain, int tile, vector<int> variations, TerrainType type, int width)
{
	this->idTerrain = idTerrain;
	this->tile = tile;
	this->variations = variations;
	this->type = type;
	chipsetW = width;
}

vector<int> Terrain::getVariations()
{
	return variations;
}

Terrain::TerrainType Terrain::getType()
{
	return type;
}

int Terrain::getId()
{
	return idTerrain;
}

