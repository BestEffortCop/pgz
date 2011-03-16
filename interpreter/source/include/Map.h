#pragma once

#ifndef __MAP_H__
#define __MAP_H__

#include "TileMap.h"
#include "SolidGrid.h"
#include "GfxEngine.h"

using namespace std;

//! Representa un mapa basado en tiles, tanto su parte gáfica como su parte de colisiones.
/*!
	Encapsula un TileMap para la parte gráfica y un SolidGrid para la parte de colisiones.
	
	Proporciona métodos para modificar las propiedades de las clases que encapsula y
	métodos de carga, así como uno de actualización y otro de renderizado, todos virtuales.
	
	Para una mayor comodidad, se puede derivar una clase de Map, sobreescribir los
	métodos que interesen (por ejemplo el de carga) y pasársela al GameState pertinente
	para que la mantenga de forma automática.
	
	La forma común de trabajar con Map es:
	- Instanciar el Map con el tamaño de tile deseado
	- Indicar al Map el tileset que debe utilizar mediante Map::setTileset().
	- Cargar el mapa:
		- Con el método por defecto
		- De forma externa al Map, pasándoselo luego mediante Map::setSolids() y Map::setTiles()
	- Mantener actualizado el mapa con Map::update()
	- Renderizar el mapa cuando corresponda con Map::render();
	
	\sa GameState
	\sa TileMap
	\sa SolidGrid
*/

class Map
{
	private:
		//! Atributos de la clase SpriteMap.
		/*!
			\param tileMap aspecto gráfico de un mapa de tiles
			\param solidGrid matriz de sólidos de un mapa de tiles
		*/
		TileMap* tileMap;
		SolidGrid* solidGrid;
	
    public:

		//! Construye el Map con el ancho y alto de tile indicados
		/*!
			\param tileW Ancho de los tiles del mapa
			\param tileH Alto de los tiles del mapa
			\param gfxEngine Puntero al GfxEngine del sistema
		*/
		Map(int tileW, int tileH, GfxEngine* gfxEngine);

		//! Destruye el Map
        virtual ~Map();

		//! Carga el la parte de colisiones del mapa con el método por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadSolids(string fname);
		
		//! Devuelve el contenido de la parte de colisiones del Map.
		virtual SolidGrid* getSolids();

		//! Establece el contenido de la parte de colisiones del Map.
		/*!
			\param solids Array con los tipos de las celdas
		*/
		virtual void setSolids(int x, int y, int** solids, int columns, int rows);
		
		//! Establece el tileset que utilizará el mapa
		/*!
			\param fname Nombre de archivo del tileset
		*/
		virtual void setTileset(string fname);
		
		//! Carga el la parte de gráficos del mapa con el método por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadTiles(string fname);
		
		//! Establece el contenido de la parte de gráficos del Map.
		/*!
			\param tiles Array con los tiles
		*/
		virtual void setTiles(int** tiles);

		//! Obtiene de la imagen del mapa ya construído.
		/*!
			\return la imagen del mapa
		*/
		Image* getMapImage();

		//! Establece de uno de los tiles del mapa
		/*!
			\param x contiene la coordenada x del tile que deseamos cambiar
			\param y contiene la coordenada y del tile que queremos cambiar
			\param tile contiene el tile del tileSet asignado al mapa que vamos a colocar en la posición indicada del mapa
		*/
		void setTile(int x, int y, int tile);

		//! Carga el mapa completo (gráficos y colisiones) con el método por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadMap(string fname);

		//! Actualiza la imagen y el estado de los sólidos del Map
		virtual void update();
		
		//! Muestra el mapa en la posición indicada
		/*!
			\param x Posición horizontal
			\param y Posición vertical
		*/
        virtual void render(int x, int y);
        
};

#endif // MAP_H
