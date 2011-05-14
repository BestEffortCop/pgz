#include "GameEntity.h"
#include "PGZGame.h"

GameEntity::GameEntity(int x, int y, Game* game, GameState* world):Entity(x,y,game,world)
{
	gfxShadow = NULL;
	size = sNone;
	paused = false;
};

GameEntity::~GameEntity()
{
	if (gfxShadow != NULL)
		delete gfxShadow, gfxShadow = NULL;
};

void GameEntity::initShadow(Size s)
{
	if (gfxShadow != NULL)
	{
		delete gfxShadow;
		gfxShadow = NULL;
	}

	// Si no nos pasan tamaño, suponemos que ya está puesto
	// y si no está puesto, es que no se quiere sombra
	if (s == sNone && size == sNone)
		return;
	else if (s == sNone && size != sNone)
		s = size;
	
	
	gfxShadow = new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getShadowGfxPath(s), game->getGfxEngine());

	/*switch (s)
	{
	case sNone:
		break;
	case sSmall:
		// Las rutas las dará dbi en algún momento
		gfxShadow = new Stamp("data/graphics/shadow-s.png", game->getGfxEngine());
		break;
	case sMedium:
		gfxShadow = new Stamp("data/graphics/shadow-m.png", game->getGfxEngine());
		break;
	default:
		break;
	}*/

	if (gfxShadow != NULL)
		gfxShadow->setAlpha(0.7f);
};

void GameEntity::onRender()
{
	if (gfxShadow != NULL && mask != NULL && visible && enabled)
	{
		gfxShadow->render(x + (mask->xoffset + mask->width / 2 - ((Stamp *)gfxShadow)->getWidth()/2), y + (mask->yoffset + mask->height - ((Stamp *)gfxShadow)->getHeight()/2 - 2));
	}

	if (visible && enabled)
		Entity::onRender();
};

void GameEntity::pause()
{
	paused = true;
};

void GameEntity::unpause()
{
	paused = false;
};

bool GameEntity::isPaused()
{
	return paused;
};