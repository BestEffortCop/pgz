#include "ToolAmmo.h"

ToolAmmo::ToolAmmo(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world) {}

ToolAmmo::~ToolAmmo() {}

void ToolAmmo::init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath, Direction dir)
{
	Tool::init(passive, p, idTool, damage, damageType);		// init del padre

	this->dir = dir;

	// Cargar imagen de munición
	graphic = new Stamp(graphicpath, game->getGfxEngine());

	loadConfig(graphicpath, getConfigurationFileName(graphicpath));

	// Crear la máscara (habrá que cargarlo de un archivo de configuración)
	mask = new MaskBox(x, y, width, height, "arrow", 0, 0);

	// Colocarla munición en función del arma que nos ha creado (acordarse de ajustar profundidad)
	depth = y;

}

bool ToolAmmo::loadConfig(std::string graphicpath, std::string fname)
{
	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. velocidad de la munición
	if (fscanf(f, "%d", &speed) < 1)
		return false;

	// 2. Ancho y alto de imagen
	int nCols, nRows;
	if (fscanf(f, "%d %d", &nCols, &nRows) < 2)
		return false;

	// creamos el gráfico de la munición
	graphic = new SpriteMap(graphicpath, nCols, nRows, game->getGfxEngine());

	// 2. Leer las animaciones
	loadAnimation(UP, "up", f);
	loadAnimation(DOWN, "down", f);
	loadAnimation(LEFT, "left", f);
	loadAnimation(RIGHT, "right", f);

	fclose(f);

	return true;
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
	int xtmp = x;
	int ytmp = y;

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
/*	if (mask != NULL) delete mask; // borramos la antigua
	mask = new MaskBox(x, y, width, height, "ammo", 0, 0); // creamos la nueva en la posición actual*/

	// Actualizamos la profundidad del gráfico
	depth = y;
}