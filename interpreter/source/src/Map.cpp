#include "Map.h"

//Construye un map de dimensiones determinadas vacio
Map::Map(int tileW, int tileH, GfxEngine* gfxEngine){
	//Construye un tileMap vacio
	tileMap = new TileMap(tileW, tileH, gfxEngine);
	//Pone el solidGrid a NULL
	solidGrid = NULL; 
};

//Destructora
Map::~Map(){
	//Borra el tileMap, no hace falta comprobar si existe dado que este se crea siempre en 
	//la constructora
	delete tileMap;
	// Si el solidGrid fue configurado mediante setter/load antes de borrar.
	if(solidGrid != NULL)
	{
		//Lo borramos
		delete solidGrid;
		solidGrid = NULL;
	}
};

//Cargamos un solid grid de archivo a partir de su dirección
void Map::loadSolids(string fname){
	solidGrid = new SolidGrid(fname); 
};

//Devolvemos el solidGrid
SolidGrid* Map::getSolids(){
	return solidGrid;
};

//Configuramos un nuevo SolidGrid a partir de sus parametros basicos
void Map::setSolids(int x, int y, int** solids, int columns, int rows){
	//Lo construimos de cero
	solidGrid = new SolidGrid(x,y,solids,tileMap->getWidth(),tileMap->getHeight(),columns,rows);
};

//Cargamos de archivo el tileSet del tileMap a partir de su dirección
void Map::setTileset(string fname){
	tileMap->setTileSet(fname);
};

//Cargamos el mapa de tiles del tileMap a partir de archivo
void Map::loadTiles(string fname){
	tileMap->loadMap(fname);
};

//Configuramos el mapa de tiles a partir de uno ya construido
void Map::setTiles(int** tiles){
	tileMap->setMap(tiles);
};

//Carga el solid grid y el mapa de tiles del tileMap a partir de un nombre común a ambos
//archivos
void Map::loadMap(string fname){
	// se busca extensión
	size_t found = fname.find_last_of(".");
	
	//Si la encuentra
	if (found != string::npos){
		//Se descarta 
		fname = fname.substr(0,found);
	}

	// Se almacena el nombre de archivo sin extensión
	string f2 = fname;

	// carga sólidos y tiles de los ficheros correspondientes
	//nombreArchivo.sol
	loadSolids(fname.append(".sol"));
	//nombreArchivo.til
	loadTiles(f2.append(".til"));
};

//Metodo update para el Map por si fuera necesario
void Map::update(){
	//Por ahora no hace nada
	/*if(tileMap != NULL) 
		tileMap->getMapImage()->refresh();*/
};

//Dibuja el tileMap por pantalla
void Map::render(int x, int y){
	//Si existe
	if (tileMap != NULL)
		//le digo al tileMap que se dibuje
		tileMap->render(x,y);
};



