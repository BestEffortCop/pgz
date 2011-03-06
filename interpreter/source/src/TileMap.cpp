
#include "tileMap.h"

TileMap::TileMap(int tileW, int tileH, GfxEngine* gfxEngine) : Graphic() 
{
	this->gfxEngine = gfxEngine;
	
	/* Se configuran mediante setters */
	tileSet = NULL;
	idMap = NULL;
	
	this->tileW = tileW;
	this->tileH = tileH;

	// control de errores
	mapImage = NULL;
};

void TileMap::loadMap(string fname)
{
	FILE* file = NULL;
	file = fopen(fname.c_str(), "r");

	// lectura de files y columnas de la matriz idMap
	fscanf(file, "%d", &colNumber);
	fscanf(file, "%d", &rowNumber);

	// reserva memoria
	int** tiles = (int **) malloc(colNumber *sizeof(int));
	for(int i = 0; i < colNumber; i++)
		tiles[i] = (int *) malloc(rowNumber*sizeof(int));

	// lee cada elemento de la matriz
	for (int j = 0; j < rowNumber; j++)
		for (int i = 0; i < colNumber; i++){
			int aux;
			fscanf(file, "%d", &aux);
			tiles[i][j] = aux;
		}

	fclose(file);

	// se guarda el mapa
	idMap = tiles;

	// Si el tileset también está cargado
	if (tileSet != NULL)
		// construye la imagen del mapa
		getMapImage();
};

TileMap::~TileMap(){
	/*
	  Nos aseguramos de que tileSet e idMap fueron configurados 
	  mediante el setter antes de intentar borrarlos.
	*/
	if(tileSet != NULL){
		delete tileSet;
		tileSet = NULL;
	}

	if(idMap != NULL){
		for (int i = 0; i < colNumber; i++) {
				delete idMap[i];
				idMap[i] = NULL;
		}
		delete idMap;
		idMap = NULL;
	}
};

void TileMap::setTileSet(string tspath){
	tileSet = new TileSet(tspath, tileW, tileH, gfxEngine);
};


void TileMap::setMap(int** map){
	idMap = map;
};

void TileMap::setCols(int col){
	this->colNumber = colNumber;
};

void TileMap::setRows(int row){
	this->rowNumber = rowNumber;
};

Image* TileMap::getMapImage(){

	// Si ya existe se devuelve la imagen ya creada.
	if (mapImage != NULL) return mapImage;

	// Si no existe el mapa se crea, con escritura habilitada.
	mapImage = new Image(colNumber*tileW, rowNumber*tileH, gfxEngine, true, true);

	// coloca todos los tiles especificados por idMap sobre mapImage
	for (int i = 0; i < colNumber; i++)
		for (int j = 0; j < rowNumber; j++)
			setTile(i, j, idMap[i][j]);

	// se actualiza la imagen con los nuevos tiles
	mapImage->refresh();

	return mapImage;
};

void TileMap::setTile(int x, int y, int tile){
	/* 
	dibuja sobre mapImage el tile de tileSet de coordenadas especificadas:
	(tile % tileSet->getColumns())*w 
	(tile / tileSet->getColumns())*h
	*/
	gfxEngine->renderPart(tileSet->getImg(), x*tileW, y*tileH,
	(tile % tileSet->getColumns())*tileW, (tile / tileSet->getColumns())*tileH, tileW, tileH, mapImage);
};
		
void TileMap::render(int x, int y){
	/*Pinta el mapa en la posición indicada*/
	if (mapImage != NULL)
		gfxEngine->renderExt(mapImage, x, y, *color, alpha, scale, scale, rotation, NULL, originX, originY);
};

int TileMap::getWidth(){
	return tileW;
};
		
int TileMap::getHeight(){
	return tileH;
};
