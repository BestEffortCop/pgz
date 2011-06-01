/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef _WORLDDECORATOR_H_
#define _WORLDDECORATOR_H_

#include <list>

#include "Decorator.h"
#include "WorldAutoTiler.h"
#include "Screen.h"
#include "OwScreen.h"
#include "DBManager.h"

using namespace std;

class WorldDecorator : public Decorator
{
	private:
		static const int N_ATTEMPTS = 5; // número de veces que va a intentar colocar una decoración

		// coloca tantas decoraciones como indique nDecos, posUsed es el vector de posiciones ya utilizadas
		void place_decos(Screen* screen, int nDecos, Decoration::DecorationSize size, std::vector<int>* posUsed);

		// Devuelve la id de la decoración que coloca
		int place_deco(Screen* s, Decoration::DecorationSize size, Decoration::DecorationType type,int idDeco, int pos);

	protected:

		// Información de con qué terrenos (y decoraciones) se están decorando las mazmorras
		struct screenInfo{
			short solidId;
			short waterId;
			short pathId;
			short floorId;
		};

		// guarda información sobre los terrenos de la pantalla
		screenInfo info;

	public:

		// Constructora
		WorldDecorator(DBManager* db);

		// Destructora
		~WorldDecorator();

		// Inicia el decorador con el tipo de zona, el tema del juego, y el tileset
		void init(string zone, short tileSetId);

		// Decora la pantalla pasada por parámetro (en función de la incialización anterior)
		virtual void decorate(Screen* screen);

		// col, row es la posición del teletransporte
		void decorateDunEntrance(Screen* screen, int col, int row);
};

#endif
