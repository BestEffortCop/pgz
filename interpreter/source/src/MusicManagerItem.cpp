#include "MusicManagerItem.h"


//! Construye el MusicManagerItem para la músic music
/*!
	Inicializa el contador de enlaces a 0.
	\param music Música encapsulada
*/
MusicManagerItem::MusicManagerItem(Music* music){
	// Enlazamos el sonido
	this->music = music;
	// contador de enlaces a 0
	links = 0;
}

//! Añade un nuevo enlace a la música
void MusicManagerItem::link(){
	this->links++; // incrementamos el nº de enlaces
}
	
//! Elimina un enlace a la música
/*!
	\return true si la música puede borrarse porque el número de enlaces es 0.
*/
bool MusicManagerItem::unlink(){
	this->links--; // decrementamos el número de enlaces
	return (this->links == 0); // Si el nº de enlaces es 0 se puede eliminar
} // true si debe borrarse
	
//! Obtiene la música encapsulada
/*!
	\return Puntero a la música encapsulada
*/
Music* MusicManagerItem::getMusic(){
	return this->music;
}
	
//! Devuelve el número de enlaces actual a la música
/*!
	\return Número de enlaces actuales
*/
int MusicManagerItem::getLinks(){
	return this->links;
};