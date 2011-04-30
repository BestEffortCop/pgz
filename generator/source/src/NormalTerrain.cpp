#include "NormalTerrain.h"

// Constructora
NormalTerrain::NormalTerrain() : Terrain()
{
}

// Destructora
NormalTerrain::~NormalTerrain()
{
}

// i filas, j columnas
void NormalTerrain::toTiles(int** source, Screen* screen, int w, int h, int i, int j)
{
	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL)
	{
		// simplemente pone su tile gráfico en la posición indicada de la pantalla
		screen->setTile(i, j, tile);
		screen->setTile(i+1, j, tile+1);
		screen->setTile(i, j+1, tile+chipsetW);
		screen->setTile(i+1, j+1, tile+chipsetW+1);
	}
}

void NormalTerrain::toSolids(int** screen, int w, int h, int i, int j)
{
	// ??
}