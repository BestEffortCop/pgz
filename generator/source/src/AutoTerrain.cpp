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

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL)
	{
		screen->setTile(col, row, tile);
		screen->setTile(col+1, row, tile + 1);
		screen->setTile(col, row+1, tile + chipsetW);
		screen->setTile(col+1, row+1, tile + chipsetW + 1);
	}

	/*int col = 2*i;
	int row = 2*j;

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL)
	{
		// Autotile2 - Basura
		bool u, d, l, r, ul, ur, dl, dr;
		u = (j == 0 || (j > 0 && source[i][j-1] == idTerrain));
		d = (j == (h-1) || (j < h-1 && source[i][j+1] == idTerrain));
		l = (i == 0 || (i > 0 && source[i-1][j] == idTerrain));
		r = (i == (w-1) || (i < w-1 && source[i+1][j] == idTerrain));
		ul =	(i == 0 && j == 0) || 
				(i == 0 && (j > 0 && source[i][j-1] == idTerrain)) || 
				(j == 0 && (i > 0 && source[i-1][j] == idTerrain)) || 
				((i > 0 && j > 0 && source[i-1][j-1] == idTerrain));
		ur =	(i == w-1 && j == 0) || 
				(i == w-1 && (j > 0 && source[i][j-1] == idTerrain)) || 
				(j == 0 && (i < w-1 && source[i+1][j] == idTerrain)) || 
				((i < w-1 && j > 0 && source[i+1][j-1] == idTerrain));
		dl =	(i == 0 && j == h-1) || 
				(i == 0 && (j < h-1 && source[i][j+1] == idTerrain)) || 
				(j == h-1 && (i > 0 && source[i-1][j] == idTerrain)) || 
				((i > 0 && j < h-1 && source[i-1][j+1] == idTerrain));
		dr =	(i == w-1 && j == h-1) || 
				(i == w-1 && (j < h-1 && source[i][j+1] == idTerrain)) || 
				(j == h-1 && (i < w-1 && source[i+1][j] == idTerrain)) || 
				((i < w-1 && j < h-1 && source[i+1][j+1] == idTerrain));

		if (u && l && d && r && ul && ur && dl && dr)
		{
			screen->setTile(col, row, getTileAt(2, 4));
			screen->setTile(col+1, row, getTileAt(3, 4));
			screen->setTile(col, row+1, getTileAt(2, 5));
			screen->setTile(col+1, row+1, getTileAt(3, 5));
		}
		else if (u && l && d && !r && ul && ur && dl && dr)
		{
			screen->setTile(col, row, getTileAt(4, 4));
			screen->setTile(col+1, row, getTileAt(4, 5));
			screen->setTile(col, row+1, getTileAt(5, 4));
			screen->setTile(col+1, row+1, getTileAt(5, 5));
		}
		else if (u && !l && d && r && ul && ur && dl && dr)
		{
			screen->setTile(col, row, getTileAt(0, 4));
			screen->setTile(col+1, row, getTileAt(1, 4));
			screen->setTile(col, row+1, getTileAt(0, 5));
			screen->setTile(col+1, row+1, getTileAt(1, 5));
		}
		else if (!u && l && d && r && ul && ur && dl && dr)
		{
			screen->setTile(col, row, getTileAt(2, 2));
			screen->setTile(col+1, row, getTileAt(2, 3));
			screen->setTile(col, row+1, getTileAt(3, 2));
			screen->setTile(col+1, row+1, getTileAt(3, 3));
		}
		else if (u && l && !d && r && ul && ur && dl && dr)
		{
			screen->setTile(col, row, getTileAt(2, 6));
			screen->setTile(col+1, row, getTileAt(3, 6));
			screen->setTile(col, row+1, getTileAt(2, 7));
			screen->setTile(col+1, row+1, getTileAt(3, 7));
		}
		else if (!u && !l && !d && !r && !ul && !ur && ! dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 2));
			screen->setTile(col+1, row, getTileAt(5, 2));
			screen->setTile(col, row+1, getTileAt(0, 7));
			screen->setTile(col+1, row+1, getTileAt(5, 7));
		}
		else if (u && !l && !d && !r && !ul && !ur && ! dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 6));
			screen->setTile(col+1, row, getTileAt(5, 6));
			screen->setTile(col, row+1, getTileAt(0, 7));
			screen->setTile(col+1, row+1, getTileAt(5, 7));
		}
		else if (!u && !l && d && !r && !ul && !ur && ! dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 2));
			screen->setTile(col+1, row, getTileAt(5, 2));
			screen->setTile(col, row+1, getTileAt(0, 3));
			screen->setTile(col+1, row+1, getTileAt(5, 3));
		}
		else if (!u && l && !d && !r && !ul && !ur && ! dl && !dr)
		{
			screen->setTile(col, row, getTileAt(4, 2));
			screen->setTile(col+1, row, getTileAt(5, 2));
			screen->setTile(col, row+1, getTileAt(4, 7));
			screen->setTile(col+1, row+1, getTileAt(5, 7));
		}
		else if (!u && !l && !d && r && !ul && !ur && ! dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 2));
			screen->setTile(col+1, row, getTileAt(1, 2));
			screen->setTile(col, row+1, getTileAt(0, 7));
			screen->setTile(col+1, row+1, getTileAt(1, 7));
		}
		else if (!u && !d && l && r && !ul && !ur && !dl && !dr)
		{
			screen->setTile(col, row, getTileAt(2, 2));
			screen->setTile(col+1, row, getTileAt(3, 2));
			screen->setTile(col, row+1, getTileAt(2, 7));
			screen->setTile(col+1, row+1, getTileAt(3, 7));
		}
		else if (u && d && !l && !r && !ul && !ur && !dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 4));
			screen->setTile(col+1, row, getTileAt(5, 4));
			screen->setTile(col, row+1, getTileAt(0, 5));
			screen->setTile(col+1, row+1, getTileAt(5, 5));
		}
		else if (u && !d && l && !r && !ul && !ur && !dl && !dr)
		{
			screen->setTile(col, row, getTileAt(4, 0));
			screen->setTile(col+1, row, getTileAt(5, 6));
			screen->setTile(col, row+1, getTileAt(4, 7));
			screen->setTile(col+1, row+1, getTileAt(5, 7));
		}
		else if (u && !d && r && !l && !ul && !ur && !dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 6));
			screen->setTile(col+1, row, getTileAt(5, 0));
			screen->setTile(col, row+1, getTileAt(0, 7));
			screen->setTile(col+1, row+1, getTileAt(1, 7));
		}
		else if (!u && d && !r && l && !ul && !ur && !dl && !dr)
		{
			screen->setTile(col, row, getTileAt(4, 2));
			screen->setTile(col+1, row, getTileAt(5, 2));
			screen->setTile(col, row+1, getTileAt(4, 1));
			screen->setTile(col+1, row+1, getTileAt(5, 3));
		}
		else if (!u && d && r && !l && !ul && !ur && !dl && !dr)
		{
			screen->setTile(col, row, getTileAt(0, 2));
			screen->setTile(col+1, row, getTileAt(1, 2));
			screen->setTile(col, row+1, getTileAt(0, 3));
			screen->setTile(col+1, row+1, getTileAt(5, 1));
		}
		else
		{
			screen->setTile(col, row, tile);
			screen->setTile(col+1, row, tile + 1);
			screen->setTile(col, row+1, tile + chipsetW);
			screen->setTile(col+1, row+1, tile + chipsetW + 1);
		}
	}
	else
		int n = 2;*/


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
};

short AutoTerrain::getTileAt(int x, int y)
{
	return (short) ((y * chipsetW) + tile + x);
};