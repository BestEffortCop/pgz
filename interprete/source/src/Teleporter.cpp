#include "Teleporter.h"


Teleporter::Teleporter(MapLocation m, int x, int y, Game* g, GameState* gs, int w, int h) : Entity(x, y, g, gs)
{
	mask = new MaskBox(0, 0, w, h, "teleporter");
	graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
	solid = false;

	destination = m;
}

Teleporter::~Teleporter()
{
}

void Teleporter::onCollision(CollisionPair pair, Entity* other)
{
	if (pair.b == "player")
	{
		((PGZGame*) game)->controller->teleportTo(destination, (Player*) other, FADE, false);
	}
}