#pragma once

#ifndef _OVERWORLD_H_
#define _OVERWORLD_H_

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string>
#include "GenTypes.h"
#include "MapTile.h"

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

	public:
		// Indicador del tamaño del overworld, genOverworld lo interpreta para asignar un ancho y alto adecuado.
		int worldSize;

		// Vector que contiene información sobre las zonas que deben generarse.
		vector<ZoneInfo>* zonesInfo;

		// Vector que contiene información sobre las mazmorras que deben generarse.
		vector<DungeonInfo>* dungeonsInfo;

		// Vector que contiene información sobre las zonas seguras que deben generarse.
		vector<SafeZoneInfo>* safeZonesInfo;

		// Punto donde comienza el personaje al iniciar por pirmera vez el juego, lo establece genOverworld y lo leerá genLife
		Point startLocation;

		// Puntos del overworld donde colocar premios/secretos, lo establece genOverworld y lo leerá genLife
		vector<Point> prizePoints;

		// Mega-matriz sobre la que trabaja genOverworld
		vector<MapTile>* mapTileMatrix;

		// Constructora: recibe la información de Decidator y la almacena en sus atributos pertinentes.
		Overworld(int wSize, vector<ZoneInfo>* zonesI, vector<DungeonInfo>* dungeonsI, vector<SafeZoneInfo>* safeZonesI);

		// Destructora
		~Overworld();

		// Getters utiles:
		int getNumZones();

		int getNumDungeons();

		int getNumSafeZones();
};


#endif
