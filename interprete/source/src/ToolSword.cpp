#include "ToolSword.h"

ToolSword::ToolSword(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world)
{
}

void ToolSword::init(bool passive, Player* p, string graphicpath, int ncol, int nrow)
{
	Tool::init(passive, p);

	// creamos el gráfico de la espada??
	graphic = new SpriteMap(graphicpath, ncol, nrow, game->getGfxEngine());

	// cargamos las diferentes animaciones de la espada
	loadAnimations(getConfigurationFileName(graphicpath));

	// Habrá que crear la máscara acorde con el gráfico para que colisione chupi guay con los enemigos
	// TEMA HOTSPOT Y DEMÁS
}

//
string ToolSword::getConfigurationFileName(string fname)
{
	// El fname debe tener extensión
	if (fname.length() < 5)
		return "";

	std::string cfgname = fname;
	// Se quita la extensión del fname (.png)
	for (int i = 0; i < 3; i++)
		cfgname.pop_back();
	cfgname.append("cfg");

	return cfgname;
};

bool ToolSword::loadAnimations(string fname)
{
	SpriteMap* gfx = ((SpriteMap*) graphic);
	int sprW = 0, sprH = 0;

	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Ancho y alto de imagen (?)
	if (fscanf(f, "%d %d", &sprW, &sprH) < 2)
		return false;

	// 2. Leer las animaciones
	loadAnimation(Direction::UP, "up", f);
	loadAnimation(Direction::DOWN, "down", f);
	loadAnimation(Direction::LEFT, "left", f);
	loadAnimation(Direction::RIGHT, "right", f);
}

bool ToolSword::loadAnimation(Direction dir, std::string name, FILE* from)
{
	// Cargar animación indicada de from
	if (from == NULL || name == "")
		return false;

	int numFrames, speed;
	int* frameList;
	SwordAnimData animData;
	FrameData frameData;

	// Leemos datos de la animación

	// 0.Speed
	if (fscanf(from, "%d", &speed) < 1)
		return false;

	// 1.Nº frames
	if (fscanf(from, "%d", &numFrames) < 1)
		return false;

	animData.animSpeed = speed;
	animData.numFrames = numFrames;
	animData.dir = dir;

	// Se instancia el contenedor de frames
	frameList = new int[numFrames];

	// Se carga cada frame
	for (int i = 0; i < numFrames; i++)
	{
		frameData = loadAnimationFrame(from);
		frameList[i] = frameData.frameId;
		animData.frameData.push_back(frameData);
	}

	// Se añade la animación al graphic con el nombre indicado
	SpriteMap* gfx = ((SpriteMap*) graphic);
	gfx->addAnim(name, frameList, numFrames, speed, true);

	// Se mappea la anim con la dirección
	// Y se agrega su info
	animList.insert(make_pair(name, animData));
	delete frameList;

	return true;
}

// De momento solo devuelve el id del frame
ToolSword::FrameData ToolSword::loadAnimationFrame(FILE* from)
{
	FrameData fd;

	// De momento rellenamos con valores vacíos el resto de campos del framdata
	fd.hotspotX = 0;
	fd.hotspotY = 0;
	fd.offsetX = 0;
	fd.offsetY = 0;
	fd.height = 0;
	fd.width = 0;

	// El archivo debe ser válido
	if (from == NULL)
		return fd;

	// Se lee el frameId
	if (fscanf(from, "%d", &fd.frameId) < 1)
		return fd;

	// Se lee el hotspot
	if (fscanf(from, "%d %d", &fd.hotspotX, &fd.hotspotY) < 1)
		return fd;

	// Se lee la máscara
	if (fscanf(from, "%d %d %d %d", &fd.offsetX, &fd.offsetY, &fd.width, &fd.height) < 1)
		return fd;

	// Y por ahora ya
	return fd;
}

bool ToolSword::playAnim(std::string name)
{
	// Si la animación no tiene datos, algo va mal
	SwordAnimData data = animList.at(name);
	if (data.numFrames < 0)
		return false;

	// Establecer nueva animación
	((SpriteMap*) graphic)->playAnim(name, data.animSpeed, false, false);

	return true;
}

void ToolSword::activate()
{
	Direction dir = player->getDir();
	
	// Ejecutamos la animación correspondiente en función de la dirección a la que mira el player
	switch(dir){
	case Direction::UP:
		/* FALTA: coger coordenadas del player para ejecutar la animación */
		playAnim("up");
		break;
	case Direction::DOWN:
		/* FALTA: coger coordenadas del player para ejecutar la animación*/
		playAnim("down");
		break;
	case Direction::LEFT:
		/* FALTA: coger coordenadas del player para ejecutar la animación*/
		playAnim("left");
		break;
	case Direction::RIGHT:
		/* FALTA: coger coordenadas del player para ejecutar la animación*/
		playAnim("right");
		break;
	}
}