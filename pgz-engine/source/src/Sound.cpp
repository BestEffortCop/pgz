#include "Sound.h"

//Constructora de Sound - Construye un sonido con la ayuda de SoundEngine
Sound::Sound(string path, SoundEngine* soundEngine)
{
	//Pasamos el sound que queremos cargar y soundEngine se encarga
	this->sound = soundEngine->loadSound(path);
	// Podríamos avisar si falla la carga, pero ya lo hace el SoundEngine.
	// Actualizamos nuestros punteros
	this->soundEngine = soundEngine;
	this->path = path;
}

//Libera la memoria ocupada por un sonido
Sound::~Sound()
{
	// Se pide a SoundEngine que elimine el sf::SoundBuffer
	soundEngine->deleteSound(this->path);

	// Se borra el sf::Sound que encapsulamos
	delete this->sound;

	// Se limpian punteros 
	this->sound = NULL;
	this->soundEngine = NULL;
}
