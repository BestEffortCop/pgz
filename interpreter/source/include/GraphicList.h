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