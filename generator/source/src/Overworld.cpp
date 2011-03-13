#include "Overworld.h"

// Constructora.
Overworld::Overworld(int worldS, vector<ZoneInfo> zonesI, vector<DungeonInfo> dungeonsI, vector<SafeZoneInfo> safeZonesI){
	// Asignamos variables a atributos.
	worldSize = worldS;
	zonesInfo = zonesI;
	dungeonsInfo = dungeonsI;
	safeZonesInfo = safeZonesI;

	// Calculamos un tamaño del mundo a partir de worldSize.
	for (int i=0; i< ;i++){
		mapTileMatrix->at(i);
	}
}

void Overworld::genScreens(){
    int screensH = worldH / 12;
    int screensW = worldW / 16;
    int screens = screensH * screensW;

    int screenNumber = 0;
    int iniTileRow;
    int iniTile;

    vector<string>* screenFiles = new vector<string>();

    for (int row = 0; row < screensH ; row++){
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
