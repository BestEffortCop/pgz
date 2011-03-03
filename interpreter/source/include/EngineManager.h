#pragma once
#ifndef __ENGINEMANAGER_H__
#define __ENGINEMANAGER_H__

#include "SFML\Window.hpp"
#include "SFML\Graphics\RenderWindow.hpp"

#include "GfxEngine.h"
#include "FrameControl.h"
#include "SoundEngine.h"
#include "Input.h"
#include "Logger.h"


//! EngineManager es la encargada de inicializar la capa de bajo nivel del motor.
/*!
	Prepara y mantiene los subsistemas de audio, gráficos, control de frames y entrada,
	permitiendo obtenerlos cuando sea necesario.
	
	También mantiene un log sobre el que el programador puede depositar
	los datos que considere necesarios.
*/
class EngineManager
{
	private:
		//! Puntero al sistema de gráficos.
		GfxEngine* gfxEngine;
		//! Control de frames.
		FrameControl* frameControl;
		//! Puntero al sistema de audio.
		SoundEngine* soundEngine;
		//! Puntero al sistema reconocedor de entrada.
		Input* input;
		//! Puntero al log del sistema.
		Logger* logger;
		//! Puntero a la ventana principal.
		sf::Window* window;

		//! Inicializa los atributos de la clase por defecto.
		bool init();

	public:
	
		//! Crea todos los subsistemas.
		/*!
			\param screenW Ancho de la ventana de la aplicación
			\param screenH Alto de la ventana de la aplicación
			\param screenBPP Profundidad de Color
			\param fps Frames por segundo del juego
			\param gameW [Opcional] Ancho de la ventana del juego
			\param gameH [Opcional] Alto dela ventana del juego
			\param gameScale [Opcional] Factor de escalado de la ventana del juego
		*/
		EngineManager(int screenW, int screenH, int screenBPP, int fps, int gameW = -1, int gameH = -1, int gameScale = -1);
		
		//! Destructora de la clase.
		~EngineManager();
		
		//! Obtiene el puntero del subsistema gráfico
		/*! \return Puntero al subsistema gráfico */
		GfxEngine* getGfxEngine();

		//! Obtiene el puntero del subsistema de control de frames
		/*! \return Puntero al subsistema de control de frames */
		FrameControl* getFrameControl();
		
		//! Obtiene el puntero del subsistema de audio
		/*! \return Puntero al subsistema de audio */
		SoundEngine* getSoundEngine();
		
		//! Obtiene el puntero del subsistema de entrada
		/*! \return Puntero al subsistema de entrada */
		Input* getInput();
		
		//! Escribe un mensaje en el log
		/*! \param message Mensaje a escribir en el log */
		void log(char* message);
};

#endif