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

#include "Decoration.h"

Decoration::Decoration(DecorationData data)
{
	this->data = data;
};

Decoration::~Decoration()
{
	this->x = -1;
	this->y = -1;
};

void Decoration::init(int x, int y)
{
	this->x = x;
	this->y = y;
};

Entity* Decoration::toEntities()
{
	std::vector<int>::iterator itTile, itType;

	if (data.tiles.size() != data.tileTypes.size())
		return NULL;	// error al cargar no coinciden el nº de tiles con sus tipos

	// creamos el vector de tileType para la entidad tileEntity
	short* tilesType = new short[data.tileTypes.size()];

	// iniciamos el iterador
	itTile = data.tiles.begin();
	itType = data.tileTypes.begin();

	int i = 0;
	int solid;

	while (itTile != data.tiles.end())
	{
		// Hasta que se cambie en el intérprete lo de varios tipos de pasables (por arriba, abajo...)
		/*if ((*itType) != 1) solid = (*itType);
		else
			solid = 1;*/
		solid = (*itType);

		tilesType[i] = solid;

		itTile++;
		itType++;
		i++;
	}
			
	// Creamos la entidad y la metemos en el vector
	// -1 -1 indican que no tienen idCollectable ni linkedTo
	return new EntityTiled(TILEDENTITY, x , y, -1, -1, data.tiles.size(), data.tiles.at(0), tilesType, data.width);
/*
	// para cada tile comprobamos el tipo y creamos la entidad que corresponda
	while (itTile != data.tiles.end())
	{
		// Diferenciamos si es sólido o no para el motor (type = 1 es base, es decir, solido)
		if ((*itType) != 1) solid = 0; 
		else solid = 1;
		// Creamos la entidad y la metemos en el vector
		// -1 -1 indican que no tienen idCollectable ni linkedTo
		EntityTiled* e = new EntityTiled(entityType::TILEDENTITY, x, y, -1, -1, (*itTile), solid);
		v.push_back(e);

		itTile++;
		itType++;
	}*/
};

Decoration::DecorationData Decoration::getDecorationData()
{
	return data;
};