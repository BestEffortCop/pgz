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
		moneyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 4, 1);

		iKey = new Stamp("data/Gfx/key.png", player->world->game->getGfxEngine());
		keyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 3, 1);
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
	ihp->setTileSet("data/Gfx/heart.png");

	//Creo el mapa del tileset
	int**map = (int**) malloc((player->maxHp/4)*sizeof(int*));
	for (int i = 0; i < (player->maxHp/4);i++)
		map[i] = (int*) malloc(sizeof(int));

	for (int i = 0; i < (player->maxHp/4);i++)
		for (int j = 0; j < 1;j++)
		{
			if (i*j*4 < player->hp)
				map[i][j] = 0;
			else if ( (i*j*4 > player->hp) && ( (i*j - 1)*4< player->hp))
				map[i][j] = 0;
			else
				map[i][j] = 0;
		}
	ihp->setMap(map, (player->maxHp/4), 1);


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

	//GameMenuController::launch();
};

void HUD::onRender()
{
	int yy = y+4, hpx = x+64, moneyx = x+148, keyx = x+200;

	if (y == 0)
		fpsDisplay->render(x+4, yy);
	ihp->render(hpx,yy);

	iMoney->render(moneyx - 8,yy-1);
	moneyDisplay->render(moneyx, yy);

	iKey->render(keyx - 8,0);
	keyDisplay->render(keyx, yy);
};