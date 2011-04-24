#include "GameEntity.h"


GameEntity::GameEntity(int x, int y, Game* game, GameState* world):Entity(x,y,game,world)
{
	gfxShadow = NULL;
	size = sNone;
};

GameEntity::~GameEntity()
{
	if (gfxShadow != NULL)
		delete gfxShadow, gfxShadow = NULL;
};

void GameEntity::initShadow(Size s)
{
	// Si no nos pasan tamaño, suponemos que ya está puesto
	// y si no está puesto, es que no se quiere sombra
	if (s == sNone && size == sNone)
		return;
	else if (size != sNone)
		s = size;
	
	switch (s)
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
	}

	if (gfxShadow != NULL)
		gfxShadow->setAlpha(0.7);
};

void GameEntity::onRender()
{
	if (gfxShadow != NULL && mask != NULL)
	{
		gfxShadow->render(x + (mask->xoffset + mask->width / 2 - ((Stamp *)gfxShadow)->getWidth()/2), y + (mask->yoffset + mask->height - ((Stamp *)gfxShadow)->getHeight()/2 - 2));
	}

	Entity::onRender();
};