#include "MusicManager.h"

//! Instancia el MusicManager
MusicManager::MusicManager(){
	this->list = new map<string, MusicManagerItem*>();
}
		
//! Destruye el MusicManager
MusicManager::~MusicManager(){
	delete this->list;
}
		
//! Comprueba si la música obtenida a partir del archivo fname ya está cargada.
/*!
	Este método tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
	\param fname Nombre de archivo fuente
	\return true si la música ya ha sido cargada
*/
bool MusicManager::isLoaded(string fname){
	// Si el iterador que devuelve find es distinto del final entonces la música ya está cargada
	return this->list->find(fname) != this->list->end();
}
		
//! Obtiene una música almacenada en el manager
/*!
	\param fname Nombre de archivo fuente solicitado
	\return Puntero a la música cargada en memoria
*/
Music* MusicManager::getMusic(string fname){
	// Antes comprobamos si el sonido está cargado para que no casque
	if (this->isLoaded(fname)){
		// Devolvemos la música del MusicManagerItem
		return this->list->find(fname)->second->getMusic();
	}
	else{
		// Si no está cargado devolvemos NULL
		return NULL;
	}

}
		
//! Añade una nueva música a la lista
/*!
	\param fname Nombre de archivo fuente
	\param music Puntero a la música
	\return false si la música o el fname ya estaban en memoria
*/
bool MusicManager::setMusic(string fname, Music* music){
	// Si la música indexada por fname no está en memoria
	if (!this->isLoaded(fname)){
		// envolvemos music en MusicManagerItem
		MusicManagerItem* musicM = new MusicManagerItem(music);
		// como al crear el MusicManagerItem el contador de enlaces está a 0, se incrementa en 1
		musicM->link();
		// se inserta el par a la lista
		this->list->insert(make_pair(fname, musicM));
		// devolvemos true porque fname no estaba en memoria
		return true;
	}
	else{
		// Si no incrementamos el nº de enlaces del sonido porque ya estaba cargado
		this->list->find(fname)->second->link();
		// devolvemos false porque ya estaba en memoria
		return false;
	}
}
		
//! Elimina una entrada de la lista
/*!
	Elimina la entrada de la lista y también la música de memoria
	\param fname Nombre de archivo fuente
	\return true si se ha eliminado correctamente
*/
bool MusicManager::remove(string fname){
	// Si está cargado en memoria...
	if (this->isLoaded(fname)){
		// Comprobamos si el nº de enlaces es 0
		if (this->list->find(fname)->second->unlink()){
			// Si no se elimina correctamente erase devuelve 0
			return (this->list->erase(fname) != 0);
		}
		else{
			// ya se ha decrementado el nº de enlaces en el unlink del if
			// devolvemos false porque el nº de enlaces es > que 0
			return false;
		}
	}
	else{
		// devolvemos false porque no estaba cargado
		return false;
	}
};