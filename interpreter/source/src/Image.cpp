#include "Image.h"

Image::Image(std::string path, GfxEngine* gfxEngine, bool transparent, bool write)
{
    // Almacenamos valores necesarios
    writeable = write;
    this->transparent = transparent;
    this->gfxEngine = gfxEngine;
    this->path = path;

    // Cargamos la imagen en memoria
    loadImage(path, transparent);

}

Image::Image(GfxEngine* gfxEngine, int width, int height, bool transparent, bool write)
{
    // Almacenamos valores necesarios
    writeable = write;
    this->transparent = transparent;
    this->gfxEngine = gfxEngine;
    this->path = "";

    // Creamos la imagen con el tamaño dado
    wpic = gfxEngine->createImage(width, height);

    // Si la creación de la imagen no ha fallado, asociamos la imagen creada
    // a la imagen que se va a pintar por pantalla
    if (wpic != NULL)
    {
        rpic = new sf::Sprite(wpic->GetImage());
    }
}

Image::~Image()
{
    // Si la imagen tiene una ruta, debemos borrarla
    // comprobando si estaba en memoria
    if (path != "")
    {
        // Si la imagen estaba cargada en memoria y no quedan referencias a ella, se borrará.
        // Si no estaba en memoria o si lo estaba pero aún quedan referencias a ella, no se borrará.
        // En cualquier caso, los elementos particulares de renderizado de esta clase serán borrados.
        gfxEngine->deleteImage(path);

        gfxEngine->freeImage(this);
    }
    // Si la imagen no tiene una ruta, borramos directamente
    // todos sus elementos.
    else
    {
        gfxEngine->deleteImage(pic);
        gfxEngine->freeImage(this);
    }
}

void Image::loadImage(std::string path, bool transparent)
{
    // Cargamos la imagen gracias al motor gráfico.
    pic = gfxEngine->loadImage(path);
    if (pic != NULL)
        rpic = new sf::Sprite(*pic);

    // Si el proceso no ha fallado y la imagen es de escritura,
    // actualizamos el elemento renderizable.
    if (rpic != NULL)
    {
        if (writeable)
        {
            // Obtenemos las dimensiones de la imagen original
            sf::Vector2f size = rpic->GetSize();

            // Creamos el elemento sobreescribible
            wpic = new sf::RenderImage();

            // Lo inicializamos a una imagen vacía de tamaño el de la imagen cargada
            // Si el proceso no falla, procedemos a actualizar la imagen de escritura
            wpic = gfxEngine->createImage(size.x, size.y);
            if (wpic != NULL)
            {
                // Pintamos la imagen cargada sobre la imagen de escritura
                wpic->Draw(*rpic);

                // Actualizamos el pintado
                wpic->Display();
            }
        }
     }
}

void Image::refresh()
{
    // Actualizamos los cambios realizados sobre la imagen modificable
    wpic->Display();

    // Asignamos la imagen actual a la imagen a pintar (rpic)
    rpic->SetImage(wpic->GetImage());
}

int Image::getWidth()
{
    return rpic->GetSize().x;
}

int Image::getHeigth()
{
    return rpic->GetSize().y;
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

