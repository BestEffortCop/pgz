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

#include "Sound.h"

//Constructora de Sound - Construye un sonido con la ayuda de SoundEngine
Sound::Sound(string path, SoundEngine* soundEngine)
{
	//Pasamos el sound que queremos cargar y soundEngine se encarga
	this->sound = soundEngine->loadSound(path);
	// Podríamos avisar si falla la carga, pero ya lo hace el SoundEngine.
	// Actualizamos nuestros punteros
	this->soundEngine = soundEngine;
	this->path = path;
}

//Libera la memoria ocupada por un sonido
Sound::~Sound()
{
	// Se pide a SoundEngine que elimine el sf::SoundBuffer
	soundEngine->deleteSound(this->path);

	// Se borra el sf::Sound que encapsulamos
	delete this->sound;

	// Se limpian punteros 
	this->sound = NULL;
	this->soundEngine = NULL;
}
