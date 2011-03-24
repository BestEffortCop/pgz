#pragma once

#ifndef _GEN_OVERWORLD_H_
#define _GEN_OVERWORLD_H_

#include <vector>
#include <stack>
#include <string>
#include <set>
#include <time.h>

#include "Zone.h"
#include "DBInterface.h"
#include "GenTypes.h"
#include "GenVoronoi.h"

using namespace std;

// Clase principal del módulo generador de mundos.
/*
	Clase principal del módulo generador de mundos.
	Describe la morfología del mundo en creación en base a sus zonas, las formas de estas y los caminos que las atraviesan.
	Además, dispone de los métodos principales que determinará el mundo resultante.
*/

class GenOverworld {
	private:
		vector<Zone*>* zones;						// Lista de zonas del overworld
		vector<set<GPoint> >* blockadeVerts;			// Lista de conjuntos de puntos por donde el main road ha atravesado las fronteras.
		vector<GPoint>* mainRoadVerts;				// Almacena la estructura del camino principal
		vector<GPoint>* interestingPoints;			// Lista de los puntos interesantes que generará genRoadRamifications()
		Overworld* overworld;						// Puntero al overworld que modifica

		OwScreen* makeNewScreen(int iniT, int screenNumber);
		int checkTileinZone(MapTile* mTile);
		void floodFillScanlineStack(int x, int y, int zoneNum);

	public:

		// Constructora
		GenOverworld(Overworld* overworld);

		// Destructora
		~GenOverworld();

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
		void genDecoration(DBInterface* myDB);

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

		// Invoca al genScreens() de las Zonas.
		void genScreens();

		void guardameSolids(string path);
		void guardameZonas(string path);
};


#endif
