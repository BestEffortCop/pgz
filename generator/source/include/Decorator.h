#pragma once

#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <list>

#include "AutoTiler.h"
#include "Screen.h"

using namespace std;

class Decorator
{
	private:
		string zone;	// Tipo de zona en la que se encuentra la pantalla
		string theme;	// Temática del juego
		AutoTiler* autoTiler;

		int** terrainIdMatrix;
		list<Decoration::DecorationData> decorationList;

	public:
		// Constructora
		Decorator();

		// Destructora
		~Decorator();

		// Inicia el decorador con el tipo de zona, el tema del juego, y el tileset
		void init(string zone, string theme, string tileSetPath);

		// Decora la pantalla pasada por parámetro (en función de la incialización anterior)
		void decorate(Screen* screen);
};

#endif
