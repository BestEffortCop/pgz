/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
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
		short gfxId;
		short npcType;
		short textId;

		EntityNPC(short type, short x, short y, short idCollectable, short linkedTo, short gfxId, short npcType, short textId);
		~EntityNPC();

		virtual bool save(FILE* file);
};

class EntityItem : public Entity {
	public:
		short id;				// Id del item o del power up en su respectiva tabla
		short gfxId;
		short effect;
		short power;
	
		EntityItem(short type, short x, short y, short idCollectable, short linkedTo, short id, short gfxId, short effect, short power);
		~EntityItem();

		virtual bool save(FILE* file);
};

class EntityTiled : public Entity {
	public:
		short tile;		// primer tile de la entidad
		short nTiles;		// número de tiles que tiene
		short* terrainTypes;	// 1 sólido 0 no sólido (foreground), 2 walkable
		short width;		// ancho de la entidad en tiles
	
		EntityTiled(short type, short x, short y, short idCollectable, short linkedTo, short nTiles, short tile, short* terrainTypes, short width);	
		~EntityTiled();

		virtual bool save(FILE* file);
};

class EntityFinalDoor : public Entity {
	public:
		short tile;		// primer tile de la entidad
		short nTiles;		// número de tiles que tiene
		short* terrainTypes;	// 1 sólido 0 no sólido (foreground), 2 walkable
		short width;		// ancho de la entidad en tiles
	
		EntityFinalDoor(short type, short x, short y, short idCollectable, short linkedTo, short nTiles, short tile, short* terrainTypes, short width);	
		~EntityFinalDoor();

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

class EntityFinalElement : public Entity {
	public:
		short gfxId;

		EntityFinalElement(short type, short x, short y, short idCollectable, short linkedTo, short gfxId);
		~EntityFinalElement();

		virtual bool save(FILE* file);
};


#endif