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
#ifndef __MASK_H__
#define __MASK_H__

#include <string>
#include <vector>

using namespace std;

//! Par de colisión que representa los tipos de colisión que se han producido.
struct CollisionPair {
	//! Tipo de colisión de la máscara A en la colisión.
	string a;
	//! Tipo de colisión de la máscara B en la colisión.
	string b;
};


//! Máscara de colisión abstracta capaz de comprobar colisiones con otras máscaras.
/*!
	Una máscara es un elemento abstracto que representa la estructura física
	de una entidad y su delimitación a la hora de calcular su contacto con otras entidades.

	Contiene además una etiqueta editable que definirá qué tipo de colisión posee
	la máscara, útil a la hora de calcular colisiones. Esta etiqueta será una cadena
	de caracteres y deberá ser construída por el programador.
*/
class Mask
{
	public:

	//! Valor de la anchura de las dimensiones globales de la máscara de colisión.
	/*!
		Toda máscara hija estará envuelta en una máscara abstracta global.
		Debe ser colocada cuidadosamente, ya que dos máscaras no colisionan
		si sus máscaras globales no están en contacto, aunque sus
		correspondientes máscaras internas sí colisionen.
	*/
	int width;

	//! Valor de la altura de las dimensiones globales de la máscara de colisión.
	/*!
		Toda máscara hija estará envuelta en una máscara abstracta global.
		Debe ser colocada cuidadosamente, ya que dos máscaras no colisionan
		si sus máscaras globales no están en contacto, aunque sus
		correspondientes máscaras internas sí colisionen.
	*/
	int height;

	//! Coordenada x de posición origen de la máscara.
	int x;
	//! Coordenada y de posición origen de la máscara.
	int y;

	//! Coordenada x de desplazamiento de la máscara con respecto a la posición original.
	int xoffset;
	//! Coordenada y de desplazamiento de la máscara con respecto a la posición original.
	int yoffset;

	//! Tipo de colisión de la máscara.
	string type;

	//! Construye la máscara a partir de una anchura y altura globales dadas.
	/*!
		\param x Coordenada x origen de la máscara.
		\param y Coordenada y origen de la máscara.
		\param width Ancho de la máscara.
		\param height Alto de la máscara.
		\param type Tipo de colisión de la máscara.
		\param xoffset Coordenada x de desplazamiento la máscara.
		\param yoffset Coordenada y de desplazamiento la máscara.
	*/
	Mask(int x, int y, int width, int height, string type, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~Mask();

	//! Comprueba si la máscara dada colisiona con otra máscara.
	/*!
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	virtual vector<CollisionPair>* collide(Mask* other);

    //! Actualiza la posición de la máscara con las nuevas coordenadas, teniendo en cuenta el desplazamiento
	/*!
		\param x Coordenada x destino.
		\param y Coordenada y destino.
	*/
	virtual void setXY(int x, int y);

	//! Devuelve la posición x de la máscara teniendo en cuenta el desplazamiento.
	/*!
		\return Coordenada x real de la máscara.
	*/
	int posX();

	//! Devuelve la posición y de la máscara teniendo en cuenta el desplazamiento.
	/*!
		\return Coordenada y real de la máscara.
	*/
	int posY();

	//! Invierte todos los pares de collisión contenidos en un vector de CollisionPair.
	/*!
		\param vect Vector de CollisionPair cuyos componentes queremos invertir.
	*/
	vector<CollisionPair>* flipAll (vector<CollisionPair>* vect);
};

#endif
