#pragma once

#ifndef __TILESET_H__
#define __TILESET_H__

using namespace std;

//!Encapsula un elemento gráfico que se divide en tiles de tamaño configurable
/*!
	Proporciona métodos para acceder a tiles de forma sencilla. Pertenece a la clase Graphic
	por ser un elemento gráfico con elementos del mapa a pintar.
*/

class TileSet : public Graphic {

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
};

#endif