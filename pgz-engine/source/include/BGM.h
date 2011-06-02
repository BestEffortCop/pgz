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
#ifndef __BGM_H__
#define __BGM_H__

#include <string>
#include "SoundEngine.h"
#include "Music.h"

using namespace std;


//! Música de fondo de la capa superior del subsistema de audio
/*!
	Envuelve una Music, facilitando su manejo y reproducción
	
	Proporciona métodos para reproducir y controlar bgms
	de forma sencilla y eficaz.
	
	\sa Music
*/
class Bgm
{
	private:
		//! Atributo que encapsula a Music
		Music* music;
		SoundEngine* soundEngine;
		float volume;
		bool playing;
		bool paused;
		bool loop;

	public:
		
		//! Construye la Bgm cargándola de un archivo
		/*!
			\param fname Nombre de archivo a cargar
			\param sndEngine Puntero al SoundEngine del sistema
		*/
		Bgm(string fname, SoundEngine *sndEngine);
		
		//! Destruye la Bgm, liberando el archivo cargado
		~Bgm();

		//! Reproduce la Bgm con el volumen indicado
		/*!
			\param volume Volumen de reproducción (-1 para volumen por defecto)
		*/
		void play(float volume = -1.f);

		//! Finaliza la reproducción
		void stop();

		//! Pausa la reproducción en curso
		void pause();

		//! Reanuda la reproducción pausada
		void resume();

		//! Informa si la Bgm está reproduciéndose actualmente
		bool isPlaying();

		//! Indica si la reproducción se repite
		/*!
			\param loop Activa o desactiva la reproducción repetida
		*/
		void setLoop(bool loop);

		//! Establece el volumen de reproducción
		/*!
			\param volume Volumen de reproducción
		*/
		void setVolume (float volume);

		//! Cambia el volumen de reproducción variándolo lentamente
		/*!
			\param volume Volumen de reproducción
			\param time Tiempo de transición
		*/
		void fade (float volume, int time);
};

#endif