#pragma once
#ifndef __SFX_H__
#define __SFX_H__

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
		void play(int volume = -1);

		//! Finaliza la reproducción del efecto de sonido
		void stop();
		
		//! Cambia el volumen de reproducción variándolo lentamente
		/*!
			\param volume Volumen de reproducción
			\param time Tiempo de transición
		*/
		void fade (int volume, int time);
		
		//! Informa si el sonido se esta reproduciendo.
		bool isPlaying();

		//! Establece el volumen de reproducción
		/*!
			\param volume Volumen de reproducción
		*/
		void setVolume (int volume);
};