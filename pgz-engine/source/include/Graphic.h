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
#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include "Color.h"
#include <stdlib.h>

//! Clase virtual de la que heredarán todos los elementos gráficos
/*!
	Ofrece funciones de update (actualización con el transcurso de un tick 
	del juego) y render (momento en que se pinta por pantalla), así como 
	modificadores de color, transparencia, escala y rotación de la imagen.
*/
class Graphic {
	protected:
		//! Color que va a tener el gráfico.
		Color* color;
		//! Transparencia del gráfico.
		float alpha;
		//! Escala horizontal en la que se representará el gráfico.
		float scaleH;
		//! Escala vertical en la que se representará el gráfico.
		float scaleV;
		//! Valor del ángulo que rotará el gráfico.
		float rotation;
		//! Origen de rotación X
		int originX;
		//! Origen de rotación Y
		int originY;

	public:
	
	//! Construye el elemento gráfico
	Graphic();
	
	//! Destructora
	virtual ~Graphic();
		
	//! Realiza la actualización en cada paso del juego.
	virtual void update();
	
	//! Realiza el renderizado de la imagen en las coordenadas dadas de la ventana de juego.
	/*!
		\param x Coordenada x de reenderizado.
		\param y Coordenada y de reenderizado.
	*/
	virtual void render(int x, int y);
		
	//! Tinta el gráfico del color dado
	/*!
		\param color Color con el que se tintará la imagen.
	*/
	virtual void setColor(Color color);
	
	//! Cambia la transparencia del gráfico a un valor alpha.
	/*!
		\param alpha Valor de la nueva transparencia del gráfico.
	*/
	virtual void setAlpha(float alpha);

	//! Cambia la escala con que será renderizado el gráfico a un valor scale.
	/*!
		\param scale Valor de la nueva escala del gráfico.
	*/
	virtual void setScale(float scaleH, float scaleV);
	
	//! Rota la imagen un angulo rotation.
	/*!
		\param rotation Valor del ángulo que rotará el gráfico.
	*/
	virtual void setRotation(float rotation);

	//! Establece la posición horizontal del origen de rotación.
	/*!
		\param x Posición horizontal del origen
	*/
	virtual void setOriginX(int x);

	//! Establece la posición vertical del origen de rotación.
	/*!
		\param x Posición vertical del origen
	*/
	virtual void setOriginY(int y);

	/* Uncomented zone of weirdness */

	//! Obtiene la transparencia del gráfico
	/*!
		\return Transparencia del gráfico entre 0 y 1
	*/
	virtual float getAlpha();

	//! Obtiene el color de tintado del gráfico
	/*!
		\return Color de tintado
	*/
	virtual Color getColor();

	//! Obtiene el ángulo de rotación del gráfico
	/*!
		\return Ángulo de rotación en grados
	*/
	virtual float getRotation();

	//! Obtiene el factor de escalado horizontal
	/*!
		\return Factor de escalado horizontal (Siendo 0.5 un escalado a la mitad de tamaño)
	*/
	virtual float getScaleH();

	//! Obtiene el factor de escalado vertical
	/*!
		\return Factor de escalado vertical (Siendo 0.5 un escalado a la mitad de tamaño)
	*/
	virtual float getScaleV();

	//! Obtiene el origen de rotación del gráfico
	/*!
		\return Coordenada horizontal del origen de rotación 
	*/
	virtual int getOriginX();

	//! Obtiene el origen de rotación del gráfico
	/*!
		\return Coordenada vertical del origen de rotación 
	*/
	virtual int getOriginY();

	virtual int getWidth();
	virtual int getHeight();
};

#endif
