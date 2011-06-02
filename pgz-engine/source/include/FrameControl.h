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
#ifndef __FRAMECONTROL_H__
#define __FRAMECONTROL_H__

// Clase "Window" de SFML en la que se apoya FrameControl
#include "SFML\Window.hpp"
#include <algorithm>

#include "Logger.h"

using namespace std;

//! Controla los frames por segundo que dibuja el juego.
/*! Permite imponer un límite a los FPS, 
	obtener la media de FPS a la que se está ejecutando el juego
	y obtener la duración del último frame.
*/
class FrameControl
{
	private:

		// Instancia de Logger
		Logger* logger;

		// Límite de fps (0 = sin límite)
		int fpsLimit;
		// Media de fps
		int fps;
		// Puntero a la ventana que gestiona
		sf::Window* window;
		// Tiempos de los últimos 10 frames del juego
		float frame_time[10];
		// Posición de la duración del último frame añadido
		int last_frame;
		// Cuántos frames han sido ejecutados (hasta 10)
		int n_frames;

	public:
		//! Instancia el controlador de frames.
		/*!
			\param fpsLimit Límite de los FPS (0 para deshabilitarlo).
		*/
		FrameControl(int fpsLimit = 0);
		//! Destructora por defecto
		~FrameControl();
		
		//! Inicializa el control de FPS. Debe llamarse después de la constructora.
		bool init(sf::Window* window, bool reboot = false);
		
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