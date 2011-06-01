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

#pragma once

#ifndef _FINALDUNGEON_H_
#define _FINALDUNGEON_H_

#define FINAL_SCREEN 0
#define LOCK_SCREEN 1

#include "Dungeon.h"
#include "DunScreen.h"
#include "Screen.h"
#include "DBManager.h"

/*
		       Lock Screen							Final Screen

		1 1 1 1 1 L L L L 1 1 1 1 1				1 1 1 1 1 1 1 1 1 1 1 1 1 1	
		1 1 1 1 1 L L L L 1 1 1 1 1				1 1	1 1 1 1 1 1 1 1 1 1 1 1
		1 1			            1 1				1 1						1 1	
		1 1    	                1 1				1
		1 1   2 2 2     2 2 2   1 1				
		1 1	  2 2 2     2 2 2   1 1				
		1 1   2 2 2     2 2 2   1 1				
		1 1                     1 1				
		1 1                     1 1
		1 1					    1 1
		1 1 1 1 1 E E E E 1 1 1 1 1 			
		1 1 1 1 1 E E E E 1 1 1 1 1				
											
		
*/
class FinalDungeon: public Dungeon {

	private:

		void generateLockScreen();

		void generateFinalScreen(); 

		void allocateSolids(DunScreen* ds, int type);

		// puertas y paredes copia de dunScreen // por no hacer público el que ya tiene
		void placeWalls(DunScreen* ds);

	public:
		// Debe encargarse de realizar las operaciones con la BDI
		FinalDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);

		// Destructora
		~FinalDungeon();

		// Desencadena la generación de la mazmorra 
		void generate();
};

#endif