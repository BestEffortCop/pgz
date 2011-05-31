#include "ToolAmmo.h"

ToolAmmo::ToolAmmo(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world) {}

ToolAmmo::~ToolAmmo() {}

void ToolAmmo::init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath, Direction dir)
{
	Tool::init(passive, p, idTool, damage, damageType);		// init del padre

	this->dir = dir;
	type = "tool";

	// Cargar imagen de munición
	//graphic = new Stamp(graphicpath, game->getGfxEngine());

	loadConfig(graphicpath, getConfigurationFileName(graphicpath));

	// Colocarla munición en función del arma que nos ha creado (acordarse de ajustar profundidad)
	depth = y;
}

bool ToolAmmo::loadConfig(std::string graphicpath, std::string fname)
{
	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "rb");

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
	std::string name;
	ToolAnimData data;

	// Ejecutamos la animación correspondiente en función de la dirección a la que nos lanzan
	switch(dir){
	case UP:
		name = "up";
		break;
	case DOWN:
		name = "down";
		break;
	case LEFT:
		name = "left";
		break;
	case UPLEFT:
		name = "left";
		break;
	case DOWNLEFT:
		name = "left";
		break;
	case RIGHT:
		name = "right";
		break;
	case UPRIGHT:
		name = "right";
		break;
	case DOWNRIGHT:
		name = "right";
		break;
	}

	data = animList.at(name);						// cogemos los datos de la animación
	if(graphic != NULL) ((SpriteMap*) graphic)->playAnim(name, data.animSpeed, true, false);	// ejecutamos la animación

	// colocamos la munición (hotspot y tal)
	this->x +=  data.frameData[0].hotspotX;
	this->y +=  data.frameData[0].hotspotY;

	if (mask != NULL) delete mask; // borramos la antigua
	mask = new MaskBox(x, y, data.frameData[0].width, data.frameData[0].height, type, 0, 0); // creamos la nueva en la posición actual

	
}

void ToolAmmo::onStep()
{
	int xtmp = x;
	int ytmp = y;

	ToolAnimData data;

	// Movimiento de la munición en función de la dirección y de la velocidad
	switch (dir)
	{
	case UP:
		ytmp -= speed;
		data = animList.at("up");
		break;
	case DOWN:
		ytmp += speed;
		data = animList.at("down");
		break;
	case LEFT:
		xtmp -= speed;
		data = animList.at("left");
		break;
	case UPLEFT:
		xtmp -= speed;
		ytmp -= speed;
		data = animList.at("left");
		break;
	case DOWNLEFT:
		xtmp -= speed;
		ytmp += speed;
		data = animList.at("left");
		break;
	case RIGHT:
		xtmp += speed;
		data = animList.at("right");
		break;
	case UPRIGHT:
		xtmp += speed;
		ytmp -= speed;
		data = animList.at("right");
		break;
	case DOWNRIGHT:
		xtmp += speed;
		ytmp += speed;
		data = animList.at("right");
		break;
	}

	// Comprobamos que no se sale de la pantalla
	if (player->getController()->getScreenMap()->isInBounds(this))
	{
		x = xtmp; y = ytmp;

		// Actualizamos la máscara
		if (mask != NULL) delete mask; // borramos la antigua
		mask = new MaskBox(x, y, data.frameData[0].width, data.frameData[0].height, type, 0, 0); // creamos la nueva en la posición actual

		// Actualizamos la profundidad del gráfico
		depth = y;
	}
	else	// si se sale del borde matamos la munición
		instance_destroy();
}

void ToolAmmo::onCollision(CollisionPair other, Entity* e)
{
	if (other.b == "tool") return;

	if (Tool::doDamage(other, e, dir))		// hacemos daño
	{
		Tool::animOnCollision(other, e);	// Animación a realizar al golpear con algo
		instance_destroy();					// una vez hecho daño nos destruimos
	}
}