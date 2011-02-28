#pragma once
#ifndef __FRAMECONTROL_H__
#define __FRAMECONTROL_H__

// Clase "Window" de SFML en la que se apoya FrameControl
#include "SFML\Window.hpp"

//! Controla los frames por segundo que dibuja el juego.
/*! Permite imponer un límite a los FPS, 
	obtener la media de FPS a la que se está ejecutando el juego
	y obtener la duración del último frame.
*/
class FrameControl
{
	private:
		// Límite de fps (0 = sin límite)
		int fpsLimit;
		// Media de fps
		int fps;
		// Puntero a la ventana que gestiona
		sf::Window* window;

	public:
		//! Instancia el controlador de frames.
		/*!
			\param fpsLimit Límite de los FPS (0 para deshabilitarlo).
		*/
		FrameControl(int fpsLimit = 0);
		//! Destructora por defecto
		~FrameControl();
		
		//! Inicializa el control de FPS. Debe llamarse después de la constructora.
		bool init(sf::Window* window);
		
		//! Establece el límite de los FPS.
		/*!
			\param fpsLimit Límite de los FPS (0 para deshabilitarlo).
		*/
		void setFPSLimit(int fpsLimit = 0);
		
		//! Obtiene el límite establecido para los FPS (No los FPS medios reales)
		/*!
			\return Límite establecido para los FPS.
		*/
		int getFPSLimit();
		
		//! Obtiene la media de FPS a la que se está ejecutando el juego
		/*
			\return Media de FPS.
		*/
		int getFramesPerSecond();
		
		//! Obtiene la duración del último frame.
		/*
			Calculada a partir de la diferencia de tiempos de los dos últimos frames.
			\return Duración del último frame.
		*/
		int getDelay();

		// Obtiene el valor de la duración del frame en cada paso del juego
		// y actualiza el valor de la media de fps en consecuencia
		// Debe llamarse en cada paso del juego
		void update();
};

#endif