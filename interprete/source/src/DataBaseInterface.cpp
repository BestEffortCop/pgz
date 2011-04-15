#include "..\include\DataBaseInterface.h"


DataBaseInterface::DataBaseInterface(void)
{

	enemies = new set<EnemyData>();
	//npcs = new set<npc_t>();
	items = new set<ItemData>();
	powUps = new set<PowerUpData>();
	exchange = new set<ExchangeItemData>();
	bosses = new set<BossData>();
	//blocks = new set<block_t>();
	//graphics = new vector<gfx_t>();
	//sounds = new vector<sfx_t>();
	//worldGens = new set<worldGen_t>;
	players = new set<HeroData>;


	string gfxPath = "data/graphics/weird-sprsheet.png";
	// Se preparan los datos temporales por ahora
	// Barbaroja como héroe
	hero.nombre = "RedBeard"; hero.gfxPath = gfxPath; hero.hpMax = 120; hero.mpMax = 6;

	// Tektite como enemigo
	enemy.idEnemy = 1; enemy.nombre = "Tektite"; enemy.gfxPath = gfxPath; enemy.hpMax = 2; enemy.defense = 1; enemy.strength = 2; enemy.mpMax = 0;
	
	// Espada como herramienta
	tool.idTool = 3; tool.nombre = "Sword"; tool.gfxPath = gfxPath;

	// Corazoncito como item
	item.idItem = 2; item.tipo = 3; item.pow = 4;

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

}

void DataBaseInterface::loadGfx() {

}

void DataBaseInterface::loadHeroes() {
	// Abrimos el archivo de Players de la BDJ
	FILE* file = fopen(".\\..\\..\\Roger en Katzaland\\Data\\Players", "r");
	int n_players = 0;
	// Leemos el número de Players (distintos) que aparecen en el juego
	short* buffer = new short[1];
	fread(buffer,sizeof(buffer), 1,file);
	n_players = buffer[0];
	
	// Leemos los datos de los players
	delete buffer; buffer = new short[2];
	for (int i = 0; i < n_players; i++) {
		fread(buffer, sizeof(buffer), 1, file);
		hero.id = buffer[0];
		//hero.gfxId = buffer[1];
		// hero name
	}
	// Liberamos el buffer y cerramos el archivo
	delete buffer; buffer = NULL;
	fclose(file);
}

void DataBaseInterface::loadEnemies() {

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
	// Temporal bogus
	return "gfx/blank.png";
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
DataBaseInterface::HeroData DataBaseInterface::getHeroData()
{
	// Temporal bogus
	return hero;
};

DataBaseInterface::EnemyData DataBaseInterface::getEnemyData(int idEnemy)
{
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
