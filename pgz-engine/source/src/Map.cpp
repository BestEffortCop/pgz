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

#include "Map.h"

//Construye un map de dimensiones determinadas vacio
Map::Map(int tileW, int tileH, GfxEngine* gfxEngine){
	//Construye un tileMap vacio
	tileMap = new TileMap(tileW, tileH, gfxEngine);
	//Pone el solidGrid a NULL
	solidGrid = NULL; 
};

//Destructora
Map::~Map(){
	//Borra el tileMap, actualmente no hace falta comprobar si existe dado que este se crea siempre en 
	//la constructora, pero se deja para futuras extensiones de la clase
	if (tileMap != NULL)
	{
		delete tileMap;
		tileMap = NULL;
	}
	// Si el solidGrid fue configurado mediante setter/load antes de borrar.
	if(solidGrid != NULL)
	{
		//Lo borramos
		delete solidGrid;
		solidGrid = NULL;
	}
};

//Cargamos un solid grid de archivo a partir de su dirección
void Map::loadSolids(string fname){
	// Borramos el antiguo, si hubiera
	if (solidGrid != NULL)
		delete solidGrid;

	solidGrid = new SolidGrid(fname);
};

//Devolvemos el solidGrid
SolidGrid* Map::getSolids(){
	return solidGrid;
};

//Configuramos un nuevo SolidGrid a partir de sus parametros basicos
void Map::setSolids(int x, int y, int** solids, int columns, int rows){
	// Borramos el antiguo, si hubiera
	if (solidGrid != NULL)
		delete solidGrid;

	//Lo construimos de cero
	solidGrid = new SolidGrid(x,y,solids,tileMap->getWidth(),tileMap->getHeight(),columns,rows);
};

//Cargamos de archivo el tileSet del tileMap a partir de su dirección
void Map::setTileset(string fname){
	if (tileMap != NULL)
		tileMap->setTileSet(fname);
};

//Cargamos de archivo el tileSet del tileMap a partir de su dirección
void Map::setTileset(TileSet* tset){
	if (tileMap != NULL)
		tileMap->setTileSet(tset);
};

//Cargamos el mapa de tiles del tileMap a partir de archivo
void Map::loadTiles(string fname){
	if (tileMap != NULL)
		tileMap->loadMap(fname);
};

//Configuramos el mapa de tiles a partir de uno ya construido
void Map::setTiles(int** tiles, int columns, int rows){
	if (tileMap != NULL)
	{
		tileMap->setMap(tiles, columns, rows);
	}
};

// Llama a tileMap para que realice la función
Image* Map::getMapImage(){
	if (tileMap != NULL)
		return tileMap->getMapImage();
	else return NULL;
}

// Llama a tileMap para que realice la función
void Map::setTile(int x, int y, int tile){
	if ((tileMap != NULL) && (tileMap->tileSet != NULL))
	{
		// Si la coordenada indicada se encuentra dentro de los límites del mapa
		if ((( x >= 0 && x < tileMap->colNumber)
			&& ( y >= 0 && y < tileMap->rowNumber))
			// Si el tile se encuentra dentro del tileset
			&& (tile >= 0 && tile < tileMap->tileSet->getColumns()*tileMap->tileSet->getRows()))
		{
			// Borramos la imagen del antiguo mapa
			delete tileMap->mapImage;
			tileMap->mapImage = NULL;

			// Modificamos el mapa de tiles
			tileMap->idMap[x][y] = tile;

			// Repintamos el mapa
			tileMap->getMapImage();
		}
	}
}

//Carga el solid grid y el mapa de tiles del tileMap a partir de un nombre común a ambos
//archivos
void Map::loadMap(string fname){
	// se busca extensión
	size_t found = fname.find_last_of(".");
	
	//Si la encuentra
	if (found != string::npos){
		//Se descarta 
		fname = fname.substr(0,found);
	}

	// Se almacena el nombre de archivo sin extensión
	string f2 = fname;

	// carga sólidos y tiles de los ficheros correspondientes
	//nombreArchivo.sol
	loadSolids(fname.append(".sol"));
	//nombreArchivo.til
	loadTiles(f2.append(".til"));
};

//Metodo update para el Map por si fuera necesario
void Map::update(){
	//Por ahora no hace nada
};

//Dibuja el tileMap por pantalla
void Map::render(int x, int y){
	//Si existe
	if (tileMap != NULL)
		//le digo al tileMap que se dibuje
		tileMap->render(x,y);
};

//! Obtiene el tileset actual del mapa
/*! \return Tileset actual */
TileSet* Map::getTileset()
{
	return tileMap->getTileset();
};