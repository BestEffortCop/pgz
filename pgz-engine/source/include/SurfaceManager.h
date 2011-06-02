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

#pragma once

#ifndef _SURFACEMANGER_H_
#define _SURFACEMANGER_H_

#include <map>
#include "SFML/Graphics.hpp"
#include "SurfaceManagerItem.h"

using namespace std;

//! Mantiene la colección de superficies en memoria.
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo gráfico. Este elemento (al que llamaremos superficie)
	no debería cargarse varias veces en memoria, 
	sino compartirse entre todos con el consecuente ahorro.
	
	De esta tarea se encarga SurfaceManager, que mantiene la lista
	de superficies cargadas en memoria de forma transparente al programador.

	Se asegura de que las imágenes cargadas desde disco a memoria
	se mantienen sin duplicados y que se eliminan las que no se 
	necesiten, mediante un contador de enlaces asociado a cada
	superficie.
	
	Proporciona funcionalidad para comprobar si una superficie ya
	está cargada, obtenerla en tal caso o añadir una nueva entrada
	en otro caso.
*/
class SurfaceManager {
	private:
		//! Mapa de superficies enlazadas por nombre de archivo fuente
		map<string,SurfaceManagerItem*>* list;

	public:
		//! Instancia el SurfaceManager
		SurfaceManager();
		
		//! Destruye el SurfaceManager
		~SurfaceManager();
		
		//! Comprueba si la superficie obtenida a partir del archivo fname ya está cargada.
		/*!
			Este método tiene un coste computacional reducido (el mapa se indexa por nombre de archivo)
			\param fname Nombre de archivo fuente
			\return true si la imagen ya ha sido cargada
		*/
		bool isLoaded(string fname);
		
		//! Comprueba si la superficie indicada ya está cargada
		/*!
			Este método tiene un coste computacional elevado (hay que recorrer toda la lista de superficies)
			\param surf Puntero a la superficie a comprobar
			\return true si la imagen ya ha sido cargada
		*/
		bool isLoaded(sf::Image* surf);
		
		//! Obtiene una superficie almacenada en el manager
		/*!
			\param fname Nombre de archivo fuente solicitado
			\return Puntero a la imagen cargada en memoria
		*/
		sf::Image* getSurface(string fname);
		
		//! Añade una nueva superficie a la lista
		/*!
			\param fname Nombre de archivo fuente
			\param surf Puntero a la superficie
			\return false si el fname ya estaban en memoria
		*/
		bool setSurface(string fname, sf::Image* surf);
		
		//! Elimina una entrada de la lista
		/*!
			Elimina la entrada de la lista y también la superficie de memoria
			\param fname Nombre de archivo fuente
			\return true si se ha eliminado correctamente
		*/
		bool remove(string fname);
		
		//! Elimina una entrada de la lista
		/*!
			Elimina la entrada de la lista y también la superficie de memoria
			\param surf Puntero a la superficie a eliminar
			\return true si se ha eliminado correctamente
		*/
		bool remove(const sf::Image* surf);
};

#endif // _SURFACEMANAGER_H_