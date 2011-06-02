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
#ifndef __GFXLIST_H__
#define __GFXLIST_H__

#include "GfxEngine.h"
#include "Graphic.h"
#include <vector>

using namespace std;

//! Miembro de la familia de Graphic que facilita el trabajo con varios gráficos simultaneamente
/*!
	Agrupa varios gráficos no necesariamente del mismo tipo, simplificando el mantenimiento
	y el renderizado de todos en conjunto.

	Los gráficos se almacenan en posiciones determinadas, 
	asignándoles un nombre de forma que se puede trabajar
	individualmente o en conjunto.

	Los Graphic que se añadan al GraphicList no deben borrarse mientras dure
	el ciclo de vida de este, al término del cual se eliminarán automáticamente.
*/
class GraphicList : public Graphic
{
private:
	GfxEngine* gfxEngine;
	vector<pair<string, Graphic*> > gfxList;
public:

	//! Construye el GraphicList
	GraphicList(GfxEngine* gfxEngine);

	//! Añade un gráfico, asignándole un nombre, en la posición indicada
	bool addGraphic(string name, Graphic* gfx, int position = -1);

	//! Recupera un gráfico para se modificado individualmente de forma rápida
	Graphic* getGraphic(string name);

	//! Recupera un gráfico para se modificado individualmente de forma rápida
	Graphic* getGraphic(int position);

	//! Update
	void update();

	// Refresh
	void refresh();

	//! Render
	void render(int x, int y);

	/* Métodos de spritemap */
	
	//! Añadir animación
	void addAnim(string name, vector<int>* frameList, int framesPerStep, bool loop, int position = -1);

	//! Reproducir animación
	void playAnim(string name, int framesPerStep, bool loop, int position = -1);
};

#endif