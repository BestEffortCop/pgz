#include "EngineManager.h"

/***********************************************
 *			Funciones Privadas				   *
 ***********************************************/

/* EngineManager::init() */
/*
	Esta función se encarga de inicializar todos los atributos de la clase
	para ello llama a los init de cada uno de ellos y comprueba que devuelvan
	true, en caso contrario escribe en el log del sistema la localización del
	error y devuelve false.
	Si todo funciona correctamente devuelve true.
*/
bool EngineManager::init()
{

	if(!gfxEngine->init((sf::RenderWindow *)window))
	{
		log("EngineManager.init()::Se ha producido un problema en gfxEngine.init()\n");
		return false;
	}

	if(!frameControl->init(window))
	{
		log("EngineManager.init()::Se ha producido un problema en frameControl.init()\n");
		return false;
	}

	if(!soundEngine->init())
	{
		log("EngineManager.init()::Se ha producido un problema en soundEngine.init()\n");
		return false;
	}

	if(!input->init(window))
	{
		log("EngineManager.init()::Se ha producido un problema en input.init()\n");
		return false;
	}

	return true;
}

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/

/* EngineManager::EngineManager(int screenW, int screenH, int screenBPP, int gameW = -1, int gameH = -1, int gameScale = -1) */
/*
	Preparamos todos los motores y luego los iniciamos mediante init()
*/
EngineManager::EngineManager(int screenW, int screenH, int screenBPP, int gameW, int gameH, int gameScale)
{
	gfxEngine = new GfxEngine(screenW, screenH, screenBPP, gameW, gameH, gameScale);
	soundEngine = new SoundEngine();
	input = new Input();
	logger = new Logger();
	window = new sf::RenderWindow();
	
	// Inicialización de los elementos
	if(!init())
	{
		log("EngineManager()::Se ha producido un problema en EngineManager.init()\n");
	}
}

/* EngineManager::~EngineManager() */
/*
	Eliminamos los distintos atributos y dejamos los punteros apuntando a NULL
*/
EngineManager::~EngineManager()
{
	delete gfxEngine;
	gfxEngine = NULL;

	delete frameControl;
	frameControl = NULL;

	delete soundEngine;
	soundEngine = NULL;

	delete input;
	input = NULL;

	delete logger;
	logger = NULL;

	delete window;
	window = NULL;
}
		
GfxEngine* EngineManager::getGfxEngine()
{
	return gfxEngine;
}

FrameControl* EngineManager::getFrameControl()
{
	return frameControl;
}
		
SoundEngine* EngineManager::getSoundEngine()
{
	return soundEngine;
}
		
Input* EngineManager::getInput()
{
	return input;
}

/* EngineManager::log(char* message) */
/*
	Escribimos un mensaje en el log utilizando las funciones de la clase Logger
*/
void EngineManager::log(char* message)
{
	logger->log(message);
}
