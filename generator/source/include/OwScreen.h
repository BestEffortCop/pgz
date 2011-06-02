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

#ifndef _OWSCREEN_H_
#define _OWSCREEN_H_

#include <string.h>
#include <fstream>
#include <vector>
#include "MapTile.h"
#include "Screen.h"

using namespace std;


// Clase que se encarga de colocar los detalles mas pequeños y los enemigos en la
// pantalla y de generar los archivos de texto que serán leidos por el intérprete.

class OwScreen : public Screen{

	private:
		// Atributos de la clase OwScreen.
		vector<MapTile*>* matrix;		// Vector con todos los tiles de la pantalla

		int screenNumber; //Número de pantalla dentro del overworld

		int zoneNum; //sirve para distinguir de las demás zonas y posible cambio a zoneNumber

		//bool contains(int elem, vector<int>* collect);	// Comprueba si un elemento está en el vector
		//bool isThereAnyEntityAt(vector<Entity*>* entities, int pos);	// Comprueba si hay una entidad en la posición pos	

		//numero de posiciones libres que hay en la screen;
		int getNumFreeTiles();
		

	public:

		// Constructora.
		OwScreen(short mapNumber, int screenN, vector<MapTile*>* screenMatrix, int zoneNum, short posX, short posY, short n_enemies, string zone, DBManager * db);

		// Destructora
		~OwScreen();

		// Coloca detalles en la pantalla ya sean arboles, farolas ...
		// Almacena el resultado en matrix
		void placeDetails();

		// Coloca enemigos genéricos en la pantalla
		// Almacena el resultado en matrix
		void placeEnemies();

		// Coloca NPCs en la pantalla
		void placeNPCs(int x, int y);

		//volcado de la info almacenada en las matrices de la clase padre.
		void generate();

		int getFreePos(vector<int>* posUsed);// Buscamos una posición random libre (sin entidades ni sólidos)

		vector<int> * OwScreen::getPosUsedEntities();

		vector<MapTile*>* getMatrix();
		int getScreenNumber();
		int getZoneNum();
		short getSolid(int x, int y);
		short getSolid(int pos);
		void setSolid(int x, int y, short solid);
		void setSolid(int pos, short solid);
};

#endif
