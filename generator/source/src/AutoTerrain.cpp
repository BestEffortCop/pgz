#include "AutoTerrain.h"

#include <iostream>

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

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL && source != NULL)
	{
		bool b;

		// Pintamos el tile de arriba a la izquierda -----------------------------
		if (j == 0 || j != 0 && source[i][j-1] == idTerrain)
		{	// Arriba
			if (i == 0 || i != 0 && source[i-1][j] == idTerrain)
			{	// Izquierda
				b = (i == 0 && j == 0) || 
					(i == 0 && (j > 0 && source[i][j-1] == idTerrain)) || 
					(j == 0 && (i > 0 && source[i-1][j] == idTerrain)) || 
				    ((i > 0 && j > 0 && source[i-1][j-1] == idTerrain));
				if (b)	// Arriba-Izquierda
					screen->setTile(col, row, getTileIdAt(4, 2));
				else
					screen->setTile(col, row, getTileIdAt(0, 4));
			}
			else
				screen->setTile(col, row, getTileIdAt(4, 0));
		}
		else
		{
			if (i == 0 || i > 0 && source[i-1][j] == idTerrain)	// Izquierda
				screen->setTile(col, row, getTileIdAt(2, 2));
			else
				screen->setTile(col, row, getTileIdAt(2, 0));
		}
		// Pintamos el tile de abajo a la izquierda -----------------------------
		if (j == h-1 || j < (h - 1) && source[i][j+1] == idTerrain)
		{	// Abajo
			if (i == 0 ||i > 0 && source[i-1][j] == idTerrain)
			{	// Izquierda
				b = (i == 0 && j == h-1) || 
				(i == 0 && (j < h-1 && source[i][j+1] == idTerrain)) || 
				(j == h-1 && (i > 0 && source[i-1][j] == idTerrain)) || 
				((i > 0 && j < h-1 && source[i-1][j+1] == idTerrain));
				if (b)	// Abajo-Izquierda
					screen->setTile(col, row+1, getTileIdAt(5, 2));
				else
					screen->setTile(col, row+1, getTileIdAt(1, 4));
			}
			else
				screen->setTile(col, row+1, getTileIdAt(5, 0));
		}
		else
		{
			if (i == 0 || i != 0 && source[i-1][j] == idTerrain)	// Izquierda
				screen->setTile(col, row+1, getTileIdAt(7, 2));
			else
				screen->setTile(col, row+1, getTileIdAt(7, 0));
		}
		// Pintamos el tile de arriba a la derecha -----------------------------
		if (j == 0 || j != 0 && source[i][j-1] == idTerrain)
		{	// Arriba
			if (i == w-1 || i != (w - 1) && source[i+1][j] == idTerrain)
			{	// Derecha
				b = (i == w-1 && j == 0) || 
				(i == w-1 && (j > 0 && source[i][j-1] == idTerrain)) || 
				(j == 0 && (i < w-1 && source[i+1][j] == idTerrain)) || 
				((i < w-1 && j > 0 && source[i+1][j-1] == idTerrain));
				if (b)	// Arriba-Derecha
					screen->setTile(col+1, row, getTileIdAt(4, 3));
				else
					screen->setTile(col+1, row, getTileIdAt(0, 5));
			}
			else
				screen->setTile(col+1, row, getTileIdAt(4, 5));
		}
		else
		{
			if (i == w-1 || i != (w - 1) && source[i+1][j] == idTerrain)	// Derecha
				screen->setTile(col+1, row, getTileIdAt(2, 3));
			else
				screen->setTile(col+1, row, getTileIdAt(2, 5));
		}
		// Pintamos el tile de abajo a la derecha -----------------------------
		if (j == h-1 || j != (h - 1) && source[i][j+1] == idTerrain)
		{	// Abajo 
			if (i == w-1 || i != (w - 1) && source[i+1][j] == idTerrain)
			{	// Derecha
				b = (i == w-1 && j == h-1) || 
				(i == w-1 && (j < h-1 && source[i][j+1] == idTerrain)) || 
				(j == h-1 && (i < w-1 && source[i+1][j] == idTerrain)) || 
				((i < w-1 && j < h-1 && source[i+1][j+1] == idTerrain));
				if (b)	// Abajo-Derecha
					screen->setTile(col+1, row+1, getTileIdAt(5, 3));
				else
					screen->setTile(col+1, row+1, getTileIdAt(1, 5));
			}
			else
				screen->setTile(col+1, row+1, getTileIdAt(5, 5));
		}
		else
		{
			if (i == w-1 || i != (w - 1) && source[i+1][j] == idTerrain)	// Derecha
				screen->setTile(col+1, row+1, getTileIdAt(7, 3));
			else
				screen->setTile(col+1, row+1, getTileIdAt(7, 5));
		}
	}
}

int AutoTerrain::getTileIdAt(int y, int x)
{
	int n = (y * chipsetW) + tile + x;
	if (n == 26)
		return 25;
	else return n;
};

short AutoTerrain::getTileAt(int x, int y)
{
	short n = (short) ((y * chipsetW) + tile + x);
	if (n == 26)
		return 25;
	else return n;
};