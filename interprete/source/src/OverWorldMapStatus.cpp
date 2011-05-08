#include "OverWorldMapStatus.h"

OverWorldMapStatus::OverWorldMapStatus() : MapStatus()
{
}

void OverWorldMapStatus::save(FILE* f){
	MapStatus::save(f);
}

void OverWorldMapStatus::load(FILE* f){
	MapStatus::load(f);
}