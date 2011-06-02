/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once
#ifndef __MASK_BOX_H__
#define __MASK_BOX_H__

#include <string>
#include "MaskCircle.h"
#include "MaskList.h"
#include "SolidGrid.h"

using namespace std;

//! Máscara de colisión única de forma rectangular.
/*!
	Se trata de un hijo de Mask, representando la máscara de colisión
	de un objeto de forma rectangular.
*/

class MaskBox : public Mask
{
	public:

	//! Construye la máscara a partir de las dimensiones globales.
	/*!
		Las dimensiones de la máscara rectangular serán las globales.
		\param x Coordenada x origen de la máscara.
		\param y Coordenada y origen de la máscara.
		\param width Ancho global de la máscara.
		\param height Alto global de la máscara.
		\param type Tipo de colisión de la máscara.
		\param xoffset Coordenada x de desplazamiento la máscara.
		\param yoffset Coordenada y de desplazamiento la máscara.
	*/
	MaskBox(int x, int y, int width, int height, string type, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~MaskBox();

	//! Comprueba si la máscara rectangular dada colisiona con otra máscara.
	/*!
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	vector<CollisionPair>* collide(Mask* other);
};

#endif
