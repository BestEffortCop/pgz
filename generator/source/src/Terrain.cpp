/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::init(int idTerrain, int tile, vector<int> variations, TerrainType type, int width)
{
	this->tile16 = tile;
	this->idTerrain = idTerrain;
	this->variations = variations;
	this->type = type;
	this->chipsetW = 2 * width/16; // nos guardamos el ancho en tiles de 8x8
	// Que le den a la fórmula, calculémoslo a lo cutre:
	int tx = tile % (chipsetW/2);
	int ty = tile / (chipsetW/2);
	this->tile = 2*tx + 2*ty*chipsetW;
	//this->tile = 2 * (tile + width/16 * (tile % (width/16))); // Nos guardamos el tile en 8x8 directamente
}

vector<int> Terrain::getVariations()
{
	return variations;
}

Terrain::TerrainType Terrain::getType()
{
	return type;
}

int Terrain::getId()
{
	return idTerrain;
}

