#include "AutoTerrain.h"

AutoTerrain::AutoTerrain() : Terrain()
{
};

AutoTerrain::~AutoTerrain()
{
};

void AutoTerrain::toTiles(int** screen, int w, int h, int i, int j)
{
	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL)
		screen[i][j] = tile;
};