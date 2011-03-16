#include "Sound.h"

//Constructora de Sound - Construye un sonido con la ayuda de SoundEngine
Sound::Sound(string path, SoundEngine* soundEngine){
	//Pasamos el sound que queremos cargar y soundEngine se encarga
	this->sound = soundEngine->loadSound(path);
	this->soundEngine = soundEngine;
	this->path = path;
}

//Libera la memoria ocupada por un sonido
Sound::~Sound(){
	soundEngine->deleteSound(this->path);
	delete this->sound;
	this->sound = NULL;
	this->soundEngine = NULL;
}
