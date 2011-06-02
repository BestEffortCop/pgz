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

#include "Music.h"

//Construye una música con la ayuda de SoundEngine
Music::Music(string path, SoundEngine* soundEngine)
{
	// Se carga la música
	this->music = soundEngine->loadMusic(path);
	// Se podría avisar si falla la carga pero ya lo hace SoundEngine

	// Se actualizan punteros
	this->soundEngine = soundEngine;
	this->path = path;
}

//Libera la memoria de una música
Music::~Music()
{
	// Se pide al SoundEngine que borre la música
	soundEngine->deleteMusic(path);

	// Se limpian los punteros
	this->music = NULL;
	this->soundEngine = NULL;
}
