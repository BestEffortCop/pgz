#pragma once
#ifndef __SOUNDMANAGERITEM_H__
#define __SOUNDMANAGERITEM_H__

#include "SFML/Audio.hpp"

//! Elemento básico del SoundManager
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo de efecto sonoro. Este elemento no debería cargarse 
	varias veces en memoria, sino compartirse entre todos 
	con el consecuente ahorro.
	
	De esta tarea se encarga SoundManager, que mantiene la lista
	de sonidos cargados en memoria de forma transparente al programador.

	SoundManagerItem es el elemento básico de esta lista.
	Relaciona un SoundBuffer (sonido) con el número de elementos que lo utilizan
	para poder liberarlo cuando no sea necesario, asegurando que no
	se elimina mientras alguien lo esté utilizando.

	\sa SoundManager
	\sa Sound
*/
class SoundManagerItem
{

private:
	//! Número de enlaces actuales al sonido encapsulado
	unsigned int links;
	//! Sound (Sound encapsulado)
	sf::SoundBuffer* soundBuffer;

public:
	//! Construye el SoundManagerItem para el músic sound
	/*!
		Inicializa el contador de enlaces a 0.
		\param sound Sonido encapsulado
	*/
	SoundManagerItem(sf::SoundBuffer* soundBuf);

	//! Añade un nuevo enlace a el sonido
	void link();
	
	//! Elimina un enlace a el sonido
	/*!
		\return true si el sonido puede borrarse porque el número de enlaces es 0.
	*/
	bool unlink(); // true si debe borrarse
	
	//! Obtiene el sonido encapsulado
	/*!
		\return Puntero a el sonido encapsulado
	*/
	sf::SoundBuffer* getSoundBuffer();
	
	//! Devuelve el número de enlaces actual al sonido
	/*!
		\return Número de enlaces actuales
	*/
	int getLinks();
};

#endif