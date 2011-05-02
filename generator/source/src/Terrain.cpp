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
	this->variations = variations;
	this->type = type;
	this->chipsetW = 2 * width/16; // nos guardamos el ancho en tiles de 8x8
	// Que le den a la fórmula, calculémoslo a lo cutre:
	int tx = tile % (chipsetW/2);
	int ty = tile / (chipsetW/2);
	this->tile = 2*tx + 2*ty*chipsetW;
	//this->tile = 2 * (tile + width/16 * (tile % (width/16))); // Nos guardamos el tile en 8x8 directamente
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

