#pragma once

#ifndef _DUNDECORATOR_H_
#define _DUNDECORATOR_H_

#include <list>

#include "Decorator.h"
#include "DungeonAutoTiler.h"
#include "Screen.h"
#include "OwScreen.h"
#include "DBManager.h"

using namespace std;

class DunDecorator : public Decorator
{
	private:
		bool place_upperTorch(Screen* screen, int col, int row);
		bool place_siderTorch(Screen* screen, int col, int row, DunDecorationPos pos);

	protected:
		// Información de con qué terrenos (y decoraciones) se están decorando las mazmorras
		struct screenInfo{
			short wallId;
			short terrainId;
			short torchId;
			short statueId;
		};

		// guarda información sobre los terrenos de la pantalla
		screenInfo info;

		// coloca "antorchas" en la parte superior, izquierda y derecha de la pantalla (si es posible)
		void place_torchs(Screen* screen);

	public:
		// Constructora
		DunDecorator(DBManager* db);

		// Destructora
		~DunDecorator();

		// Inicia el decorador con el tipo de zona, el tema del juego, y el tileset
		void init(string zone, string theme, short tileSetId);

		// Decora la pantalla pasada por parámetro (en función de la incialización anterior)
		void decorate(Screen* screen);

};

#endif
