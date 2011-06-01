/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "MusicManagerItem.h"


//! Construye el MusicManagerItem para la músic music
/*!
	Inicializa el contador de enlaces a 0.
	\param music Música encapsulada
*/
MusicManagerItem::MusicManagerItem(sf::Music* music){
	// Enlazamos el sonido
	this->music = music;
	// contador de enlaces a 0
	links = 1;
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
sf::Music* MusicManagerItem::getMusic(){
	return this->music;
}
	
//! Devuelve el número de enlaces actual a la música
/*!
	\return Número de enlaces actuales
*/
int MusicManagerItem::getLinks(){
	return this->links;
};