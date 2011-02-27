#include "Sfx.h"

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/

/* Sfx::Sfx(string fname, SoundEngine* soundEngine) */
/*
Creamos un elemento de tipo Sound (que estamos encapsulando), y apuntamos al
SoundEngine que nos va a gestionar para pasarle las órdenes
*/
Sfx::Sfx(string fname, SoundEngine* soundEngine)
{
	soundEngine = soundEngine;
	sound = new Sound(fname,soundEngine);

	volume= -1;
	loop = true;
	playing  = false;
}
		
/* Sfx::~Sfx() */
/*
Eliminamos el elemento Sound que creamos, al soundEngine le ponemos el puntero
a NULL pero no le hacemos el delete pues otras clases podrían estar utilizándolo
*/
Sfx::~Sfx()
{
	delete sound;
	sound = NULL;

	soundEngine = NULL;
}

/* Sfx::play(int volume = -1) */
/*
Establecemos el valor de playing para indicar el estado de la música
y reproducimos la música usando SoundEngine.
*/
void Sfx::play(int volume = -1)
{
	playing = true;
	soundEngine->playSound(sound,volume,loop);
}

/* void Sfx::stop() */
/*
Paramos la reproducción de este sonido utilizando la funcionalidad
de SoundEngine
*/
void Sfx::stop()
{
	playing = false;
	soundEngine->stopSound(this);
}
		
void Sfx::fade (int volume, int time)
{
	soundEngine->fadeSound(this,volume,time);
}

/* Sfx::isPlaying() */
/*
Comprobamos si no esta parado y si es el que se esta reproduciendo en este 
momento (preguntandoselo al SoundEngine) y si se cumplen todas esas condiciones devolvemos True.
*/
bool Sfx::isPlaying()
{
	return playing && soundEngine->isSoundPlaying(this);
}

/* Sfx::setVolume(bool loop) */
/*
Establecemos el valor del volumen y luego si nuestro sonido se
esta reproduciendo cambiamos también dicho valor en el SoundEngine.
*/
void Sfx::setVolume (int volume)
{
	this->volume = volume;

	if (soundEngine->isSoundPlaying(this))
		soundEngine->setSoundVolume(volume);
}