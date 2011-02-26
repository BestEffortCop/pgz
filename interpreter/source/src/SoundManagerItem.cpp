#include "SoundManagerItem.h"


//! Construye el SoundManagerItem para el músic sound
/*!
	Inicializa el contador de enlaces a 0.
	\param sound Sonido encapsulado
*/
SoundManagerItem::SoundManagerItem(Sound* sound){
	// Enlazamos el sonido
	this->sound = sound;
	// contador de enlaces a 0
	links = 0;
}

//! Añade un nuevo enlace al sonido
void SoundManagerItem::link(){
	this->links++; // incrementamos el nº de enlaces
}
	
//! Elimina un enlace al sonido
/*!
	\return true si el sonido puede borrarse porque el número de enlaces es 0.
*/
bool SoundManagerItem::unlink(){
	this->links--; // decrementamos el número de enlaces
	return (this->links == 0); // Si el nº de enlaces es 0 se puede eliminar
} // true si debe borrarse
	
//! Obtiene el sonido encapsulado
/*!
	\return Puntero a el sonido encapsulado
*/
Sound* SoundManagerItem::getSound(){
	return this->sound;
}
	
//! Devuelve el número de enlaces actual al sonido
/*!
	\return Número de enlaces actuales
*/
int SoundManagerItem::getLinks(){
	return this->links;
};