#include "Teleporter.h"


Teleporter::Teleporter(MapLocation m, int x, int y, Game* g, GameState* gs, int w, int h) : Entity(x, y, g, gs)
{
	mask = new MaskBox(x, y, w, h, "teleporter");
	//graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
	solid = false;

	destination = m;
	teleportType = STEP;
	transitionEffect = FADE;
}

Teleporter::~Teleporter()
{
}

void Teleporter::onCollision(CollisionPair pair, Entity* other)
{
	if (pair.b == "player")
	{
		if (teleportType == STEP || teleportType == LEFT || teleportType == RIGHT || teleportType == UP || teleportType == DOWN)
		{
			((PGZGame*) game)->controller->teleportTo(destination, (Player*) other, transitionEffect, false);
		}
		else if (teleportType == INSIDE)
		{
			if (isInside(other->mask))
			{
				((PGZGame*) game)->controller->teleportTo(destination, (Player*) other, transitionEffect, false);
			}
		}
	}
}

void Teleporter::setTeleportType(TeleportType type)
{
	teleportType = type;
	if (type == LEFT)
	{
		mask->xoffset = 0;
		mask->yoffset = 0;
		mask->width = 2;
		mask->height = 16;
	}
	else if (type == RIGHT)
	{
		mask->xoffset = 14;
		mask->yoffset = 0;
		mask->width = 2;
		mask->height = 16;
	}
	else if (type == UP)
	{
		mask->xoffset = 0;
		mask->yoffset = 0;
		mask->width = 16;
		mask->height = 2;
	}
	else if (type == DOWN)
	{
		mask->xoffset = 0;
		mask->yoffset = 14;
		mask->width = 16;
		mask->height = 2;
	}
	else if (type == DUNGEONFINAL)
	{
		graphic = new Stamp("data/basic-gfx/teleport.png", game->getGfxEngine());
		teleportType = INSIDE;
	}
}

void Teleporter::setTransition(TransitionEffect te)
{
	transitionEffect = te;
}

bool Teleporter::isInside(Mask* mask)
{
	//Calculamos los vertices superior izquierdo e inferior derecho
	// Vértice superior izquierdo
	int x1 = mask->x + mask->xoffset;
	int y1 = mask->y + mask->yoffset;
	// Vértice inferior derecho
	int x2 = mask->x + mask->xoffset + mask->width;
	int y2 = mask->y + mask->yoffset + mask->height;

	if ((x1 >= this->mask->x + this->mask->xoffset) 
		&& (x2 <= this->mask->x + this->mask->xoffset + this->mask->width) 
		&& (y1 >= this->mask->y + this->mask->yoffset) 
		&& (y2 <= this->mask->y + this->mask->yoffset + this->mask->height))
		return true;

	return false;
}

void Teleporter::onRender()
{
	if (visible && enabled && mask != NULL)
		if (graphic == NULL)
			game->getGfxEngine()->renderRectangle(x+mask->xoffset, mask->yoffset+y, mask->width, mask->height, Color(200, 10, 215));
		else
			graphic->render(x, y);
};