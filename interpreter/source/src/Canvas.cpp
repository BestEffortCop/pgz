#include "Canvas.h"

//! Construye el Canvas con los parámetros indicados
Canvas::Canvas(int x, int y, int width, int height, GfxEngine* gfxEngine) : Graphic()
{
	// Se preparan los atributos
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
	this->gfxEngine = gfxEngine;
	
	// Se crea el lienzo a partir de una imagen para escritura
	img = new Image(gfxEngine, width, height, true, true);
}

//! Destruye el Canvas (no los gráficos que lo forman)
Canvas::~Canvas()
{
	if (img != NULL)
		delete img, img = NULL;
};

//! Obtiene el ancho del Canvas
int Canvas::getW() 
{ 
	return w; 
};

//! Obtiene el alto del Canvas
int Canvas::getH() 
{ 
	return h;
};

//! Dibuja un  objeto en el lienzo, en la posición indicada
void Canvas::draw(Graphic* gfx, int x, int y)
{
	// El gfx ha de ser válido
	if (gfx == NULL)
		return;

	// Se establece mi imagen como destino del render
	gfxEngine->setRenderTarget(img);
	// Se pide al gfx que se dibuje
	gfx->render(x, y);
	// Se resetea el destino del render
	gfxEngine->resetRenderTarget();
};

//! Dibuja un  objeto en el lienzo, en la posición indicada
void Canvas::drawPart(Graphic* gfx, int x, int y, int xOrigin, int yOrigin, int w, int)
{
	// El gfx debe ser válido
	if (gfx == NULL)
		return;
	// El gfx debe tener algo que renderizar
	Image* i = gfx->getImage();
	if (i == NULL)
		return;
	// Render sobre mi imagen
	if (w > 0 && h > 0)
		gfxEngine->renderPart(i, x, y, xOrigin, yOrigin, w, h, img);
	else
		gfxEngine->render(i, x, y, img);
};

//! Rellena el lienzo con el color indicado
void Canvas::clear(Color c)
{
	gfxEngine->clearImage(img, c);
};

//! Renderiza el Canvas
void Canvas::render(int x, int y)
{
	gfxEngine->render(img, x, y);
};