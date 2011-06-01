/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
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

#pragma once

#ifndef _DECORATION_H_
#define _DECORATION_H_

#include <vector>
#include "Screen.h"

class Decoration
{
	public:

		enum DecorationSize {sNone, small, medium, big};
		enum DecorationType {tNone, solid, walkable, hangable, symmetric, dungeonStatue, dungeonEntrance, dunFloorEntrance, elementsFD};
		enum DecorationNear {nNone, Path, Water, Solid};

		struct DecorationData
		{
			int idDeco;
			std::vector<int> compatibleTerrains; // id del terreno con el que puede ir (útil para hangables)
			int width, height;
			DecorationType type;
			DecorationSize size;
			DecorationNear near;
			std::vector<int> tileTypes;	// vector que guarda los tipos de cada tile (guardados por filas)
			std::vector<int> tiles;		// vector que guarda el idenrificador de cada tile (guardados por filas)
		};

	private:
		DecorationData data;	// datos de la decoración

	public:
		int x, y;	// posición (en tiles) de la decoración en la pantalla

		// Constructora
		Decoration(DecorationData data);
		void init(int x, int y);
		// Destructora
		virtual ~Decoration();

		// Método que devuelve las entidades (bueno no recuerdo bien, debe ser review by Rafa)
		Entity* toEntities();

		// Getter del data
		DecorationData getDecorationData();
};

#endif