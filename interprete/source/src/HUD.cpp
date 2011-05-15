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

		iMoney = new Stamp("data/Gfx/rupee.png", player->world->game->getGfxEngine());
		moneyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 5, 1);

		iKey = new Stamp("data/Gfx/key.png", player->world->game->getGfxEngine());
		keyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 3, 1);


		iWeapon1 = new Stamp("data/Gfx/HUDweapon.png", player->world->game->getGfxEngine());
		iWeapon2 = new Stamp("data/Gfx/HUDweapon.png", player->world->game->getGfxEngine());

		Weapon1 = NULL;
		Weapon2 = NULL;
	}
};

HUD::~HUD()
{
	delete font;
	delete fpsDisplay;
	delete moneyDisplay;
	delete keyDisplay;
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
	tmp += "FPS: ";
	tmp += itoa(player->world->game->getFPS(), buf, 10);
	fpsDisplay->setText(tmp);

	//HP de verdad 
	ihp = new FriendlyTileMap(8,8,player->world->game->getGfxEngine());
	ihp->setTileSet("data/Gfx/hearts.png");

	//Creo el mapa del tileset
	int cols = (player->maxHp/4);
	int rows = 1;

	if (cols > 13)
	{
		rows = cols/13 + 1;
		cols = 13;
	}

	int**map = (int**) malloc(cols*sizeof(int*));
	for (int i = 0; i < cols;i++)
		map[i] = (int*) malloc(rows*sizeof(int));

	for (int i = 0; i < cols;i++)
		for (int j = 0; j < rows;j++)
		{
			if ((i + j*cols)*4 < player->hp)
				map[i][j] = 0;
			else if (((i + j*cols)*4 > player->hp) && (((i+ j*cols) - 1)*4< player->hp))
				map[i][j] = 1;
			else if((i + j*cols) >= player->maxHp)
				map[i][j] = -1;
			else
				map[i][j] = 2;
		}
	ihp->setMap(map, cols, rows);

	// $ textLabel
	tmp.clear();
	tmp += "x";
	tmp += itoa(player->getController()->getData()->getGameData()->getGameStatus()->getCurrentMoney() , buf, 10);
	moneyDisplay->setText(tmp);
	moneyDisplay->setColor(Color::Cyan);
	//moneyDisplay->setColor(Color(10, 244, 30));


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
		Weapon1 = new Stamp(player->getController()->getToolController()->getToolGraphicPath(id1), player->world->game->getGfxEngine());
	else
		Weapon1 = NULL;
	if (id2 != -1)
		Weapon2 = new Stamp(player->getController()->getToolController()->getToolGraphicPath(id2), player->world->game->getGfxEngine());
	else Weapon2 = NULL;
};

void HUD::onRender()
{
	int yy = y+4, hpx = x, moneyx = x+148, keyx = x+200;

	if (y == 0)
		fpsDisplay->render(x+4, yy + 16);
	if (ihp->getRows() == 1)
		ihp->render(hpx,yy+4);
	else
		ihp->render(hpx,yy-4);

	iWeapon1->render(hpx + 108, 0);
	iWeapon2->render(hpx + 125, 0);

	if (Weapon1 != NULL)
		Weapon1->render(hpx + 108, 0);
	if (Weapon2 != NULL)
		Weapon2->render(hpx + 125, 0);

	iMoney->render(moneyx - 8,yy-1);
	moneyDisplay->render(moneyx, yy);

	iKey->render(keyx - 8,0);
	keyDisplay->render(keyx, yy);
};