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

#include "SoundManager.h"


//! Instancia el SoundManager
SoundManager::SoundManager()
{
	this->list = new std::map<std::string, SoundManagerItem*>();
}
		
//! Destruye el SoundManager
SoundManager::~SoundManager()
{
	std::map< std::string, SoundManagerItem* >::iterator it = list->begin();
	 SoundManagerItem* tmp;
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
		
//! Comprueba si el sonido obtenido a partir del archivo fname ya está cargado.
/*!
	Este método tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
	\param fname Nombre de archivo fuente
	\return true si el sonido ya ha sido cargado
*/
bool SoundManager::isLoaded(std::string fname)
{
	// Si el iterador que devuelve find es distinto del final entonces el sonido ya está cargado
	return this->list->find(fname) != this->list->end();
}
		
//! Obtiene un sonido almacenado en el manager
/*!
	\param fname Nombre de archivo fuente solicitado
	\return Puntero al sonido cargado en memoria
*/
sf::SoundBuffer* SoundManager::getSoundBuffer(std::string fname)
{
	std::map<std::string, SoundManagerItem*>::iterator it;
	//solo lo buscamos una vez, si está entonces 'it' apunta a él
	it = list->find(fname);
	if(it != list->end())
	{
		SoundManagerItem* tmp = it->second;
		//incrementamos la cantidad de enlaces con uno.
		tmp->link();
		//devolvemos el puntero a la imagen
		return tmp->getSoundBuffer();
	}
	else
		//no hemos encontrado la imagen solicitada
		return NULL;
}
		
//! Añade un nuevo sonido a la lista
/*!
	\param fname Nombre de archivo fuente
	\param sound Puntero a el sonido
	\return false si el fname ya estaban en memoria
*/
bool SoundManager::setSoundBuffer(std::string fname, sf::SoundBuffer* soundBuf)
{
	// Si el sonido indexado por fname no está en memoria
	if (soundBuf && !this->isLoaded(fname))
	{
		// envolvemos soundBuffer en SoundManagerItem
		SoundManagerItem* item = new SoundManagerItem(soundBuf);
		//item->link();  -> Ya se crea un Item con link = 1. No tiene sentido link = 0 ahora mismo.
		// se inserta el par a la lista
		this->list->insert(std::pair<std::string, SoundManagerItem*>(fname, item));
		// devolvemos true porque fname no estaba en memoria
		return true;
	}
	else
		//Ya existe un soundBuffer con ese nombre, por eso no se guarda.
		return false;
}
		
//! Elimina una entrada de la lista
/*!
	Elimina la entrada de la lista y también el sonido de memoria
	\param fname Nombre de archivo fuente
	\return true si se ha eliminado correctamente
*/
bool SoundManager::remove(std::string fname)
{
	// Si está cargado en memoria...
	std::map<std::string, SoundManagerItem*>::iterator it;
	//lo buscamos y si está, tenemos su dirección en it. Nos ahorramos una búsqueda
	it = list->find(fname);
	if(it != list->end())	//si llega a end la búsqueda es que no está.
	{
		SoundManagerItem* tmp = it->second;
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