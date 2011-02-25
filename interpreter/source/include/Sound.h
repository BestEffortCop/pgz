#pragma once

#ifndef __SOUND_H__
#define __SOUND_H__

using namespace std;

//! Sound es la clase que envuelve el elemento del motor que representa un sonido real.
/*!

*/
class Sound {
	public:

		//! Constructora parametrizada.
		/*!
			\param path Ruta del sonido que se desea cargar.
			\param soundEngine El motor de sonido.
		*/
		Sound(string path, sfxEngine* soundEngine); 
		
		//! Destructora
		/*!
			Libera el sonido de memoria.
		*/
		~Sound();
};

#endif