#pragma once

#ifndef _ZONE_H_
#define _ZONE_H_

#include <vector>

#include "Overworld.h"
#include "GenDungeon.h"
#include "OwScreen.h"
#include "GenTypes.h"
//#include "DBInterface.h"

using namespace std;

// Clase contenedor que delimita una zona del mundo mediante un polígono.
/*
	Con un conjunto de puntos, por afinidad, se determina la forma de la zona sobre se realizará toda la funcionalidad asociada a la clase.
	Esto abarca la posibilidad de colocar zonas seguras, mazmorras y comprobar dadas unas coordenadas enteras de un tile en mapTileMatrix, su pertenencia
	a la zona.
*/

class Zone {

	private:
		// Atributos de la clase Zone.
		/*
			shape vector de coordenadas de tiles que definen un polígono para una zona del mundo.
			typeId tipo de zona.
			dungeonNumber número de orden de la mazmorra que contiene (-1 si no tiene mazmorra)
		*/
		vector<Point>* shape;
		int typeId;
		int dungeonNumber;

	public:
		// Construye un delimitador de zonas mediante un stl::vector indicando el tipo de la misma.
		/*
			shape vector de coordenadas de tile que definen un polígono para una zona del mundo.
			typeId tipo de zona.
		*/
		Zone(int zoneTypeId, vector<Point>* zoneShape);

		// Destructora
		~Zone();

		// Devuelve el tipo de zona en forma de int.
		int getTypeId();

		// Permite modificar el tipo asociado a una zona.
		void setTypeId(int tId);

		// Devuelve el conjunto de puntos delimitador de zona.
		vector<Point>* getShape();

		// Permite modificar el delimitador de zona.
		void setShape(vector<Point>* s);

		// Comprueba si el tile pos en mapTileMatrix se encuentra en el polígono asociado a la zona y si es así devuelve el MapTile correspondiente.
		/*
			pos coordenadas x e y de un tile en mapTileMatrix.
		*/
		MapTile inZone(Point pos);

		/* Permite colocar un mazmorra dentro de la zona de forma pseudo-aleatoria o bien mediante una posición especificada por parámetro.
			Se ha de tomar decisiones sobre la tool y el keyObject que se le proporcionará al generador de mazmorras entre los conjuntos dados.
			Así mismo se determina la dificultad de la mazmorra mediante los parámetros gameDiff y dungNumber en este nivel.
		*/
		/*
			idTools conjunto de identificadores de herramienta. Se ha de seleccionar uno de ellos.
			dungNumber número de mazmorras colocadas hasta el momento.
			gameDiff dificultad del juego.
			typeId tipo de la zona en la que se encuentra la mazmorra
			keyObjects conjunto de posibles objetos clave de la mazmorra a generar. Se ha de seleccionar uno de ellos.
			dungSize tamaño de la mazmorra (en número de habitaciones aproximadas)
			ratePuzzleAction ratio puzzle/acción.
			idMiniBosses conjunto de minibosses que puede seleccionar el generador de mazmorras. Si es NULL no hay miniboss en la mazmorra.
			idBosses conjunto de bosses que puede seleccionar el generador de mazmorras.
			idEnemies conjunto de enemigos que puede seleccionar el generador de mazmorras.
			pos posición donde colocar la mazmorra en la zona.
		*/
		void placeDungeon(vector<int>* idTools,int dungNumber, int gameDiff,int typeId, vector<int>* keyObjects, int dungSize, int ratio,
			vector<int>* idBosses, vector<int>* idEnemies, Point pos, vector<int>* idMiniBosses = NULL);

		// Por decidir, de primeras coloca la entrada a una zona segura.
		/*
			idZone tipo de zona segura.
			pos posición donde colocar la entrada a la zona segura. Si es NULL se coloca de forma pseudo-aleatoria.
		*/
		void placeSafeZone(int idZone,Point* pos=NULL);

		// Divide el overworld en pantallas creando una instancia de OwScreen que procesa las secciones de mapa.
		void genScreens();

		// Devuelve el número de orden de la mazmorra que se encuentra en la zona
		int getDungeonNumber();

		// Establece un nuevo número de orden de la mazmorra de la zona
		void setDungeonNumber(int dunNum);
};


#endif // _ZONE_H_
