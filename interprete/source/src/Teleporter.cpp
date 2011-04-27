#include "Teleporter.h"


Teleporter::Teleporter(MapLocation m, int x, int y, Game* g, GameState* gs, int w, int h) : Entity(x, y, g, gs)
{
	mask = new MaskBox(x, y, w, h, "teleporter");
	graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
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
		if (teleportType == STEP)
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

	if ((x1 >= this->mask->x + mask->xoffset) && (x2 <= this->mask->x + mask->xoffset + this->mask->width) && (y1 >= this->mask->y + mask->yoffset) && (y2 <= this->mask->y + mask->yoffset + this->mask->height))
		return true;

	return false;
}