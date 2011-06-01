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

#ifndef _DECIDATOR_H_
#define _DECIDATOR_H_

#include <vector>
#include <fstream>
#include <sstream>
#include "DBManager.h"
#include <iostream>
#include <map>

using namespace std;

class Decidator{
	private:

		DBManager* db;				// Base de datos.

		short initialMaxLife;		// vida inicial del player (dificultad) 4 de vida -> 1 corazón
		short initialMap;			// Id del mapa en el que comienza al player al comienzo del juego
		short numMaps;				// Número de mapas del juego
		short numPieces;			//Num. Piezas corazón: número de piezas para conseguir un corazón (dificultad).
		short numKeyObj;			//Num. Obj. Clave: número de objetos clave al inicio del juego (dificultad).
		short initialMoney;			//Dinero (dificultad)
		string worldName;			// Nombre del juego
		string thematic;			// Temática del juego
		short player;				// Identificador del player seleccionado
		string playerName;			// Nombre del player
		short difficulty;			// Dificultad del juego
		short worldSize;			// Tamaño del mundo
		//short worldSizeRow;		// Tamaño del mundo alto
		//short worldSizeColumn;	// Tamaño del mundo ancho
		short numZones;				// Número de zonas
		short numSafeZones;			// Número de zonas seguras
		vector<short>* zonesSet;	// Conjunto de ids de zonas seleccionadas
		vector<short>* enemiesSet;	// Conjunto de ids de enemigos seleccionados
		short numEnemies;			// Número de enemigos por pantalla
		short numTools;				// Número de herramientas
		vector<short>* toolsSet;	// Conjunto de herramientas seleccionadas
		short numDungeons;			// Número de herramientas
		short ratio;				//ratio puzzle/action (seguramente no se tenga en cuenta)
		short dungeonsSizeRow;		// Tamaño de las mazmorras alto
		short dungeonsSizeColumn;	// Tamaño de las mazmorras ancho
		short consistency;			// consistencia (seguramente no se tenga en cuenta)
		short numPigeons;			// Número de Pigeons en el juego
		short numBigHearts;			// Número de corazones grandes repartidos por el mundo

		void evaluateData(map<string, string> datos);
		void completeData();
		vector<short>* loadShortCSV(string input);

		void printMainInfo();

	public:
		Decidator(DBManager* myDB, string path);
		~Decidator();

		bool save();

		/* Getters */
		short getInitialMaxLife();		
		short getInitialMap();			
		short getNumMaps();				
		short getNumPieces();			
		short getNumKeyObj();			
		short getInitialMoney();			
		string getWorldName();			
		string getThematic();				
		short getPlayer();				
		string getPlayerName();			
		short getDifficulty();
		short getWorldSize();
		/*short getWorldSizeRow();
		short getWorldSizeColumn();		*/
		short getNumZones();
		short getNumSafeZones();
		vector<short>* getZonesSet();
		short getNumEnemies();
		vector<short>* getEnemiesSet();	
		short getNumTools();				
		vector<short>* getToolsSet();	
		short getNumDungeons();			
		short getRatio();				
		short getDungeonsSizeRow();		
		short getDungeonsSizeColumn();	
		short getConsistency();	
		ZoneInfo getWorldGen();
		short getDungeonGen();
		short getNumPigeons();
		short getNumBigHearts();	

		//debug (COMO QUE DEBUG ! PUTA MIERDA ES ESTA)
		inline void setNumMaps(short numMaps){this->numMaps = numMaps;};

		void clearInitialTools();
		void addInitialTool(short idTool);
};

#endif