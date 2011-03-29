
#include "tileMap.h"

//Construtye un tileMap a partir del ancho y alto del tile y el subsistema grafico 
TileMap::TileMap(int tileW, int tileH, GfxEngine* gfxEngine) : Graphic() 
{
	//Se apunta al subsistema grafico
	this->gfxEngine = gfxEngine;
	
	/* Se configuran mediante setters */
	tileSet = NULL;
	idMap = NULL;
	
	//Parametros de la constructora, ancho y alto de un tile
	this->tileW = tileW;
	this->tileH = tileH;

	// control de errores
	mapImage = NULL;
};

//Constructora por carga desde archivo
void TileMap::loadMap(string fname)
{
	//Si habiamos asignado un idMap
	if(idMap != NULL){
		//Por cada fila
		for (int i = 0; i < colNumber; i++) {
				//Borramos su contenido
				delete idMap[i];
				idMap[i] = NULL;
		}
		//Borramos el contenido de la variable
		delete idMap;
		idMap = NULL;
	}

	//Crea y abre un archivo de tipo un FILE a partir del nombre de archivo, del cual
	//en el cual se encuentra el map que queremos construir
	FILE* file = NULL;
	file = fopen(fname.c_str(), "r");

	// lectura de filas y columnas de la matriz idMap
	fscanf(file, "%d", &colNumber);
	fscanf(file, "%d", &rowNumber);

	// reserva memoria para los tiles
	int** tiles = (int **) malloc(colNumber *sizeof(int));
	for(int i = 0; i < colNumber; i++)
		tiles[i] = (int *) malloc(rowNumber*sizeof(int));

	//Vamos copiando el mapa de tiles en una variable auxiliar
	for (int j = 0; j < rowNumber; j++)
		for (int i = 0; i < colNumber; i++){
			//lee cada elemento de la matriz
			int aux;
			fscanf(file, "%d", &aux);
			tiles[i][j] = aux;
		}

	//Cerramos el FILE
	fclose(file);

	// se guarda el mapa
	idMap = tiles;
	tiles = NULL;

	// Si el tileset también está cargado
	if (tileSet != NULL)
		// construye la imagen del mapa
		getMapImage();
};


//Destructora
TileMap::~TileMap(){
	/*
	  Nos aseguramos de que tileSet e idMap fueron configurados 
	  mediante el setter antes de intentar borrarlos.
	*/
	//Si se habia asignado un TileSet
	if(tileSet != NULL){
		//Lo borramos
		delete tileSet;
		tileSet = NULL;
	}
	//Si habiamos asignado un idMap
	if(idMap != NULL){
		//Por cada fila
		for (int i = 0; i < colNumber; i++) {
				//Borramos su contenido
				delete idMap[i];
				idMap[i] = NULL;
		}
		//Borramos el contenido de la variable
		delete idMap;
		idMap = NULL;
	}
};

//Asignamos al TileMap un nuevo tileSet cargado a partir de su nombre y un ancho y alto de tile
void TileMap::setTileSet(string tspath){
	// Si existía un TileSet, se borra
	if (tileSet != NULL)
		delete tileSet;

	tileSet = new TileSet(tspath, tileW, tileH, gfxEngine);
};

//Asignamos al TileMap un nuevo tileSet
void TileMap::setTileSet(TileSet* tset){
	// Si existía un TileSet, se borra
	if (tileSet != NULL)
		delete tileSet;

	tileSet = tset;
};

//Asignamos al map un nuevo mapa de enteros
void TileMap::setMap(int** map, int col, int row){
	idMap = map;
	this->colNumber = col;
	this->rowNumber = row;
};

//Asignamos el numero de columnas del TileMap
void TileMap::setCols(int col){
	this->colNumber = col;
};

//Asignamos el número de filas del TileMap
void TileMap::setRows(int row){
	this->rowNumber = row;
};


//Devolvemos la imagen del tileMap
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

//Pinta sobre la mapImage el tile deseado del TileSet
void TileMap::setTile(int x, int y, int tile){
	/* 
	dibuja sobre mapImage el tile de tileSet de coordenadas especificadas:
	(tile % tileSet->getColumns())*w 
	(tile / tileSet->getColumns())*h
	*/
	if (mapImage != NULL)
		gfxEngine->renderPart(tileSet->getImg(), x*tileW, y*tileH,
		(tile % tileSet->getColumns())*tileW, (tile / tileSet->getColumns())*tileH, tileW, tileH, mapImage);
};

	//Pinta la imagen por pantalla
void TileMap::render(int x, int y){
	//En caso de que la imagen exista
	if (mapImage != NULL)
		/*Pinta el mapa en la posición indicada*/
		gfxEngine->renderExt(mapImage, x+originX, y+originY, *color, alpha, scaleH, scaleV, rotation, NULL, originX, originY);
};

//Devuelve el ancho del tileMap
int TileMap::getWidth(){
	return tileW;
};

//Devuelve el alto del tileMap
int TileMap::getHeight(){
	return tileH;
};
