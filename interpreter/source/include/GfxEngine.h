#pragma once
#ifndef __GFXENGINE_H__
#define __GFXENGINE_H__

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
	
	//! Inicializa el GfxEngine
	/*! Necesita que se le indique la ventana creada para la aplicación
		\param window Ventana instanciada de la librería subyaciente
	*/
	bool init(sf::RenderWindow* window);
	
	/*********************************************************************\
	*	Manejo de la ventana del juego y de la ventana de la aplicación	  *
	\*********************************************************************/
	
	//! Establece las dimensiones de la ventana de la aplicación
	/*!
		En caso de no ser capaz de establecer las nuevas dimensiones, los valores
		no se verán modificados.
		\param width Ancho de la ventana
		\param height Alto de la ventana
		\return True si la operación ha tenido éxito, false en otro caso
	*/
	bool setScreenSize(int width, int height);
	
	//! Establece las dimensiones de la ventana del juego
	/*!
		En caso de no ser capaz de establecer las nuevas dimensiones, los valores
		no se verán modificados.
		\param width Ancho de la ventana
		\param height Alto de la ventana
		\return True si la operación ha tenido éxito, false en otro caso
	*/
	bool setGameScreenSize(int width, int height);
	
	//! Establece el factor de escalado de la ventana del juego
	/*!
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
	Color getScreenBackgroundColor(Color color);
	
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
	void renderExt(Image* image, int x, int y, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest = NULL);
	
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
	void renderPartExt(Image* image, int x, int y, int xOrigin, int yOrigin, int width, int height, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest = NULL);
	
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
};

#endif