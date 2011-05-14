#include "WorldAutoTiler.h"

WorldAutoTiler::WorldAutoTiler(std::string tileSetPath){

	FILE* f = loadTilesetConfig(tileSetPath);
	fclose(f);
}

WorldAutoTiler::~WorldAutoTiler(){
	AutoTiler::~AutoTiler();
}