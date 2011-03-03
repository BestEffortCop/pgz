#include "Sound.h"

//Constructora de Sound - Construye un sonido con la ayuda de SoundEngine
Sound::Sound(string path, SoundEngine* soundEngine){
	this->sound = soundEngine->loadSound(path);
	this->soundEngine = soundEngine;
}

//Libera la memoria ocupada por un sonido
Sound::~Sound(){
	delete this->sound;
	this->sound = NULL;
	this->soundEngine = NULL;
}
