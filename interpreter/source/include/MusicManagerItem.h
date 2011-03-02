#pragma once
#ifndef __MUSICMANAGERITEM_H__
#define __MUSICMANAGERITEM_H__

//#include "SFML/Audio.hpp"
#include "Music.h"

//! Elemento básico del MusicManager
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo de audio musical. Este elemento
	no debería cargarse varias veces en memoria,
	sino compartirse entre todos con el consecuente ahorro.
	
	De esta tarea se encarga MusicManager, que mantiene la lista
	de sonidos cargados en memoria de forma transparente al programador.

	MusicManagerItem es el elemento básico de esta lista.
	Relaciona un elemento de la clase Music (música) con el número de elementos que la utilizan
	para poder liberarla cuando no sea necesaria, asegurando que no
	se elimina mientras alguien la está utilizando.

	\sa MusicManager
	\sa Music
*/
class MusicManagerItem
{

private:
	//! Número de enlaces actuales a la música encapsulada
	unsigned int links;
	//! Música (Music encapsulada)
	Music* music;

public:
	//! Construye el MusicManagerItem para la músic music
	/*!
		Inicializa el contador de enlaces a 0.
		\param music Música encapsulada
	*/
	MusicManagerItem(Music* music);

	//! Añade un nuevo enlace a la música
	void link();
	
	//! Elimina un enlace a la música
	/*!
		\return true si la música puede borrarse porque el número de enlaces es 0.
	*/
	bool unlink(); // true si debe borrarse
	
	//! Obtiene la música encapsulada
	/*!
		\return Puntero a la música encapsulada
	*/
	Music* getMusic();
	
	//! Devuelve el número de enlaces actual a la música
	/*!
		\return Número de enlaces actuales
	*/
	int getLinks();
};

#endif