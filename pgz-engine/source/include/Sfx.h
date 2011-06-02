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
#ifndef __SFX_H__
#define __SFX_H__

#include <string>
#include "SoundEngine.h"
#include "Sound.h"

using namespace std;


//! Efecto de sonido de la capa superior del subsistema de audio
/*!
	Envuelve un Sound, facilitando su manejo y reproducción
	
	Proporciona métodos para reproducir y controlar sonidos
	de forma sencilla y eficaz.
	
	\sa Sound
*/
class Sfx
{
	private:
		//! Atributo que encapsula a Sound
		Sound* sound;
		SoundEngine* soundEngine;
		float volume;
		bool playing;
		bool paused;
		bool loop;

	public:
		
		//! Construye el sonido, cargándolo de un archivo
		/*!
			\param fname Archivo de audio a cargar
			\param soundEngine Puntero al SoundEngine del sistema
	    */
		Sfx(string fname, SoundEngine* soundEngine);
		
		//! Destruye el sonido, liberando el archivo cargado
		~Sfx();

		//! Reproduce un efecto de sonido con el volumen indicado
		/*!
			\param volume Volumen de la reproducción
		*/
		void play(float volume = -1);

		//! Finaliza la reproducción del efecto de sonido
		void stop();
		
		//! Cambia el volumen de reproducción variándolo lentamente
		/*!
			\param volume Volumen de reproducción
			\param time Tiempo de transición
		*/
		void fade (float volume, int time);
		
		//! Informa si el sonido se esta reproduciendo.
		bool isPlaying();

		//! Establece el volumen de reproducción
		/*!
			\param volume Volumen de reproducción
		*/
		void setVolume (float volume);
};

#endif