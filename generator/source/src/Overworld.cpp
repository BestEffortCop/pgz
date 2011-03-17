#include "Overworld.h"

// Constructora.
Overworld::Overworld(int worldS, vector<ZoneInfo>* zonesI, vector<DungeonInfo>* dungeonsI,
                     vector<SafeZoneInfo>* safeZonesI){
	// Asignamos variables a atributos.
	worldSize = worldS;
	zonesInfo = zonesI;
	dungeonsInfo = dungeonsI;
	safeZonesInfo = safeZonesI;

	mapTileMatrix = new vector<MapTile*>(); 

	// Calculamos un tamaño del mundo a partir de worldSize.
	worldSizeH = screenHeight * ((rand() % (5 * worldSize)) + 10); 	// Aseguramos un mundo de al menos 10 x 10 pantallas.  70
	worldSizeW = screenWidth *  ((rand() % (5 * worldSize)) + 10);

	// Inicializamos tileMapMatrix
	for (int i=0; i< (worldSizeH*worldSizeW); i++)
		mapTileMatrix->push_back(new MapTile());
}


Overworld::~Overworld(){
	vector<MapTile*>::iterator it;
    for(it = mapTileMatrix->begin(); it != mapTileMatrix->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete mapTileMatrix;
	mapTileMatrix = NULL;
}

// Getters utiles:
int Overworld::getNumZones(){
	if (zonesInfo != NULL)
		return zonesInfo->size();
	return 0;
}

int Overworld::getNumDungeons(){
	if (dungeonsInfo != NULL)
		return dungeonsInfo->size();
	return 0;
}

int Overworld::getNumSafeZones(){
	if (safeZonesInfo != NULL)
		return safeZonesInfo->size();
	return 0;
}
