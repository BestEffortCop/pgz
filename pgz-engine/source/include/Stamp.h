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
#ifndef __STAMP_H__
#define __STAMP_H__

#include "GfxEngine.h"
#include "Graphic.h"
#include "Image.h"

using namespace std;

//! Miembro de la familia de Graphic que renderiza una imagen fija en una posición determinada
class Stamp : public Graphic 
{
	private:
		//! Atributos de la clase Stamp.
		/*!
			\param gfxEngine contiene la información de la gestión de gráficos
			\param image puntero al gráfico asociado a la clase
			\param w ancho de la imagen
			\param h alto de la imagen
		*/
		GfxEngine* gfxEngine; 
		Image* image;

		// Indica si la imagen se ha cargado en el Stamp
		bool loaded;

		int w,h;

	public:
		
		//! Construye el Stamp a partir de un archivo de imagen
		/*!
			\param fname Nombre del archivo a cargar
			\param gfxEngine Puntero al GfxEngine del sistema
		*/
		Stamp(string fname, GfxEngine* gfxEngine);
		
		//! Construye el Stamp a partir de una imagen ya cargada
		/*!
			\param image Imagen que tendrá el Stamp
			\param gfxEngine Puntero al GfxEngine del sistema
		*/
		Stamp(Image* image, GfxEngine* gfxEngine);
		
		//! Destruye el Stamp
		~Stamp();

		//! Obtiene el ancho del Stamp
		/*! \return Ancho del Stamp */
		int getWidth();
		
		//! Obtiene el alto del Stamp
		/*! \return Alto del Stamp */
		int getHeight();

		//! Renderiza el Stamp en la posición indicada
		/*!
			\param x Coordenada horizontal
			\param y Coordenada vertical
		*/
		void render(int x, int y);
};

#endif
