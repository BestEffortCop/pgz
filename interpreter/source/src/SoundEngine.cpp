#include "SoundEngine.h"

//Constructora por defecto de SoundEngine
SoundEngine::SoundEngine(){
	systemSoundVolume = 50.0; //Setea el volumen global de sonidos
	systemMusicVolume = 50.0; //Setea el volumen global de músicas
	init();
}

//Destructora
SoundEngine::~SoundEngine(){
	delete soundManager; //Libera la memoria de soundManager
	delete musicManager; //Libera la memoria de musicManager
}

//Inicializa las estructuras necesarias
bool SoundEngine::init(){
	soundManager = new SoundManager(); //Crea un SoundManager para su posterior utilización
	musicManager = new MusicManager(); //Crea un MusicManager para su posterior utilización
	if (soundManager == NULL || musicManager == NULL ) //Comprueba si se han creado las estructuras correctamente
		return false;
	else return true;
} 


//Métodos comunes a sonidos y músicas
void SoundEngine::setSoundVolume(float soundVolume) { systemSoundVolume = soundVolume;} //Cambia el volumen global de sonidos
float SoundEngine::getSoundVolume() { return systemSoundVolume;}

void SoundEngine::setMusicVolume(float musicVolume) { systemMusicVolume = musicVolume;} //Cambia el volumen global de música
float SoundEngine::getMusicVolume() { return systemMusicVolume;}

void SoundEngine::stopAllSounds(){;} //Por implementar
void SoundEngine::stopAllMusic(){ stopMusic();} //Detiene la música de fondo que se está reproduciendo actualmente


//Métodos relacionados con la reproducción de Sonidos

//Carga un sonido en memoria para su posterior reproducción
sf::Music* SoundEngine::loadSound(string path){

	sf::Music* sound = new sf::Music();
	if( !soundManager->isLoaded(path)){ //Comprueba si ya está cargada en memoria
		if ( !sound->OpenFromFile(path.c_str()) ){ //Si no está cargada intenta cargarla
			cout<<"fallo al cargar sonido"<<endl;
		}
		return sound;
	}
	else return soundManager->getSound(path)->sound; // Si está cargada la devuelve
}

//Reproduce un sonido
void SoundEngine::playSound(Sound* sound, bool loop, float volume){

	if (volume == -1) 
		sound->sound->SetVolume(systemSoundVolume);//Si no se ha solicitado un volumen concreto se pone el del sistema
	else
		sound->sound->SetVolume(volume); //Si se ha solicitado, se cambia al solicitado

	if (sound->sound->GetLoop() != loop) //Si el loop solicitado es distinto al que teníamos
		sound->sound->SetLoop(loop);     //Lo cambiamos

	sound->sound->Play();

}

void SoundEngine::fadeSound(Sound* sound, float volume, int time){;}//Mirar

//Devuelve si sound se está reproduciendo actualmente
bool SoundEngine::isSoundPlaying(Sound* sound){
	if (sound!=NULL && sound->sound->GetStatus() == sf::Music::Playing ) //Si existe el sonido y está reproduciéndose, se devuelve true
		return true;
	else return false;
}

//Detiene la reproducción de sound
void SoundEngine::stopSound(Sound* sound){
	if (isSoundPlaying(sound)) //Si el sonido está reproduciéndose, se detiene.
		sound->sound->Stop();
}

//Métodos relacionados con la reproducción de Música

//Carga en memoria la música que haya en path
sf::Music* SoundEngine::loadMusic(string path){
	sf::Music* music = new sf::Music();
	if( !musicManager->isLoaded(path)){//Comprueba si el sonido está cargado actualmente en memoria
		if( !music->OpenFromFile(path.c_str()) ){ //Si no está cargado, se carga
			//Error
		}
		return music;
	}
	else return musicManager->getMusic(path)->music; //Si está cargado, se devuelve
}

//Reproduce una música de fondo, controlando que solo haya una reproduciéndose al mismo tiempo
void SoundEngine::playMusic(Music* music, bool loop, float volume){
	
	if (actPlayingMusic != NULL && isMusicPlaying(actPlayingMusic)) //Si hay alguna música de fondo reproduciéndose, se para
		stopMusic();

	if (volume == -1)
		music->music->SetVolume(systemMusicVolume); //Si no se solicita un volumen específico, se reproduce con el volumen del sistema
	else
		music->music->SetVolume(volume); // Si se solicita un volumen específico, se cambia


	if (music->music->GetLoop() != loop) //Si el loop solicitado es distinto
		music->music->SetLoop(loop);     //Se cambia

	music->music->Play();

	actPlayingMusic = music;
}

//Finaliza la reproducción de una música de fondo con atenuación
void SoundEngine::fadeMusic(float volume, int time){
	/*if (actPlayingMusic != NULL && isMusicPlaying(actPlayingMusic)){
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

//Nos dice si music está reproduciéndose actualmente
bool SoundEngine::isMusicPlaying(Music* music){
	if (music != NULL && music->music->GetStatus() == sf::Music::Playing ) //Si la música existe y está reproduciendose, se devuelve true
		return true;
	else return false;
}

//Pausa la música de fondo
void SoundEngine::pauseMusic(){
	if (isMusicPlaying(actPlayingMusic)) //Si la música está reproduciéndose, se pausa
		actPlayingMusic->music->Pause();
}

//Devuelve si la música de fondo está pausada
bool SoundEngine::isMusicPaused(Music* music){
	if (music != NULL && music->music->GetStatus() == sf::Music::Paused) //Si la música existe y está pausada, se devuelve true
		return true;
	else return false;
}

//Se reanuda la reproducción de la música de fondo pausada
void SoundEngine::resumeMusic(){
	if (isMusicPaused(actPlayingMusic)) //Si la música está pausada, de reanuda su reproducción
		actPlayingMusic->music->Play();
}


//Se para la música de fondo que se está reproduciendo actualmente
void SoundEngine::stopMusic(){
	if ( isMusicPlaying(actPlayingMusic) || isMusicPaused(actPlayingMusic) ) //Si la música está reproduciéndose o pausada, se para
		actPlayingMusic->music->Stop();
}

//Si alguna música de fondo está reproduciéndose o pausada cambiamos su loop
void SoundEngine::setLoop(bool loop){
	if ( isMusicPlaying(actPlayingMusic) || isMusicPaused(actPlayingMusic) ) //Se cambia el loop de la música, 
		actPlayingMusic->music->SetLoop(loop);					             //siempre y cuando esté reproduciéndose o pausada
		

}





