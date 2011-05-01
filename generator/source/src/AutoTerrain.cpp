#include "AutoTerrain.h"

AutoTerrain::AutoTerrain() : Terrain()
{
};

AutoTerrain::~AutoTerrain()
{
};

void AutoTerrain::toTiles(int** source, Screen* screen, int w, int h, int i, int j)
{
	int row = 2*i;
	int col = 2*j;

	if (i < h && i >= 0 && j < w && j >= 0 && screen != NULL){
		// Pintamos el tile de arriba a la izquierda -----------------------------
		if (i != 0 && source[i-1][j] == idTerrain){	// Arriba
			if (j != 0 && source[i][j-1] == idTerrain){	// Izquierda
				if (source[i-1][j-1] == idTerrain)	// Arriba-Izquierda
					screen->setTile(row, col, getTileIdAt(4, 2));
				else
					screen->setTile(row, col, getTileIdAt(0, 4));
			}
			else
				screen->setTile(row, col, getTileIdAt(4, 0));
		}
		else{
			if (j != 0 && source[i][j-1] == idTerrain)	// Izquierda
				screen->setTile(row, col, getTileIdAt(2, 2));
			else
				screen->setTile(row, col, getTileIdAt(2, 0));
		}
		// Pintamos el tile de abajo a la izquierda -----------------------------
		if (i != h - 1 && source[i+1][j] == idTerrain){	// Abajo
			if (j != 0 && source[i][j-1] == idTerrain){	// Izquierda
				if (source[i+1][j-1] == idTerrain)	// Abajo-Izquierda
					screen->setTile(row+1, col, getTileIdAt(5, 2));
				else
					screen->setTile(row+1, col, getTileIdAt(1, 4));
			}
			else
				screen->setTile(row+1, col, getTileIdAt(5, 0));
		}
		else{
			if (j != 0 && source[i][j-1] == idTerrain)	// Izquierda
				screen->setTile(row+1, col, getTileIdAt(7, 2));
			else
				screen->setTile(row+1, col, getTileIdAt(7, 0));
		}
		// Pintamos el tile de arriba a la derecha -----------------------------
		if (i != 0 && source[i-1][j] == idTerrain){	// Arriba
			if (j != w - 1 && source[i][j+1] == idTerrain){	// Derecha
				if (source[i-1][j+1] == idTerrain)	// Arriba-Derecha
					screen->setTile(row, col+1, getTileIdAt(4, 3));
				else
					screen->setTile(row, col+1, getTileIdAt(0, 5));
			}
			else
				screen->setTile(row, col+1, getTileIdAt(4, 5));
		}
		else{
			if (j != w - 1 && source[i][j+1] == idTerrain)	// Derecha
				screen->setTile(row, col+1, getTileIdAt(2, 3));
			else
				screen->setTile(row, col+1, getTileIdAt(2, 5));
		}
		// Pintamos el tile de abajo a la derecha -----------------------------
		if (i != h - 1 && source[i+1][j] == idTerrain){	// Abajo 
			if (j != w - 1 && source[i][j+1] == idTerrain){	// Derecha
				if (source[i+1][j+1] == idTerrain)	// Abajo-Derecha
					screen->setTile(row+1, col+1, getTileIdAt(5, 3));
				else
					screen->setTile(row+1, col+1, getTileIdAt(1, 5));
			}
			else
				screen->setTile(row+1, col+1, getTileIdAt(5, 5));
		}
		else{
			if (j != w - 1 && source[i][j+1] == idTerrain)	// Derecha
				screen->setTile(row+1, col+1, getTileIdAt(7, 3));
			else
				screen->setTile(row+1, col+1, getTileIdAt(7, 5));
		}
	}
}

int AutoTerrain::getTileIdAt(int row, int col)
{
	return (row * chipsetW) + tile + col;
}