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

#include "Image.h"

Image::Image(std::string path, GfxEngine* gfxEngine, bool transparent, bool write)
{
    // Almacenamos valores necesarios
    writeable = write;
    this->transparent = transparent;
    this->gfxEngine = gfxEngine;
    this->path = path;

	// Se prepara el logger
	logger = Logger::Instance();

	// Todavía no se ha cargado nada
	loaded = false;
	wpic = NULL;
	rpic = NULL;

    // Cargamos la imagen en memoria
    if (!loadImage(path, transparent))
	{
		// Si falla, debemos procurar que no explote el asunto
	}
}

Image::Image(int width, int height, GfxEngine* gfxEngine, bool transparent, bool write)
{
    // Almacenamos valores necesarios
    writeable = write;
    this->transparent = transparent;
    this->gfxEngine = gfxEngine;
    this->path = "";

	// No hemos cargado nada
	loaded = false;

    // Creamos la imagen con el tamaño dado
    wpic = gfxEngine->createImage(width, height);

    // Si la creación de la imagen no ha fallado, asociamos la imagen creada
    // a la imagen que se va a pintar por pantalla
    if (wpic != NULL)
    {
        rpic = new sf::Sprite(wpic->GetImage());
    }
	else 
	{
		// Si la creación falla no tenemos superficies ni podemos escribir.
		rpic = NULL;
		writeable = false;
	}
}

Image::~Image()
{
	// si hemos cargado algún archivo, lo liberamos
	if (loaded)
		gfxEngine->deleteImage(path);

    // borramos la imagen de sólo lectura si no es vacía
    if (rpic != NULL) delete rpic;

    // borramos la imagen modificable si no es vacía
    if (wpic != NULL) delete wpic;

	//Logger::DestroyInstance();
}

bool Image::loadImage(std::string path, bool transparent)
{
	// Liberamos la imagen antigua si la hubiera
	if (loaded)
		gfxEngine->deleteImage(path);

	// Borramos las superficies si las tuviéramos
	if (rpic != NULL) delete rpic;
	if (wpic != NULL) delete wpic;

    // Cargamos la imagen gracias al motor gráfico.
	// Se trata de cargar la imagen
	sf::Image* img = gfxEngine->loadImage(path, transparent);

	// Si la carga falla
	if (img == NULL)
	{
		// No tenemos nada
		rpic = NULL;
		wpic = NULL;
		loaded = false;
		// Y se avisa de ello
		logger->log(std::string("Image::loadImage - No se ha podido cargar el archivo \"" + path + "\".").c_str());
		return false;
	};

    rpic = new sf::Sprite(*img);

    // Si el proceso no ha fallado y la imagen es de escritura,
    // actualizamos el elemento renderizable.
    if (rpic != NULL)
    {
		loaded = true;

        if (writeable)
        {
            // Obtenemos las dimensiones de la imagen original
            sf::Vector2f size = rpic->GetSize();

            // Creamos el elemento sobreescribible
            wpic = new sf::RenderImage();

            // Lo inicializamos a una imagen vacía de tamaño el de la imagen cargada
            // Si el proceso no falla, procedemos a actualizar la imagen de escritura
            if (wpic->Create((unsigned int) size.x, (unsigned int) size.y))
            {
                // Pintamos la imagen cargada sobre la imagen de escritura
                wpic->Draw(*rpic);

                // Actualizamos el pintado
                wpic->Display();
            }
        }

		return true;
     }
	else
	{
		logger->log(std::string("Image::loadImage - No se ha podido procesar el archivo \"" + path + "\".").c_str());
		return false;
	}
}

void Image::refresh()
{
	// Sólo es necesario actualizar si la imagen admite escritura
	if (!writeable) return;

    // Actualizamos los cambios realizados sobre la imagen modificable
    wpic->Display();

    // Asignamos la imagen actual a la imagen a pintar (rpic)
    rpic->SetImage(wpic->GetImage());
}

int Image::getWidth()
{
	// Si no hay imagen, devuelve ancho 0
	if (rpic != NULL)
		return (int) rpic->GetSize().x;
	else 
		return 0;
}

int Image::getHeigth()
{
	// Si no hay imagen, devuelve alto 0
	if (rpic != NULL)
		return (int) rpic->GetSize().y;
	else
		return 0;
}

std::string Image::getPath()
{
    return path;
}

sf::RenderImage* Image::getSurfaceW()
{
    return wpic;
}

sf::Sprite* Image::getSurfaceR()
{
    return rpic;
}