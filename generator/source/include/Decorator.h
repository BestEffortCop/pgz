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
	private:
		string zone;	// Tipo de zona en la que se encuentra la pantalla
		string theme;	// Temática del juego
		AutoTiler* autoTiler;
		DBManager* db;
		string IdTileset;

		int** terrainIdMatrix;
		list<Decoration*> decorationList;

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
		void init(string zone, string theme, short tileSetId);

		// Decora la pantalla pasada por parámetro (en función de la incialización anterior)
		void decorate(Screen* screen);

		// Elige un tile adecuado para un TiledPushable, por ejemplo
		short gimmeTile();
		// Elige un tile adecuado para un FloorButton
		short gimmeFloorButton();
		// Devuelve true si se puede colocar, sino false
		bool checkDecoCollision(Decoration* d);
		// Comprueba si una decoración se sale de la pantalla
		bool isInBounds(Decoration* d, Screen* s);
		// Comprueba si hay algun sólido en el espacio que ocupa la decoración
		bool Decorator::checkSolidCollision(Decoration* d, Screen* s);
};

#endif
