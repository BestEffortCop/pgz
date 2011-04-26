#include "ToolAmmo.h"

ToolAmmo::ToolAmmo(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world) {}

ToolAmmo::~ToolAmmo() {}

void ToolAmmo::init(bool passive, Player* p, int idTool, std::string graphicpath, Direction dir)
{
	Tool::init(passive, p, idTool);		// init del padre

	this->dir = dir;

	// Cargar imagen de munición

	// Colocarla munición en función del arma que nos ha creado (acordarse de ajustar profundidad)

	// Crear la máscara
}



void ToolAmmo::onInit()
{
	activate();
}

void ToolAmmo::activate()
{
	// m... algo habrá que hacer digo yo
}

void ToolAmmo::onStep()
{
	int xtmp, ytmp;

	// Movimiento de la munición en función de la dirección y de la velocidad
	switch (dir)
	{
	case UP:
		ytmp -= speed;
		break;
	case DOWN:
		ytmp += speed;
		break;
	case LEFT:
		xtmp -= speed;
		break;
	case UPLEFT:
		xtmp -= speed;
		ytmp -= speed;
		break;
	case DOWNLEFT:
		xtmp -= speed;
		ytmp += speed;
		break;
	case RIGHT:
		xtmp += speed;
		break;
	case UPRIGHT:
		xtmp += speed;
		ytmp -= speed;
		break;
	case DOWNRIGHT:
		xtmp += speed;
		ytmp += speed;
		break;
	}

	// De momento no hacemos ninguna comprobación
	x = xtmp; y = ytmp;

	// Actualizamos la máscara
	if (mask != NULL) delete mask; // borramos la antigua
	mask = new MaskBox(x, y, width, height, "ammo", 0, 0); // creamos la nueva en la posición actual

	// Actualizamos la profundidad del gráfico
	depth = y;
}