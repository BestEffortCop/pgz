#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::init(int idTerrain, vector<int> variations, TerrainType type)
{
	this->idTerrain = idTerrain;
	this->variations = variations;
	this->type = type;
}

vector<int> Terrain::getVariations()
{
	return variations;
}

TerrainType Terrain::getType()
{
	return type;
}

int Terrain::getId()
{
	return idTerrain;
}

