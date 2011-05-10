#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdio.h>

class Entity {
	public:
		short type;	// Tipo de entidad
		short x;
		short y;
		short idCollectable;
		short linkedTo;

		Entity(short type, short x, short y, short idCollectable, short linkedTo);
		virtual ~Entity();
		
		virtual bool save(FILE* file);
};

class EntityNPC : public Entity {
	public:
		short idNPC;
		short idText;

		EntityNPC(short type, short x, short y, short idCollectable, short linkedTo, short idNPC, short idText);
		~EntityNPC();

		virtual bool save(FILE* file);
};

class EntityItem : public Entity {
	public:
		short gfxId;
		short effect;
		short power;
	
		EntityItem(short type, short x, short y, short idCollectable, short linkedTo, short gfxId, short effect, short power);
		~EntityItem();

		virtual bool save(FILE* file);
};

class EntityTiled : public Entity {
	public:
		short* tiles;		// vector de tiles de la entidad
		short nTiles;		// número de tiles que tiene
		short* terrainTypes;	// 1 sólido 0 no sólido (foreground), 2 walkable
		short width;		// ancho de la entidad en tiles
	
		EntityTiled(short type, short x, short y, short idCollectable, short linkedTo, short nTiles, short* tiles, short* terrainTypes, short width);	
		~EntityTiled();

		virtual bool save(FILE* file);
};

class EntityDoor : public Entity {
	public:
		short idTile;

	
		EntityDoor(short type, short x, short y, short idCollectable, short linkedTo, short idTile);
		~EntityDoor();

		virtual bool save(FILE* file);
};

class EntityBossDoor : public Entity {
	public:
		short idTile;

	
		EntityBossDoor(short type, short x, short y, short idCollectable, short linkedTo, short idTile);
		~EntityBossDoor();

		virtual bool save(FILE* file);
};

class EntityDmgBlockade : public Entity {
	public:
		short idGfx;
		short typeB;
		short idDmg;
	
		EntityDmgBlockade(short type, short x, short y, short idCollectable, short linkedTo, short idGfx, short typeB, short idDmg);
		~EntityDmgBlockade();

		virtual bool save(FILE* file);
};

class EntityTiledPushable : public Entity {
	public:
		short idGfx;
	
		EntityTiledPushable(short type, short x, short y, short idCollectable, short linkedTo, short idGfx);
		~EntityTiledPushable();

		virtual bool save(FILE* file);
};

class EntityFloorButton : public Entity {
	public:
		short idGfx;
	
		EntityFloorButton(short type, short x, short y, short idCollectable, short linkedTo, short idGfx);
		~EntityFloorButton();

		virtual bool save(FILE* file);
};

class EntityTeleporter : public Entity {
	public:
		short idMap;
		short screenX;
		short screenY;
		short tileX;
		short tileY;

		EntityTeleporter(short type, short x, short y, short idCollectable, short linkedTo, short idMap, short screenX, short screenY, short tileX, short tileY);
		~EntityTeleporter();

		virtual bool save(FILE* file);
};

class EntityTool : public Entity {
	public:
		short idTool;

		EntityTool(short type, short x, short y, short idCollectable, short linkedTo, short idTool);
		~EntityTool();

		virtual bool save(FILE* file);
};

#endif