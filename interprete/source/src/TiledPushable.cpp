#include "TiledPushable.h"

TiledPushable::TiledPushable(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), iPushable()
{
	tileset = new FriendlyTileMap(16,16,game->getGfxEngine());
	mask = new MaskBox(x, y, tileset->getTileWidth(), tileset->getTileHeight(), "semisolid");
	tileId = NULL;

	iPushable::init(1);
};

void TiledPushable::init(std::string tset, int tile, bool foreground)
{
	//Asigno el tileset
	tileset->setTileSet(tset);
	tileId = tile;
	
	//Creo el mapa del tileset
	int**map = (int**) malloc(sizeof(int*));
	map[0] = (int*) malloc(sizeof(int));
	map[0][0] = tile;
	tileset->setMap(map, 1, 1);

	//Asigno el tipo a la mascara
	mask->type = "pushable";

	//Asigno los valores a las distintas propiedades
	type = "pushable";
	collidable = true;
	solid = true;
	depth = y;
};

TiledPushable::~TiledPushable()
{
	Entity::~Entity();
}

void TiledPushable::onStep()
{
	depth = y;
}

void TiledPushable::onRender()
{
	if (tileset == NULL)
		return;

	tileset->render(x,y);
};