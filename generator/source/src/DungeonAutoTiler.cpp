#include "DungeonAutoTiler.h"

DungeonAutoTiler::DungeonAutoTiler(std::string tileSetPath) : AutoTiler(tileSetPath){
	loadDungeonConfig(loadTilesetConfig(tileSetPath));
}

DungeonAutoTiler::~DungeonAutoTiler(){
	AutoTiler::~AutoTiler();
}

bool DungeonAutoTiler::loadDungeonConfig(FILE* file){
	return true;	
}