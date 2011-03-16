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