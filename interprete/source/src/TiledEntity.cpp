#include "TiledEntity.h"

TiledEntity::TiledEntity(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
{
	tileset = NULL;
	tilesId = NULL;
	tilesType = NULL;
	nTiles = 0;
	width = 0;
	height = 0;
	solid = true;
	depth = y;
};

void TiledEntity::init(TileSet* tset, short* tiles, short* tilesType, short nTiles, short width)
{
	this->nTiles = nTiles;
	this->width = width;
	this->tileset = tset;
	this->tilesId = tiles;
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
};

void TiledEntity::onRender()
{
	if (!visible || !enabled || tileset == NULL)
		return;

	int tw = tileset->getTileW() * 2, th = tileset->getTileH() * 2;	// multiplicamos x2 para conseguir tamaño 16, que es el tamaño de las decoraciones
	game->getGfxEngine()->renderPart(tileset->getImg(), x, y, 
		tw*(tilesId[0] % (tileset->getColumns()/2)), th*(tilesId[0] / (tileset->getColumns()/2)), width * tw, height * th);
};