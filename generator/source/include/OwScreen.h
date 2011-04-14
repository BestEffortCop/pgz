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

	public:

		// Constructora.
		OwScreen(short mapNumber, int screenN, vector<MapTile*>* screenMatrix, int zoneNum, short posX, short posY, short n_enemies, string zone, string theme, DBManager * db);

		// Destructora
		~OwScreen();

		// Coloca detalles en la pantalla ya sean arboles, farolas ...
		// Almacena el resultado en matrix
		void placeDetails();

		// Coloca enemigos genéricos en la pantalla
		// Almacena el resultado en matrix
		void placeEnemies();

		//volcado de la info almacenada en las matrices de la clase padre.
		void generate();

		vector<MapTile*>* getMatrix();
		int getScreenNumber();
		int getZoneNum();
		short getSolid(int x, int y);
		short getSolid(int pos);
		void setSolid(int x, int y, short solid);
		void setSolid(int pos, short solid);
};

#endif
