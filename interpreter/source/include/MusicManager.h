#pragma once

#ifndef _MUSICMANGER_H_
#define _MUSICMANGER_H_

#include <map>
#include "MusicManagerItem.h"
#include "Music.h"

class Music;

class MusicManagerItem;

//! Mantiene la colección de músicas en memoria.
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo de audio musical. Este elemento
	no debería cargarse varias veces en memoria,
	sino compartirse entre todos con el consecuente ahorro.
	
	De esta tarea se encarga MusicManager, que mantiene la lista
	de sonidos cargados en memoria de forma transparente al programador.

	Se asegura de que las músicas cargadas desde disco a memoria
	se mantienen sin duplicados y que se eliminan las que no se 
	necesiten, mediante un contador de enlaces asociado a cada
	música.
	
	Proporciona funcionalidad para comprobar si una música ya
	está cargada, obtenerla en tal caso o añadir una nueva entrada
	en otro caso.
*/
class MusicManager {
	private:
		//! Mapa de músicas enlazadas por nombre de archivo fuente
		map<std::string,MusicManagerItem*>* list;

	public:
		//! Instancia el MusicManager
		MusicManager();
		
		//! Destruye el MusicManager
		~MusicManager();
		
		//! Comprueba si la música obtenida a partir del archivo fname ya está cargada.
		/*!
			Este método tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
			\param fname Nombre de archivo fuente
			\return true si la música ya ha sido cargada
		*/
		bool isLoaded(std::string fname);
		
		//! Obtiene una música almacenada en el manager
		/*!
			\param fname Nombre de archivo fuente solicitado
			\return Puntero a la música cargada en memoria
		*/
		sf::Music* getMusic(std::string fname);
		
		//! Añade una nueva música a la lista
		/*!
			\param fname Nombre de archivo fuente
			\param music Puntero a la música
			\return false si la música o el fname ya estaban en memoria
		*/
		bool setMusic(std::string fname, sf::Music* music);
		
		//! Elimina una entrada de la lista
		/*!
			Elimina la entrada de la lista y también la música de memoria
			\param fname Nombre de archivo fuente
			\return true si se ha eliminado correctamente
		*/
		bool remove(std::string fname);
};

#endif // _SURFACEMANAGER_H_