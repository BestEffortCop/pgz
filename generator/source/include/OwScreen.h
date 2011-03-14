#pragma once

#ifndef _OWSCREEN_H_
#define _OWSCREEN_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "MapTile.h"
#include <stdio>

using namespace std;

// Clase que se encarga de colocar los detalles mas pequeños y los enemigos en la
// pantalla y de generar los archivos de texto que serán leidos por el intérprete.

class OwScreen{

	private:
		// Atributos de la clase OwScreen.
		vector<MapTile>* matrix;	// Vector con todos los tiles de la pantalla
		int screenNumber;

	public:

		// Constructora. Guarda en infoZone la información de zona pasada por parámetro
		OwScreen(ZoneInfo zonesInfo, int iniT, int screensW, Overworld* ow, int screenN);
		OwScreen(ZoneInfo zonesInfo, vector<MapTile>* tiles, int screenN);

		// Destructora
		~OwScreen();

		// Crea un vector dependiendo del atributo infoZone de los posibles detalles a colocar.
		// Coloca detalles en la pantalla ya sean arboles, farolas ...
		// Almacena el resultado en matrix
		void placeDetails();

		// Crea un vector dependiendo del atributo infoZone de los posibles enemigos a colocar.
		// Coloca enemigos genéricos en la pantalla
		// Almacena el resultado en matrix
		void placeEnemies();

		// Devuelve el path del archivo con toda la información de la pantalla que cargará el intérprete.
		string createScreenFiles();

		void writeInFile(const string& cad, ofstream& sal)const;
		
};

#endif
