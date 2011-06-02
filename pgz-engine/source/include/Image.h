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
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "SFML/Graphics.hpp"
#include "GfxEngine.h"

class Logger;
class GfxEngine;

//! Parte importante del subsistema gráfico del motor.
/*!
	Una Image representa un mapa de bits cualquiera. Su ciclo de vida comienza
	a petición del programador, ya sea cargando un archivo de imagen (bmp, png...)
	o creándo una imagen vacía. Las imágenes pueden ser dibujadas sobre la
	pantalla de juego o sobre otras imágenes.

	Image encapsula un mapa de bits al nivel de la librería gráfica subyaciente.
*/

class Image
{
	friend class GfxEngine;

	protected:

        // Referencia al motor gráfico
        GfxEngine* gfxEngine;

        bool writeable;
        bool transparent;
		bool loaded;		// Indica si la imagen ha sido cargada de archivo
		Logger* logger;

        // Imagen capaz de ser destino de un renderizado
        sf::RenderImage* wpic;

        // Imagen a pintar, elemento de sólo lectura
        sf::Sprite* rpic;

        // Ruta de la imagen
        std::string path;

        // Devuelve la imagen modificable
		sf::RenderImage* getSurfaceW();

		// Devuelve la imagen de sólo lectura
		sf::Sprite* getSurfaceR();

	public:

	//! Construye la imagen especificada con una ruta y unos parámetros dados.
	/*!
		Este método, además de inicializar los parámetros de la imagen,
		llama al método Image::loadImage() para cargar el mapa de bits en memoria.
		\param path Ruta de la imagen dada.
		\param gfxEngine Puntero al subsistema gráfico.
		\param transparent [Opcional] Flag que determina si la imagen será transparente o no.
		\param write [Opcional] Flag que determina si se puede pintar sobre la imagen o no.
	*/
	Image(std::string path, GfxEngine* gfxEngine, bool transparent = true, bool write = false);

	//! Construye una imagen vacía para trabajar sobre ella.
	/*!
		\param gfxEngine Puntero al subsistema gráfico.
		\param width Anchura de la imagen a crear.
		\param height Altura de la imagen a crear.
		\param transparent [Opcional] Flag que determina si la imagen será transparente o no.
		\param write [Opcional] Flag que determina si se puede pintar sobre la imagen o no.
	*/
	Image(int width, int height, GfxEngine* gfxEngine, bool transparent = true, bool write = false);

	//! Destructora.
	~Image();

	//! Carga la imagen especificada en la ruta.
	/*!
		\param path Ruta de la imagen dada.
		\param transparent [Opcional] Flag que determina si la imagen será transparente o no.
	*/
	bool loadImage(string path, bool transparent = true);

	//! Realiza los cambios sobre la imagen writeable.
	void refresh();

	//! Obtiene el ancho de la imagen.
	/*!
		\return path Ancho de la imagen dada.
	*/
	int getWidth();

	//! Obtiene el alto de la imagen.
	/*!
		\return path Alto de la imagen dada.
	*/
	int getHeigth();

	//! Obtiene la ruta de la imagen.
	/*!
		\return path Ruta de la imagen.
	*/
	std::string getPath();
};

#endif
