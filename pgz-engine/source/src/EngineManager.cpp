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
	// Se inicializan los subsistemas a partir de la ventana ya creada
	
	// Gráficos
	if(!gfxEngine->init((sf::RenderWindow *)window))
	{
		log("EngineManager.init - Se ha producido un problema iniciando el Subsistema Gráfico");
		return false;
	}

	// Timing
	if(!frameControl->init(window))
	{
		log("EngineManager.init - Se ha producido un problema iniciando el Subsistema de Temporización");
		return false;
	}

	// Audio
	if(!soundEngine->init())
	{
		log("EngineManager.init - Se ha producido un problema iniciando el Subsistema de Audio");
		return false;
	}

	// Entrada
	if(!input->init(window))
	{
		log("EngineManager.init - Se ha producido un problema iniciando el Subsistema de Entrada");
		return false;
	}

	// Todo ha ido bien
	return true;
}

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/

/* EngineManager::EngineManager(int screenW, int screenH, int screenBPP, int gameW = -1, int gameH = -1, int gameScale = -1) */
/*
	Preparamos todos los motores y luego los iniciamos mediante init()
*/
EngineManager::EngineManager(int screenW, int screenH, int screenBPP, int fps, int gameW, int gameH, int gameScale)
{
	// Se construyen los subsistemas para su posterior inicialización
	
	// Sistema de log
	logger = Logger::Instance();

	// Gráfico
	gfxEngine = new GfxEngine(screenW, screenH, screenBPP, gameW, gameH, gameScale);

	// Timing
	frameControl = new FrameControl(fps);

	// Audio
	soundEngine = new SoundEngine();

	// Entrada
	input = new Input();

	// Se instancia la ventana de la aplicación
	window = new sf::RenderWindow();

	// Se procede a inicializar los subsistemas
	logger->log("Iniciando Subsistemas...");
	
	// Inicialización
	if(!init())
	{
		// Si algo falla se avisa de ello
		log("Se produjeron errores al iniciar los Subsistemas.");
	}
}

/* EngineManager::~EngineManager() */
/*
	Eliminamos los distintos atributos y dejamos los punteros apuntando a NULL
*/
EngineManager::~EngineManager()
{
	// Notify
	logger->log("Finalizando Subsistemas...");

	delete gfxEngine;
	gfxEngine = NULL;

	delete frameControl;
	frameControl = NULL;

	delete soundEngine;
	soundEngine = NULL;

	delete input;
	input = NULL;

	logger->log("Subsistemas finalizados correctamente");

	logger->log(randomEndMessage());

	Logger::DestroyInstance();
	logger = NULL;
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

const char* EngineManager::randomEndMessage()
{
	// Se devuelve un divertido a la par que informativo mensaje de hasta la vista para el log
	int numMsg = 10;

	switch (rand()%numMsg)
	{
		case 0: return "¡Gracias por su visita!"; break;
		case 1: return "Por favor, vuelva otro día"; break;
		case 2: return "Hasta la vista, baby"; break;
		case 3: return "I'll be back"; break;
		case 4: return "THE END"; break;
		case 5: return "Que tenga un buen día"; break;
		case 6: return "Hasta que nos olamos"; break;
		case 7: return "Thanks for your patronage"; break;
		case 8: return "Fare thee well"; break;
		case 9: return "Godspeed, traveller"; break;
		default: return "ERROR404: MESSAGE_DEFAULT_NOT_FOUND"; break;
	};
};