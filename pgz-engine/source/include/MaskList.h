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
#ifndef __MASK_LIST_H__
#define __MASK_LIST_H__

#include "Mask.h"
#include "MaskBox.h"
#include "MaskCircle.h"

//! Lista de máscaras de colisión
/*!
	Se trata de un hijo de Mask, representando la máscara de colisión
	de un objeto en varias partes.
*/

class MaskList : public Mask
{
	public:

	//! Lista de las máscaras de colisión que contiene.
	vector<Mask*>* masks;

	//! Construye la máscara a partir de una lista de máscaras y las dimensiones globales.
	/*!
		\param x Coordenada x origen de la máscara.
		\param y Coordenada y origen de la máscara.
		\param width Ancho global de la máscara.
		\param height Alto global de la máscara.
		\param type Tipo de colisión de la máscara.
		\param m Lista de máscaras ya creada.
		\param xoffset Coordenada x de desplazamiento la máscara.
		\param yoffset Coordenada y de desplazamiento la máscara.
	*/
	MaskList(int x, int y, int width, int height, string type, vector<Mask*>* m, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~MaskList();

	//! Comprueba si la máscara dada colisiona con otra máscara.
	/*!
		Hace uso del método de la clase padre para comprobar si cada
		una de las máscaras de su lista colisiona con la máscara other.

		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	vector<CollisionPair>* collide(Mask* other);

    void setXY(int x, int y);

	private:

	//! Método privado para concatenar vectores de CollisionPair
	/*!
		\param fromVect vector del cual sacamos datos.
		\param toVect vector al que concatenamos datos.
	*/
	void concatVect(vector<CollisionPair> *fromVect, vector<CollisionPair> *toVect);
};

#endif
