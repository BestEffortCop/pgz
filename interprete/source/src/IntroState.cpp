#include "IntroState.h"
#include <iostream>
#include <fstream>

IntroState::IntroState(int w, int h, Game* g) : GameState(g, w, h)
{
	font = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());
	bg = new TileSet("data/graphics/system-dummy.png",8,8,game->getGfxEngine());

	textlist.clear();
	loadText("./data/prologue.txt");
}


IntroState::~IntroState()
{
	if (font != NULL)
		delete font;
	if (bg != NULL)
		delete bg;
	if (m != NULL)
		delete m;
}


void IntroState::onStep()
{
	if (game->getInput()->keyPressed(((PGZGame*) game)->controller->mainInputConfig.keySTART))
		((PGZGame*) game)->startNewgame();
};

bool IntroState::remove(Entity* e)
{
	if (e == m)
	{
		m = NULL;
		((PGZGame*) game)->startNewgame();
	}

	return GameState::remove(e);

}
void IntroState::renderBG()
{
	game->getGfxEngine()->renderRectangle(0, 0, roomw, roomh, Color::Black);
}

void IntroState::loadText(std::string path)
{
	ifstream file (path);

	TileTextLabel* label;
	std::string line;
	std::string tmp;

	while ( file.good() )
	{
		getline(file,tmp);
		if (file.good())
		{
			tmp.append("\n");
			tmp.append("\n");
		}
		line.append(tmp);
	}

	m = new MessageDialog(font,27,30,bg,game->getGfxEngine(),0,0,this,game);
	m->setText(line);
	add(m);

	file.close();
}