#include "AutoTerrain.h"

AutoTerrain::AutoTerrain() : Terrain()
{
};

AutoTerrain::~AutoTerrain()
{
};

void AutoTerrain::toTiles(int** source, Screen* screen, int w, int h, int i, int j)
{
/*	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL){
		if (source[i-1][j] == idTerrain){	// Arriba
			if (source[i][j-1] == idTerrain)	// Izquierda
				if (source[i-1][j-1] == idTerrain)	// Arriba-Izquierda
					screen[i][j] = getTileIdAt(i + 4, j + 2);	// ESTA MAL FALTA COMPROBAR CON ABAJO
				else
					screen[i][j] = getTileIdAt(i, j + 4);
			else 
				screen[i][j] = getTileIdAt(i + 4, j);

			if (source[i][j+1] == idTerrain)	// Derecha
				if (source[i-1][j+1] == idTerrain)	// Arriba-Derecha
					screen[i][j] = getTileIdAt(i + 4, j + 3);
				else
					screen[i][j] = getTileIdAt(i, j + 5);
			else
				screen[i][j] = getTileIdAt(i + 4, j + 5);


		}	
	}*/
};

int AutoTerrain::getTileIdAt(int row, int col)
{
	return (row * chipsetW) + tile + col;
}