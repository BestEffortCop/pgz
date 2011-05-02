#include "Tool.h"

// Inicialización por defecto
Tool::Tool(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world)
{
	passive = true;
	player = NULL;

	// tipo de la máscara
	type = "tool";
}

Tool::~Tool()
{
}

void Tool::init(bool passive, Player* p, int idTool, int damage, short damageType)
{
	this->passive = passive;
	this->player = p;
	this->idTool = idTool;
	this->damage = damage;
	this->damageType = damageType;
}

bool Tool::isPassive()
{
	return passive;
}

bool Tool::loadAnimations(std::string graphicpath, std::string fname)
{
	SpriteMap* gfx = ((SpriteMap*) graphic);
	int nCols = 0, nRows = 0;

	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Animación que tendrá que ejecutar el player
	if (fscanf(f, "%d", &playeranim) < 1)
		return false;

	// 2. Ancho y alto de imagen
	if (fscanf(f, "%d %d", &nCols, &nRows) < 2)
		return false;

	// creamos el gráfico de la herramienta
	graphic = new SpriteMap(graphicpath, nCols, nRows, game->getGfxEngine());

	// 3. Leer las animaciones
	loadAnimation(UP, "up", f);
	loadAnimation(DOWN, "down", f);
	loadAnimation(LEFT, "left", f);
	loadAnimation(RIGHT, "right", f);

	fclose(f);

	return true;
}

std::string Tool::getConfigurationFileName(string fname)
{
	// El fname debe tener extensión
	if (fname.length() < 5)
		return "";

	std::string cfgname = fname;
	// Se quita la extensión del fname (.png)

#ifdef _VS2008_
	cfgname.substr(0, cfgname.size()-3);
#endif
#ifdef _VS2010_
	for (int i = 0; i < 3; i++)
		cfgname.pop_back();
#endif

	cfgname.append("cfg");

	return cfgname;
}

bool Tool::loadAnimation(Direction dir, std::string name, FILE* from)
{
	// Cargar animación indicada de from
	if (from == NULL || name == "")
		return false;

	int numFrames, speed;
	int* frameList;
	ToolAnimData animData;
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

Tool::FrameData Tool::loadAnimationFrame(FILE* from)
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

bool Tool::playAnim(std::string name)
{
	// Si la animación no existe, algo va mal
	std::map<std::string, ToolAnimData>::iterator it;
	it = animList.find(name);
	if (it == animList.end())
		return false;
	// Si la animación no tiene datos, algo va mal
	ToolAnimData data = (*it).second;
	if (data.numFrames < 0)
		return false;

	// Establecer nueva animación
	if(graphic != NULL) ((SpriteMap*) graphic)->playAnim(name, data.animSpeed, false, false);

	return true;
}

bool Tool::animFinished()
{
	if(graphic != NULL)
		return ((SpriteMap*) graphic)->animFinished();
	else
		return true;
}

void Tool::placeTool()
{
	// Comprobamos qué animación es la que se está ejecutando
	std::string name;
	if(graphic != NULL)
		name = ((SpriteMap*) graphic)->getCurrentAnim();
	else
		return; // si no existe gráfico no se puede colocar

	// Actualizamos la posición de la entidad si hay alguna animación en curso
	if (name != "none")
	{
		// hotspot actual del player
		pair<int, int> hotPlayer;
		hotPlayer = player->getCurrentHotSpot();
#ifdef _VS2010_
		ToolAnimData animData = animList.at(name); // cogemos la información de la animación actual
#endif
#ifdef _VS2008_
		// Si la animación no existe, algo va mal
		std::map<std::string, ToolAnimData>::iterator it;
		it = animList.find(name);
		if (it == animList.end())
			return;
		// Si la animación no tiene datos, algo va mal
		ToolAnimData animData = (*it).second;
#endif

		int frame = ((SpriteMap*) graphic)->getCurrentFrame(); // cogemos el frame actual
		FrameData fd = animData.frameData[frame];

		// Actualizamos la posición en función del hotspot del player y del hotspot del frame actual de la espada
		x = player->x + hotPlayer.first - fd.hotspotX;
		y = player->y + hotPlayer.second - fd.hotspotY;

		// Actualizamos la máscara
		if (mask != NULL) delete mask; // borramos la antigua
		mask = new MaskBox(x, y, fd.width, fd.height, "tool", fd.offsetX, fd.offsetY); // creamos la nueva en la posición actual

		// Actualizamos la profundidad del gráfico
		depth = y;
	}
}
