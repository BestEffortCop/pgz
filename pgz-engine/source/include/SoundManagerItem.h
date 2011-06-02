/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

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