#include "TiledEntity.h"

TiledEntity::TiledEntity(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
{
	tileset = NULL;
	tileId = NULL;
	tilesType = NULL;
	nTiles = 0;
	width = 0;
	height = 0;
	solid = true;
	depth = y;
};

TiledEntity::~TiledEntity()
{
	delete tilesType;
}


void TiledEntity::init(TileSet* tset, short tile, short* tilesType, short nTiles, short width)
{
	this->nTiles = nTiles;
	this->width = width;
	this->tileset = tset;
	this->tileId = tile;
	this->tilesType = tilesType;
	this->height = nTiles / width;

	// Creamos la grid donde guardaremos los tilesType
	int** grid = new int*[width];
	for (int i = 0; i < width; i++)
		grid[i] = new int[height];

	// Rellenamos la grid
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			grid[j][i] = tilesType[i*width + j];

	mask = new SolidGrid(x, y, grid, tileset->getTileW()*2, tileset->getTileH()*2, width, height);
	
	/*if (!foreground)
		mask = new MaskBox(x, y, tileset->getTileW()*2, tileset->getTileH()*2, "semisolid");
	else
		depth += 1;
		setCollidable(false);*/

	// Buscamos base y sexo
	bool found = false;
	int i = 0;
	while (i < height && !found)
	{
		found |= (grid[0][i] != 0);
		i++;
	}

	if (found)
	{
		// Base encontrada
		i--;
		depth = y+tileset->getTileH()*2*i;
	}
	else
		depth = y;
};

void TiledEntity::onRender()
{
	if (!visible || !enabled || tileset == NULL)
		return;

	int tw = tileset->getTileW() * 2, th = tileset->getTileH() * 2;	// multiplicamos x2 para conseguir tamaño 16, que es el tamaño de las decoraciones
	game->getGfxEngine()->renderPart(tileset->getImg(), x, y, 
		tw*(tileId % (tileset->getColumns()/2)), th*(tileId / (tileset->getColumns()/2)), width * tw, height * th);
};