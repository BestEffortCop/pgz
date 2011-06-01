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

#include "World.h"

// Constructora
World::World(int difficulty, GenOverworld* genOverw, DBManager* myDataB){
	// Asignamos dificultad
	gameDiff = difficulty;
	genOw = genOverw;
	myDB = myDataB;			// AÑADIDO DB PARA INVOCACION DE GENDECORATION
}

// Destructora
World::~World(){
	overworld = NULL;
	genOw = NULL;
	myDB = NULL;
}

// Setter Overworld
void World::setOverworld(Overworld* ow){
	overworld = ow;
}

// Construcción del overworld
void World::buildOverworld(){
	cout<<"5#Generating World Frontiers\n";
	genOw->genFrontiers();
	cout<<"5#Subdividing World Space\n";
	genOw->genShape();
	cout<<"5#Generating World Zones Screens\n";
	genOw->assignTilesAndScreens();
	cout<<"5#Generating Geographical Detail\n";
	genOw->genGeoDetail();
	cout<<"5#Generating Dungeons\n";
	genOw->placeDungeons();
	cout<<"5#Generating Final Dungeon\n";
	genOw->placeFinalDungeon();
	cout<<"5#Placing Safe Zones\n";
	genOw->placeSafeZones();
	cout<<"5#Creating Main Road\n";
	genOw->genMainRoad();
	cout<<"5#Generating Road Ramifications\n";
	genOw->genRoadRamifications();
	cout<<"5#Placing Zone Blockades\n";
	genOw->genBlockades();
	cout<<"5#Placing Powerups and Pidgeons\n";
	genOw->placePowUPandPigeons();
	cout<<"5#Placing NPC's\n";
	genOw->placeNPCs();
	cout<<"5#Decorating World\n";
	genOw->genDecoration(myDB);
	cout<<"5#Saving Screens\n";
	genOw->genScreens();
	// Archivos debug:
	//genOw->guardameSolids("solids.txt");
	//genOw->guardameZonas("Zones.txt");
	//genOw->guardamePant("Pant.txt");
	//genOw->guardameAutotile("Auto.txt");
}