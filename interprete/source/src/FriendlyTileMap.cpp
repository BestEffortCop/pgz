#include "FriendlyTileMap.h"

FriendlyTile::FriendlyTile(int tileId)
{
	this->tileId = tileId;
	alpha = 1.0f;
};

void FriendlyTile::render(int x, int y, TileSet* tset, GfxEngine* gfxEngine, float scaleH, float scaleV, Color c, float a, Image* dest)
{
	int tileW = tset->getTileW();
	int tileH = tset->getTileH();

	if (gfxEngine == NULL || tset == NULL || tileId < 0 || tset->getColumns() == 0)
		return;

	// multiplicación de color
	Color col(c.r*color.r/255, c.g*color.g/255, c.b*color.b/255);

	// alpha al mínimo
	float alf = min(a, alpha);

	gfxEngine->renderPartExt(tset->getImg(), x, y, (tileId % tset->getColumns())*tileW,
		(tileId / tset->getColumns())*tileH, tileW, tileH, col, alf, scaleH, scaleV, 0, dest);
};

FriendlyTileMap::FriendlyTileMap(int tileW, int tileH, GfxEngine* gfxEngine)
{
	this->tileW = tileW;
	this->tileH = tileH;
	this->gfxEngine = gfxEngine;

	rowNumber = -1;
	colNumber = -1;

	loadedTset = false;
	tileSet = NULL;
	tMap = NULL;
};

FriendlyTileMap::~FriendlyTileMap()
{
	if (loadedTset && tileSet != NULL)
		delete tileSet, tileSet = NULL;

	if (tMap != NULL)
	{
		for (int i = 0; i < colNumber; i++)
			delete tMap[i], tMap[i] = NULL;
		delete tMap;
		tMap = NULL;
	}
};

void FriendlyTileMap::setTileSet(std::string tspath)
{
	if (tileSet != NULL && loadedTset)
		delete tileSet;

	tileSet = new TileSet(tspath, tileW, tileH, gfxEngine);
	loadedTset = true;
};

void FriendlyTileMap::setTileSet(TileSet* tset)
{
	if (tileSet != NULL && loadedTset)
		delete tileSet;

	tileSet = tset;
	loadedTset = false;
};

void FriendlyTileMap::setMap(int** map, int col, int row)
{
	// Machacamos el antiguo mapa
	for (int i = 0; i < colNumber; i++)
		delete tMap[i], tMap[i] = NULL;
	delete tMap, tMap = NULL;

	colNumber = col;
	rowNumber = row;

	// Se crea el nuevo mapa
	tMap = (FriendlyTile**) malloc(colNumber*sizeof(FriendlyTile*));
	for (int i = 0; i < colNumber; i++)
		tMap[i] = (FriendlyTile*) malloc(rowNumber*sizeof(FriendlyTile));

	// Y se rellena con los datos
	for (int i = 0; i < colNumber; i++)
		for (int j = 0; j < rowNumber; j++)
			tMap[i][j] = FriendlyTile(map[i][j]);

	// Ahora se borra el map para acomodarse a la implementación de TileMap
	for (int i = 0; i < colNumber; i++)
		delete map[i], map[i] = NULL;
	delete map, map = NULL;
};

TileSet* FriendlyTileMap::getTileset()
{
	return tileSet;
};

void FriendlyTileMap::loadMap(std::string fname)
{
	// no :)
	return;
};

void FriendlyTileMap::setCols(int col)
{
	// Habría que reservar memoria o algo
	// No se hace porque no se usa en realidad
	colNumber = col;
};

void FriendlyTileMap::setRows(int row)
{
	// Habría que reservar memoria o algo
	// No se hace porque no se usa en realidad
	rowNumber = row;
};

int FriendlyTileMap::getCols()
{
	return colNumber;
};

int FriendlyTileMap::getRows()
{
	return rowNumber;
};


int FriendlyTileMap::getWidth()
{
	return (this->tileW * this->colNumber);
}


int FriendlyTileMap::getHeight()
{
	return (this->tileH * this->rowNumber);
}

Image* FriendlyTileMap::getMapImage()
{
	// Se crea una imagen que debe ser borrada fuera
	Image* img = new Image(tileW*colNumber, tileH*rowNumber, gfxEngine, true, true);
	
	for (int i = 0; i < colNumber; i++)
		for (int j = 0; j < rowNumber; j++)
			tMap[i][j].render((int) (i*tileW*getScaleH()), (int) (j*tileH*getScaleV()), tileSet, gfxEngine, getScaleH(), getScaleV(), *color, alpha, img);

	return img;
};

void FriendlyTileMap::render(int x, int y)
{
	// Tan solo dibujamos tutto!
	for (int i = 0; i < colNumber; i++)
		for (int j = 0; j < rowNumber; j++)
			tMap[i][j].render((int) (x+i*tileW*getScaleH()), (int) (y+j*tileH*getScaleV()), tileSet, gfxEngine, getScaleH(), getScaleV(), *color, alpha);
};

int FriendlyTileMap::getTileWidth()
{
	return tileW;
};

int FriendlyTileMap::getTileHeight()
{
	return tileH;
};

void FriendlyTileMap::setTile(int x, int y, int tile)
{
	// Se pone el tile restableciendo :)
	if (x < colNumber && y < rowNumber)
		tMap[x][y] = FriendlyTile(tile);
};

void FriendlyTileMap::setTileExt(int x, int y, int tile, Color color, float alpha, float scaleH, float scaleV, float rotation)
{
	if (x < colNumber && y < rowNumber)
	{
		tMap[x][y].tileId = tile;
		tMap[x][y].color = color;
		tMap[x][y].alpha = alpha;
	}
};

void FriendlyTileMap::clear()
{
	for (int i = 0; i < colNumber; i++)
		for (int j = 0; j < rowNumber; j++)
			tMap[i][j] = FriendlyTile(-1);
};