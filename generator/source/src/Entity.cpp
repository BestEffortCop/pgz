#include "Entity.h"

Entity::Entity(short type, short x, short y, short idCollectable, short linkedTo) {
	this->type = type;
	this->x = x;
	this->y = y;
	this->idCollectable = idCollectable;
	this->linkedTo = linkedTo;
}

EntityNPC::EntityNPC(short type, short x, short y, short idCollectable, short linkedTo, short gfxId, short npcType, short textId) :
	Entity(type, x, y, idCollectable, linkedTo) {
		this->gfxId = gfxId;
		this->npcType = npcType;
		this->textId = textId;
}

EntityItem::EntityItem(short type, short x, short y, short idCollectable, short linkedTo, short id, short gfxId, short effect, short power) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->id = id;
	this->gfxId = gfxId;
	this->effect = effect;
	this->power = power;
}

EntityTiled::EntityTiled(short type, short x, short y, short idCollectable, short linkedTo, short nTiles, short tile, short* terrainTypes, short width) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->nTiles = nTiles;
	this->tile = tile;
	this->terrainTypes = terrainTypes;
	this->width = width;
}

EntityDoor::EntityDoor(short type, short x, short y, short idCollectable, short linkedTo, short idTile) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idTile = idTile;
}

EntityBossDoor::EntityBossDoor(short type, short x, short y, short idCollectable, short linkedTo, short idTile) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idTile = idTile;
}

EntityDmgBlockade::EntityDmgBlockade(short type, short x, short y, short idCollectable, short linkedTo, short idGfx, short typeB, short idDmg) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idGfx = idGfx;
	this->typeB = typeB;
	this->idDmg = idDmg;
}

EntityTiledPushable::EntityTiledPushable(short type, short x, short y, short idCollectable, short linkedTo, short idGfx) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idGfx = idGfx;
}

EntityFloorButton::EntityFloorButton(short type, short x, short y, short idCollectable, short linkedTo, short idGfx) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idGfx = idGfx;
}

EntityTeleporter::EntityTeleporter(short type, short x, short y, short idCollectable, short linkedTo, short idMap, short screenX, short screenY, short tileX, short tileY) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idMap = idMap;
	this->screenX = screenX;
	this->screenY = screenY;
	this->tileX = tileX;
	this->tileY = tileY;
}

EntityTool::EntityTool(short type, short x, short y, short idCollectable, short linkedTo, short idTool) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->idTool = idTool;
}

EntityFinalElement::EntityFinalElement(short type, short x, short y, short idCollectable, short linkedTo, short gfxId) :
	Entity(type, x, y, idCollectable, linkedTo) {
	this->gfxId = gfxId;
}

Entity::~Entity() {}

EntityNPC::~EntityNPC() {}

EntityItem::~EntityItem() {}

EntityTiled::~EntityTiled()
{	
	if (terrainTypes != NULL)
		delete terrainTypes, terrainTypes = NULL;
}

EntityDoor::~EntityDoor() {}

EntityBossDoor::~EntityBossDoor() {}

EntityDmgBlockade::~EntityDmgBlockade() {}

EntityTiledPushable::~EntityTiledPushable() {}

EntityFloorButton::~EntityFloorButton() {}

EntityTeleporter::~EntityTeleporter() {}

EntityTool::~EntityTool() {}

EntityFinalElement::~EntityFinalElement() {}

bool Entity::save(FILE* file) {
	short buffer[5];
	buffer[0] = type;
	buffer[1] = x;
	buffer[2] = y;
	buffer[3] = idCollectable;
	buffer[4] = linkedTo;
	if (fwrite(buffer, sizeof(short), 5, file) < 0)
		return false;
	return true;
}

bool EntityNPC::save(FILE* file){
	if (!Entity::save(file)) return false;
	short buffer[3];
	buffer[0] = gfxId;
	buffer[1] = npcType;
	buffer[2] = textId;
	if (fwrite(buffer, sizeof(short), 3, file) < 0)
		return false;
	return true;
}

bool EntityItem::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[4];
	buffer[0] = id;
	buffer[1] = gfxId;
	buffer[2] = effect;
	buffer[3] = power;
	if (fwrite(buffer, sizeof(short), 4, file) < 0) 
		return false;
	return true;
}

bool EntityTiled::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short* buffer = new short[nTiles + 1];
	
	// guardamos el ancho de la entidad
	short aux1[1];
	aux1[0] = width;
	if (fwrite(aux1, sizeof(short), 1, file) < 0){
		delete buffer;
		return false;
	}

	// guardamos el tile en el buffer
	buffer[0] = tile;

	// guardamos los tipos de los tiles en el buffer
	for (short i = 1; i < nTiles + 1; i++)
		buffer[i] = terrainTypes[i-1];
	
	// escribimos el número de tiles
	short aux[1];
	aux[0] = nTiles;
	if (fwrite(aux, sizeof(short), 1, file) < 0){
		delete buffer;
		return false;
	}

	if (fwrite(buffer, sizeof(short), nTiles + 1, file) < 0)
	{
		delete buffer;
		return false;
	}

	delete [] buffer;
	return true;
}

bool EntityDoor::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[1];
	buffer[0] = idTile;
	if (fwrite(buffer, sizeof(short), 1, file) < 0) 
		return false;
	return true;
}

bool EntityBossDoor::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[1];
	buffer[0] = idTile;
	if (fwrite(buffer, sizeof(short), 1, file) < 0) 
		return false;
	return true;
}

bool EntityDmgBlockade::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[3];
	buffer[0] = idGfx;
	buffer[1] = typeB;
	buffer[2] = idDmg;
	if (fwrite(buffer, sizeof(short), 3, file) < 0) 
		return false;
	return true;
}

bool EntityTiledPushable::save(FILE* file ) {
	if (!Entity::save(file)) return false;
	short buffer[1];
	buffer[0] = idGfx;
	if (fwrite(buffer, sizeof(short), 1, file) < 0) 
		return false;
	return true;
}

bool EntityFloorButton::save(FILE* file ) {
	if (!Entity::save(file)) return false;
	short buffer[1];
	buffer[0] = idGfx;
	if (fwrite(buffer, sizeof(short), 1, file) < 0) 
		return false;
	return true;
}

bool EntityTeleporter::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[5];
	buffer[0] = idMap;
	buffer[1] = screenX;
	buffer[2] = screenY;
	buffer[3] = tileX;
	buffer[4] = tileY;
	if (fwrite(buffer, sizeof(short), 5, file) < 0) 
		return false;
	return true;
}

bool EntityTool::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[1];
	buffer[0] = idTool;
	if (fwrite(buffer, sizeof(short), 1, file) < 0) 
		return false;
	return true;
}

bool EntityFinalElement::save(FILE* file) {
	if (!Entity::save(file)) return false;
	short buffer[1];
	buffer[0] = gfxId;
	if (fwrite(buffer, sizeof(short), 1, file) < 0) 
		return false;
	return true;
}