#include "ToolMelee.h"

ToolMelee::ToolMelee(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world)
{
}

ToolMelee::~ToolMelee(){};

void ToolMelee::init(bool passive, Player* p, Player::PlayerAnim playeranim, std::string graphicpath, int ncol, int nrow)
{
	Tool::init(passive, p);

	// creamos el gráfico de la herramienta
	graphic = new SpriteMap(graphicpath, ncol, nrow, game->getGfxEngine());

	// cargamos las diferentes animaciones de la herramienta
	loadAnimations(getConfigurationFileName(graphicpath));

	this->playeranim = playeranim;
}

void ToolMelee::onInit()
{
	if (player->changeState(Player::Attack))
		activate();
}

bool ToolMelee::loadAnimations(string fname)
{
	SpriteMap* gfx = ((SpriteMap*) graphic);
	int nCols = 0, nRows = 0;

	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Ancho y alto de imagen (?)
	if (fscanf(f, "%d %d", &nCols, &nRows) < 2)
		return false;

	// 2. Leer las animaciones
	loadAnimation(UP, "up", f);
	loadAnimation(DOWN, "down", f);
	loadAnimation(LEFT, "left", f);
	loadAnimation(RIGHT, "right", f);

	fclose(f);

	return true;
}

void ToolMelee::activate()
{
	Direction dir = player->getDir();	
	
	// Ejecutamos la animación correspondiente en función de la dirección a la que mira el player
	switch(dir){
	case UP:
		playAnim("up");
		break;
	case DOWN:
		playAnim("down");
		break;
	case LEFT:
		playAnim("left");
		break;
	case RIGHT:
		playAnim("right");
		break;
	}

	// Hacemos que el player ejecute la animación
	player->playAnim(playeranim);

	placeTool();
}

void ToolMelee::onEndStep()
{
	placeTool();
}


void ToolMelee::onRender()
{
	// TESTEO: Dibuja la máscara del frame actual
	//game->getGfxEngine()->renderRectangle(x+fd.offsetX, y+fd.offsetY, fd.width, fd.height, Color::Blue);

	GameEntity::onRender();
}

void ToolMelee::onCollision()
{
}
