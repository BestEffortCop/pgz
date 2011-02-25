#include "EngineManager.h"

/***********************************************
 *			Funciones Privadas				   *
 ***********************************************/

EngineManager::init()
{
	window = new sf::RenderWindow();

	if(!gfxEngine.init(window))
	{
		log("EngineManager.init()::Se ha producido un problema en gfxEngine.init()\n");
	}

	if(!soundEngine.init())
	{
		log("EngineManager.init()::Se ha producido un problema en soundEngine.init()\n");
	}

	if(!input.init())
	{
		log("EngineManager.init()::Se ha producido un problema en input.init()\n");
	}
}

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/
EngineManager::EngineManager(int screenW, int screenH, int screenBPP, int gameW = -1, int gameH = -1, int gameScale = -1)
{
	gfxEngine = new GfxEngine(screenW, screenH, screenBPP, gameW, gameH, gameScale);
	soundEngine = new SoundEngine();
	input = new Input();
	log = new Logger();
}
		
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
