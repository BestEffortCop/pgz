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
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Image.h"
#include "Graphic.h"

//! Canvas es un miembro de la familia de Graphic sobre el que se puede dibujar.
/*!
	Permite mostrar de forma cómoda una imagen compuesta por varias otras.
	
	El programador ha de tener cuidado de no liberar las imágenes que componen
	el Canvas mientras dure la vida de este.
	
	\sa Graphic
*/
class Canvas : public Graphic
{
private:
	GfxEngine* gfxEngine;
	Image* img;
	int w, h;

public:

	//! Posición horizontal
	int x;
	
	//! Posición vertical
	int y;
	
	//! Construye el Canvas con los parámetros indicados
	/*! 
		\param x posición horizontal
		\param y posición vertical
		\param width ancho del lienzo
		\param height alto del lienzo
		\param gfxEngine puntero al GfxEngine del sistema
	*/
	Canvas(int x, int y, int width, int height, GfxEngine* gfxEngine);

	//! Destruye el Canvas (no los gráficos que lo forman)
	~Canvas();

	//! Obtiene el ancho del Canvas
	/*! \return ancho del Canvas */
	int getW();
	//! Obtiene el alto del Canvas
	/*! \return alto del Canvas */
	int getH();

	//! Dibuja un objeto en el lienzo, en la posición indicada
	/*!
		\param gfx objeto gráfico a dibujar
		\param x posición horizontal
		\param y posición vertical
	*/
	void draw(Graphic* gfx, int x, int y);

	/*//! Dibuja un objeto en el lienzo, en la posición indicada
	/*!
		Se puede dibujar parte del objeto gráfico especificando
		las coordenadas del rectángulo que la contiene.
		\param gfx objeto gráfico a dibujar
		\param x posición horizontal
		\param y posición vertical
		\param xOrigin coordenada horizontal de la esquina superior derecha de la parte a dibujar
		\param yOrigin coordenada vertical de la esquina superior derecha de la parte a dibujar
		\param w ancho de la parte a dibujar
		\param h alto de la parte a dibujar
	*./
	void drawPart(Graphic* gfx, int x, int y, int xOrigin = 0, int yOrigin = 0, int w = 0, int h = 0);*/

	//! Rellena el lienzo con el color indicado
	/*! \param c color de relleno */
	void clear(Color c);

	//! Actualiza el lienzo para reflejar los cambios
	void refresh();

	//! Renderiza el Canvas
	/*!
		\param x Posición horizontal
		\param y Posición vertical
	*/
	void render(int x, int y);
};

#endif