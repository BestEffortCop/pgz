#include "BGM.h"

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
	soundEngine = sndEngine;
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
	delete music;
	music = NULL;

	soundEngine = NULL;
}

/* Bgm::play(int volume = -1) */
/*
Establecemos los valores de playing y paused para indicar el estado de la música
y reproducimos la música usando SoundEngine.
*/
void Bgm::play(int volume)
{
	playing = true;
	paused = false;
	soundEngine->playMusic(music, loop, volume);
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
void Bgm::setVolume (int volume)
{
	this->volume = volume;

	if (soundEngine->isMusicPlaying(music))
		soundEngine->setMusicVolume(volume);
}

void Bgm::fade (int volume, int time)
{
	soundEngine->fadeMusic(volume, time);
}