#include "HUD.h"

#include "Controller.h"

HUD::HUD(int x, int y, Player* player, int width, int height)
{
	this->x = x; this->y = y;
	this->player = player;

	if (player != NULL)
	{
		font = new TileFont(player->getController()->getDataBaseInterface()->getFont(), player->world->game->getGfxEngine());

		fpsDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 7, 1);

		iMoney = new FriendlyTileMap(16, 16, player->world->game->getGfxEngine());
		iMoney->setTileSet(((PGZGame*)player->world->game)->controller->getDataBaseInterface()->getHud());
		int** map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 4;
		iMoney->setMap(map, 1, 1);
		moneyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 5, 1);


		//Hay que crearlo cada vez porque el FriendlyTileMap te borra el map que le pasa
		iKey = new FriendlyTileMap(16, 16, player->world->game->getGfxEngine());
		iKey->setTileSet(((PGZGame*)player->world->game)->controller->getDataBaseInterface()->getHud());
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 3;
		iKey->setMap(map, 1, 1);
		keyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 3, 1);

		iWeapon1 = new FriendlyTileMap(16, 16, player->world->game->getGfxEngine());
		iWeapon1->setTileSet(((PGZGame*)player->world->game)->controller->getDataBaseInterface()->getHud());
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 5;
		iWeapon1->setMap(map, 1, 1);


		iWeapon2 = new FriendlyTileMap(16, 16, player->world->game->getGfxEngine());
		iWeapon2->setTileSet(((PGZGame*)player->world->game)->controller->getDataBaseInterface()->getHud());
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 5;
		iWeapon2->setMap(map, 1, 1);

		Weapon1 = NULL;
		Weapon2 = NULL;

		//Me creo el mapa de Tiles, no hace falta fijar el tamaño, ya que al ser un friendlyTileMap
		//Cualquier setMap borra todo el mapa antiguo y lo vuelve a crear, por lo que no nos importa
		//que el tamaño se tenga que modificar en el step cada paso porque lo iba a hacer de todas formas

		ihp = new FriendlyTileMap(16, 16, player->world->game->getGfxEngine());
		ihp->setTileSet(((PGZGame*)player->world->game)->controller->getDataBaseInterface()->getHud());
		ihp->setScale(0.5f,0.5f);
	}
};

HUD::~HUD()
{
	delete font;
	delete fpsDisplay;
	delete moneyDisplay;
	delete keyDisplay;

	delete iMoney;
	delete iKey;
	delete iWeapon1;
	delete iWeapon2;

	delete Weapon1;
	Weapon1 = NULL;
	delete Weapon2;
	Weapon2 = NULL;
	
	delete ihp;
}

void HUD::setPosition(int a, int b)
{
	x = a; y = b;
};

std::pair<int, int> HUD::getPosition()
{
	return make_pair(x, y);
};

void HUD::refresh()
{
	if (player == NULL)
		return;

	char buf[256];
	std::string tmp = "";

	// FPS
	//tmp += "FPS: ";
	//tmp += itoa(player->world->game->getFPS(), buf, 10);
	//fpsDisplay->setText(tmp);

	//HP

	//Calculo las dimensiones de la vida en el HUD
	int cols = (player->maxHp/4);
	int rows = 1;

	if (cols > 13)
	{
		rows = cols/13 + 1;
		cols = 13;
	}

	//Creo el mapa de tiles
	int**map = (int**) malloc(cols*sizeof(int*));
	for (int i = 0; i < cols;i++)
		map[i] = (int*) malloc(rows*sizeof(int));

	for (int i = 0; i < cols;i++)
		for (int j = 0; j < rows;j++)
		{
			if ((i + 1 + j*cols)*4 <= player->hp)
				map[i][j] = 0;
			else if (((i + 1 + j*cols)*4 >= player->hp) && (((i + 1+ j*cols) - 1)*4 < player->hp))
				map[i][j] = 1;
			else if(((i + 1) + j*cols)*4 >= player->maxHp)
				map[i][j] = 2;
			else
				map[i][j] = 2;
		}
	ihp->setMap(map, cols, rows);
	ihp->setScale(0.5f,0.5f);

	// $ textLabel
	tmp.clear();
	tmp += "x";
	tmp += itoa(player->getController()->getData()->getGameData()->getGameStatus()->getCurrentMoney() , buf, 10);
	moneyDisplay->setText(tmp);
	moneyDisplay->setColor(Color::Cyan);

	// Keys
	tmp.clear();
	tmp += "x";
	tmp += itoa(player->getController()->getData()->getMapData(player->getController()->getData()->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus()->getKeys() , buf, 10);
	keyDisplay->setText(tmp);
	keyDisplay->setColor(Color(255, 220, 15));

	//Armas
	int id1 = player->getController()->getToolController()->equippedToolAt(0);
	int id2 = player->getController()->getToolController()->equippedToolAt(1);

	if (id1 != -1)
	{
		if (Weapon1 != NULL)
			delete Weapon1;
		Weapon1 = new Stamp(player->getController()->getToolController()->getToolGraphicPath(id1), player->world->game->getGfxEngine());
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 6;
		iWeapon1->setMap(map, 1, 1);
	}
	else
	{
		Weapon1 = NULL;
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 5;
		iWeapon1->setMap(map, 1, 1);
	}

	if (id2 != -1)
	{
		if (Weapon2 != NULL)
			delete Weapon2;
		Weapon2 = new Stamp(player->getController()->getToolController()->getToolGraphicPath(id2), player->world->game->getGfxEngine());
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 7;
		iWeapon2->setMap(map, 1, 1);
	}
	else 
	{
		Weapon2 = NULL;
		map = (int**)malloc(sizeof(int*)*1);
		map[0] = (int*) malloc(sizeof(int));
		map[0][0] = 5;
		iWeapon2->setMap(map, 1, 1);
	}
};

void HUD::onRender()
{
	int yy = y+4, hpx = x, moneyx = x+148, keyx = x+200;

	//if (y == 0)
	//	fpsDisplay->render(x+4, yy + 16);
	if (ihp->getRows() == 1)
		ihp->render(hpx,yy+4);
	else
		ihp->render(hpx,yy-4);

	if (Weapon1 != NULL)
		Weapon1->render(hpx + 108, 0);

	if (Weapon2 != NULL)
		Weapon2->render(hpx + 125, 0);

	iWeapon1->render(hpx + 108, 0);
	iWeapon2->render(hpx + 125, 0);

	iMoney->render(moneyx - 8, 0);
	moneyDisplay->render(moneyx + 4, yy);

	iKey->render(keyx - 8,0);
	keyDisplay->render(keyx + 4, yy);
};