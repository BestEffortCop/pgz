#pragma once
#ifndef __DBI_H__
#define __DBI_H__

#include <string>
#include <fstream>
#include <set>

#include "GameEntity.h"

using namespace std;

/**
	Por supuesto falta todo el tema de parsing de archivos o conexión con DBase 
																				**/

class DataBaseInterface
{

public:

	/* ** Estructuras de Datos con la info de los elementos ** */
	// Notas:
	// + Se mantienen las ids en las structs por si hacen falta para checks
	// + Todos los ids son int de forma tentativa, y así con el resto de atributos
	
	// Player: Nombre | idGfx | Atributos[HpMax?, Strength, ...]
	struct HeroData { short id; string nombre; string gfxPath; /*string gfxId*/ int hpMax; int mpMax; /*...*/ };

	struct GfxData {short id; string path;};

	// Enemy: idEnemy | Nombre | idGfx | [Hp?, Mp?, Str, Def] | [Componente1..N]
	struct EnemyData { int idEnemy; string nombre; string gfxPath; int hpMax; int mpMax; int strength; int defense; /* Componentes */ };

	// Tools: idTool | Nombre | idGfx | ...?
	struct ToolData { int idTool; string nombre; string gfxPath; /*...*/ };

	// Items: idItem | idGfx | Tipo | Power (? nombre ?)
	struct ItemData { int idItem; int tipo; int pow; }; 

	// Tsets: idTset | idGfx (o en vez de idGfx guardamos el path?)
	struct TsetData { int idTset; string gfxPath; };

	// KItem: idKItem (?) | Nombre | idGfx
	struct KeyItemData { string nombre; string gfxPath; };

	// PowUp: idPowUp | idGfx | Tipo | Pow
	struct PowerUpData { int idPowUp; string gfxPath; int tipo; int pow; };

	// Pigns: idPigeon (?) | Nombre | idGfx
	struct PigeonData { string nombre; string gfxPath; };

	// Chnge: idInterchange | Nombre | idGfx
	struct ExchangeItemData { int idExchange; string nombre; string gfxPath; };

	// Bosss: idBoss | Nombre | y más! (o quizás esto va en Instancias?)
	struct BossData { int idBoss; string nombre; int hp; };

private:
		set<EnemyData>* enemies;			// Conjunto de enemigos del juego
		//set<NPCData>* npcs;				// Conjunto de NPCs del juego
		set<ItemData>* items;				// Conjunto de ítems del juego
		set<PowerUpData>* powUps;			// Conjunto de PowerUps del juego
		set<ExchangeItemData>* exchange;		// Conjunto de objetos de intercambio del juego
		set<BossData>* bosses;			// Conjunto de bosses del juego
		//set<block_t>* blocks;			// Conjunto de bloqueos que aparecen en el juego
		//set<worldGen_t>* worldGens;		// Conjunto de generadores de mundo
		//set<dungeonGen_t>* dungeonGens;	// Conjunto de generadores de mazmorra
		set<HeroData>* players;			// Conjunto de players del juego

protected:
	// Temporal, por supuesto
	// Se declaran contenedores temporales a devolver cuando se pida algo
	HeroData hero;
	EnemyData enemy;
	ToolData tool;
	ItemData item;
	TsetData tset;
	KeyItemData keyItem;
	PowerUpData powUp;
	PigeonData pidgey;
	ExchangeItemData xItem;
	BossData boss;
	
public:

	/* Métodos */

	DataBaseInterface(void);
	~DataBaseInterface(void);

	// Obtención de recursos
	string getImagePath(int idGfx);
	string getSoundPath(int idSnd);
	string getMusicPath(int idMus);

	// Obtención de elementos
	HeroData getHeroData();
	EnemyData getEnemyData(int idEnemy);
	ToolData getToolData(int idTool);
	ItemData getItemData(int idItem);
	TsetData getTilesetData(int idTset);
	KeyItemData getKeyItemData();
	PowerUpData getPowerUpData(int idPowUp);
	PigeonData getPigeonData();
	ExchangeItemData getExchangeItemData(int idIItem);
	BossData getBossData(int idBoss);

	std::string getShadowGfxPath(GameEntity::Size size);

	void loadData();
	void loadGfx();
	void loadHeroes();
	void loadItems();
	void loadEnemies();
	
};

#endif