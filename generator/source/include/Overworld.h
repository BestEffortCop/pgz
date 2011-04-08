#pragma once

#ifndef _OVERWORLD_H_
#define _OVERWORLD_H_

#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <string>
#include "GenTypes.h"
#include "MapTile.h"
#include "OwScreen.h"


#define MAX_STR_LENGTH 20  //tamaño del nombre del archivo de guardado

using namespace std;

// Clase encargada de almacenar los datos que genera la clase GenOverworld y de posteriormente crear los archivos de mapa que cargará el motor.
/*
	Recibimos información de Decidator sobre el tamaño del mundo, zonas, mazmorras y zonas seguras.
	Una instancia de GenOverworld trabaja sobre nosotros y modifica mapTileMatrix, startLocation, prizePoints. Para ello, esta se instancia pasándole un puntero al propio objeto (this).
	Con toda esta información el generador de vida aportará sus modificaciones adicionales.
	El Overwolrd finalizado llama a su operación genScreens para generar los archivos de mapa.
*/

class Overworld{
	private:
		// Tamaño de la matriz mapTileMatrix
		int worldSizeH;	// Alto
		int worldSizeW;	// Ancho

		// Indicador del tamaño del overworld, genOverworld lo interpreta para asignar un ancho y alto adecuado.
		int worldSize;
		// Dificultad del juego
		short worldDiff; 
		// Numero de zonas
		short numZones;
		// Numero de mazmorras
		short numDungeons;
		// Numero de SafeZones
		short numSafeZones;

		// Para el intérprete y su persistencia.
		short n_puzzles;
		short n_collectables;
		short n_blockades;
		
		// Punto donde comienza el personaje al iniciar por pirmera vez el juego, lo establece genOverworld y lo leerá genLife
		GPoint startLocation;

		vector<OwScreen*>* screenList;

	public:

		// Puntos del overworld donde colocar premios/secretos, lo establece genOverworld y lo leerá genLife
		vector<GPoint> prizePoints;

		// Mega-matriz sobre la que trabaja genOverworld
		vector<MapTile*>* mapTileMatrix;

		// Constructora: recibe la información de Decidator y la almacena en sus atributos pertinentes.
		Overworld(int wSize, int wDiff, int numZones, int numDungeons, int numSafeZones);

		// Destructora
		~Overworld();

		bool save();

		void addScreen(OwScreen* screen);

		// Getters utiles:
		int getNumZones();
		int getNumDungeons();
		int getNumSafeZones();
		int getWorldDiff();
		GPoint getStartLocation();

		int getWorldSizeH();
		int getWorldSizeW();
		MapTile* getMapTile(int x, int y);
};


#endif
