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
		static const int NWALKABLES = 3;	// número máximo de decoraciones "walkables" que puede colocar"

		bool place_upperTorchs(Screen* screen, int col, int row);
		bool place_leftTorchs(Screen* screen, int col, int row);
		bool place_rightTorchs(Screen* screen, int col, int row);

		bool place_upperTorch(Screen* screen, int col, int row);
		bool place_siderTorch(Screen* screen, int col, int row, DunDecorationPos pos);

		bool checkWallCollision(Decoration* d, Screen* screen);

		void place_FinalStatues(Screen* screen);
		void place_Stage(Screen* screen);

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

		// coloca las estatuas por la pantalla si es posible
		void place_statues(Screen* screen);

		// coloca decoraciones por las que se pueda andar encima (máximo NWALKABLES)
		void place_walkables(Screen* screen);

		// coloca los terrenos y los muros
		void place_terrains(Screen* screen);

	public:
		// Constructora
		DunDecorator(DBManager* db);

		// Destructora
		~DunDecorator();

		// Inicia el decorador con el tipo de zona, el tema del juego, y el tileset
		void init(string zone, short tileSetId);

		// Decora la pantalla pasada por parámetro (en función de la incialización anterior)
		void decorate(Screen* screen);

		// Decora la entrada de la mazmorra
		void decorateDunEntrance(Screen* screen, int col, int row);

		// Decora la pantalla pasada por parámetro como una Lock Screen
		void decorateLS(Screen* screen);

		// Decora la pantalla pasada por parámetro como una Final Screen
		void decorateFS(Screen* screen);
};

#endif
