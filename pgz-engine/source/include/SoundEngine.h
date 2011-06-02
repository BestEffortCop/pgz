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

#ifndef __SOUNDENGINE_H__
#define __SOUNDENGINE_H__


#include "SFML/Audio.hpp"
#include <iostream>
#include <conio.h>

#include "Music.h"
#include "Sound.h"

#include "SoundManager.h"
#include "MusicManager.h"

#include "Logger.h"

class Sound;
class Music;
class MusicManager;
class SoundManager;

using namespace std;


//! Subsistema de sonido que facilita el trabajo con elementos de audio al programador.
/*!
	Es la parte principal en la reproducción de sonido, encapsulando la
	librería de audio subyaciente.

	Se encarga de trabajar con archivos de música (representados en la clase Music) y
	archivos de sonido (clase Sound). Sólo se prodrá reproducir un archivo de música al
	tiempo, mientras que varios archivos de sonido pueden estar siendo reproducidos
	al mismo tiempo.

	SoundEngine proporciona pues métodos para manejar la reproducción y parámetros tanto
	elementos de sonido como de música.

	\sa Sound
	\sa Music
*/
class SoundEngine
{
	friend class Sound;
	friend class Music;

	private:
		float systemSoundVolume; //Volumen global de sonidos del sistema
		float systemMusicVolume; //Volumen global de música del sistema
		Logger* logger;
		Music* actPlayingMusic; //Almacena la música que se está reproduciendo en ese momento
		SoundManager* soundManager; //Puntero a SoundManager
		MusicManager* musicManager; //Puntero a MusicManager

		//! Carga el sonido de la ruta especificada.
		/*!
			Si el sonido ya ha sido cargado, SoundEngine se encargará de devolver el
			mismo puntero con el que se cargó.
			\param path ruta donde se encuentra el sonido a cargar.
			\return Objeto que representa el archivo de sonido especificado.
		*/
		sf::Sound* loadSound(string path);

		//! Carga el archivo de música de la ruta especificada.
		/*!
			Si la pista ya ha sido cargada, MusicEngine se encargará de devolver el
			mismo puntero con el que se cargó.
			\param path ruta donde se encuentra el archivo de música a cargar.
			\return Objeto que representa el archivo de múrica especificado.
		*/
		sf::Music* loadMusic(string path);

	public:
		//! Construye el SoundEngine
		/*!
			Preparara las estructuras necesarias para la reproducción de sonidos,
			dejando a SoundEngine::init() la inicialización
			de la clase y por tanto de la librería de sonido.
		*/
		SoundEngine();

		//! Destructora
		~SoundEngine();

		//! Inicializa los parametros de la clase y rellena las estructuras.
		/*!
			Inicializa el SoundEngine para que pueda realizar su función.
		*/
		bool init();

	/*********************************************************************\
	*	Métodos comunes a todos los tipos de archivos de audio			  *
	\*********************************************************************/

		//! Establece el volumen global de la reproducción de sonidos.
		/*!
			Este método modifica el valor del volumen global de sonidos, con el
			cuál se reproducirán todos los sonidos en los que no se especifique un
			volumen particular.
			\param soundVolume valor numérico del nuevo volumen del sistema.
		*/
		void setSoundVolume(float soundVolume);

		//! Obtiene el volumen de sonidos del sistema.
		/*!
			\return Volumen actual de la reproducción por defecto de sonidos.
		*/
		float getSoundVolume();

		//! Establece el volumen global de la reproducción de pistas de música.
		/*!
			Este método modifica el valor del volumen global de la música, con el
			cuál se reproducirán todos las pistas de música en las que no se
			especifique un volumen particular.
			\param musicVolume valor numérico del nuevo volumen del sistema.
		*/
		void setMusicVolume(float musicVolume);

		//! Obtiene el volumen de pistas de música del sistema.
		/*!
			\return Volumen actual de la reproducción por defecto de música.
		*/
		float getMusicVolume();

		//! Detiene todos los sonidos en reproducción actualmente.
		void stopAllSounds();

		//! Detiene la música actual en reproducción.
		void stopAllMusic();

	/*********************************************************************\
	*	Métodos relacionados con la reproducción de sonidos				  *
	\*********************************************************************/

		//! Reproduce un sonido especificado en la ruta al volumen dado y con o sin repeticiones.
		/*!
			\param sound sonido a reproducir.
			\param volume Volumen con el que se quiere reproducir. Si no se especifica,
			el sonido se reproducirá con el volumen global de sonidos del sistema.
			\param loop Flag que indica si el sonido se volverá a reproducir tras finalizar o no.
		*/
		void playSound(Sound* sound, float volume = -1.0, bool loop = false);

		//! Elimina un sonido.
		/*!
			Se eliminará el sonido ya sea solo el link o todo (incluido el buffer) porque 
			nadie más lo está usando.
			\param path ruta del sonido que se quiere eliminar
		*/
		bool deleteSound(string path);

		//! Cambia gradualmente el volumen de un sonido.
		/*!
			\param sound Sonido sobre el que se aplicará el cambio de volumen.
			\param volume Volumen al que se quiere llegar de manera gradual.
			\param time Tiempo que se tardará en llegar al volumen especificado.
		*/
		void fadeSound(Sound* sound, float volume, int time);

		//! Indica si se esta reproduciendo un sonido.
		/*!
			\param sound Sonido a comprobar.
			\return Valor booleano indicando si el sonido se está reproduciendo o no.
		*/
		bool isSoundPlaying(Sound* sound); // true si se está reproduciéndose ese sonido

		//! Detiene la reproducción de un sonido.
		/*!
			El sonido especificado será reproducido. Si se estaba reproduciendo varias
			veces al mismo tiempo, todas las instancias serán detenidas.
			\param sound Sonido que se va a detener.
		*/
		void stopSound(Sound* sound);

	/*********************************************************************\
	*	Métodos relacionados con la reproducción de pistas de música		  *
	\*********************************************************************/

		//! Reproduce una pista de música especificada en la ruta.
		/*!
			La pista especificada comenzará su repreoducción. Si ya se estaba reproduciendo,
			comenzará de nuevo desde el principio. Si se encontraba pausada, se reanudará su reproducción.
			Podrá reproducirse con o sin repeticiones.
			\param music Pista de música a reproducir.
			\param volume Volumen con el que se quiere reproducir. Si no se especifica,
			la pista se reproducirá con el volumen global de música del sistema.
			\param loop Flag que indica si la pista de múics se volverá a reproducir tras finalizar o no.
		*/
		void playMusic(Music* music, float volume = -1.0, bool loop = true, bool withStop = false);

		//! Elimina una musica.
		/*!
			Se eliminará la musica ya sea solo el link (virtual) o toda la instancia porque 
			nadie más lo está usando.
			\param path ruta del sonido que se quiere eliminar
		*/
		bool deleteMusic(string path);

		//! Cambia gradualmente el volumen de la pista de música sonando actualmente.
		/*!
			\param volume Volumen al que se quiere llegar de manera gradual.
			\param time Tiempo que se tardará en llegar al volumen especificado.
		*/
		void fadeMusic(float volume, int time);

		//! Indica si se esta reproduciendo una pista de música.
		/*!
			\param music Música a comprobar.
			\return Valor booleano indicando si la pista de música se está reproduciendo o no.
		*/
		bool isMusicPlaying(Music* music);

		//! Informa si la pista de música actual está pausada.
		/*!
			\param music Música a comprobar.
			\return Valor booleano indicando si la pista de música está pausada o no.
		*/
		bool isMusicPaused(Music* music);

		//! Pausa la reproducción de la pista de música actual.
		void pauseMusic();

		//! Continúa la reproducción de la pista de música actual, si ésta ha sido previamente pausada.
		void resumeMusic();

		//! Detiene la reproducción de la pista de música actual.
		void stopMusic();

		//! Cambia el modo de repetición de la pista de música actual.
		/*!
			\param loop Valor booleano cuya valor indica si la pista de música actual debe ser reproducida
			tras finalizar (true) o no (false).
		*/
		void setLoop(bool loop);
};

#endif
