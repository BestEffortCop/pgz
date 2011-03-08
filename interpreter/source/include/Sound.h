#pragma once

#ifndef __SOUND_H__
#define __SOUND_H__


#include <SFML/Audio.hpp>
#include "SoundEngine.h"

using namespace std;

class SoundEngine;

//! Sound es la clase que envuelve el elemento del motor que representa un sonido real.
/*!

*/
class Sound {
	friend class SoundEngine;
	private:
		SoundEngine* soundEngine;
		sf::Sound* sound;
		string path;
	
	public:
		

		//! Constructora parametrizada.
		/*!
			\param path Ruta del sonido que se desea cargar.
			\param soundEngine El motor de sonido.
		*/
		Sound(string path, SoundEngine* soundEngine);

		//! Destructora
		/*!
			Libera el sonido de memoria.
		*/
		~Sound();

		bool getLoop(){return sound->GetLoop();}
		float getVolume(){return sound->GetVolume();}

};

#endif
