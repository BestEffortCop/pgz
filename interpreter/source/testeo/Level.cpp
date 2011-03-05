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
	_add(new objStar(200, 100, g, this));
	_add(new objBad(240, 170, g, this));

	mx = 0; my = 0;
}

void Level::onStep()
{
	mx = game->getInput()->getMouseX()/game->getGfxEngine()->getGameScreenScaleH() - game->getGfxEngine()->getGameScreenX();
	my = game->getInput()->getMouseY()/game->getGfxEngine()->getGameScreenScaleV() - game->getGfxEngine()->getGameScreenY();

	if (game->getInput()->keyPressed(Input::kENTER))
		add(new objBad(mx, my, game, this));
}
