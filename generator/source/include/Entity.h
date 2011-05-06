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
		short tile;
		short terrainType;	// 1 sólido 0 no sólido
	
		EntityTiled(short type, short x, short y, short idCollectable, short linkedTo, short tile, short terrainType);	
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

class EntityPuzzleElement : public Entity {
	public:

		EntityPuzzleElement(short type, short x, short y, short idCollectable, short linkedTo);
		~EntityPuzzleElement();

		virtual bool save(FILE* file);
};

#endif