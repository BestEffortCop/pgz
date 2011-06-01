/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
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

#ifndef _DEFTYPES_H_
#define _DEFTYPES_H_

#include <string>

using namespace std;

struct player_t {
	short id;
	string name;
	short gfxId;
	short hp;		// Puntos de vida
	short mp;		// Puntos de magia
	short atk;		// Ataque
	short def;		// Defensa

	bool operator<(const player_t &p) const { return id < p.id; }
};

struct essential_elem_t {
	short id;
	short type;
	string path;
};

struct enemy_t {
	short id;
	short gfxId;
	short hp;
	short atk;
	short df;
	string name;

	bool operator<(const enemy_t &e) const { return id < e.id; }
};

struct npc_t {
	short id;
	short gfxId;
	short sfxId;
	short movComp;

	string name;
	bool operator<(const npc_t &npc) const { return id < npc.id; }
};

struct tool_t {
	short id;
	short gfxId;
	short dmgType;	// Tipo de daño (bloqueos que abre)
	short gfxAmmo;	// Gráfico de la munición del arma (id, -1 uno si no usa munición)
	short maxAmmo;	// Munición máxima
	short strength;	// Fuerza del arma/herramienta
	string name;
	short type;		// Tipo de herramienta (melee o lo otro)

	bool operator<(const tool_t &t) const { return id < t.id; }
};

// Ítems y PowUps tienen los mismos campos (de momento)
struct item_t {
	short id;
	short power;
	short effect;
	short gfxId;
	string name;
	bool operator<(const item_t &pu) const { return id < pu.id;}
};

// KeyItems y pigeons
struct obj_t {
	short id;
	short gfxId;
	string name;
	bool operator<(const obj_t &i) const { return id < i.id; }
};

struct boss_t {
	short id;
	string name;

	bool operator<(const boss_t &b) const { return id < b.id; }
};

struct block_t {
	short id;
	short type;
	short gfxId;
	short dmgType;

	bool operator<(const block_t &b) const { return id < b.id;}
};

struct gfx_t {
	short id;
	string path;

	bool operator<(const gfx_t &g) const { return id < g.id;}
};

struct sfx_t {
	short id;
	string path;

	bool operator<(const sfx_t &s) const { return id < s.id;}
};

struct zone_t {
	short id;
	short idTileSet;
	string name;
	string gen;

	bool operator<(const zone_t &z) const { return id < z.id;}
};

struct dungeon_t {
	short id;
	short idTileSet;

	bool operator<(const dungeon_t &d) const { return id < d.id;}
};

struct puzzle_elem_t {
	short id;
	short type; // De momento no me molesto en hacer un enum, el 0 es el FloorButton
	short gfxId;

	bool operator<(const puzzle_elem_t &p) const { return id < p.id;}
};

#endif