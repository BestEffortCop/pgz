#include "SoundEngine.h"

//Constructora por defecto de SoundEngine
SoundEngine::SoundEngine()
{
	systemSoundVolume = 50.0; //Setea el volumen global de sonidos
	systemMusicVolume = 50.0; //Setea el volumen global de músicas
	init();
}

//Destructora
SoundEngine::~SoundEngine()
{
	delete soundManager; //Libera la memoria de soundManager
	delete musicManager; //Libera la memoria de musicManager
}

//Inicializa las estructuras necesarias
bool SoundEngine::init()
{
	soundManager = new SoundManager(); //Crea un SoundManager para su posterior utilización
	musicManager = new MusicManager(); //Crea un MusicManager para su posterior utilización
	actPlayingMusic = NULL;
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

	if (volume == -1) 
		sound->sound->SetVolume(systemSoundVolume);//Si no se ha solicitado un volumen concreto se pone el del sistema
	else
		sound->sound->SetVolume(volume); //Si se ha solicitado, se cambia al solicitado

	if (sound->sound->GetLoop() != loop) //Si el loop solicitado es distinto al que teníamos
		sound->sound->SetLoop(loop);     //Lo cambiamos

	sound->sound->Play();

}

void SoundEngine::fadeSound(Sound* sound, float volume, int time){;}//Mirar

/*
Devuelve si sound se está reproduciendo actualmente
*/
bool SoundEngine::isSoundPlaying(Sound* sound)
{
	if (sound!=NULL)
		if(sound->sound->GetStatus() == sf::Sound::Playing ) //Si existe el sonido y está reproduciéndose
			return true;
		else return false;
	else return false;
}

/*
Detiene la reproducción de sound
*/
void SoundEngine::stopSound(Sound* sound)
{
	if (isSoundPlaying(sound)) //Si el sonido está reproduciéndose, se detiene.
		sound->sound->Stop();
}


//----------------------------------------------------
//Métodos relacionados con la reproducción de Música -
//----------------------------------------------------

/*
Carga en memoria la música correspondiente a la path
*/
sf::Music* SoundEngine::loadMusic(string path)
{
	if( !musicManager->isLoaded(path)) //Comprueba si el sonido está cargado actualmente en memoria
	{ 
		sf::Music* music = new sf::Music();
		if( !music->OpenFromFile(path) )//Si no está cargado, se carga
		{ 
			//Error, no se ha podido cargar el archivo
			return NULL;
		}
		//falta guardar en musicManager el sonido que acabamos de cargar!!
		return music;
	}
	else return musicManager->getMusic(path)->music; //Si está cargado, se devuelve
}

/*
Reproduce una música de fondo, controlando que solo haya una reproduciéndose al mismo tiempo
*/
void SoundEngine::playMusic(Music* music, float volume, bool loop)
{	
	if (actPlayingMusic != NULL)
		if(isMusicPlaying(actPlayingMusic)) //Si hay alguna música de fondo reproduciéndose, se para
			stopMusic();

	if (volume == -1)
		music->music->SetVolume(systemMusicVolume); //Si no se solicita un volumen específico, se reproduce con el volumen del sistema
	else
		music->music->SetVolume(volume); // Si se solicita un volumen específico, se cambia


	if (music->music->GetLoop() != loop) //Si el loop solicitado es distinto
		music->music->SetLoop(loop);     //Se cambia

	actPlayingMusic = music;
	music->music->Play();
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
		if( music->music->GetStatus() == sf::Music::Playing ) //Si la música existe y está reproduciendose, se devuelve true
			return true;
		else return false;
	else return false;
}

/*
Pausa la música de fondo
*/
void SoundEngine::pauseMusic()
{
	if (isMusicPlaying(actPlayingMusic)) //Si la música está reproduciéndose, se pausa
		actPlayingMusic->music->Pause();
}

/*
Devuelve si la música de fondo está pausada
*/
bool SoundEngine::isMusicPaused(Music* music)
{
	if (music != NULL) //music == actPlayingMusic && ?
		if(music->music->GetStatus() == sf::Music::Paused) //Si la música está pausada, se devuelve true
			return true;
		else return false;
	else return false;
}

/*
Se reanuda la reproducción de la música de fondo pausada
*/
void SoundEngine::resumeMusic()
{
	if (isMusicPaused(actPlayingMusic)) //Si la música está pausada, de reanuda su reproducción
		actPlayingMusic->music->Play();
}


/*
Se para la música de fondo que se está reproduciendo actualmente
*/
void SoundEngine::stopMusic()
{
	if ( isMusicPlaying(actPlayingMusic) || isMusicPaused(actPlayingMusic) ) //Si la música está reproduciéndose o pausada, se para
		actPlayingMusic->music->Stop();
}

/*
Si alguna música de fondo está reproduciéndose o pausada cambiamos su loop
*/
void SoundEngine::setLoop(bool loop)
{
	if ( isMusicPlaying(actPlayingMusic) || isMusicPaused(actPlayingMusic) ) //Se cambia el loop de la música, 
		actPlayingMusic->music->SetLoop(loop);					             //siempre y cuando esté reproduciéndose o pausada
}





