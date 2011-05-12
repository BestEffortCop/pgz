#include "DungeonWall.h"

DungeonWall::DungeonWall() : AutoTerrain(){}

DungeonWall::~DungeonWall(){}

void DungeonWall::init(int wallId, int tileId, vector<int> variations, int chipsetWidth){
	AutoTerrain::init(wallId, tileId, variations, solid, chipsetWidth);
}

void DungeonWall::toTiles(int** source, Screen* screen, int w, int h, int col, int row){
	
	/*if (col < w && col >= 0 && row < h && row >= 0 && screen != NULL && source != NULL)
	{
		if (source[col][row - 1] == idTerrain)	// Arriba
			if (source[col - 1][row] == idTerrain) // Izquierda
				if (source[col + 1][row] == idTerrain) // Derecha
					if (source[col][row + 1] == idTerrain) // Abajo
						setTile(screen, col, row, getTileAt(4, 2));
					else
						setTile(screen, col, row, getTileAt(6, 2));
				else
					if (source[col][row + 1] == idTerrain)	// Abajo
						setTile(screen, col, row, getTileAt(4, 4));
					else
						setTile(screen, col, row, getTileAt(6, 4));
			else
				if (source[col + 1][row] == idTerrain) // Derecha
					if (source[col][row + 1] == idTerrain) // Abajo
						setTile(screen, col, row, getTileAt(4, 0));
					else
						setTile(screen, col, row, getTileAt(6, 0));
				else
					setTile(screen, col, row, getTileAt(4, 2));			// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!

		else 
			if (source[col - 1][row] == idTerrain) // Izquierda
				if (source[col + 1][row] == idTerrain) // Derecha
					if (source[col][row + 1] == idTerrain) // Abajo
						setTile(screen, col, row, getTileAt(2, 2));
					else
						setTile(screen, col, row, getTileAt(2, 2));		// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!
				else
					if (source[col][row + 1] == idTerrain)	// Abajo
						setTile(screen, col, row, getTileAt(2, 4));
					else
						setTile(screen, col, row, getTileAt(2, 2));		// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!
			else
				if (source[col + 1][row] == idTerrain) // Derecha
					if (source[col][row + 1] == idTerrain) // Abajo
						setTile(screen, col, row, getTileAt(2, 0));
					else
						setTile(screen, col, row, getTileAt(6, 0));
				else
					setTile(screen, col, row, getTileAt(4, 2));			// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!

						
	}*/

	// HACER DE NUEVO
}

void DungeonWall::setTile(Screen* s, int col, int row, int tile){
	s->setTile(col, row, tile);					// Arriba izquierda
	s->setTile(col+1, row, tile+1);				// Arriba derecha
	s->setTile(col, row+1, tile+chipsetW);		// Abajo izquierda
	s->setTile(col+1, row+1, tile+chipsetW+1);	// Abajo derecha
}