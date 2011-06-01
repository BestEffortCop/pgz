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

#include "GenOverworld.h"

GenOverworld::GenOverworld(Overworld* overworld, vector<GenZone*>* genZones, GenDungeon* genDungeon, Decorator* decorator, DBManager* myDB)
{
	this->overworld = overworld;
	this->genZones = genZones;
	this->myDB = myDB;
	this->genDungeon = genDungeon;
	this->decorator = decorator;
}
GenOverworld::~GenOverworld()
{
	overworld = NULL;
	genZones = NULL;
	myDB = NULL;
}

void GenOverworld::guardameSolids(string path)
{
	overworld->guardameSolids(path);
}

void GenOverworld::guardameZonas(string path)
{
	overworld->guardameZonas(path);
}

void GenOverworld::guardamePant(string path)
{
	overworld->guardamePant(path);
}

void GenOverworld::guardameAutotile(string path)
{
	overworld->guardameAutotile(path);
};