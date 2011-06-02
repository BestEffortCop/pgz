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
	img = new Image(width, height, gfxEngine, true, true);
}

//! Destruye el Canvas (no los gráficos que lo forman)
Canvas::~Canvas()
{
	// Se borra el lienzo si no es nulo
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

	// Nuestra imagen debe exisitir para dibujar sobre ella
	if (img == NULL)
		return;

	// Se establece mi imagen como destino del render
	gfxEngine->setRenderTarget(img);
	// Se pide al gfx que se dibuje
	gfx->render(x, y);
	// Se resetea el destino del render
	gfxEngine->resetRenderTarget();
};

/*//! Dibuja un  objeto en el lienzo, en la posición indicada
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
};*/

//! Actualiza la imagen del Canvas para reflejar los cambios
void Canvas::refresh()
{
	// Se refresca la imagen si está creada
	if (img != NULL)
		img->refresh();
}

//! Rellena el lienzo con el color indicado
void Canvas::clear(Color c)
{
	// Se rellena el lienzo
	gfxEngine->clearImage(img, c);
};

//! Renderiza el Canvas
void Canvas::render(int x, int y)
{
	// Renderiza el lienzo con los parámetros indicados
	gfxEngine->renderExt(img, x+originX, y+originY, *color, alpha, scaleH, scaleV, rotation, NULL, originX, originY);
};