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

#ifndef __TILESET_H__
#define __TILESET_H__

#include "GfxEngine.h"
#include "Image.h"
#include "Graphic.h"

using namespace std;

//!Encapsula un elemento gráfico que se divide en tiles de tamaño configurable
/*!
	Proporciona métodos para acceder a tiles de forma sencilla. Pertenece a la clase Graphic
	por ser un elemento gráfico con elementos del mapa a pintar.
*/

class TileSet 
{
	private:
		//! Atributos de la clase tileSet.
		/*!
			\param gfxEngine contiene la información de la gestión de los gráficos.
			\param image contiene la imagen asociada al tileSet.
			\param path contiene la ruta en la que se encuentra el tileSet.
			\param tileW contiene el ancho de un tile.
			\param tileH contiene el alto de un tile.
			\param tileSetW contiene el ancho del tileSet.
			\param tileSetH contiene el alto del tileSet.
			\param colNumber contiene el numero de tiles de ancho del tileSet.
			\param rowNumber contiene el número de tiles de alto del tileSet.
		*/
		GfxEngine* gfxEngine;
		Image* image;
		string path;
		int tileW;
		int tileH;
		int tileSetW;
		int tileSetH;
		int colNumber;
		int rowNumber;
	
	public:
		//! Construye un tileSet a partir de la ruta el alto y ancho de un tile el motor grafico y su transparencia
		/*!
			\param path Contiene la ruta en la que se encuentra el tileSet a cargar
			\param tileW Contiene el ancho de un tile
			\param tileH Contiene el alto de un tile
			\param gfxEngine Contiene la información de la gestión de los gráficos.
			\param transparent Contiene la información de si debe llevar o no transparencia el tileSet (por defecto a true)
		*/
		TileSet(string path, int tileW, int tileH, GfxEngine* gfxEngine, bool transparent = true);
		
		//! Elimina el tileSet
		~TileSet();
		
		//! Obtiene de la imagen.
		/*!
			\return la imagen del tileSet
		*/
		Image* getImg();
		
		//! Obtiene del numero de columnas.
		/*!
			\return el número de columnas
		*/
		int getColumns();
		
		//! Obtiene del numero de filas.
		/*!
			\return el número de filas
		*/
		int getRows();

		//! Obtiene el ancho de un tile
		int getTileW();

		//! Obtiene el alto de un tile
		int getTileH();
};

#endif