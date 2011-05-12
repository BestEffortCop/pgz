#include "FinalDungeon.h"

FinalDungeon::FinalDungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db) : Dungeon(zone,theme,gameDiff,dungNumber,ratio,tool,keyObj, dungeonPos, db) {

	// Obtener el tileSet apropiado y su path
	string tileSetPath = db->getPath("TileSet", db->getDungeon(zone));
	decorator->init(zone, theme, tileSetPath);
}


FinalDungeon::~FinalDungeon() {}

void FinalDungeon::generate() {


}