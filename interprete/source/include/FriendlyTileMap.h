#pragma once
#ifndef __FTMAP_H__
#define __FTMAP_H__

#include "TileSet.h"
#include "Graphic.h"

class FriendlyTile
{
public:
	int tileId;
	float alpha;
	Color color;

	FriendlyTile(int tileId);
	void render(int x, int y, TileSet* tset, GfxEngine* gfxEngine, Color c = Color::White, float alpha = 1.0f, Image* dest = NULL);
};

class FriendlyTileMap : public Graphic 
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
		FriendlyTile** tMap;

		GfxEngine* gfxEngine;

	public:

		//! Construye un tileMap a partir del alto y ancho de un tile y el motor grafico
		/*!
			\param tileW contiene el ancho de un tile
			\param tileH contiene el alto de un tile
			\param gfxEngine contiene la información de la gestión de los gráficos.
		*/
		FriendlyTileMap(int tileW, int tileH, GfxEngine* gfxEngine);

		//! Destructora
		~FriendlyTileMap();

		//! Establece del tileSet en el que se basará el mapa
		/*!
			\param tspath contiene la ruta del tileSet
		*/
		void setTileSet(std::string tspath);

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
		void loadMap(std::string fname);

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

		//! Devuelve el ancho del mapa
		/*!
			\return el ancho del mapa
		*/
		int getWidth();

		//! Devuelve el alto del mapa
		/*!
			\return el alto del mapa
		*/
		int getHeight();

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
		int getTileWidth();

		//! Obtiene del alto de cada tile del tileMap
		/*!
			\return el alto de los tiles del tileMap
		*/
		int getTileHeight();

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

		//! Limpia el FriendlyTileMap
		void clear();
};

#endif