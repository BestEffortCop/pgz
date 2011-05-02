#include "AutoTerrain.h"

AutoTerrain::AutoTerrain() : Terrain()
{
};

AutoTerrain::~AutoTerrain()
{
};

void AutoTerrain::toTiles(int** source, Screen* screen, int w, int h, int i, int j)
{
	int col = 2*i;
	int row = 2*j;

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL){
		// simplemente pone su tile gráfico en la posición indicada de la pantalla
		screen->setTile(col, row, tile);
		screen->setTile(col+1, row, tile + 1);
		screen->setTile(col, row+1, tile + chipsetW);
		screen->setTile(col+1, row+1, tile + chipsetW + 1);
	}
	/*int col = 2*i;
	int row = 2*j;

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL && source != NULL)
	{
		// Pintamos el tile de arriba a la izquierda -----------------------------
		if (j != 0 && source[i][j-1] == idTerrain)
		{	// Arriba
			if (i != 0 && source[i-1][j] == idTerrain)
			{	// Izquierda
				if (source[i-1][j-1] == idTerrain)	// Arriba-Izquierda
					screen->setTile(col, row, getTileIdAt(4, 2));
				else
					screen->setTile(col, row, getTileIdAt(0, 4));
			}
			else
				screen->setTile(col, row, getTileIdAt(4, 0));
		}
		else
		{
			if (i != 0 && source[i-1][j] == idTerrain)	// Izquierda
				screen->setTile(col, row, getTileIdAt(2, 2));
			else
				screen->setTile(col, row, getTileIdAt(2, 0));
		}
		// Pintamos el tile de abajo a la izquierda -----------------------------
		if (j != (h - 1) && source[i][j+1] == idTerrain)
		{	// Abajo
			if (i != 0 && source[i-1][j] == idTerrain)
			{	// Izquierda
				if (source[i-1][j+1] == idTerrain)	// Abajo-Izquierda
					screen->setTile(col, row+1, getTileIdAt(5, 2));
				else
					screen->setTile(col, row+1, getTileIdAt(1, 4));
			}
			else
				screen->setTile(col, row+1, getTileIdAt(5, 0));
		}
		else
		{
			if (i != 0 && source[i-1][j] == idTerrain)	// Izquierda
				screen->setTile(col, row+1, getTileIdAt(7, 2));
			else
				screen->setTile(col, row+1, getTileIdAt(7, 0));
		}
		// Pintamos el tile de arriba a la derecha -----------------------------
		if (j != 0 && source[i][j-1] == idTerrain)
		{	// Arriba
			if (i != (w - 1) && source[i+1][j] == idTerrain)
			{	// Derecha
				if (source[i+1][j-1] == idTerrain)	// Arriba-Derecha
					screen->setTile(col+1, row, getTileIdAt(4, 3));
				else
					screen->setTile(col+1, row, getTileIdAt(0, 5));
			}
			else
				screen->setTile(col+1, row, getTileIdAt(4, 5));
		}
		else
		{
			if (i != (w - 1) && source[i+1][j] == idTerrain)	// Derecha
				screen->setTile(col+1, row, getTileIdAt(2, 3));
			else
				screen->setTile(col+1, row, getTileIdAt(2, 5));
		}
		// Pintamos el tile de abajo a la derecha -----------------------------
		if (j != (h - 1) && source[i][j+1] == idTerrain)
		{	// Abajo 
			if (i != (w - 1) && source[i+1][j] == idTerrain)
			{	// Derecha
				if (source[i+1][j+1] == idTerrain)	// Abajo-Derecha
					screen->setTile(col+1, row+1, getTileIdAt(5, 3));
				else
					screen->setTile(col+1, row+1, getTileIdAt(1, 5));
			}
			else
				screen->setTile(col+1, row+1, getTileIdAt(5, 5));
		}
		else
		{
			if (i != (w - 1) && source[i+1][j] == idTerrain)	// Derecha
				screen->setTile(col+1, row+1, getTileIdAt(7, 3));
			else
				screen->setTile(col+1, row+1, getTileIdAt(7, 5));
		}
	}
	else
	{
		int b = 2; /// Si llega aquí, hay algo raro
	}*/
}

int AutoTerrain::getTileIdAt(int y, int x)
{
	return (y * chipsetW) + tile + x;
}