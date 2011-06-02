/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
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

#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "Overworld.h"
#include "GenOverworld.h"
	
class World {
	private:
		int gameDiff;	// dificultad del juego a generar
		Overworld* overworld; // Puntero al OverWorld que instancia la clase
		GenOverworld* genOw;
		DBManager* myDB;
	
	public:	
		// Constructora y destructora
		World(int difficulty, GenOverworld* genOverw, DBManager* myDataB);
		~World();

		// Setter de overworld
		void setOverworld(Overworld* ow);
		// Construcción del overworld
		void buildOverworld();
};
	
#endif
