#pragma once

#ifndef _GEN_OVERWORLD_H_
#define _GEN_OVERWORLD_H_

#include <vector>
#include <string>
#include <set>
#include "Zone.h"

#include "DBInterface.h"
#include <time.h>

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
		vector<set<Point> >* blockadeVerts;			// Lista de conjuntos de puntos por donde el main road ha atravesado las fronteras.
		vector<Point>* mainRoadVerts;				// Almacena la estructura del camino principal
		vector<Point>* interestingPoints;			// Lista de los puntos interesantes que generará genRoadRamifications()
		Overworld* overworld;						// Puntero al overworld que modifica
	
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
		
		// Coloca grandes bloques sólidos
		void genGeoDetail();
		
		// Elige el tile a colocar en los huecos libres del overworld. Esto puede realizarse mediante capas.
		void genDecoration(BDInterface myDB);
		
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
		
};


#endif
