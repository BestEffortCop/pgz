#include "Level.h"

Level::Level(Game* g) : GameState(g, 640, 320)
{
    //m = new Map("map.txt", "solid.txt", "ts.png", 32, 24, g->getGfxEngine());
    bg = new Stamp("bg-sky.png", g->getGfxEngine());

	cursor = new Stamp("badguy.png", g->getGfxEngine());

	light = new objLight(284, 4, g, this);
	player = new objTest(100, 142, g, this);
	p2 = new Player2(200, 100, g, this);
	_add(player);
	_add(p2);
	_add(light);
	_add(new objBad(100, 100, g, this));
	//_add(new objStar(200, 100, g, this));
	_add(new objBad(240, 170, g, this));

	aMap = new Map(16, 16, g->getGfxEngine());

	aMap->setTileset("download.png");
	aMap->loadMap("mapa.patroclos");

	counter = 0;

	canvas = new Canvas(0, 0, 120, 160, g->getGfxEngine());

	//canvas->draw(bg, 0, 0);
	//canvas->draw(cursor, 10, 10);
	//canvas->draw(cursor, 60, 60);
	canvas->draw(player->graphic, 0, 0);

	canvas->setOriginX(15);
	canvas->setOriginY(25);

	canvas->refresh();

	mx = 0; my = 0;
}

void Level::onStep()
{
	mx = game->getInput()->getMouseX()/game->getGfxEngine()->getGameScreenScaleH() - game->getGfxEngine()->getGameScreenX();
	my = game->getInput()->getMouseY()/game->getGfxEngine()->getGameScreenScaleV() - game->getGfxEngine()->getGameScreenY();

	if (game->getInput()->mouseReleased(Input::Right))
		add(new objBad(mx, my, game, this));

	counter++;

	canvas->setAlpha(abs(sin((float) counter*3.14/180)));
	canvas->setColor(Color(abs(cos((float) counter*3.14/180))*255, 100, 100));
	canvas->setRotation(sin((float) counter*3.14/180)*15);
}
