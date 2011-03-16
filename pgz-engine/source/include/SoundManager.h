#pragma once

#ifndef _SOUNDMANGER_H_
#define _SOUNDMANGER_H_

#include <map>
#include "SoundManagerItem.h"

class Sound;

class SoundManagerItem;


//! Mantiene la colección de sonidos en memoria.
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo de efecto sonoro. Este elemento no debería cargarse 
	varias veces en memoria, sino compartirse entre todos 
	con el consecuente ahorro.
	
	De esta tarea se encarga SoundManager, que mantiene la lista
	de sonidos cargados en memoria de forma transparente al programador.

	Se asegura de que los sonidos cargados desde disco a memoria
	se mantienen sin duplicados y que se eliminan los que no se 
	necesiten, mediante un contador de enlaces asociado a cada
	sonido.
	
	Proporciona funcionalidad para comprobar si un sonido ya
	está cargado, obtenerlo en tal caso o añadir una nueva entrada
	en otro caso.
*/
class SoundManager {
	private:
		//! Mapa de sonidos indexado por nombre de archivo fuente
		std::map<std::string,SoundManagerItem*>* list;

	public:
		//! Instancia el SoundManager
		SoundManager();
		
		//! Destruye el SoundManager
		~SoundManager();
		
		//! Comprueba si el sonido obtenida a partir del archivo fname ya está cargado.
		/*!
			Este método tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
			\param fname Nombre de archivo fuente
			\return true si el sonido ya ha sido cargado
		*/
		bool isLoaded(std::string fname);
		
		//! Obtiene una sonido almacenado en el manager
		/*!
			\param fname Nombre de archivo fuente solicitado
			\return Puntero a el sonido cargado en memoria
		*/
		sf::SoundBuffer* getSoundBuffer(std::string fname);
		
		//! Añade un nuevo sonido a la lista
		/*!
			\param fname Nombre de archivo fuente
			\param sound Puntero a el sonido
			\return false si el sonido o el fname ya estaban en memoria
		*/
		bool setSoundBuffer(std::string fname, sf::SoundBuffer* soundBuf);
		
		//! Elimina una entrada de la lista
		/*!
			Elimina la entrada de la lista y también el sonido de memoria
			\param fname Nombre de archivo fuente
			\return true si se ha eliminado correctamente
		*/
		bool remove(std::string fname);
};

#endif