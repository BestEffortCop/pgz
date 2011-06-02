/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
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
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "TileFont.h"


TileFont::TileFont(string path, GfxEngine* gfxEngine):Font()
{
	int tileW,tileH;
	posicion = new map<int, int>();

	// se busca extensión
    size_t found = path.find_last_of(".");
        
    //Si la encuentra
    if (found != string::npos){
            //Se descarta 
            path = path.substr(0,found);
    }
	// Se almacena el nombre de archivo sin extensión
    string pathconf = path;

    // carga configuracion y tileSet de los ficheros correspondientes
    //nombreArchivo.png
    path = path.append(".png");
    //nombreArchivo.txt
    pathconf= pathconf.append(".cfg");
	
	//Abro el archivo para lectura
	FILE* file = NULL;
    file = fopen(pathconf.c_str(), "rb");

	// lectura de ancho y alto de tile
    fscanf(file, "%d", &tileW);
    fscanf(file, "%d", &tileH);

	//Voy colocando todos los pares codigo asci, posicion en el tileSet
	for (int i = 0; i < NUM_CHAR; i++)
	{
		int aux;
		fscanf(file, "%d", &aux);
		posicion->insert(make_pair(aux,i));
	}
	//cerramos el archivo una vez hemos terminado de leerlo
	fclose(file);

	//Creamos nuestro tileSet
	tileSet = new TileSet(path,tileW,tileH,gfxEngine);
}

TileFont::~TileFont()
{
	//Si nadie ha borrado su tileSet(que puede pasar)
	if (tileSet != NULL)
	{
        //Lo borramos
        delete tileSet;
        tileSet = NULL;
    }
	//Si el map posicion se ha creado lo borramos
	if(posicion)
	{
        //Lo borramos
        delete posicion;
        posicion = NULL;
    }
}


int TileFont::getGlyphId(char c)
{
	// Creamos un iterador para map
    map<int, int>::iterator it;
    //Pido que busque el caracter solicitado
    it = posicion->find((int) c);
    if (it == posicion->end())
            //Si no está hemos acabado y devolvemos -1
            return -1;
	return it->second - 1;

}


int TileFont::getTileH() {return tileSet->getTileH();}

int TileFont::getTileW() {return tileSet->getTileW();}

TileSet* TileFont::getTileSet() {return tileSet;}