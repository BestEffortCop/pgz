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

#ifndef _GEN_VOROWORLD_H_
#define _GEN_VOROWORLD_H_

#include <vector>
#include <stack>
#include <set>
#include <time.h>
#include <queue>

#include "GenVoronoi.h"
#include "GenOverworld.h"
#include "Screen.h"
#include "Decidator.h"
#define UPDIR 1
#define RIGHTDIR 2 
#define DOWNDIR 3
#define LEFTDIR 4

using namespace std;

// Clase principal del módulo generador de mundos.
/*
	Clase principal del módulo generador de mundos.
	Describe la morfología del mundo en creación en base a sus zonas, las formas de estas y los caminos que las atraviesan.
	Además, dispone de los métodos principales que determinará el mundo resultante.
*/

class GenVoroWorld : public GenOverworld{
	private:

		GPointList ptList;	 // Puntos que usa voronoi para generar zonas, utiles porque estan dentro de la zona seguro

		OwScreen* makeNewScreen(int iniT, int screenNumber);
		int checkTileinZone(MapTile* mTile);
		void floodFillScanlineStack(int x, int y, int zoneNum);
		GPolygon voronoiPoly;

		// De momento lo pongo aquí
		void filterTilesDim1();
		void filterScreenFrontiers(bool open);
		void filterUnreachableAreas();
		bool floodSearch(int posIni, vector<MapTile*>* matrix, vector<bool>* checkedMatrix, vector<bool>* connectMatrix);
		int connectWithRoad(int pos, vector<MapTile*>* matrix, vector<bool>* checkedMatrix, vector<bool>* connectMatrix);
		
		void drawLateralTurn(int& tile, int& row, bool up, int maxEndRow);
		void drawVerticalTurn(int& tile, int& col, bool right, int maxCol);

		bool contains(int elem, vector<int>* collect);
		int findNearestZone(int actZone, GenZone* zIni, vector<int>* choosed);
		int findNearestDungeon(int actZone, vector<int>* choosed);
		bool isFrontierNear(int iniT, int range);
		bool isEdgeInDirection(int iniT, int range, int direction);
		bool isRoadNear(int iniT, int range);
		bool isRoadInDirection(int iniT, int range, int direction);
		bool isBorderOfScreen(GPoint g);

		bool isADungeonPlace(int screenX, int screenY);

		void doRamification(int iniTile, short firstDir);
		void extendsMainRoad();

		void drillSolids(int iniT, int range, bool mainRoad);
		void placeEntrance(int entrance);

		void expandFrontiers(vector<GPoint> bresen);

	public:

		// Constructora
		GenVoroWorld(Overworld* overworld, vector<GenZone*>* genZones, GenDungeon* genDungeon, Decorator* decorator, DBManager* mydb);

		// Destructora
		~GenVoroWorld();

		// Divide el mapa en tantas zonas como le indique overworld
		void genFrontiers();

		// Modifica las zonas generadas por genFrontiers() para darles una forma más poligonal / atractiva / menos random.
		// Modifica mapTileMatrix.
		void genShape();

		// Asigna cada MapTile de mapTileMatrix a su zona, además crea OwScreen tambien asignando su zona.
		void assignTilesAndScreens();

		// llama al genGeoDetail de cada zona
		void genGeoDetail();

		// Elige el tile a colocar en los huecos libres del overworld. Esto puede realizarse mediante capas.
		void genDecoration(DBManager* myDB);

		// Encapsula el propio método de la clase Zone
		void placeDungeons();

		// Análogo a placeDungeons()
		void placeSafeZones();

		// Conecta las zonas que componen el mapa según el orden de las mazmorras que contienen
		void genMainRoad();

		//Genera caminos desde el camino principal perforando bloques (como pueden ser montañas o bosques) y almacena
		//los posibles puntos interesantes. Éstos son los ultimos puntos perforados de los caminos “interesantes”
		//(puede considerarse un camino interesante aquel camino que sea largo, o que haya perforado mucho en un bosque...).
		//Esta lista de puntos interesantes se utilizará posteriormente para colocar coleccionables o cualquier otra
		//cosa que indicara el generador de vida.
		void genRoadRamifications();

		// Bloquea los caminos que conectan zonas
		void genBlockades();
		
		//coloca los NPC's por el mundo
		void placeNPCs();

		//colocamos la mazmorra/pantalla final
		void placeFinalDungeon();

		//Coloca los Pigeons y los powerUP en los interestingPoints
		void placePowUPandPigeons();

		// Invoca al genScreens() de las Zonas.
		void genScreens();

		void guardameSolids(string path);
		void guardameZonas(string path);
};


#endif
