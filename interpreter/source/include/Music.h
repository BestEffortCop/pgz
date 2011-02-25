#pragma once

#ifndef __MUSIC_H__
#define __MUSIC_H__

using namespace std;

//! Music es la clase que envuelve el elemento del motor que representa una pista de música.
/*!

*/
class Music {
	public:

		//! Constructora parametrizada.
		/*!
			\param path ruta de la musica que se desea cargar.
			\param soundEngine el motor de sonido.
		*/
		Music(string path,sfxEngine* soundEngine);

		//! Destructora.
		/*!
			Libera la pista de música de memoria.
		*/
		~Music();
};

#endif