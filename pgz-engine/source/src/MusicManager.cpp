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

#include "MusicManager.h"

//! Instancia el MusicManager
MusicManager::MusicManager()
{
	this->list = new map<std::string, MusicManagerItem*>();
}
		
//! Destruye el MusicManager
MusicManager::~MusicManager()
{
	std::map< std::string, MusicManagerItem* >::iterator it = list->begin();
	MusicManagerItem* tmp;
	while (it != list->end())
	{
		tmp = it->second;
		it++;
		if (tmp)
		{
			//Invocamos Destructora de SoundManagerItem
			delete tmp;
			tmp = NULL;
		}
	}

	delete list;
	list = NULL;
}
		
//! Comprueba si la música obtenida a partir del archivo fname ya está cargada.
/*!
	Este método tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
	\param fname Nombre de archivo fuente
	\return true si la música ya ha sido cargada
*/
bool MusicManager::isLoaded(string fname)
{
	// Si el iterador que devuelve find es distinto del final entonces la música ya está cargada
	return this->list->find(fname) != this->list->end();
}
		
//! Obtiene una música almacenada en el manager
/*!
	\param fname Nombre de archivo fuente solicitado
	\return Puntero a la música cargada en memoria
*/
sf::Music* MusicManager::getMusic(std::string fname){
	std::map<std::string, MusicManagerItem*>::iterator it;
	//solo lo buscamos una vez, si está entonces 'it' apunta a él
	it = list->find(fname);
	if(it != list->end())
	{
		MusicManagerItem* tmp = it->second;
		//incrementamos la cantidad de enlaces con uno.
		tmp->link();
		//devolvemos el puntero a la imagen
		return tmp->getMusic();
	}
	else
		//no hemos encontrado la imagen solicitada
		return NULL;
}
		
//! Añade una nueva música a la lista
/*!
	\param fname Nombre de archivo fuente
	\param music Puntero a la música
	\return false si la música o el fname ya estaban en memoria
*/
bool MusicManager::setMusic(std::string fname, sf::Music* music){
	// Si la música indexada por fname no está en memoria
	if (music && !this->isLoaded(fname)){
		// envolvemos music en MusicManagerItem
		MusicManagerItem* musicM = new MusicManagerItem(music);
		// se inserta el par a la lista
		this->list->insert(std::pair<std::string, MusicManagerItem*>(fname, musicM));
		// devolvemos true porque fname no estaba en memoria
		return true;
	}
	else{
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
bool MusicManager::remove(std::string fname){
	// Si está cargado en memoria...
	std::map<std::string, MusicManagerItem*>::iterator it;
	//lo buscamos y si está, tenemos su dirección en it. Nos ahorramos una búsqueda
	it = list->find(fname);
	if(it != list->end())	//si llega a end la búsqueda es que no está.
	{
		MusicManagerItem* tmp = it->second;
		if (tmp->unlink()) //true, si se le han acabado los links virtuales.
		{
			//delete tmp->getSound(); // Esto lo debe hacer el Engine
			delete tmp;
			tmp = NULL;

			list->erase(it);
			//lo hemos eliminado del todo
			return true;
		}
		//solo hemos quitado un enlace simbólico, pero hay más enlaces.
		return false;
	}
	else
		// no se encuentra ningún sonido con este nombre
		return false;
};