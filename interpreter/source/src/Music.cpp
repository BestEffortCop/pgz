#include "Music.h"

//Construye una música con la ayuda de SoundEngine
Music::Music(string path, SoundEngine* soundEngine){
	this->music = soundEngine->loadMusic(path);
	this->soundEngine = soundEngine;
}

//Libera la memoria de una música
Music::~Music(){
	delete this->music;
	this->music = NULL;
	this->soundEngine = NULL;
}
