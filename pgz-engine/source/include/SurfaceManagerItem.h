#pragma once
#ifndef __SURFACEMANAGERITEM_H__
#define __SURFACEMANAGERITEM_H__

#include "SFML/Graphics.hpp"

//! Elemento básico del SurfaceManager
/*!
	Dentro de un mismo juego distintos elementos pueden compartir
	un mismo archivo gráfico. Este elemento (al que llamaremos superficie)
	no debería cargarse varias veces en memoria, 
	sino compartirse entre todos con el consecuente ahorro.
	
	De esta tarea se encarga SurfaceManager, que mantiene la lista
	de superficies cargadas en memoria de forma transparente al programador.
	
	SurfaceManagerItem es el elemento básico de esta lista.	
	Relaciona una superficie (sf::Image) con el número de Images que la utilizan
	para poder liberarla cuando no sea necesaria, asegurando que no
	se elimina mientras alguien la está utilizando.

	\sa Image
	\sa SurfaceManager
*/
class SurfaceManagerItem
{

private:
	//! Número de enlaces actuales a la superficie encapsulada
	unsigned int links;
	//! Superficie (sf::Image encapsulada)
	sf::Image* surface;

public:
	//! Construye el SurfaceManagerItem para la superficie surf
	/*!
		Inicializa el contador de enlaces a 0.
		\param surf Superficie encapsulada
	*/
	SurfaceManagerItem(sf::Image* surf);

	//! Destructora que no elimina la propia imagen o superficie.
	~SurfaceManagerItem(){};

	//! Añade un nuevo enlace a la superficie
	void link();
	
	//! Elimina un enlace a la superficie
	/*!
		\return true si la superficie puede borrarse porque el número de enlaces es 0.
	*/
	bool unlink();
	
	//! Obtiene la superficie encapsulada
	/*!
		\return Puntero a la superficie encapsulada
	*/
	sf::Image* getSurface();
	
	//! Devuelve el número de enlaces actual a la superficie
	/*!
		\return Número de enlaces actuales
	*/
	int getLinks();
};

#endif