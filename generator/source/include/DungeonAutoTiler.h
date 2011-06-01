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

#ifndef _DUNGEONAUTOTILER_H_
#define _DUNGEONAUTOTILER_H_

#include "AutoTiler.h"
#include <vector>
#include <map>
#include "DungeonWall.h"

	enum DunDecorationPos {top, left, right, bottom};
	struct DungeonDecoData{
		DunDecorationPos pos; // si es hangable (antorchas) nos dice en qué pared ponerla
	};

class DungeonAutoTiler : public AutoTiler{
	
private:
		// mapa que guarda la 
		std::map<int, DungeonDecoData> dungeonDecos;

		// Carga la configuración propia de la mazmorra
		bool loadDungeonConfig(FILE* file);

		// Carga todos los muros posibles
		bool loadWalls(FILE* file);

		// Carga todas las decoraciones posibles
		bool loadDunDecorationList(FILE* file);

		// Carga los datos de cada muro
		DungeonWall* loadWall(FILE* file);

		// Carga la lista de decoraciones de mazmorra
		bool loadDungeonDecoList(FILE* file);

		// Carga los datos de cada decoración de mazmorra
		void loadDungeonDeco(FILE* file);

	public:

		// Constructora
		DungeonAutoTiler(std::string tileSetPath);
		// Destructora
		~DungeonAutoTiler();

		// devuelve la decoración de una antorcha para esa dirección
		Decoration* getDungeonDeco(DunDecorationPos pos, int wallId, Decoration::DecorationType type);
};

#endif