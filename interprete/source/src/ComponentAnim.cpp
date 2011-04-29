#include "ComponentAnim.h"

ComponentAnim::ComponentAnim(Game* game, Controller* cont) : Component()
{
	this->cont = cont;
	this->game = game;
};

void ComponentAnim::onCInit(Enemy* e)
{
	this->e = e;
	alreadyPlaying = false;
	e->graphic = new SpriteMap(e->gfxPath, 5, 4, game->getGfxEngine());

	loadAnimations(getConfigurationFileName(e->gfxPath));
};

void ComponentAnim::onCRender(Enemy* e)
{
	e->Entity::onRender();
};

void ComponentAnim::onCStep(Enemy* e)
{
	if (e->inAnim && !alreadyPlaying){
		playAnim(e->currentAnim);
		alreadyPlaying = true;
	}
	if (((SpriteMap*) e->graphic)->animFinished()){
		e->inAnim = false;
		alreadyPlaying = false;
	}
};


std::string ComponentAnim::getAnimName(Enemy::StandardEnemyAnimation anim, Direction dir)
{
	if (dir == NONE) dir = e->dir;
	// Se obtiene el nombre de la animación a partir del enum
	std::map<std::pair<Enemy::StandardEnemyAnimation, Direction>, std::string>::iterator it;
	it = animList.find(make_pair(anim, dir));
	// Si el iterador alcanca el final de la lista, no está la anim
	if (it == animList.end())
		return "";
	else
		return (*it).second;
};


bool ComponentAnim::playAnim(Enemy::StandardEnemyAnimation anim, int speed, Direction dir)
{
	if (dir == NONE)
		dir = e->dir;
	// Si la animación no existe, seguro que no se puede
	std::string name = getAnimName(anim, dir);
	if (name == "")
		return false;

	// Si la animación no tiene datos, algo va mal
	EnemyAnimData data = getAnimationData(anim, dir);
	if (data.numFrames < 0)
		return false;

	if (speed < 0)
		speed = data.animSpeed;

	// 1. Comprobación de estado actual: ¿permite manipulación?
	if (alreadyPlaying)
		return false;
	// 2. Establecer nueva animación
	((SpriteMap*) e->graphic)->playAnim(name, speed, false, false);
	e->currentAnim = anim;

	return true;
};

std::string ComponentAnim::getConfigurationFileName(std::string fname)
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

bool ComponentAnim::loadAnimations(std::string fname)
{
	SpriteMap* gfx = ((SpriteMap*) e->graphic);
	int sprW = 0, sprH = 0;

	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Ancho y alto de imagen (?)
	if (fscanf(f, "%d %d", &sprW, &sprH) < 2)
		return false;

	// 2. Leer todas las animaciones
	// Stand
	loadAnimation(Enemy::STAND, UP, "stu", f);
	loadAnimation(Enemy::STAND, DOWN, "std", f);
	loadAnimation(Enemy::STAND, LEFT, "stl", f);
	loadAnimation(Enemy::STAND, RIGHT, "str", f);

	// Walk
	loadAnimation(Enemy::WALK, UP, "wau", f);
	loadAnimation(Enemy::WALK, DOWN, "wad", f);
	loadAnimation(Enemy::WALK, LEFT, "wal", f);
	loadAnimation(Enemy::WALK, RIGHT, "war", f);

	// AtkMelee
	loadAnimation(Enemy::ATKMELEE, UP, "amu", f);
	loadAnimation(Enemy::ATKMELEE, DOWN, "amd", f);
	loadAnimation(Enemy::ATKMELEE, LEFT, "aml", f);
	loadAnimation(Enemy::ATKMELEE, RIGHT, "amr", f);

	// AtkRanged
	loadAnimation(Enemy::ATKRANGED, UP, "aru", f);
	loadAnimation(Enemy::ATKRANGED, DOWN, "ard", f);
	loadAnimation(Enemy::ATKRANGED, LEFT, "arl", f);
	loadAnimation(Enemy::ATKRANGED, RIGHT, "arr", f);

	// AtkSpecial
	loadAnimation(Enemy::ATKSPECIAL, UP, "asu", f);
	loadAnimation(Enemy::ATKSPECIAL, DOWN, "asd", f);
	loadAnimation(Enemy::ATKSPECIAL, LEFT, "asl", f);
	loadAnimation(Enemy::ATKSPECIAL, RIGHT, "asr", f);

	// Damaged
	loadAnimation(Enemy::DAMAGED, UP, "dmu", f);
	loadAnimation(Enemy::DAMAGED, DOWN, "dmd", f);
	loadAnimation(Enemy::DAMAGED, LEFT, "dml", f);
	loadAnimation(Enemy::DAMAGED, RIGHT, "dmr", f);

	// Dead
	loadAnimation(Enemy::DEAD, UP, "deu", f);
	loadAnimation(Enemy::DEAD, DOWN, "ded", f);
	loadAnimation(Enemy::DEAD, LEFT, "del", f);
	loadAnimation(Enemy::DEAD, RIGHT, "der", f);

	fclose(f);

	return true;
};

bool ComponentAnim::loadAnimation(Enemy::StandardEnemyAnimation anim, Direction direction, std::string name, FILE* from)
{
	// Cargar animación indicada de from
	if (from == NULL || name == "")
		return false;

	int numFrames, speed;
	int* frameList;
	EnemyFrameData frameData;
	EnemyAnimData animData;

	// Leemos datos de la animación

	// 0.Speed
	if (fscanf(from, "%d", &speed) < 1)
		return false;

	// 1.Nº frames
	if (fscanf(from, "%d", &numFrames) < 1)
		return false;

	animData.animSpeed = speed;
	animData.numFrames = numFrames;

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
	SpriteMap* gfx = ((SpriteMap*) e->graphic);
	gfx->addAnim(name, frameList, numFrames, speed, true);

	// Se mappea la anim
	animList.insert(make_pair(make_pair(anim, direction), name));
	// Y se agrega su info
	animDataList.insert(make_pair(make_pair(anim, direction), animData));
	delete frameList;

	return true;
};

ComponentAnim::EnemyFrameData ComponentAnim::loadAnimationFrame(FILE* from)
{
	// Se carga un frame de from
	// Se prepara un frame vacío
	EnemyFrameData fd;
	fd.frameId = 0;
	fd.collisionMask.offsetX = 0;
	fd.collisionMask.offsetY = 0;
	fd.collisionMask.width = 0;
	fd.collisionMask.height = 0;
	fd.hotspotX = 0;
	fd.hotspotY = 0;

	// El archivo debe ser válido
	if (from == NULL)
		return fd;

	// Se lee el frameId
	if (fscanf(from, "%d", &fd.frameId) < 1)
		return fd;

	// Se lee el hotspot
	if (fscanf(from, "%d %d", &fd.hotspotX, &fd.hotspotY) < 1)
		return fd;

	// Y por ahora ya
	return fd;
};

ComponentAnim::EnemyAnimData ComponentAnim::getAnimationData(Enemy::StandardEnemyAnimation anim, Direction dir)
{
	if (dir == NONE) dir = e->dir;
	// Se obtiene el nombre de la animación a partir del enum
	std::map<std::pair<Enemy::StandardEnemyAnimation, Direction>, EnemyAnimData>::iterator it;
	it = animDataList.find(make_pair(anim, dir));
	// Si el iterador alcanca el final de la lista, no está la anim
	if (it == animDataList.end())
	{
		EnemyAnimData a; a.animSpeed = -1; a.numFrames = -1;
		return a;
	}
	else
		return (*it).second;
};
