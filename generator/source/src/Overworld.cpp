#include "Overworld.h"

// Constructora.
Overworld::Overworld(int worldS, vector<ZoneInfo> zonesI, vector<DungeonInfo> dungeonsI, vector<SafeZoneInfo> safeZonesI){
	// Asignamos variables a atributos.
	worldSize = worldS;
	zonesInfo = zonesI;
	dungeonsInfo = dungeonsI;
	safeZonesInfo = safeZonesI;

	// Calculamos un tamaño del mundo a partir de worldSize.
	int worldSizeH = 12 * (rand() % (20 * worldSize)) + 10; 	// Aseguramos un mundo de al menos 10 x 10 pantallas.
	int worldSizeW = 16 *  (rand() % (20 * worldSize)) + 10; 
	
	// Inicializamos tileMapMatrix
	for (int i=0; i<worldSizeH * worldSizeW; i++)
		mapTileMatrix->pushBack(new MapTile());
	
}

void Overworld::genScreens(){
    int screensH = worldSizeH / 12;
    int screensW = worldSizeW / 16;
    int screens = screensH * screensW;

    int screenNumber = 0;
    int iniTileRow;
    int iniTile;

    vector<string>* screenFiles = new vector<string>();

    for (int row = 0; row < screensH; row++){
        iniTileRow = 16*12*screenNumber;
        for (int col = 0; col < screensW; col++){
            iniTile = col*16 + iniTileRow;
            OwScreen* screen = new OwScreen(zoneInfo, iniTile, screensW, this, screenNumber);
            screen->placeDetails();
            screen->placeEnemies();
            string screenpath = screen->createScreenFiles();
            pantallas->push_back(screenpath);
            screenNumber++;
        }
    }
}
