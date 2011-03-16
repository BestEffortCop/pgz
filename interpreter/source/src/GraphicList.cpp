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