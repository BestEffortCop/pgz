#include "BGM.h"

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/

Bgm::Bgm(string fname, SoundEngine* sndEngine)
{
	music = new Music(fname,sndEngine);
}
		
Bgm::~Bgm();

//! Reproduce la Bgm con el volumen indicado
/*!
	\param volume Volumen de reproducción (-1 para volumen por defecto)
*/
void Bgm::play(int volume = -1);

//! Finaliza la reproducción
void Bgm::stop();

//! Pausa la reproducción en curso
void Bgm::pause();

//! Reanuda la reproducción pausada
void Bgm::resume();

//! Informa si la Bgm está reproduciéndose actualmente
bool Bgm::isPlaying();

//! Indica si la reproducción se repite
/*!
	\param loop Activa o desactiva la reproducción repetida
*/
void Bgm::setLoop(bool loop);

//! Establece el volumen de reproducción
/*!
	\param volume Volumen de reproducción
*/
void Bgm::setVolume (int volume);

//! Cambia el volumen de reproducción variándolo lentamente
/*!
	\param volume Volumen de reproducción
	\param time Tiempo de transición
*/
void Bgm::fade (int volume, int time);