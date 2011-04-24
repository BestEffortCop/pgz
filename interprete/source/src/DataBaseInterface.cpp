#include "DataBaseInterface.h"

DataBaseInterface::DataBaseInterface(void)
{
	graphics = new vector<GfxData>();
	enemies = new vector<EnemyData>();
	//npcs = new set<npc_t>();
	items = new vector<ItemData>();
	powUps = new vector<ItemData>();
	exchange = new set<ExchangeItemData>();
	bosses = new set<BossData>();
	//blocks = new set<block_t>();
	//graphics = new vector<gfx_t>();
	//sounds = new vector<sfx_t>();
	//worldGens = new set<worldGen_t>;
	players = new vector<HeroData>;


	string gfxPath = "data/graphics/weird-sprsheet.png";
	// Se preparan los datos temporales por ahora
	// Barbaroja como héroe
	hero.nombre = "RedBeard"; hero.gfxPath = gfxPath; 
	hero.hpMax = 120; hero.mpMax = 6;

	// Tektite como enemigo
	enemy.idEnemy = 1; enemy.nombre = "Tektite"; enemy.gfxPath = gfxPath; 
	enemy.hpMax = 2; enemy.defense = 1; enemy.strength = 2; enemy.mpMax = 0;
	
	// Espada como herramienta
	tool.idTool = 3; tool.nombre = "Sword"; tool.gfxPath = gfxPath;

	// Corazoncito como item
	item.idItem = 2; item.effect = 3; item.power = 4;

	// Tset random
	tset.idTset = 0; tset.gfxPath = gfxPath;

	// Opamp como KeyItem
	keyItem.nombre = "Opamp Sagrado"; keyItem.gfxPath = gfxPath;

	// HeartPiece como PowerUp
	powUp.idPowUp = 4; powUp.gfxPath = gfxPath; powUp.tipo = 2; powUp.pow = 4;

	// Concha como pigeon
	pidgey.nombre = "Shell"; pidgey.gfxPath = gfxPath;

	// YoshiDoll como Xitem
	xItem.idExchange = 6; xItem.nombre = "Yoshi Doll"; xItem.gfxPath = gfxPath;

	// Goriya X como Boss
	boss.nombre = "Goriya X"; boss.idBoss = 8000; boss.hp = 1;
};

void DataBaseInterface::loadData() {
	loadGfx();
	loadHeroes();
	loadEnemies();
	loadItems();
	loadPowerUps();
}

void DataBaseInterface::loadGfx() {
	FILE* file = fopen(".\\data\\Gfx", "r");

	int n_graphics = 0;
	short buffer[1];
	fread(buffer, sizeof(short), 1, file);
	n_graphics = buffer[0];
	
	GfxData g;
	char aux[255];
	for (int i = 0; i < n_graphics; i++) {
		fread(buffer, sizeof(short), 1, file);
		g.id = buffer[0];
		fread(buffer, sizeof(short), 1, file); // Leemos el tamaño del path
		char* path = new char[buffer[0]];
		fread(path, sizeof(path), 1, file); // Leemos el path
		sprintf(aux, "%s", path); // Guardamos su valor
		g.path = aux;
		delete path; path = NULL; // Liberamos la memoria
		graphics->push_back(g); // Guardamos el nuevo gráfico
	}
}

void DataBaseInterface::loadHeroes() {
	// Abrimos el archivo de Players de la BDJ
	FILE* file = fopen(".\\data\\Players", "r");
	int n_players = 0;
	// Leemos el número de Players (distintos) que aparecen en el juego
	short* buffer = new short[1];
	fread(buffer,sizeof(buffer), 1,file);
	n_players = buffer[0];
	
	HeroData h;
	delete buffer; buffer = new short[7];
	for (int i = 0; i < n_players; i++) {
		fread(buffer, sizeof(buffer), 7, file);
		h.id = buffer[0];
		h.gfxId = buffer[1];
		h.hpMax = buffer[2];
		h.mpMax = buffer[3];
		h.strength = buffer[4];
		h.defense = buffer[5];

		char* name = new char[buffer[6]];
		fread(name, buffer[6], 1, file);
		h.nombre = name;

		players->push_back(h);

		delete name; name = NULL;
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DataBaseInterface::loadEnemies() {
	FILE* file = fopen(".\\data\\Enemies", "r");
	short n_enemies = 0;
	short n_enemiesBuf[1];
	fread(n_enemiesBuf, sizeof(short), 1, file);
	n_enemies = n_enemiesBuf[0];

	EnemyData e;
	short enemyData[7];
	for (int i = 0; i < n_enemies; i++) {
		fread(enemyData, sizeof(short), 7, file);
	
		e.idEnemy = enemyData[0];
		e.gfxId = enemyData[1];
		e.hpMax = enemyData[2];
		e.strength = enemyData[3];
		e.defense = enemyData[4];
		e.mpMax = -1; // No hay en la BDD, de momento
		
		char* name = new char[enemyData[5]];
		char* cfgPath = new char[enemyData[6]];

		fread(name, enemyData[5], 1, file);
		fread(cfgPath, enemyData[6], 1, file);

		e.nombre = name;
		e.cfgPath = cfgPath;

		delete name; name = NULL;
		delete cfgPath; cfgPath = NULL;

		enemies->push_back(e);
	}

	fclose(file);
}

void DataBaseInterface::loadItems() {
	FILE* file = fopen(".\\data\\Items", "r");

	short n_itemsBuf[1];
	fread(n_itemsBuf, sizeof(short), 1, file);
	short n_items = n_itemsBuf[0];

	ItemData it;
	short buffer[5];
	for (int i = 0; i < n_items; i++) {
		fread(buffer, sizeof(short), 5, file);

		it.idItem = buffer[0];
		it.power = buffer[1];
		it.effect = buffer[2];
		it.gfxId = buffer[3];

		char* name = new char[buffer[4]];
		fread(name, buffer[4], 1, file);
		it.name = name;

		items->push_back(it);

		delete name; name = NULL;
	}

	fclose(file);
}

void DataBaseInterface::loadPowerUps() {
	FILE* file = fopen(".\\data\\PowerUps", "r");

	short n_itemsBuf[1];
	fread(n_itemsBuf, sizeof(short), 1, file);
	short n_items = n_itemsBuf[0];

	ItemData it;
	short buffer[5];
	for (int i = 0; i < n_items; i++) {
		fread(buffer, sizeof(short), 5, file);

		it.idItem = buffer[0];
		it.power = buffer[1];
		it.effect = buffer[2];
		it.gfxId = buffer[3];

		char* name = new char[buffer[4]];
		fread(name, buffer[4], 1, file);
		it.name = name;

		items->push_back(it);

		delete name; name = NULL;
	}

	fclose(file);
}


DataBaseInterface::~DataBaseInterface(void){
	delete enemies; enemies = NULL;
	//npcs = new set<npc_t>();
	delete items; items = NULL;
	delete powUps; powUps = NULL;
	delete exchange; exchange = NULL;
	delete bosses; bosses = NULL;
	//blocks = new set<block_t>();
	//graphics = new vector<gfx_t>();
	//sounds = new vector<sfx_t>();
	//worldGens = new set<worldGen_t>;
	delete players; players = NULL;
};

// Recursos
string DataBaseInterface::getImagePath(int idGfx)
{
	/* Algoritmo a utilizar cuando se puedan cargar cosas de la BDJ
	   for (vector<GfxData>::iterator it = graphics->begin(); it < graphics->end(); it++)
	       if (it->id == idGfx) return it->path;

		return "";
	*/

	// Temporal bogus
	return "data/graphics/key.png";
};
string DataBaseInterface::getSoundPath(int idSnd)
{
	// Temporal bogus
	return "sfx/soudesuka.wav";
};
string DataBaseInterface::getMusicPath(int idMus)
{
	// Temporal bogus
	return "bgm/ending.ogg";
};

// Obtención de elementos
DataBaseInterface::HeroData DataBaseInterface::getHeroData(int heroNumber)
{
	/* Algoritmo a utilizar cuando se puedan cargar cosas de la BDJ
	   if (hero >= 0 && hero < players->size())
	       return players->at(heroNumber);

		return hero; // Suponiendo que siga existiendo ese temporal bogus
	*/

	// Temporal bogus
	return hero;
};

DataBaseInterface::EnemyData DataBaseInterface::getEnemyData(int idEnemy)
{
	/* Algoritmo a utilizar cuando se puedan cargar cosas de la BDJ
	   for (vector<EnemyData>::iterator it = enemies->begin(); it < enemies->end(); it++)
	       if (it->idEnemy == idEnemy) return *it;

		return enemy; // Suponiendo que siga existiendo ese temporal bogus
	*/
	// Temporal bogus
	return enemy;
};

DataBaseInterface::ToolData DataBaseInterface::getToolData(int idTool)
{
	// Temporal bogus
	return tool;
};

DataBaseInterface::ItemData DataBaseInterface::getItemData(int idItem)
{
	// Temporal bogus
	return item;
};

DataBaseInterface::TsetData DataBaseInterface::getTilesetData(int idTset)
{
	// Temporal bogus
	return tset;
};

DataBaseInterface::KeyItemData DataBaseInterface::getKeyItemData()
{
	// Temporal bogus
	return keyItem;
};

DataBaseInterface::PowerUpData DataBaseInterface::getPowerUpData(int idPowUp)
{
	// Temporal bogus
	return powUp;
};

DataBaseInterface::PigeonData DataBaseInterface::getPigeonData()
{
	// Temporal bogus
	return pidgey;
};

DataBaseInterface::ExchangeItemData DataBaseInterface::getExchangeItemData(int idIItem)
{
	// Temporal bogus
	return xItem;
};

DataBaseInterface::BossData DataBaseInterface::getBossData(int idBoss)
{
	// Temporal bogus
	return boss;
};

std::string DataBaseInterface::getShadowGfxPath(GameEntity::Size size)
{
	// Esto mirará en la BDJ o algo
	switch (size)
	{
	case GameEntity::sNone: return "data/graphics/blank.png"; break;
	case GameEntity::sSmall: return "data/graphics/shadow-s.png"; break;
	case GameEntity::sMedium: return "data/graphics/shadow-m.png"; break;
	default:
		return "data/graphics/blank.png";
		break;
	};
	// Si llegamos aquí, bogus
	return "data/graphics/blank.png";
};