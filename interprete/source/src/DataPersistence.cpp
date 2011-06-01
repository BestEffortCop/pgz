/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "DataPersistence.h"

DataPersistence::DataPersistence()
{
	gameData = new GameData();
};

DataPersistence::~DataPersistence()
{
	for (std::vector<MapData*>::iterator it = mapDataList.begin(); it != mapDataList.end(); it++)
	{
		delete (*it);
	} 
	mapDataList.clear();

	delete gameData;
}


bool DataPersistence::addMapData(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses, int numCollectables)
{
	if ((mapId >= 0) && (mapId < mapDataList.size()))
		if (mapDataList[mapId] != NULL) return false;
	
	MapData* newmap = new MapData();
	newmap->init(mapId, type, w, h, layout, numPuzzles, numDoors, numMinibosses, numCollectables);

	std::vector<MapData*>::iterator it = mapDataList.begin();
	for (int i = 0; i < mapId; i++)
		it++;

	mapDataList.insert(it, newmap);

	return true;
};

GameData* DataPersistence::getGameData()
{
	return gameData;
};

MapData* DataPersistence::getMapData(int mapId)
{
	// ABSOLUTELY NOT ERROR PROOF!
	return mapDataList[mapId];
};

int DataPersistence::getMapNumber()
{
	return mapDataList.size();
};

void DataPersistence::save(string path){
	FILE* f = fopen(path.c_str(), "wb");

	vector<MapData*>::iterator it = mapDataList.begin();

	// Escribimos el número de mapas del juego
	int* buffer = new int[1];
	buffer[0] = mapDataList.size();
	fwrite(buffer, sizeof(int), 1, f);

	delete buffer;
	// Guardamos los datos del juego
	gameData->save(f);


	// Escribimos los datos de los mapas
	while (it != mapDataList.end()){
		(*it)->save(f);	
		it++;
	}

	fclose(f);

}

int DataPersistence::getMaxLife(){
	return gameData->getGameStatus()->getMaxLife();
}

int DataPersistence::getCurrentMoney(){
	return gameData->getGameStatus()->getCurrentMoney();
}

int DataPersistence::getGameProgress(){
	return gameData->getGameStatus()->getGameProgress();
}

int DataPersistence::getNumPigeons(){
	return gameData->getGameStatus()->getNumPigeons();
}

bool DataPersistence::load(FILE* f){
	// Carga el archivo y lee
	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// Número de mapas
	int buffer[1];
	fread(buffer, sizeof(int), 1, f);
	this->numMapas = buffer[0];

	if (numMapas == 0)
		return false;
	if (gameData != NULL){
		delete gameData;
		gameData = NULL;
	}
	gameData = new GameData();
	gameData->load(f);
	if (mapDataList.size() != 0){
		for (std::vector<MapData*>::iterator it = mapDataList.begin(); it != mapDataList.end(); it++){
			delete (*it);
		} 
		mapDataList.clear();
	}
	// Cargamos los datos de los mapas
	for (int i = 0; i < numMapas; i++){
		MapData* newmap = new MapData();
		newmap->load(f);
		newmap->setId(i);
		mapDataList.push_back(newmap);
	}

	fclose(f);
	

	return true;
}