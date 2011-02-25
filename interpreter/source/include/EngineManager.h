#pragma once
#ifndef __ENGINEMANAGER_H__
#define __ENGINEMANAGER_H__

//! EngineManager es la encargada de inicializar la capa de bajo nivel del motor.
/*!
	Prepara y mantiene los subsistemas de audio, gráficos y entrada,
	permitiendo obtenerlos cuando sea necesario.
	
	También mantiene un log sobre el que el programador puede depositar
	los datos que considere necesarios.
*/
class EngineManager
{
	public:
	
		//! Inicializa todos los subsistemas
		/*!
			\param screenW Ancho de la ventana de la aplicación
			\param screenH Alto de la ventana de la aplicación
			\param screenBPP Profundidad de Color
			\param gameW [Opcional] Ancho de la ventana del juego
			\param gameH [Opcional] Alto dela ventana del juego
			\param gameScale [Opcional] Factor de escalado de la ventana del juego
		*/
		EngineManager(int screenW, int screenH, int screenBPP, int gameW = -1, int gameH = -1, int gameScale = -1);
		
		//! Obtiene el puntero del subsistema gráfico
		/*! \return Puntero al subsistema gráfico */
		GfxEngine* getGfxEngine();
		
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