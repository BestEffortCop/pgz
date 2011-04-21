#include "NormalTerrain.h"

// Constructora
NormalTerrain::NormalTerrain() : Terrain()
{
}

// Destructora
NormalTerrain::~NormalTerrain()
{
}

void NormalTerrain::toTiles(int** screen, int w, int h, int i, int j)
{
	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL)
		screen[i][j] = tile; // simplemente pone su tile gráfico en la posición indicada de la pantalla
}