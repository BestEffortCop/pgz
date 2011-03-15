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

// Getters utiles:
int Overworld::getNumZones(){
	if (zonesInfo != NULL)
		return zonesInfo->size();
	return 0;
}

int Overworld::getNumDungeons();
	if (dungeonsInfo != NULL)
		return dungeonsInfo->size();
	return 0;

int Overworld::getNumSafeZones(){
	if (safeZonesInfo != NULL)
		return safeZonesInfo->size();
	return 0;
}