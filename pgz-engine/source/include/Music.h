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