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

#ifndef _GAME_H_
#define _GAME_H_

#include "World.h"
#include "GenVoroWorld.h"
#include "GenWormZone.h"
#include "GenForestZone.h"
#include "GenFieldZone.h"
#include "Decidator.h"
#include "WorldDecorator.h"
#include "GenLagoonZone.h"
#include "GenDesertZone.h"

class GenGame{
	private:
		World* world;
		Overworld* ow;
		GenOverworld* genOw;
		vector<GenZone*>* zones;
		Decidator* decidator;

		set<int> selectedTools;

		std::string outputPath;

	public:

		// Constructora
		GenGame();
		// Destructora
		~GenGame();

		// Generamos el mundo
		void genGame(DBManager* myDB);

		void addTool(int id);
		bool toolSelected(int id);
};

#endif