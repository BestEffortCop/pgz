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
};

GfxEngine::~GfxEngine()
{
	// Se borra el SurfaceManager
	delete surfaceManager;
	surfaceManager = NULL;

	// Se borran las ventanas
	if (appScreen != NULL)
		delete appScreen, appScreen = NULL;

	if (gameScreen != NULL)
		delete gameScreen, gameScreen = NULL;

	// Punteros a NULL
	currentRenderTarget = NULL;

	// Se borra el color de fondo
	if (screenBgColor != NULL)
		delete screenBgColor, screenBgColor = NULL;
};

bool GfxEngine::init(sf::RenderWindow* window)
{
	// Si la ventana es inválida falla el init
	if (window == NULL)
		return false;

	// Si no tenemos RenderImages disponibles, falla el init
	if (!sf::RenderImage::IsAvailable())
		return false;

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
		return false;

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
	// Tratamos de cambiar el tamaño de la ventana de app
	appScreen->Create(sf::VideoMode(width, height, screenBPP), "");

	// Almacenamos los nuevos valores
	screenW = width;
	screenH = height;

	return true;
};

bool GfxEngine::setGameScreenSize(int width, int height)
{
	// No hace falta comprobar que quepa en pantalla
	// eso se hace desde fuera

	// Re-creamos la parte gráfica de la gameScreen con los nuevos parámetros
	if (gameScreen->Create(width, height))
	{
		// Si fallan las nuevas dimensiones
		// dejamos todo como estaba
		gameScreen->Create(gameW, gameH);
		return false;
	}

	// Actualizamos a los nuevos parámetros
	gameW = width;
	gameH = height;

	return true;
};

bool GfxEngine::setGameScreenScale(int hFactor, int vFactor)
{
	// Se cambia el escalado sólo si cabe en pantalla
	if (gameW*hFactor > screenW || gameH*vFactor > screenH)
		return false;
	else
	{
		// Si cabe, actualizamos valores
		gameScaleH = hFactor;
		gameScaleV = vFactor;

		// Actualizamos la posición de la gameScreen
		centerGameScreen();
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

void GfxEngine::setScreenBackgroundColor(Color* color)
{
	// Se establecen los parámetros indicados
	// al color de fondo
	screenBgColor->r = color->r;
	screenBgColor->g = color->g;
	screenBgColor->b = color->b;
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
	/* Pendiente de Image, descomentar cuando toque */

	// Si el destino no admite escritura, no se hace nada
	if (target->getSurfaceW() == NULL)
		return;
	else
	{
		// En otro caso, se cambia el destino del render
		currentRenderTarget = target->getSurfaceW();
	}

	/**/
	return;
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
		return;

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

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
		return;

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

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
		return;

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);
	// Y se amplía según se indique
	spr.SetScale((float) xScale, (float) yScale);

	// Renderizado
	target->Draw(spr);
};

//! Renderiza una Image aplicando efectos
void GfxEngine::renderExt(Image* image, int x, int y, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
		return;

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);
	// Se aplican los efectos indicados
	// Tintado
	spr.SetColor(sf::Color((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b, (sf::Uint8) (255*alpha)));
	// Transparencia ??

	// Renderizado
	target->Draw(spr);
};

//! Renderiza parte de una Image aplicando efectos
void GfxEngine::renderPartExt(Image* image, int x, int y, int xOrigin, int yOrigin, int width, int height, Color color, float alpha, float scaleH, float scaleV, float rotation, Image* dest)
{
	// Destino del render
	sf::RenderTarget* target;

	// El elemento a renderizar ha de exisitir
	if (image == NULL || image->getSurfaceR() == NULL)
		return;

	// Si se no se especifica el destino, se dibuja sobre
	// el destino actual del render por defecto
	if (dest == NULL)
		target = currentRenderTarget;
	else target = dest->getSurfaceW();

	// Se crea un clon del sprite a renderizar en la posición indicada
	sf::Sprite spr(*image->getSurfaceR());
	spr.SetPosition((float) x, (float) y);
	// Se coge la parte indicada
	spr.SetSubRect(sf::IntRect(xOrigin, yOrigin, width, height));
	// Se aplican los efectos indicados
	// Tintado
	spr.SetColor(sf::Color((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b, (sf::Uint8) (255*alpha)));
	// Transparencia ??

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
		return;

	// Y debe admitir escrituras
	if (image->getSurfaceW() == NULL)
		return;

	image->getSurfaceW()->Clear(sf::Color((sf::Uint8) color.r, (sf::Uint8) color.g, (sf::Uint8) color.b));
};

sf::RenderImage* GfxEngine::createImage(int w, int h)
{
	// Este método construye imágenes sobre las que se escribirá

	// Se instancia una RenderImage
	sf::RenderImage* img = new sf::RenderImage();
	// Se prepara para escritura
	img->Create(w, h);

	// Se devuelve
	return img;
};

sf::Image* GfxEngine::loadImage(std::string fname)
{
	// Si ya se había cargado el archivo
	if (surfaceManager->isLoaded(fname))
		// Se devuelve la imagen ya cargada
		return surfaceManager->getSurface(fname);
	else
	{
		// Si no se ha cargado, se construye una nueva imagen
		sf::Image* img = new sf::Image();

		// Se carga el archivo
		if (img->LoadFromFile(fname))
		{
			// Se hace transparente el magenta
			img->CreateMaskFromColor(sf::Color::Magenta);

			// Se almacena en el SurfaceManager
			surfaceManager->setSurface(fname, img);

			// Se devuelve el puntero
			return img;
		}
		// Si falla la carga, no hay nada que devolver
		else return NULL;
	}
};

bool GfxEngine::deleteImage(std::string fname)
{
	// La imagen ha de estar cargada en memoria
	if (!surfaceManager->isLoaded(fname))
		// Si no lo está, no puede borrarse
		return false;
	else
	{
		// Si lo está, indicamos que un elemento ha dejado de necesitarla
		// Se coge el puntero para borrarla si fuera necesaria
		sf::Image* img = surfaceManager->getSurface(fname);
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
	return false;
};