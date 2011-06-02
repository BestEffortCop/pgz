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

#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include "tileSet.h"
#include "GfxEngine.h"
#include "Image.h"
#include "Graphic.h"
#include <stdio.h>


using namespace std;

//! Representa el aspecto gráfico de un mapa de tiles
/*!
	Encapsula un tileSet que le servirá de base y guarda el grafico resultante de componer los tiles
	que se le indiquen.
	Se compone indicando que número de un tileSet va en cada posición de su rejilla.

	Para usarlo, tras construir la instancia de TileMap habrá que cargar o indicar el tileset que se va a usar
	y luego cargar o pasar el mapa.
*/

class TileMap : public Graphic 
{
	friend class Map;
	private:
		//! Atributos de la clase TileMap.
		/*!
			\param tileW ancho de un tile
			\param tileH alto de un tile
			\param rowNumber número de filas del mapa
			\param ColNumber número de columnas del mapa
			\param tileSet conjunto de tiles
			\param idMap identifica el tile dentro de tileSet con su posición en el mapa
			\param mapImage imagen del mapa
			\param gfxEngine contiene la información de la gestión de gráficos
		*/
		int tileW,tileH;
		int rowNumber,colNumber;
		
		bool loadedTset;
		TileSet* tileSet;
		int** idMap;
		Image* mapImage;

		GfxEngine* gfxEngine;

	public:

		//! Construye un tileMap a partir del alto y ancho de un tile y el motor grafico
		/*!
			\param tileW contiene el ancho de un tile
			\param tileH contiene el alto de un tile
			\param gfxEngine contiene la información de la gestión de los gráficos.
		*/
		TileMap(int tileW, int tileH, GfxEngine* gfxEngine);

		//! Destructora
		~TileMap();

		//! Establece del tileSet en el que se basará el mapa
		/*!
			\param tspath contiene la ruta del tileSet
		*/
		void setTileSet(string tspath);

		//! Establece el TileSet del mapa
		/*!
			La instancia a la que apunta tset no debe borrarse, de ello se encargará TileMap.

			\param tset Puntero al nuevo TileSet
		*/
		void setTileSet(TileSet* tset);

		//! Obtiene el tileset actual del mapa
		/*! \return Tileset actual */
        virtual TileSet* getTileset();

		//! Establece del mapa en si, a partir de otro mapa
		/*!
			La instancia a la que apunta map no debe borrarse, de ello se encargará TileMap.

			\param map contiene el mapa del que será copiado el mapa
		*/
		void setMap(int** map, int col, int row);

		//! Carga un mapa del archivo indicado
		/*!
			El método de carga requiere que el archivo que se le pasa tenga el siguiente formato:

			COLUMNAS FILAS
			TIPO1 TIPO2 TIPO3 ... TIPON

			Siendo N = COLUMNAS x FILAS

			\param fname Nombre de archivo con el mapa
		*/
		void loadMap(string fname);

		//! Establece del número de columnas del mapa
		/*!
			\param col contiene el número de columnas del mapa
		*/
		void setCols(int col);

		//! Establece del número de filas del mapa
		/*!
			\param row contiene el número de filas del mapa
		*/
		void setRows(int row);

		//! Establece del número de columnas del mapa
		/*!
			\return el número de columnas del mapa
		*/
		int getCols();

		//! Devuelve del número de filas del mapa
		/*!
			\return el número de filas del mapa
		*/
		int getRows();

		//! Obtiene de la imagen del mapa ya construído.
		/*!
			\return la imagen del mapa
		*/
		Image* getMapImage();

		//! Se en carga de dibujar el tileMap en una posición en concreto
		/*!
			\param x contiene la coordenada x del tile en el que empezará el tileMap
			\param y contiene la coordenada y del tile en el que empezará el tileMap
		*/
		void render(int x, int y);

		//! Obtiene del ancho de cada tile del tileMap
		/*!
			\return el ancho de los tiles del tileMap
		*/
		int getWidth();

		//! Obtiene del alto de cada tile del tileMap
		/*!
			\return el alto de los tiles del tileMap
		*/
		int getHeight();

		//! Establece de uno de los tiles del mapa
		/*!
			\param x contiene la coordenada x del tile que deseamos cambiar
			\param y contiene la coordenada y del tile que queremos cambiar
			\param tile contiene el tile del tileSet que vamos a colocar en la posición indicada del mapa
		*/
		void setTile(int x, int y, int tile);

		//! Establece de uno de los tiles del mapa con efectos
		/*!
			\param x contiene la coordenada x del tile que deseamos cambiar
			\param y contiene la coordenada y del tile que queremos cambiar
			\param tile contiene el tile del tileSet que vamos a colocar en la posición indicada del mapa
		*/
		void setTileExt(int x, int y, int tile, Color color, float alpha, float scaleH, float scaleV, float rotation);
};

#endif // _TILEMAP_H_
