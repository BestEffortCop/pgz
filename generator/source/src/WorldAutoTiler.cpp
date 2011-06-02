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
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "WorldAutoTiler.h"

WorldAutoTiler::WorldAutoTiler(std::string tileSetPath){

	FILE* f;
	f = loadWorldConfig(loadTilesetConfig(tileSetPath));

	if (f != NULL)
		fclose(f);
}

WorldAutoTiler::~WorldAutoTiler(){
	AutoTiler::~AutoTiler();
}

FILE* WorldAutoTiler::loadWorldConfig(FILE* file)
{
	// comrprobamos que existe el archivo
	if (file == NULL)
		return NULL;

	// nº Decoraciones
	int nDeco;
	if (fscanf_s(file, "%d", &nDeco) < 1)
		return NULL;

	// Cargamos los campos auxiliares de cada decoración
	for (int i = 0; i < nDeco; i++)
		if (!loadWorldDeco(file))
			return NULL;

	return file;
}

bool WorldAutoTiler::loadWorldDeco(FILE* file)
{
	// comrprobamos que existe el archivo
	if (file == NULL)
		return false;

	// idDecoración, proximidad
	int idDeco, near;
	if (fscanf_s(file, "%d %d", &idDeco, &near) < 2)
		return NULL;

	// añandimos los campos a la decoración
	decorationList.at(idDeco).near = (Decoration::DecorationNear) near;

	return true;
}

Decoration* WorldAutoTiler::getDecoDunEntrance(int floorId)
{
	Decoration* decoEntrance = NULL;

	// buscamos una entrada a mazmorra de 6 tiles
	std::vector<Decoration::DecorationData>::iterator it = decorationList.begin();
	while (it != decorationList.end() && decoEntrance == NULL)
	{
		if (it->height * it->width == 6)
			decoEntrance = new Decoration(*it);
		else
			it++;
	}

	// devolvemos la entrada
	return decoEntrance;
}