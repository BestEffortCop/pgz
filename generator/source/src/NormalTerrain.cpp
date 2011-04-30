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
void NormalTerrain::toTiles(int** source, int** screen, int w, int h, int i, int j)
{
	int row = 2*i;
	int col = 2*j;

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL){
		// simplemente pone su tile gráfico en la posición indicada de la pantalla
		screen[row][col] = tile;
		screen[row][col+1] = tile + 1;
		screen[row+1][col] = tile + chipsetW;
		screen[row+1][col+1] = tile + chipsetW + 1;
	}
}

void NormalTerrain::toSolids(int** screen, int w, int h, int i, int j)
{
	// ??
}