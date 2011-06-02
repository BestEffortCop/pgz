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

#include "Game.h"

// Constructora y destructora

Game::Game(int screenW, int screenH, int bpp, int gameW, int gameH, int scale, int fps) 
{
	// Faltan datos para iniciar la aplicación, debe cerrarse en cuanto avise, para lo cual neceista el engineManager
	bool mustClose = (screenW <= 0 || screenH <= 0 || bpp <= 0);

	// Se establece una configuración básica para avisar del fallo
	if (mustClose)
	{
		screenW = 160; screenH = 144; bpp = 8;
	};

	// Si no se indica el ancho del juego, se supone el ancho de la ventana
	if (gameW <= 0) gameW = screenW;
	// Si no se indica el alto del juego, se supone el alto de la ventana
	if (gameH <= 0) gameH = screenH;

	// Si no se indica la escala del juego, suponemos escala real
	if (scale <= 0) scale = 1;

	// Si no se indican los fps, suponemos sin límite
	if (fps < 0) fps = 0;
	
	// Instancia el EngineManager con la configuración solicitada
	engineManager = new EngineManager(screenW, screenH, bpp, fps, gameW, gameH, scale);

	// Si se debe cerrar la app por falta de datos, este es el momento
	if (mustClose)
		engineManager->log("Configuración incorrecta para iniciar la aplicación."), exit(2);
	else
		engineManager->log("Aplicación arrancada correctamente.");

	// Guarda un puntero a los subsistemas de sonido, gráficos, entrada y control de frames
	if ((soundEngine = engineManager->getSoundEngine()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Audio, cerrando aplicación."), exit(2);
	if ((gfxEngine = engineManager->getGfxEngine()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Gráficos, cerrando aplicación."), exit(2);
	if ((input = engineManager->getInput()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Entrada, cerrando aplicación."), exit(2);
	if ((frameControl = engineManager->getFrameControl()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Timing, cerrando aplicación."), exit(2);

	engineManager->log("Subsistemas iniciados correctamente.");
	
	// Guarda la configuración del juego
	changeWorld = false;
	finished = false;
	gameWidth = gameW;
	gameHeight = gameH;
	screenWidth = screenW;
	screenHeight = screenH;
	theoricFps = fps;
	bpps = bpp;
	// de momento conservamos el ratio
	gameScaleWidth = scale;
	gameScaleHeight = scale;

	// Incialmente no guardamos estado del juego (world)
	gameState = NULL;
	nextState = NULL;
}

// Llama al evento asociado a la destrucción y elimina el engineManager instanciado
Game::~Game() 
{
	onDestroy();

	if (gameState != NULL)
		delete gameState, gameState = NULL;
	if (nextState != NULL)
		delete nextState, nextState = NULL;

	engineManager->log("Finalizando ejecución...");

	if (engineManager != NULL) 
	{ 
		delete engineManager; engineManager = NULL; 
	}
}

// Métodos de la clase

void Game::onStep() {};

void Game::step() 
{
	// Acciones a realizar si existe un GameState asignado al Game
	if (gameState != NULL) 
	{	
		// Actualiza el input
		input->checkInput();
		finished = input->getFinished();
		
		// se llama al evento onStep del juego
		onStep();
		
		// actualiza el gameState
		gameState->_update();

		// renderiza el gameState
		gameState->onRender();

		// pintamos sobre la pantalla de juego
		gfxEngine->display();
	}
	
	// Cambios en el GameState
	if (changeWorld)
		// Si hay un nuevo world válido
		if (gameState != NULL && nextState != NULL) 
		{
			// Invoca al evento de finalización del antiguo world
			gameState->onEnd();
			// Elimina el antiguo world
			delete gameState;
			// Actualiza al siguiente estado
			gameState = nextState;
			// No hay siguiente estado
			nextState = NULL;
			// Ya no hay que cambiar el world
			changeWorld = false;
			// Llama al evento de iniciación del nuevo world
			gameState->onInit();
		}
	
	// Obtiene el valor de la duración del último paso y actualiza el valor de los fps medios
	frameControl->update();
}

// Proporciona al Game el nuevo World al que se debe transitar
void Game::changeGameState(GameState* gState) {
	nextState = gState;
	changeWorld = true;
}

// Devuelve un puntero al world actual
GameState* Game::getGameState() { return gameState; }

// Devuelve un puntero al sistema de gráficos
GfxEngine* Game::getGfxEngine() { return gfxEngine; }

// Devuelve un puntero al sistema de sonido
SoundEngine* Game::getSoundEngine() { return soundEngine; }

// Devuelve un puntero al sistema de entrada
Input* Game::getInput() { return input; }

// Comprueba si la ejecución debe finalizar
bool Game::isFinished() { return finished; }

// Devuelve un puntero a un struct con la configuración del juego
GameConfig* Game::getGameConfig() 
{
	GameConfig* config = new GameConfig();
	config->gameWidth = this->gameWidth;
	config->gameHeight = this->gameHeight;
	config->screenWidth = this->screenWidth;
	config->screenHeight = this->screenHeight;
	config->theoricFps = this->theoricFps;
	config->bpps = this->bpps;
	config->gameScaleWidth = this->gameScaleWidth;
	config->gameScaleHeight = this->gameScaleHeight;
	
	return config;
}

// Determina si el juego debe o no finalizar
void Game::setFinished(bool finished) { this->finished = finished; }

void Game::setFPS(int fps)
{
	frameControl->setFPSLimit(fps);
};

int Game::getFPS()
{
	return frameControl->getFramesPerSecond();
};

int Game::getTargetFPS()
{
	return frameControl->getFPSLimit();
};

void Game::onDestroy() {}