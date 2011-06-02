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
#ifndef __GFXENGINE_H__
#define __GFXENGINE_H__

#include "SFML/Graphics.hpp"
#include "Color.h"
#include "SurfaceManager.h"
#include "Image.h"

#include "Logger.h"

class Image;

//! Subsitema gráfico encargado de facilitar funciones de renderizado al programador
/*!
	Se trata de la pieza clave del motor gráfico y usa la clase Image
	encapsulando ambas la librería gráfica subyaciente.

	Permite trabajar con los siguientes elementos:
	- Ventana de la aplicación (Screen)
	- Ventana del juego (GameScreen)

	La ventana de la aplicación es la ventana que ve el usuario.
	Sobre ella se dibuja la ventana del juego, que debe ser menor o igual en tamaño, y si el tamaño
	de la ventana de la aplicación lo permite, puede mostrarse expandida en un factor determinado.
	El trabajo con la ventana de la aplicación es transparente al usuario, que sólo debe indicar
	el tamaño de la misma.

	GfxEngine proporciona, además, métodos para dibujar elementos sobre la ventana del juego;
	así como métodos para el manejo de imágenes (Images).
*/


class GfxEngine
{
	friend class Image;
	friend class EngineManager;

	private:

	/* Instancia de logger */
	Logger* logger;

	/* Ventana del juego y de la aplicación */

	int gameX, gameY;						// Posición de la ventana del juego
	int gameW, gameH;						// Dimensiones de la ventana del juego
	int gameScaleH, gameScaleV;				// Escala de la ventana del juego

	int screenW, screenH;					// Dimensiones de la ventana de la aplicación
	int screenBPP;							// Profundidad de color de la ventana de la app
	Color* screenBgColor;					// Color de fondo de la ventana de la app

	int targetScreenW, targetScreenH;		// Dimensiones deseadas de la ventana de la aplicación
	int targetBPP;							// Profundidad de color deseada de la ventana de la app
	
	bool fullScreenMode;					// Indica si está en fullscreen o no
	std::string windowTitle;				// Título de la ventana de aplicación

	sf::RenderWindow* appScreen;			// Ventana de la aplicación
	sf::RenderImage* gameScreen;			// Ventana del juego
	sf::RenderImage* currentRenderTarget;	// Destino de render actual

	SurfaceManager* surfaceManager;			// Nuestro SurfaceManager

	/* ****************** *\
	|*	Métodos privados  *|
	\* ****************** */

	//! Inicializa el GfxEngine
	/*! Necesita que se le indique la ventana creada para la aplicación
		\param window Ventana instanciada de la librería subyaciente
	*/
	bool init(sf::RenderWindow* window);

	// Centra la ventana del juego en la ventana de la aplicación
	void centerGameScreen();

	/* *** Manejo de imágenes *** */

	// Crea una imagen (para escritura) de tamaño w x h
	sf::RenderImage* createImage(int w, int h);

	// Carga la imagen indicada
	sf::Image* loadImage(std::string fname, bool transparent = true);

	// Libera la imagen indicada
	bool deleteImage(std::string fname);
	bool deleteImage(sf::Image* image);

	public:

	//! Construye el GfxEngine con los parámetros indicados.
	/*!
		Este método sólo prepara la estructura del GfxEngine,
		que deberá inicializarse expresamente mediante GfxEngine::Init()
		\param screenw Ancho de la ventana de la aplicación
		\param screenh Alto de la ventana de la aplicación
		\param screenbpp Profundidad de color
		\param gameW [Opcional] Ancho de la ventana del juego (-1 para el ancho de la ventana de aplicación)
		\param gameH [Opcional] Alto de la ventana del juego (-1 para el alto de la ventana de aplicación)
		\param zoom [Opcional] Factor de ampliación de la ventana de juego.
	*/
	GfxEngine(int screenw, int screenh, int screenbpp, int gameW = -1, int gameH = -1, int zoom = -1);

	//! Destructora
	~GfxEngine();

	/*********************************************************************\
	*	Manejo de la ventana del juego y de la ventana de la aplicación	  *
	\*********************************************************************/

	//! Establece las dimensiones de la ventana de la aplicación
	/*!
		En caso de no ser capaz de establecer las nuevas dimensiones, los valores
		no se verán modificados.

		Las dimensiones indicadas deben ser capaces de contener la ventana de juego
		con la configuración de escalado actual.

		\param width Ancho de la ventana
		\param height Alto de la ventana
		\return True si la operación ha tenido éxito, false en otro caso
	*/
	bool setScreenSize(int width, int height);

	//! Establece las dimensiones de la ventana del juego
	/*!
		En caso de no ser capaz de establecer las nuevas dimensiones, los valores
		no se verán modificados.

		Las dimensiones indicadas deben caber en la ventana de la aplicación
		con la configuración de escalado actual.

		\param width Ancho de la ventana
		\param height Alto de la ventana
		\return True si la operación ha tenido éxito, false en otro caso
	*/
	bool setGameScreenSize(int width, int height);

	//! Establece el factor de escalado de la ventana del juego
	/*!
		Las ventana del juego tras aplicar el escalado deben caber en la ventana de la aplicación.

		\param hFactor Escalado horizontal (1 para tamaño real)
		\param vFactor Escalado Vertical (1 para tamaño real)
		\return True si la operación ha tenido éxito, false en otro caso
	*/
	bool setGameScreenScale(int hFactor, int vFactor);

	//! Obtiene el ancho de la ventana de la aplicación
	/*! \return Ancho de la ventana de la aplicación */
	int getScreenWidth();

	//! Obtiene el alto de la ventana de la aplicación
	/*! \return Alto de la ventana de la aplicación */
	int getScreenHeight();

	//! Obtiene la posición horizontal de la ventana del juego sobre la ventana de la aplicación
	/*! \return Posición horizontal de la ventana del juego */
	int getGameScreenX();

	//! Obtiene la posición vertical de la ventana del juego sobre la ventana de la aplicación
	/*! \return Posición vertical de la ventana del juego */
	int getGameScreenY();

	//! Obtiene el ancho de la ventana del juego
	/*! \return Ancho de la ventana del juego */
	int getGameScreenWidth();

	//! Obtiene el alto de la ventana del juego
	/*! \return Alto de la ventana del juego */
	int getGameScreenHeight();

	//! Obtiene el factor de zoom horizontal del juego
	/*! \return Factor de zoom horizontal del juego */
	int getGameScreenScaleH();

	//! Obtiene el factor de zoom vertical del juego
	/*! \return Factor de zoom vertical del juego */
	int getGameScreenScaleV();

	//! Establece el color del área de la ventana de la aplicación no ocupada por la ventana del juego
	/*! \param color Color de fondo */
	void setScreenBackgroundColor(Color color);

	//! Obtiene el color del área de la ventana de la aplicación no ocupada por la ventana del juego
	/*! \return Color del área de la ventana de la aplicación no ocupada por la ventana del juego */
	Color getScreenBackgroundColor();

	/*********************************************************************\
	*						Métodos de Renderizado						  *
	\*********************************************************************/

	//! Establece la Image sobre la que se realizarán los renderizados que no especifiquen destino.
	/*! \param target Image sobre la que se realizará el renderizado (debe estar inicializada y aceptar escritura) */
	void setRenderTarget(Image* target);

	//! Establece la ventana del juego como destino de los renderizados que no especifiquen destino.
	void resetRenderTarget();

	//! Renderiza una Image sobre el destino especificado o sobre la ventana del juego si no se especifica.
	/*!
		\param image Imagen a renderizar
		\param x Posición horizontal de image en dest
		\param y Posición vertical de image en dest
		\param dest [Opcional] Imagen destino del renderizado (NULL para Imagen por defecto)
	*/
	void render(Image* image, int x, int y, Image* dest = NULL);

	//! Renderiza parte de una Image sobre el destino especificado o sobre la ventana del juego si no se especifica.
	/*!
		\param image Imagen a renderizar
		\param x Posición horizontal de image en dest
		\param y Posición vertical de image en dest
		\param xOrigin Coordenada X de la esquina superior izquierda de la parte de image a renderizar
		\param yOrigin Coordenada Y de la esquina superior izquierda de la parte de image a renderizar
		\param width Ancho de la parte de image a renderizar
		\param height Alto de la parte de image a renderizar
		\param dest [Opcional] Imagen destino del renderizado (NULL para Imagen por defecto)
	*/
	void renderPart(Image* image, int x, int y, int xOrigin, int yOrigin, int width, int height, Image* dest = NULL);

	//! Renderiza una Image ampliada sobre el destino especificado o sobre la ventana del juego si no se especifica.
	/*!
		\param image Imagen a renderizar
		\param x Posición horizontal de image en dest
		\param y Posición vertical de image en dest
		\param xScale Factor de ampliación horizontal
		\param yScale Factor de ampliación vertical
		\param dest [Opcional] Imagen destino del renderizado (NULL para Imagen por defecto)
	*/
	void renderResized(Image* image, int x, int y, int xScale, int yScale, Image* dest = NULL);

	//! Renderiza una Image aplicando efectos
	/*!
		\param image Imagen a renderizar
		\param x Posición horizontal de image en dest
		\param y Posición vertical de image en dest
		\param color Color de tintado de image
		\param alpha Transparencia a aplicar
		\param scaleH Factor de ampliación horizontal
		\param scaleV Factor de ampliación vertical
		\param rotation Ángulo de rotación a aplicar
		\param dest [Opcional] Imagen destino del renderizado (NULL para destino por defecto)
	*/
	void renderExt(Image* image, int x, int y, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest = NULL, int originX = 0, int originY = 0);

	//! Renderiza parte de una Image aplicando efectos
	/*!
		\param image Imagen a renderizar
		\param x Posición horizontal de image en dest
		\param y Posición vertical de image en dest
		\param xOrigin Coordenada X de la esquina superior izquierda de la parte de image a renderizar
		\param yOrigin Coordenada Y de la esquina superior izquierda de la parte de image a renderizar
		\param width Ancho de la parte de image a renderizar
		\param height Alto de la parte de image a renderizar
		\param color Color de tintado de image
		\param alpha Transparencia a aplicar
		\param scaleH Factor de ampliación horizontal
		\param scaleV Factor de ampliación vertical
		\param rotation Ángulo de rotación a aplicar
		\param dest [Opcional] Imagen destino del renderizado (NULL para destino por defecto)
	*/
	void renderPartExt(Image* image, int x, int y, int xOrigin, int yOrigin, int width, int height, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest = NULL, int originX = 0, int originY = 0);

	//! Renderiza la ventana del juego centrada sobre la ventana de la aplicación, aplicando el escalado correspondiente
	/*!
		Es necesario llamar a este método para que el contenido de la ventana del juego sea visible al jugador.
	*/
	void display();

	/*********************************************************************\
	*						Manejo de Imágenes							  *
	\*********************************************************************/
/*
	//! Crea una imagen vacía con el ancho y el alto especificados con modo de escritura si fuera necesario.
	/*!
		A partir del momento en que se devuelva la imagen creada,
		será tarea del programador mantenerla y borrarla cuando no sea necesaria.
		Si la imagen acepta escritura, ocupa más en memoria y habrá que manejarla con
		mayor cuidado, aunque sólo las imágenes que acepten escritura podrán ser destino
		de los métodos de renderizado.

		\param width Ancho de la imagen
		\param height Alto de la imagen
		\param write Modo de escritura activado para la imagen
		\return Un puntero a la nueva imagen o NULL si ha habido algún problema
	*_/
	Image* createImage(int width, int height, bool write = false);

	/* No estoy seguro de estas,
		podrían eliminarse y que se encarge Image::~Image()

	//! Elimina la superficie que encapsula la imagen indicada por fname.
	bool deleteImage(string* fname);

	//! Elimina la superficie que encapsula la imagen que se le pasa.
	bool deleteImage(Image* image);
	*/

	//! Rellena la imagen con el color indicado
	/*!
		\param image Imagen a rellenar
		\param color Color de relleno
	*/
	void clearImage(Image* image, Color color);

	/*********************************************************************\
	*						Sección Experimental						  *
	\*********************************************************************/

	//! Dibuja un rectángulo coloreado de determinado tamaño en la posición indicada, en un determinado destino
	/*!
		Si se activa outline, se dibujará sólo el perímetro del mismo con el color indicado
		\param x Posición horizontal de la esquina superior izquierda del rectángulo
		\param y Posición vertical de la esquina superior izquierda del rectángulo
		\param width Ancho del rectángulo
		\param height Alto del rectángulo
		\param color Color de relleno o del perímetro del rectángulo
		\param dest [Opcional] Destino del render
	*/
	void renderRectangle(int x, int y, int width, int height, Color color, bool outline = false, Image* dest = NULL);

	//! Hace la imagen transparente
	/*!
		La imagen debe aceptar escritura
		\param image Puntero a la imagen a limpiar
	*/
	void clearImageTransparent(Image* image);

	//! Guarda la imagen en el archivo indicado
	/*!
		\param image Puntero a la imagen a guardar
		\param fname Archivo sobre el que guardar
		\return Si el guardado ha tenido éxito o no
	*/
	bool saveImage(Image* image, std::string fname);

	//! Establece el modo pantalla completa o ventana
	/*!
		\param on True para pantalla completa, false para ventana
		\return Si el cambio ha tenido éxito o no
	*/
	bool setFullscreen(int on);

	//! Comprueba si el modo es pantalla completa o ventana
	/*!
		\return True si está en pantalla completa
	*/
	bool getFullscreen();

	//! Establece el título a mostrar en la ventana del juego
	/*!
		\param title Título a mostrar
		\return Si el cambio ha tenido éxito o no
	*/
	bool setWindowTitle(std::string title);

	//! Obtiene el título de la ventana del juego
	/*!
		\return Título de la ventana
	*/
	std::string getWindowTitle();
};

#endif
