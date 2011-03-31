#pragma once

#ifndef _DEFTYPES_H_
#define _DEFTYPES_H_

#include <string>

using namespace std;

struct enemy_t {
	short id;
	short gfxId;
	short hp;
	short atk;
	short df;
	string name;
	string confPath;

	bool operator<(const enemy_t &e) const { return id < e.id; }
};

struct npc_t {
	short id;
	short gfxId;
	short sfxId;
	string name;
	string confPath;
	
	bool operator<(const npc_t &n) const { return id < n.id; }
};

struct tool_t {
	short id;
	short gfxId;
	// Más cosas por decidir
	string name;
};

// Ítems y PowUps tienen los mismos campos (de momento)
struct item_t {
	short id;
	short type;
	short effect;
	short gfxId;
	
	bool operator<(const item_t &i) const { return id < i.id; }
};

// KeyItems y pigeons
struct obj_t {
	short id;
	short gfxId;
	string name;
};

// Objetos de intercambio
struct exchange_t {
	short id;
	short gfxId;
	short previous; // Id del objeto anterior en la cadena
	string name;

	bool operator<(const exchange_t &e) const { return id < e.id; }
};

struct boss_t {
	short id;
	string name;
};

#endif