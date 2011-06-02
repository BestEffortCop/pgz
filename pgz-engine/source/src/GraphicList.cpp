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

#include "GraphicList.h"
#include "Canvas.h"

GraphicList::GraphicList(GfxEngine* gfxEngine) : Graphic()
{
	// Se guarda el puntero a GfxEngine
	this->gfxEngine = gfxEngine;

	// Se inicializa la lista de gráficos
	gfxList.clear();
};

bool GraphicList::addGraphic(string fname, Graphic* gfx, int position)
{
	// Falta comprobar si el fname ya estaba en la lista (O(n)...)

	// Si no se indica posición, se añade al final
	if (position == -1)
		gfxList.push_back(make_pair(fname, gfx));
	else
		// En otro caso, se inserta en donde pidan
		gfxList.insert(gfxList.begin()+position, make_pair(fname, gfx));

	return true;
};

Graphic* GraphicList::getGraphic(string name)
{
	// Se busca el gráfico asociado a name
	// Iterando el vector
	vector<pair<string, Graphic*> >::iterator it = gfxList.begin();
	// Hasta terminar
	while (it != gfxList.end())
	{
		// O encontrarlo
		if (it->first == name)
			// En cuyo caso se devuelve
			return it->second;
		// Se sigue iterando
		it++;
	};

	// Si no aparece, se devuelve null
	return NULL;
};

Graphic* GraphicList::getGraphic(int position)
{
	return gfxList[position].second;
};

void GraphicList::update()
{
	// Se recorre el vector
	vector<pair<string, Graphic*> >::iterator it = gfxList.begin();
	// Hasta terminar
	while (it != gfxList.end())
	{
		// Actualizando cada gráfico
		it->second->update();
		it++;
	};
};

void GraphicList::refresh()
{
	// Se recorre el vector
	vector<pair<string, Graphic*> >::iterator it = gfxList.begin();
	// Hasta terminar
	while (it != gfxList.end())
	{
		// Renderizando cada gráfico
		if (Canvas* c = dynamic_cast<Canvas *> (it->second))
			c->refresh();
		it++;
	};
};

void GraphicList::render(int x, int y)
{
	// Se recorre el vector
	vector<pair<string, Graphic*> >::iterator it = gfxList.begin();
	// Hasta terminar
	while (it != gfxList.end())
	{
		// Renderizando cada gráfico
		it->second->render(x, y);
		it++;
	};
};

void GraphicList::addAnim(string name, vector<int>* frameList, int framesPerStep, bool loop, int position)
{
};