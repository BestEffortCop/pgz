#include "TiledEntity.h"

TiledEntity::TiledEntity(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
{
	tileset = NULL;
	tileId = NULL;
	solid = true;
	depth = y;
};

void TiledEntity::init(TileSet* tset, int tile, bool foreground)
{
	tileset = tset;
	tileId = tile;

	if (!foreground)
		mask = new MaskBox(x, y, tileset->getTileW(), tileset->getTileH(), "semisolid");
	else
		depth += 1;
		setCollidable(false);
};

void TiledEntity::onRender()
{
	if (tileset == NULL)
		return;

	int tw = tileset->getTileW(), th = tileset->getTileH();
	game->getGfxEngine()->renderPart(tileset->getImg(), x, y, 
		tw*(tileId % tileset->getColumns()), th*(tileId / tileset->getColumns()), tw, th);
};