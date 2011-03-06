#include "Map.h"

Map::Map(int tileW, int tileH, GfxEngine* gfxEngine){
	tileMap = new TileMap(tileW, tileH, gfxEngine);
	solidGrid = NULL; 
};

Map::~Map(){
	delete tileMap;
	// Comprobamos si fue configurado mediante setter/load antes de borrar.
	if(solidGrid != NULL)
		delete solidGrid;
};
	
void Map::loadSolids(string fname){
	solidGrid = new SolidGrid(fname); 
};

SolidGrid* Map::getSolids(){
	return solidGrid;
};

void Map::setSolids(int x, int y, int** solids, int columns, int rows){
	solidGrid = new SolidGrid(x,y,solids,tileMap->getWidth(),tileMap->getHeight(),columns,rows);
};
		
void Map::setTileset(string fname){
	tileMap->setTileSet(fname);
};
		
void Map::loadTiles(string fname){
	tileMap->loadMap(fname);
};
		
void Map::setTiles(int** tiles){
	tileMap->setMap(tiles);
};

void Map::loadMap(string fname){
	// se busca extensión
	size_t found = fname.find_last_of(".");

	if (found != string::npos){
		// si la encuentra se descarta 
		fname = fname.substr(0,found);
	}

	// Se almacena el nombre de archivo sin extensión
	string f2 = fname;

	// carga sólidos y tiles de los ficheros correspondientes
	loadSolids(fname.append(".sol"));

	loadTiles(f2.append(".til"));
};

void Map::update(){
	/*if(tileMap != NULL) 
		tileMap->getMapImage()->refresh();*/
};

void Map::render(int x, int y){
	if (tileMap != NULL)
		tileMap->render(x,y);
};



