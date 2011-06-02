/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "TiledEntity.h"

TiledEntity::TiledEntity(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
{
	tileset = NULL;
	tileId = NULL;
	tilesType = NULL;
	nTiles = 0;
	width = 0;
	height = 0;
	solid = true;
	depth = y;
};

TiledEntity::~TiledEntity()
{
	delete tilesType;
}


void TiledEntity::init(TileSet* tset, short tile, short* tilesType, short nTiles, short width)
{
	this->nTiles = nTiles;
	this->width = width;
	this->tileset = tset;
	this->tileId = tile;
	this->tilesType = tilesType;
	this->height = nTiles / width;

	bool floorDeco = false;

	// Creamos la grid donde guardaremos los tilesType
	int** grid = new int*[width];
	for (int i = 0; i < width; i++)
		grid[i] = new int[height];

	// Rellenamos la grid
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			switch (tilesType[i*width + j])
			{
			case 0: grid[j][i] = 0; break;
			case 1: grid[j][i] = 1; break;
			case 2: grid[j][i] = 0; floorDeco = true; break;
			default: grid[j][i] = tilesType[i*width + j];
			}
		}

	mask = new SolidGrid(x, y, grid, tileset->getTileW()*2, tileset->getTileH()*2, width, height);

	/*if (!foreground)
		mask = new MaskBox(x, y, tileset->getTileW()*2, tileset->getTileH()*2, "semisolid");
	else
		depth += 1;
		setCollidable(false);*/

	if (floorDeco)
		depth = -1;
	else
	{
		// Buscamos el tile de base (== 1) más alto
		int higherBase = (height+1)*tileset->getTileH()*2;
		bool found = false;
		int j = 0;
		for (int i = 0; i < width; i++)
		{
			j = 0;
			found = false;
			while (j < height && !found)
			{
				found = (grid[i][j] == 1);
				j++;
			}

			if (found)
			{
				j--;
				if (j < higherBase) higherBase = j;
			}
		}

		if (higherBase != (height+1)*tileset->getTileH()*2)
		{
			depth = y+higherBase*2*tileset->getTileH();
		}
		else depth = y+2*tileset->getTileH();
	}
};

void TiledEntity::onRender()
{
	if (!visible || !enabled || tileset == NULL)
		return;

	int tw = tileset->getTileW() * 2, th = tileset->getTileH() * 2;	// multiplicamos x2 para conseguir tamaño 16, que es el tamaño de las decoraciones
	game->getGfxEngine()->renderPart(tileset->getImg(), x, y, 
		tw*(tileId % (tileset->getColumns()/2)), th*(tileId / (tileset->getColumns()/2)), width * tw, height * th);
};