#pragma once

#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <list>

#include "AutoTiler.h"
#include "Screen.h"
#include "OwScreen.h"
#include "DBManager.h"

using namespace std;

class Decorator
{
	protected:

		string zone;	// Tipo de zona en la que se encuentra la pantalla

		bool changedZone;	// booleano que nos dice cuándo se cambia de zona (para cambiar el estilo de decoración o lo que sea)

		AutoTiler* autoTiler;
		DBManager* db;
		short idTileset;

		int** terrainIdMatrix;				// matriz de terrenos
		list<Decoration*> decorationList;	// lista de decoraciones

		// Devuelve true si se puede colocar, sino false
		bool checkDecoCollision(Decoration* d);
		
		// Comprueba si una decoración se sale de la pantalla
		virtual bool isInBounds(Decoration* d, Screen* s);
		
		// Comprueba si hay algun sólido en el espacio que ocupa la decoración
		bool checkSolidCollision(Decoration* d, Screen* s);

		// Comprueba que no choca con entidades
		bool checkEntitiesCollision(Decoration* d, Screen* s);

		// Transforma los terrenos de la matriz a tiles
		void terrainsToTiles(Screen* screen);

		// Devuelve el número de espacios libres de una pantalla
		int getFreeSpace(Screen* s);

		// Coloca decoraciones de manera simétrica y devuelve el número de espacios libres
		int place_symmetrics(Screen* s, int terrainId);

		// elimina las decoraciones de la lista
		void clearDecorations();

		// borra los terrenos de la matriz de terrenos
		void clearTerrains();

	public:
		// Constructora
		Decorator(DBManager* db);

		// Destructora
		~Decorator();

		// Inicia el decorador con el tipo de zona, el tema del juego, y el tileset
		virtual void init(string zone, short tileSetId);

		// Decora la pantalla pasada por parámetro (en función de la incialización anterior)
		virtual void decorate(Screen* screen){};

		// Elige un tile adecuado para un TiledPushable, por ejemplo
		short gimmeTile();
		// Elige un tile adecuado para un FloorButton
		short gimmeFloorButton();
};

#endif
