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

#include "Bgm.h"

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/

/* Bgm::Bgm(string fname, SoundEngine* sndEngine) */
/*
Creamos un elemento de tipo Music (que estamos encapsulando), y apuntamos al
SoundEngine que nos va a gestionar para pasarle las órdenes
*/
Bgm::Bgm(string fname, SoundEngine* sndEngine)
{
	this->soundEngine = sndEngine;
	music = new Music(fname,sndEngine);

	volume= -1;
	loop = true;
	playing  = false;
	paused = false;
}

/* Bgm::~Bgm() */
/*
Eliminamos el elemento Music que creamos, al sndEngine le ponemos el puntero
a NULL pero no le hacemos el delete pues otras clases podrían estar utilizándolo
*/
Bgm::~Bgm()
{
	if (music)
		delete music;
	music = NULL;

	soundEngine = NULL;
}

/* Bgm::play(int volume = -1) */
/*
Establecemos los valores de playing y paused para indicar el estado de la música
y reproducimos la música usando SoundEngine.
*/
void Bgm::play(float volume)
{
	playing = true;
	paused = false;
	soundEngine->playMusic(music, volume, loop);
}

/* void Bgm::stop() */
/*
Paramos la reproducción de este sonido utilizando la funcionalidad
de SoundEngine
*/
void Bgm::stop()
{
	paused = false;
	playing = false;
	soundEngine->stopMusic();
}

/* Bgm::pause() */
/*
Pausamos la reproducción de este sonido utilizando la funcionalidad
de SoundEngine
*/
void Bgm::pause()
{
	paused = true;
	soundEngine->pauseMusic();
}

/* Bgm::resume() */
/*
Reanudamos la reproducción de este sonido, si estaba previamente
pausado utilizando la funcionalidad de SoundEngine
*/
void Bgm::resume()
{
	if (paused)
	{
		soundEngine->resumeMusic();
		paused = false;
		playing = true;
	}
}

/* Bgm::isPlaying() */
/*
Comprobamos si esta esta música pausada, si no esta parada y por
último si es la que se esta reproduciendo en este momento (preguntandoselo
al SoundEngine) y si se cumplen todas esas condiciones devolvemos True.
*/
bool Bgm::isPlaying()
{
	return !paused && playing && soundEngine->isMusicPlaying(music);
}

/* Bgm::setLoop(bool loop) */
/*
Establecemos el valor del loop y luego si nuestra música es la que se 
esta reproduciendo cambiamos también dicho valor en el SoundEngine.
*/
void Bgm::setLoop(bool loop)
{
	this->loop = loop;
	
	if (soundEngine->isMusicPlaying(music))
		soundEngine->setLoop(loop);
}

/* Bgm::setVolume(bool loop) */
/*
Establecemos el valor del volumen y luego si nuestra música es la que se 
esta reproduciendo cambiamos también dicho valor en el SoundEngine.
*/
void Bgm::setVolume (float volume)
{
	this->volume = volume;

	if (soundEngine->isMusicPlaying(music))
		soundEngine->setMusicVolume(volume);
}

void Bgm::fade (float volume, int time)
{
	soundEngine->fadeMusic(volume, time);
}