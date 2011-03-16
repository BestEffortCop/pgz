#pragma once

#ifndef _OWSCREEN_H_
#define _OWSCREEN_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "MapTile.h"
#include "GenTypes.h"
//#include "Overworld.h"
//#include <stdio>

using namespace std;

// Clase que se encarga de colocar los detalles mas pequeños y los enemigos en la
// pantalla y de generar los archivos de texto que serán leidos por el intérprete.

class OwScreen{

	private:
		// Atributos de la clase OwScreen.
		vector<MapTile*>* matrix;		// Vector con todos los tiles de la pantalla
		vector<int>* enemyList;		// Vector con los enemigos disponibles de la zona
		vector<MapTile*>* detailsList;	// Vector con los detalles disponibles de la zona
		int screenNumber;

	public:

		// Constructora.
		//OwScreen(int iniT, int screensW, Overworld* ow, int screenN);
		OwScreen(int init, int screensPerRow, vector<MapTile*>* mapMatrix, int screenN, vector<int>* enemies, vector<MapTile*>* details);
		

		// Destructora
		~OwScreen();

		// Coloca detalles en la pantalla ya sean arboles, farolas ...
		// Almacena el resultado en matrix
		void placeDetails();

		// Coloca enemigos genéricos en la pantalla
		// Almacena el resultado en matrix
		void placeEnemies();

		// Devuelve el path del archivo con toda la información de la pantalla que cargará el intérprete.
		string createScreenFiles();

		void writeInFile(const string& cad, ofstream& sal)const;
		
};

#endif
