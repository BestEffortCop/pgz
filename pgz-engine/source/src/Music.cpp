#include "Music.h"

//Construye una música con la ayuda de SoundEngine
Music::Music(string path, SoundEngine* soundEngine)
{
	// Se carga la música
	this->music = soundEngine->loadMusic(path);
	// Se podría avisar si falla la carga pero ya lo hace SoundEngine

	// Se actualizan punteros
	this->soundEngine = soundEngine;
	this->path = path;
}

//Libera la memoria de una música
Music::~Music()
{
	// Se pide al SoundEngine que borre la música
	soundEngine->deleteMusic(path);

	// Se limpian los punteros
	this->music = NULL;
	this->soundEngine = NULL;
}
