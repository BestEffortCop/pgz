#pragma once

#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "SFML/Audio.hpp"
#include "SoundEngine.h"

using namespace std;

class SoundEngine;

//! Music es la clase que envuelve el elemento del motor que representa una pista de música.
/*!

*/
class Music 
{
	friend class SoundEngine;
	
	private:
		SoundEngine* soundEngine;
		sf::Music* music;
		string path;

	public:
		
		//! Constructora parametrizada.
		/*!
			\param path ruta de la musica que se desea cargar.
			\param soundEngine el motor de sonido.
		*/
		Music(string path, SoundEngine* soundEngine);

		//! Destructora.
		/*!
			Libera la pista de música de memoria.
		*/
		~Music();
};

#endif