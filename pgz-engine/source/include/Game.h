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

#ifndef __GAMEH__
#define __GAMEH__

#include "EngineManager.h"
#include "FrameControl.h"
#include "GameState.h"
#include "SoundEngine.h"
#include "GfxEngine.h"
#include "Input.h"

using namespace std;

//! GameConfig es una estructura que contiene la información de configuración del juego. Es utilizada por Game.
//! \sa Game
struct GameConfig
{
	//! Ancho de la ventana del juego
	int gameWidth;
	
	//! Alto de la ventana del juego
	int gameHeight;
	
	//! Ancho de la ventana de la aplicación
	int screenWidth;
	
	//! Alto de la ventana de la aplicación
	int screenHeight;
	
	//! FPS teóricos del juego
	int theoricFps;
	
	//! Profundidad de color (en BitsPerPixel)
	int bpps;
	
	//! Factor de escalado horizontal del juego
	int gameScaleWidth;
	//! Factor de escalado vertical del juego
	int gameScaleHeight;
};

class GameState;

//! Game es la clase principal del motor que controla todo lo relacionado con el juego.
/*!
	Se encarga de iniciar y mantener el bucle del juego.
	Para ello gestiona un GameState, permitiendo actualizarlo y cambiarlo por otro,
	además de manejar la entrada y el renderizado. Si el juego no tiene un GameState
	asignado, finalizará su ejecución.
	
	También permite interactuar con la capa inferior del motor de juego para
	un control preciso de los subsistemas.
	
	Se encarga además de la correcta finalización de todo el sistema.
	
	El programador debe derivar una clase de Game y redefinir sus métodos para
	que realicen las acciones que requiera.
*/
class Game {
	protected:
		//! Atributos de la clase game.
		/*!
			\param gameState contiene la información de la configuración actual del juego.
			\sa GameState
			\param sfxEngine contiene la información de la gestión del sonido.
			\param gfxEngine contiene la información de la gestión de los gráficos.
			\param input contiene la información relacionada con la entrada.
			\param finished señala si el juego ha terminado o no.
		*/
		GameState* gameState;
		GameState* nextState;			// new!
		SoundEngine* soundEngine;
		GfxEngine* gfxEngine;
		EngineManager* engineManager;	// new!
		FrameControl*  frameControl;	// new!
		Input* input;
		bool finished;
		bool changeWorld;				// new! (indica si toca cambiar el GameState)
		
		// configuración del juego
		int gameWidth;
		int gameHeight;
		int screenWidth;
		int screenHeight;
		int theoricFps;
		int bpps;
		int gameScaleWidth;
		int gameScaleHeight;
		
	public:
		//! Constructora por defecto.
		/*!
			Inicializará los distintos elementos y pondrá finished a false.
		*/
		Game(int screenW, int screenH, int bpp, int gameW, int gameH, int scale, int fps);
		
		//! Destruye el Game
		virtual ~Game();
		
		//! Evento ejecutado antes del update en cada step.
		/*!
			Contendrá las acciones que deban realizarse cada paso del juego.
			Se llama en cada step, inicialmente vacío, pero sobreescribible por clases derivadas.
		*/
		virtual void onStep();
		
		//! Realiza un paso global del juego.
		/*!
			Se encarga de todo lo que se ha de hacer en cada step:
			- Actualiza el input
			- Ejecuta su evento Game::onStep()
			- Actualiza el GameState actual, y por extensión todas las entidadesa
			- Comprueba el framerate
			- Renderiza el GameState
		*/
		void step();
		
		//! Cambia el GameState actual
		/*!
			\param gameState Siguiente GameState
		*/
		virtual void changeGameState(GameState* gameState);
		
		//! Obtiene el GameState actual
		/*!
			\return GameState actual del juego.
		*/
		virtual GameState* getGameState();
		
		//! Obtiene el subsistema gráfico del sistema
		/*!
			\return Puntero al subsistema gráfico
		*/
		GfxEngine* getGfxEngine();
		
		//! Obtiene el subsistema de audio del sistema
		/*!
			\return Puntero al subsistema de audio
		*/
		SoundEngine* getSoundEngine();
		
		//! Obtiene el subsistema de entrada
		/*!
			\return Puntero al subsistema de entrada
		*/
		Input* getInput();

		//! Indica si el juego ha finalizado
		/*!
			\return true si el juego ha finalizado
		*/
		virtual bool isFinished();
		
		//! Obtiene la configuración actual del juego
		/*!
			\return GameConfig con la configuración del juego
			\sa GameConfig
		*/
		virtual GameConfig* getGameConfig();
		
		//! Establece la finalización del juego
		/*!
			\param finished Juego finalizado
		*/
		virtual void setFinished(bool finished = true);
		
		//! Establece el límite de FPS del juego
		/*!
			\param fps Frames por Segundo
		*/
		virtual void setFPS(int fps);

		//! Obtiene el límite de FPS del juego
		/*!
			\return Frames por Segundo teóricos del juego
		*/
		virtual int getTargetFPS();

		//! Obtiene los FPS a los que está funcionando el juego
		/*!
			\return Frames por Segundo reales del juego
		*/
		virtual int getFPS();

		//! Evento ejecutado antes de finalizar el juego
		/*!
			Contendrá las acciones a realizar antes de finalizar el juego.
			Inicialmente vacío, pero sobreescribible por clases derivadas.
		*/
		virtual void onDestroy();
};

#endif