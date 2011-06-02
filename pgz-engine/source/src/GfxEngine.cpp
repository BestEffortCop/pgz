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

#include "GfxEngine.h"

GfxEngine::GfxEngine(int screenw, int screenh, int screenbpp, int gameW, int gameH, int zoom)
{
	/*
	   Cogemos dimensiones, profundidad de color y color de fondo
	   de la ventana de aplicación
	*/
	screenW = screenw;
	screenH = screenh;
	screenBPP = screenbpp;
	screenBgColor = new Color(0, 0, 0);

	targetScreenW = screenW;
	targetScreenH = screenH;
	targetBPP = screenBPP;

	fullScreenMode = false;
	windowTitle = "";

	/* Cogemos dimensiones de la ventana del juego */

	// Por defecto es igual a la ventana de la aplicación
	if (gameW <= 0)
		this->gameW = screenW;
	else this->gameW = gameW;

	if (gameH <= 0)
		this->gameH = screenH;
	else this->gameH = gameH;

	// Factor de ampliación
	// Si es demasiado grande o no nos lo indican, lo ponemos a 1
	if (zoom < 1 || this->gameW*zoom > screenW || this->gameH*zoom > screenH)
		gameScaleH = 1, gameScaleV = 1;
	else gameScaleH = zoom, gameScaleV = zoom;

	// Con los datos de las dos ventanas, centramos la de juego
	// sobre la de aplicación
	centerGameScreen();

	// Punteros a null por ahora
	appScreen = NULL;
	gameScreen = NULL;
	currentRenderTarget = NULL;

	// Instanciamos el SurfaceManager
	surfaceManager = new SurfaceManager();

	// Se obtiene una copia de Logger
	logger = Logger::Instance();
};

GfxEngine::~GfxEngine()
{
	// Se avisa
	logger->log("Se finaliza el Subsistema Gráfico.");

	// Se borra el SurfaceManager
	logger->dlog("\tSe elimina el Surface Manager.");
	delete surfaceManager;
	surfaceManager = NULL;

	// Se borran las ventanas
	logger->dlog("\tSe liberan las ventanas.");
	if (appScreen != NULL)
		delete appScreen, appScreen = NULL;

	if (gameScreen != NULL)
		delete gameScreen, gameScreen = NULL;

	// Punteros a NULL
	currentRenderTarget = NULL;

	// Se borra el color de fondo
	if (screenBgColor != NULL)
		delete screenBgColor, screenBgColor = NULL;

	logger->dlog("\tFinalización efectuada correctamente.");

	//Logger::DestroyInstance();
};

bool GfxEngine::init(sf::RenderWindow* window)
{
	// Se avisa
	logger->log("Se inicializa el subsistema gráfico");

	// Si la ventana es inválida falla el init
	if (window == NULL)
	{
		logger->log("No se pudo inicializar el subsistema gráfico: La ventana de aplicación no existe");
		return false;
	}

	// Si no tenemos RenderImages disponibles, falla el init
	/*if (!sf::RenderImage::IsAvailable())
	{
		logger->log("No se pudo inicializar el subsistema gráfico: El sistema no soporta superficies de escritura");
		return false;
	}*/

	// Cogemos la ventana de la aplicación
	appScreen = window;

	// E instanciamos la parte gráfica con los parámetros indicados
	appScreen->Create(sf::VideoMode(screenW, screenH, screenBPP), "default", sf::Style::Titlebar | sf::Style::Close);

	// Instanciamos la ventana del juego
	gameScreen = new sf::RenderImage();
	// Que es el destino de render por defecto
	currentRenderTarget = gameScreen;
	// Y preparamos la parte gráfica
	if (!setGameScreenSize(gameW, gameH))
	{
		logger->log("No se pudo inicializar el subsistema gráfico: Fallo al preparar la ventana del juego");
		return false;
	}

	return true;
}

/*********************************************************************\
*	Manejo de la ventana del juego y de la ventana de la aplicación	  *
\*********************************************************************/

void GfxEngine::centerGameScreen()
{
	// Se centra la ventana de juego en la ventana de la app
	if (gameW*gameScaleH == screenW)
		gameX = 0;
	else gameX = (screenW/2 - (gameW*gameScaleH)/2);

	if (gameH*gameScaleV == screenH)
		gameY = 0;
	else gameY = (screenH/2 - (gameH*gameScaleV)/2);
};

bool GfxEngine::setScreenSize(int width, int height)
{
	// Si no va a caber la ventana de juego, se cancela la operación
	if (width < gameW * gameScaleH || height < gameH * gameScaleV)
	{
		logger->log("No se pudo cambiar el tamaño de la ventana de aplicación: La ventana del juego no cabría en las nuevas dimensiones");
		return false;
	};

	// Tratamos de cambiar el tamaño de la ventana de app
	appScreen->Create(sf::VideoMode(width, height, screenBPP), "");

	// Almacenamos los nuevos valores
	screenW = width;
	screenH = height;

	// Se centra la ventana de juego en la de aplicación
	centerGameScreen();

	// Se avisa del éxito de la operación
	logger->log("Tamaño de la ventana de la aplicación cambiado correctamente");

	return true;
};

bool GfxEngine::setGameScreenSize(int width, int height)
{
	// Se comprueba que quepa en pantalla con la configuración actual
	if (width * gameScaleH > screenW || height * gameScaleV > screenH)
		return false;

	// Re-creamos la parte gráfica de la gameScreen con los nuevos parámetros
	if (!gameScreen->Create(width, height))
	{
		// Si fallan las nuevas dimensiones
		// dejamos todo como estaba
		bool ok = gameScreen->Create(gameW, gameH);

		if (ok)
			logger->log("No se pudo cambiar el tamaño de la ventana del juego. Se mantiene el tamaño anterior");
		else
			logger->log("No se pudo cambiar el tamaño de la ventana del juego ni volver a la configuración anterior");

		return ok;
	}

	// Actualizamos a los nuevos parámetros
	gameW = width;
	gameH = height;

	// Se centra en la ventana de la aplicación
	centerGameScreen();

	return true;
};

bool GfxEngine::setGameScreenScale(int hFactor, int vFactor)
{
	// Se cambia el escalado sólo si cabe en pantalla
	if (gameW*hFactor > screenW || gameH*vFactor > screenH)
	{
		logger->log("No se pudo cambiar el factor de escalado de la ventana del juego: La ventana del juego no cabría en la de aplicación");
		return false;
	}
	else
	{
		// Si cabe, actualizamos valores
		gameScaleH = hFactor;
		gameScaleV = vFactor;

		// Actualizamos la posición de la gameScreen
		centerGameScreen();

		logger->log("Factor de escalado de la ventana del juego cambiado correctamente");
		return true;
	}
};

int GfxEngine::getScreenWidth()
{
	return screenW;
};

int GfxEngine::getScreenHeight()
{
	return screenH;
};

int GfxEngine::getGameScreenX()
{
	return gameX;
};

int GfxEngine::getGameScreenY()
{
	return gameY;
};

int GfxEngine::getGameScreenWidth()
{
	return gameW;
};

int GfxEngine::getGameScreenHeight()
{
	return gameH;
};

int GfxEngine::getGameScreenScaleH()
{
	return gameScaleH;
};

int GfxEngine::getGameScreenScaleV()
{
	return gameScaleV;
};

void GfxEngine::setScreenBackgroundColor(Color color)
{
	// Se establecen los parámetros indicados
	// al color de fondo
	screenBgColor->r = color.r;
	screenBgColor->g = color.g;
	screenBgColor->b = color.b;
};

Color GfxEngine::getScreenBackgroundColor()
{
	// Se devuelve un clon del color actual
	return Color(screenBgColor->r, screenBgColor->g, screenBgColor->b);
};

/*********************************************************************\
*						Métodos de Renderizado						  *
\*********************************************************************/

//! Establece la Image sobre la que se realizarán los renderizados que no especifiquen destino.
void GfxEngine::setRenderTarget(Image* target)
{
	// Si el destino no admite escritura, no se hace nada
	if (target->getSurfaceW() == NULL)
	{
		logger->log("GfxEngine::setRenderTarget - No se pudo cambiar el destino del render debido a que la imagen indicada no acepta escrituras");
		return;
	}
	else
	{
		// En otro caso, se cambia el destino del render
		currentRenderTarget = target->getSurfaceW();
	}
};

//! Establece la ventana del juego como destino de los renderizados que no especifiquen destino.
void GfxEngine::resetRenderTarget()
{
	currentRenderTarget = gameScreen;
};

//! Renderiza una Image sobre el destino especificado o sobre la ventana del juego si no se especifica.
void GfxEngine::render(Image* image, int x, int y, Image* dest)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
	{
		logger->log("GfxEngine::render - No se pudo realizar el render, ya que el objeto a renderizar no existe");
		return;
	}

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	if (target == NULL)
	{
		logger->log("GfxEngine::render - No se pudo realizar el render, ya que el destino no existe");
		return;
	}

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);

	// Renderizado
	target->Draw(spr);
};

//! Renderiza parte de una Image sobre el destino especificado o sobre la ventana del juego si no se especifica.
void GfxEngine::renderPart(Image* image, int x, int y, int xOrigin, int yOrigin, int width, int height, Image* dest)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
	{
		logger->log("GfxEngine::renderPart - No se pudo realizar el render, ya que el objeto a renderizar no existe");
		return;
	}

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	if (target == NULL)
	{
		logger->log("GfxEngine::renderPart - No se pudo realizar el render, ya que el destino no existe");
		return;
	}

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);
	// Y se coge la parte indicada
	spr.SetSubRect(sf::IntRect(xOrigin, yOrigin, width, height));

	// Renderizado
	target->Draw(spr);
};

//! Renderiza una Image ampliada sobre el destino especificado o sobre la ventana del juego si no se especifica.
void GfxEngine::renderResized(Image* image, int x, int y, int xScale, int yScale, Image* dest)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
	{
		logger->log("GfxEngine::renderResized - No se pudo realizar el render, ya que el objeto a renderizar no existe");
		return;
	}

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();
	
	if (target == NULL)
	{
		logger->log("GfxEngine::renderResized - No se pudo realizar el render, ya que el destino no existe");
		return;
	}

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);
	// Y se amplía según se indique
	spr.SetScale((float) xScale, (float) yScale);

	// Renderizado
	target->Draw(spr);
};

//! Renderiza una Image aplicando efectos
void GfxEngine::renderExt(Image* image, int x, int y, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest, int originX, int originY)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
	{
		logger->log("GfxEngine::renderExt - No se pudo realizar el render, ya que el objeto a renderizar no existe");
		return;
	}

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	if (target == NULL)
	{
		logger->log("GfxEngine::renderExt - No se pudo realizar el render, ya que el destino no existe");
		return;
	}

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);
	// Se aplican los efectos indicados
	// Rotación
	spr.SetOrigin((float) originX, (float) originY);
	spr.SetRotation(rotation);
	// Tintado y transparencia
	spr.SetColor(sf::Color((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b, (sf::Uint8) (255*alpha)));

	// Se amplía según se indique
	spr.SetScale((float) scaleH, (float) scaleV);

	// Renderizado
	target->Draw(spr);
};

//! Renderiza parte de una Image aplicando efectos
void GfxEngine::renderPartExt(Image* image, int x, int y, int xOrigin, int yOrigin, int width, int height, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest, int originX, int originY)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
	{
		logger->log("GfxEngine::renderPartExt - No se pudo realizar el render, ya que el objeto a renderizar no existe");
		return;
	}

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	if (target == NULL)
	{
		logger->log("GfxEngine::renderPartExt - No se pudo realizar el render, ya que el destino no existe");
		return;
	}

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());

	// Se coge la parte indicada
	spr.SetSubRect(sf::IntRect(xOrigin, yOrigin, width, height));
		spr.SetPosition((float) x, (float) y);
	// Se aplican los efectos indicados
	// Rotación
	spr.SetOrigin((float) originX, (float) originY);
	spr.SetRotation(rotation);
	// Tintado y transparencia
	spr.SetColor(sf::Color((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b, (sf::Uint8) (255*alpha)));
	
	// Se amplía según se indique
	spr.SetScale((float) scaleH, (float) scaleV);

	// Renderizado
	target->Draw(spr);
};

//! Renderiza la ventana del juego centrada sobre la ventana de la aplicación, aplicando el escalado correspondiente
void GfxEngine::display()
{
	// Se actualiza la pantalla de juego
	gameScreen->Display();

	// Se rellena la ventana de app con el color de fondo
	appScreen->Clear(sf::Color((sf::Uint8) screenBgColor->r, (sf::Uint8) screenBgColor->g, (sf::Uint8) screenBgColor->b));

	// Se renderiza la pantalla de juego sobre la ventana de app
	// Se crea un sprite a renderizar en la posición indicada
	sf::Sprite spr(gameScreen->GetImage());
	spr.SetPosition((float) gameX, (float) gameY);
	// Y se amplía según se indique
	spr.SetScale((float) gameScaleH, (float) gameScaleV);
	// Render
	appScreen->Draw(spr);

	// Se actualiza la ventana de app
	appScreen->Display();
};

/*********************************************************************\
*						Manejo de Imágenes							  *
\*********************************************************************/

//! Rellena la imagen con el color indicado
void GfxEngine::clearImage(Image* image, Color color)
{
	// La imagen debe ser válida
	if (image == NULL)
	{
		logger->log("GfxEngine::clearImage - Error: La imagen no existe");
		return;
	}

	// Y debe admitir escrituras
	if (image->getSurfaceW() == NULL)
	{
		logger->log("GfxEngine::clearImage - Error: La imagen no admite escritura");
		return;
	}

	image->getSurfaceW()->Clear(sf::Color((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b));
};

sf::RenderImage* GfxEngine::createImage(int w, int h)
{
	// Este método construye imágenes sobre las que se escribirá

	// Se instancia una RenderImage
	sf::RenderImage* img = new sf::RenderImage();
	// Se prepara para escritura
	if (!img->Create(w, h))
		// Si no se puede, se borra la imagen y se devuelve NULL
		logger->log("GfxEngine::createImage - No se pudo crear la imagen"), delete img, img = NULL;
	img->SetSmooth(false);
	// Se devuelve
	return img;
};

sf::Image* GfxEngine::loadImage(std::string fname, bool transparent)
{
	// Si ya se había cargado el archivo
	if (surfaceManager->isLoaded(fname))
	{		
		// Se devuelve la imagen ya cargada
		return surfaceManager->getSurface(fname);
	}
	else
	{
		// Si no se ha cargado, se construye una nueva imagen
		sf::Image* img = new sf::Image();

		// Se carga el archivo
		if (img->LoadFromFile(fname))
		{
			if (transparent)
				// Se hace transparente el magenta
				img->CreateMaskFromColor(sf::Color::Magenta);
			img->SetSmooth(false);
			// Se almacena en el SurfaceManager
			surfaceManager->setSurface(fname, img);

			// Se devuelve el puntero
			return img;
		}
		// Si falla la carga, no hay nada que devolver
		else 
		{
			logger->log(std::string("GfxEngine::loadImage - Error al cargar archivo \"" + fname + "\"").c_str());
			delete img;
			return NULL;
		}
	}
};

bool GfxEngine::deleteImage(std::string fname)
{
	// La imagen ha de estar cargada en memoria
	if (!surfaceManager->isLoaded(fname))
	{
		logger->log(std::string("GfxEngine::deleteImage - Error al liberar imagen \"" + fname + "\": No es competencia de SurfaceManager").c_str());
		// Si no lo está, no puede borrarse
		return false;
	}
	else
	{
		// Si lo está, indicamos que un elemento ha dejado de necesitarla
		// Se coge el puntero para borrarla si fuera necesaria
		sf::Image* img = surfaceManager->getSurface(fname);

		// Como esto añade un enlace a la imagen, se elimina
		// este enlace antes de comprobar si se debe borrar
		surfaceManager->remove(fname);

		// Y ahora se comprueba si se debe borrar
		if (surfaceManager->remove(fname))
		{
			// Si nadie la necesita, se borra
			delete img;
			// Y se avisa de ello
			return true;
		}
		// Si aún se necesita, no se borra
		return false;
	}
};

bool GfxEngine::deleteImage(sf::Image* image)
{
	// La imagen ha de ser válida
	if (image != NULL)
	{
		// Siempre que nos pidan borrar una imagen, habrá que borrarla
		// es tarea del programador comprobar si se puede hacer o no
		delete image;
		return true;
	}
	logger->log("GfxEngine::deleteImage - Imposible liberar una imagen no existente");
	return false;
};

void GfxEngine::renderRectangle(int x, int y, int width, int height, Color color, bool outline, Image* dest)
{
	// Destino del render
	sf::RenderTarget* target;

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	if (target == NULL)
	{
		logger->log("GfxEngine::renderRectangle - No se pudo realizar el render, ya que el destino no existe");
		return;
	}

	// Se prepara el color
	sf::Color c((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b);

	// Si se quiere borde, se prepara
	float outl = 0.0f;
	if (outline)
	{
		// Si hay borde, el relleno es transparente
		outl = 1.0f;
		target->Draw(sf::Shape::Rectangle((float) x, (float) y, (float) width, (float) height, sf::Color(0, 0, 0, 0), outl, c));
	}
	else
		// Si no, el borde es transparente
		target->Draw(sf::Shape::Rectangle((float) x, (float) y, (float) width, (float) height, c, outl, sf::Color(0, 0, 0, 0)));
};

void GfxEngine::clearImageTransparent(Image* image)
{
	if (image == NULL)
	{
		logger->log("GfxEngine::clearImageTransparent - Error: La imagen no existe");
		return;
	}

	// Sólo se puede limpiar si la imagen admite escritura
	if (image->writeable)
		// En cuyo caso se rellena de un color con alpha 0
		image->getSurfaceW()->Clear(sf::Color(0, 0, 0, 0));
	else
		logger->dlog("GfxEngine::clearImageTransparent - Error: La imagen no admite escritura");
};

bool GfxEngine::saveImage(Image* image, std::string fname)
{
	// La imagen debe exisitir
	if (image == NULL)
		return false;
	else
		return image->getSurfaceR()->GetImage()->SaveToFile(fname);
};

bool GfxEngine::setFullscreen(int on)
{
	// Se establece el modo pantalla completa
	if (on)
	{
		// Se obtiene la lista de modos de video válidos en FullScreen
		std::vector<sf::VideoMode> modes = sf::VideoMode::GetFullscreenModes();
		// Buscamos uno válido
		std::vector<sf::VideoMode>::iterator it =  modes.end();
		sf::VideoMode aMode;
		bool found = false;
		while (it > modes.begin() && !found)
		{
			it--;
			aMode = (*it);
			if (aMode.IsValid() && aMode.Width >= screenW && aMode.Height >= screenH && aMode.BitsPerPixel == targetBPP)
				found = true;
		}
		if (found)
		{
			screenW = (*it).Width;
			screenH = (*it).Height;
			screenBPP = (*it).BitsPerPixel;
			appScreen->Create(sf::VideoMode(screenW, screenH, screenBPP), "", sf::Style::Fullscreen);

			logger->log("Cambiado a modo pantalla completa con éxito");
			fullScreenMode = true;
		}
		else
		{
			logger->log("No se pudo cambiar al modo pantalla completa");
			return false;
		}
	}
	else
	{
		appScreen->Create(sf::VideoMode(targetScreenW, targetScreenH, targetBPP), "");
		screenW = targetScreenW;
		screenH = targetScreenH;
		screenBPP = targetBPP;
		
		// Se avisa del éxito de la operación
		logger->log("Cambiado a modo ventana con éxito");
		fullScreenMode = false;
	}

	// Se centra la ventana de juego en la de aplicación
	centerGameScreen();

	return true;
};

bool GfxEngine::setWindowTitle(std::string title)
{
	appScreen->SetTitle(title);
	windowTitle = title;
	return true;
};

bool GfxEngine::getFullscreen()
{
	return fullScreenMode;
};

std::string GfxEngine::getWindowTitle()
{
	return windowTitle;
};