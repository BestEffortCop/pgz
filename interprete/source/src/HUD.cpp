#include "HUD.h"

#include "Controller.h"

HUD::HUD(int x, int y, Player* player, int width, int height)
{
	this->x = x; this->y = y;
	this->player = player;
	this->width = width;
	this->height = height;

	if (player != NULL)
	{
		font = new TileFont(player->getController()->getDataBaseInterface()->getFont(), player->world->game->getGfxEngine());

		// Temporal!
		fpsDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 7, 1);

		hpDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 7, 1);
		mpDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 4, 1);
		moneyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 3, 1);
		keyDisplay = new TileTextLabel(font, player->world->game->getGfxEngine(), 3, 1);
	}
};

HUD::~HUD()
{
	delete font;
	delete fpsDisplay;
	delete hpDisplay;
	delete mpDisplay;
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

	// HP
	tmp.clear();
	tmp += itoa(player->hp, buf, 10);
	tmp += "/";
	tmp += itoa(player->maxHp, buf, 10);
	hpDisplay->setText(tmp);
	hpDisplay->setColor(Color(230, 40, 10));

	// MP
	tmp.clear();
	tmp += itoa(player->mp, buf, 10);
	mpDisplay->setText(tmp);
	mpDisplay->setColor(Color(10, 10, 240));

	// $
	tmp.clear();
	tmp += itoa(player->getController()->getData()->getGameData()->getGameStatus()->getCurrentMoney() , buf, 10);
	moneyDisplay->setText(tmp);
	moneyDisplay->setColor(Color(10, 244, 30));

	// Keys
	tmp.clear();
	tmp += itoa(player->getController()->getData()->getMapData(player->getController()->getData()->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus()->getKeys() , buf, 10);
	keyDisplay->setText(tmp);
	keyDisplay->setColor(Color(255, 220, 15));
};

void HUD::onRender()
{
	int yy = y+4, hpx = x+64, mpx = x+128, moneyx = x+168, keyx = x+200;

	if (y == 0)
		fpsDisplay->render(x+4, yy);
	hpDisplay->render(hpx, yy);
	mpDisplay->render(mpx, yy);
	moneyDisplay->render(moneyx, yy);
	keyDisplay->render(keyx, yy);
};