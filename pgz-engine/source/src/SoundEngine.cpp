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

#include "SoundEngine.h"

//Constructora por defecto de SoundEngine
SoundEngine::SoundEngine()
{
	systemSoundVolume = 50.0; //Setea el volumen global de sonidos
	systemMusicVolume = 50.0; //Setea el volumen global de músicas
}

//Destructora
SoundEngine::~SoundEngine()
{
	// Se avisa
	logger->log("Se finaliza el Subsistema de Audio.");

	stopAllMusic();
	stopAllSounds();

	//Libera la memoria de soundManager
	logger->dlog("\tSe elimina el Sound Manager.");
	if (soundManager != NULL) 
		delete soundManager, soundManager = NULL;

	//Libera la memoria de musicManager
	logger->dlog("\tSe elimina el Music Manager.");
	if (musicManager != NULL)
		delete musicManager, musicManager = NULL;

	logger->dlog("\tFinalización efectuada correctamente.");

	//Logger::DestroyInstance();
}

//Inicializa las estructuras necesarias
bool SoundEngine::init()
{
	soundManager = new SoundManager(); //Crea un SoundManager para su posterior utilización
	musicManager = new MusicManager(); //Crea un MusicManager para su posterior utilización
	actPlayingMusic = NULL;
	logger = Logger::Instance();
	if (soundManager == NULL || musicManager == NULL ) //Comprueba si se han creado las estructuras correctamente
		return false;
	else return true;
} 

//-------------------------------------
//Métodos comunes a sonidos y músicas -
//-------------------------------------
void SoundEngine::setSoundVolume(float soundVolume) { systemSoundVolume = soundVolume;} //Cambia el volumen global de sonidos
float SoundEngine::getSoundVolume() { return systemSoundVolume;}

void SoundEngine::setMusicVolume(float musicVolume) { systemMusicVolume = musicVolume;} //Cambia el volumen global de música
float SoundEngine::getMusicVolume() { return systemMusicVolume;}

void SoundEngine::stopAllSounds(){;} //Por implementar
void SoundEngine::stopAllMusic(){ stopMusic();} //Detiene la música de fondo que se está reproduciendo actualmente


//-----------------------------------------------------
//Métodos relacionados con la reproducción de Sonidos -
//-----------------------------------------------------

/*
Carga un sonido en memoria para su posterior reproducción, dejando constancia en soundManager.
Si ya se encuentra en soundManager, entonces reutiliza el ya cargado ahorrando memoria.
*/
sf::Sound* SoundEngine::loadSound(string path)
{
	sf::Sound* sound;
	if(soundManager->isLoaded(path)) //Comprueba si ya está cargada en memoria
		// Si ya está en memoria, le pasamos el buffer de antes.
		return sound = new sf::Sound(*(soundManager->getSoundBuffer(path))); 
	else 
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		if (!soundBuffer->LoadFromFile(path))
		{
			//Error no se ha podido cargar el archivo de audio.
			logger->log(std::string("SoundEngine::loadSound - No se ha podido cargar el archivo: \"" + path + "\"").c_str());
			return NULL;
		}			
		//añadimos el nuevo buffer que acabamos de cargar.
		soundManager->setSoundBuffer(path, soundBuffer);

		//SetBuffer(soundBuffer); SetLoop(false); SetPitch(0); SetVolumen(100); SetPosition(0,0,0);
		sound = new sf::Sound(*soundBuffer);

		return sound;
	}	
}

/*
Reproduce un sonido y actualiza características del sonido
*/
void SoundEngine::playSound(Sound* sound, float volume, bool loop)
{
	if (sound == NULL)
	{
		logger->log("SoundEngine::playSound - No se puede reproducir un sonido inexistente.");
		return;
	};

	if (volume == -1) 
		sound->sound->SetVolume(systemSoundVolume);//Si no se ha solicitado un volumen concreto se pone el del sistema
	else
		sound->sound->SetVolume(volume); //Si se ha solicitado, se cambia al solicitado

	if (sound->sound->GetLoop() != loop) //Si el loop solicitado es distinto al que teníamos
		sound->sound->SetLoop(loop);     //Lo cambiamos
	
	sound->sound->Play();
}

/*
Eliminamos un link del sonido con nombre path y si llegan a cero links, la eliminamos de la memoria
*/
bool SoundEngine::deleteSound(string path)
{
	if (!soundManager->isLoaded(path))
		// Si no lo está, no puede borrarse
		return false;
	else
	{
		// Si lo está, indicamos que un elemento ha dejado de necesitarlo
		// Se coge el puntero para borrarla si fuera necesaria
		sf::SoundBuffer* buf = soundManager->getSoundBuffer(path);

		// Como esto añade un enlace al buffer, se elimina
		// este enlace antes de comprobar si se debe borrar
		soundManager->remove(path);

		// Y ahora se comprueba si se debe borrar
		if (soundManager->remove(path))
		{
			// Si nadie la necesita, se borra
			delete buf; 
			buf = NULL;
			// Y se avisa de ello
			return true;
		}
		// Si aún se necesita, no se borra. Quedan enlaces virtuales.
		return false;
	}
}

void SoundEngine::fadeSound(Sound* sound, float volume, int time){;}//Mirar

/*
Devuelve si sound se está reproduciendo actualmente
*/
bool SoundEngine::isSoundPlaying(Sound* sound)
{
	// El sonido ha de exisitir para poder comprobar si se reproduce
	if (sound!=NULL)
		return (sound->sound->GetStatus() == sf::Sound::Playing);
	else return false;
}

/*
Detiene la reproducción de sound
*/
void SoundEngine::stopSound(Sound* sound)
{
	if (isSoundPlaying(sound)) //Si el sonido está reproduciéndose, se detiene.
	{
			sound->sound->Stop();
	}
}


//----------------------------------------------------
//Métodos relacionados con la reproducción de Música -
//----------------------------------------------------

/*
Carga en memoria la música correspondiente a la path
*/
sf::Music* SoundEngine::loadMusic(string path)
{
	if(musicManager->isLoaded(path)) //Comprueba si el sonido está cargado actualmente en memoria
		return musicManager->getMusic(path); //Ya se encuentra en el manager cargado.
	else
	{
		sf::Music* music = new sf::Music();
		if(!music->OpenFromFile(path))//Si no está cargado, se carga
		{ 
			//Error, no se ha podido cargar el archivo
			logger->log(std::string("SoundEngine::loadMusic - No se ha podido cargar el archivo: \"" + path + "\"").c_str());
			return NULL;
		}
		//guardamos el archivo cargado en el manager para futuros usos
		musicManager->setMusic(path, music);

		return music;
	}
}

/*
Reproduce una música de fondo, controlando que solo haya una reproduciéndose al mismo tiempo
*/
void SoundEngine::playMusic(Music* music, float volume, bool loop, bool withStop)
{
	if (music == NULL)
	{
		logger->log("SoundEngine::playMusic - Error al tratar de reproducir una música inexistente.");
		return;
	};

	if (music->music == NULL)
	{
		logger->log(string("SoundEngine::playMusic - Error al tratar de reproducir el archivo no cargado: \"" + music->path + "\".").c_str());
		return;
	};

	if (volume == -1)
		music->music->SetVolume(systemMusicVolume); //Si no se solicita un volumen específico, se reproduce con el volumen del sistema
	else
		music->music->SetVolume(volume); // Si se solicita un volumen específico, se cambia


	if (music->music->GetLoop() != loop) //Si el loop solicitado es distinto
		music->music->SetLoop(loop);     //Se cambia

	//tras modificar la musica que queremos reproducir, ahora vemos como reproducirla
	if (actPlayingMusic == music) //es la música actual?
	{
		if (isMusicPlaying(actPlayingMusic)) //Se está reproduciendo ahora?
		{
			if (withStop)
			{
				//resetea la musica
				stopMusic();
				music->music->Play();
			}
		}
		else
			music->music->Play();
	}
	else
	{
		//paramos la musica actual ya se esté reproduciendo o esté pausada
		stopMusic();
		//cogemos como música actual la nueva
		actPlayingMusic = music;
		//la reproducimos
		music->music->Play();
	}
}

/*
Eliminamos un link de la música con nombre path y si llegan a cero links, la eliminamos de la memoria
*/
bool SoundEngine::deleteMusic(string path)
{
	if (!musicManager->isLoaded(path))
		// Si no lo está, no puede borrarse
		return false;
	else
	{
		// Si lo está, indicamos que un elemento ha dejado de necesitarlo
		// Se coge el puntero para borrarla si fuera necesaria
		sf::Music* m = musicManager->getMusic(path);

		// Como esto añade un enlace al buffer, se elimina
		// este enlace antes de comprobar si se debe borrar
		musicManager->remove(path);

		// Y ahora se comprueba si se debe borrar
		if (musicManager->remove(path))
		{
			// Si nadie la necesita, se borra
			//se agotaron sus links
			delete m; 
			m = NULL;
			// Y se avisa de ello
			return true;
		}
		// Si aún se necesita, no se borra. Quedan enlaces virtuales.
		return false;
	}
}

/*
Finaliza la reproducción de una música de fondo con atenuación
*/
void SoundEngine::fadeMusic(float volume, int time)
{
	/*if (actPlayingMusic != NULL && isMusicPlaying(actPlayingMusic))
	{
		int actVolume = (int)  actPlayingMusic->music->GetVolume();

		int diferencia = actVolume - (int)volume;
		if ( diferencia > 0){
			int delay = (time*1000/45);

			for (int i = (int)volume; i<actVolume; i++){
				actPlayingMusic->music->SetVolume(actVolume - i);
				Sleep(delay);
			}
		}
		stopMusic();
	}*/;
} 

/*
Nos dice si music está reproduciéndose actualmente
*/
bool SoundEngine::isMusicPlaying(Music* music)
{
	if (music != NULL)
		return ( music->music->GetStatus() == sf::Music::Playing ); //Si la música existe y está reproduciendose, se devuelve true
	else 
		return false;
}

/*
Devuelve si la música de fondo está pausada
*/
bool SoundEngine::isMusicPaused(Music* music)
{
	if (music != NULL) //music == actPlayingMusic && ?
		return (music->music->GetStatus() == sf::Music::Paused); //Si la música está pausada, se devuelve true
	else 
		return false;
}

/*
Pausa la música de fondo
*/
void SoundEngine::pauseMusic()
{
	//ya se comprueba que no sea null musica actual
	if (isMusicPlaying(actPlayingMusic)) //Si la música está reproduciéndose, se pausa
		actPlayingMusic->music->Pause();
}

/*
Se reanuda la reproducción de la música de fondo pausada
*/
void SoundEngine::resumeMusic()
{
	//ya se comprueba que no sea null musica actual
	if (isMusicPaused(actPlayingMusic)) //Si la música está pausada, de reanuda su reproducción
		actPlayingMusic->music->Play();
}


/*
Se para la música de fondo que se está reproduciendo actualmente
*/
void SoundEngine::stopMusic()
{
	//estas ya comprueban si está a NULL musica actual
	if ( isMusicPlaying(actPlayingMusic) || isMusicPaused(actPlayingMusic) ) //Si la música está reproduciéndose o pausada, se para
		actPlayingMusic->music->Stop();
}

/*
Si alguna música de fondo está reproduciéndose o pausada cambiamos su loop
*/
void SoundEngine::setLoop(bool loop)
{
	if(actPlayingMusic != NULL)
		actPlayingMusic->music->SetLoop(loop);
}





