#pragma once
#ifndef __FRAMECONTROL_H__
#define __FRAMECONTROL_H__

//! Controla los frames por segundo que dibuja el juego.
/*! Permite imponer un límite a los FPS, 
	obtener la media de FPS a la que se está ejecutando el juego
	y obtener la duración del último frame.
*/
class FrameControl
{
	public:
		//! Instancia el controlador de frames.
		/*!
			\param fpsLimit Límite de los FPS (0 para deshabilitarlo).
		*/
		FrameControl(int fpsLimit = 0);
		//! Destructora por defecto
		~FrameControl();
		
		//! Inicializa el control de FPS. Debe llamarse después de la constructora.
		void init();
		
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
};

#endif