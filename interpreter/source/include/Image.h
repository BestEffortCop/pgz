#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "SFML/Graphics.hpp"
#include "GfxEngine.h"

using namespace std;

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
	Image(string path, GfxEngine* gfxEngine, bool transparent = true, bool write = false);
	
	//! Construye una imagen vacía para trabajar sobre ella.
	/*!
		\param gfxEngine Puntero al subsistema gráfico.
		\param width Anchura de la imagen a crear.
		\param height Altura de la imagen a crear.
		\param transparent [Opcional] Flag que determina si la imagen será transparente o no.
		\param write [Opcional] Flag que determina si se puede pintar sobre la imagen o no.
	*/
	Image(GfxEngine* gfxEngine, int width, int height, bool transparent = true, bool write = false);

	//! Destructora.
	~Image();

	//! Carga la imagen especificada en la ruta.
	/*!
		\param path Ruta de la imagen dada.
		\param transparent [Opcional] Flag que determina si la imagen será transparente o no.
	*/
	void loadImage(string path, bool transparent = true);

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
};

#endif
