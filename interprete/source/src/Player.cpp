#include "Player.h"

#define IMG_WIDTH 14    // ancho de la imagen del player
#define IMG_HEIGHT 15    // alto de la imagen del player

// Suponemos que mask y graphic no están inicialmente creados, sino dejaría basura
Player::Player(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world) {

   // Creamos la máscara
   mask = new MaskBox(x, y, IMG_WIDTH, IMG_HEIGHT, "player", 1, 7); // offsets están a cero por defecto

   // Cambiamos la configuración por defecto de los flags que nos interesan
   solid = true;

   lastX = lastY = 0;
};

Player::~Player()
{
	// Delete todo
	animList.clear();
	animDataList.clear();
};

bool Player::init(std::string gfxpath, int ncol, int nrow, int hp, int mp, Controller* c)
{
	iDamageable::init(hp, hp, 1, 0xFF);
	// Asignamos el gráfico a la entidad player, de momento una imagen estática
	graphic = new SpriteMap(gfxpath, ncol, nrow, game->getGfxEngine());
	this->hp = hp;
	this->mp = mp;

	controller = c;

	loadAnimations(getConfigurationFileName(gfxpath));

	state = Normal;
	dir = DOWN;
	facing = DOWN;
	lastEnemyDirection = NONE;

	dead = false;

	return true;
}

bool Player::getNewPos(int& xtemp, int& ytemp, int sp)
{
	int move_pixels = sp; // número de píxeles que se mueve el player

	if	(((game->getInput()->key(Input::kRIGHT)) || (game->getInput()->key(Input::kLEFT)))
			&&
		 ((game->getInput()->key(Input::kUP)) || (game->getInput()->key(Input::kDOWN))))
		 move_pixels = sp-sp/3;

	if (game->getInput()->key(Input::kRIGHT)) {xtemp += move_pixels; dir = RIGHT;}
	if (game->getInput()->key(Input::kLEFT)) {xtemp -= move_pixels; dir = LEFT;}
		// movimento vertical
	if (game->getInput()->key(Input::kUP)) {ytemp -= move_pixels; dir = UP;}
	if (game->getInput()->key(Input::kDOWN)) {ytemp += move_pixels; dir = DOWN;}

	return ((xtemp != x) || (ytemp != y));
}

void Player::onStep()
{
	int xtemp, ytemp;
	bool moved;

	lastX = x;
	lastY = y;

	switch (state)
	{
		case Normal:
			/* ********************** Normal ************************* */
			xtemp = x;
			ytemp = y;

			// Comprobamos entrada para mover al player

			moved = getNewPos(xtemp, ytemp, 3);

			if (game->getInput()->key(Input::kLCTRL))
				collidable = false;
			else
				collidable = true;

			if (moved)
			{
				if (abs(xtemp - x) >= abs(ytemp - y))
					if ((xtemp - x) >= 0)
						dir = RIGHT;
					else
						dir = LEFT;
				else
					if ((ytemp - y) >= 0)
						dir = DOWN;
					else
						dir = UP;

				currentAction = aWalk;
			}
			else
			{
				currentAction = aStand;
			}

			if (place_free(x, ytemp))
			{    
				y = ytemp; 
			}
			else
			{   
				world->moveToContact(x,ytemp, this);
			}

			if (place_free(xtemp, y))
			{    
				x = xtemp; 
			}
			else
			{   
				world->moveToContact(xtemp,y, this); 
			}

			if (game->getInput()->key(Input::kA))
				playAnim(Slash);
			if (game->getInput()->key(Input::kS))
				playAnim(Thrust);

			break;
		case Animation:
			/* ********************** Animation ************************* */
			if (((SpriteMap*) graphic)->animFinished())
			{
				state = savedState;
			}
			break;
		case Damaged:
			/* ********************** Damaged ************************* */
			xtemp = x, ytemp = y;

			// Bounce del player
			if (lastEnemyDirection == UP) ytemp += getTimer(5)/2;
			else if (lastEnemyDirection == DOWN) ytemp -= getTimer(5)/2;
			else if (lastEnemyDirection == LEFT) xtemp += getTimer(5)/2;
			else if (lastEnemyDirection == RIGHT) xtemp -= getTimer(5)/2;
			else if (lastEnemyDirection == UPLEFT) ytemp += getTimer(5)/2, xtemp += getTimer(5)/2;
			else if (lastEnemyDirection == UPRIGHT) ytemp += getTimer(5)/2, xtemp -= getTimer(5)/2;
			else if (lastEnemyDirection == DOWNLEFT) ytemp -= getTimer(5)/2, xtemp += getTimer(5)/2;
			else if (lastEnemyDirection == DOWNRIGHT) ytemp -= getTimer(5)/2, xtemp -= getTimer(5)/2;

			// Le dejamos que se mueva un poco
			getNewPos(xtemp, ytemp, 2);

			// Actualizamos posición
			if (place_free(x, ytemp))
			{    
				y = ytemp; 
			}
			else
			{   
				world->moveToContact(x,ytemp, this);
			}

			if (place_free(xtemp, y))
			{    
				x = xtemp; 
			}
			else
			{   
				world->moveToContact(xtemp,y, this); 
			}

			break;
		case Cutscene:
			/* ********************** Cutscene ************************* */
			break;
		case Dead:
			/* ********************** Dead ************************* */
			break;
	};
	
	graphic->setColor(Color::White);
	graphic->setAlpha(1);

	// Graphic settings
	switch (state)
	{
	case Normal:
		switch (currentAction)
		{
		case aStand:
			((SpriteMap*) graphic)->playAnim(getAnimName(Stand, dir));
			break;
		case aWalk:
			((SpriteMap*) graphic)->playAnim(getAnimName(Walk, dir));
			break;
		case aPush:
			graphic->setColor(Color::Green);
			break;
		}
		break;
	case Attack:
		graphic->setColor(Color::Red);
		break;
	case Animation:
		if (savedState == Attack)
			graphic->setColor(Color::Red);
		if (savedState == Damaged)
			graphic->setColor(Color::Yellow);
		break;
	case Damaged:
		graphic->setColor(Color::Yellow);
		graphic->setAlpha(0.7);
		break;
	case Cutscene:
		break;
	case Dead:
		graphic->setColor(Color(30, 30, 30));
		break;
	}

	depth = y;
};

Direction Player::getDir()
{
	return dir;
}

std::string Player::getAnimName(PlayerAnim anim, Direction dir)
{
	if (dir == NONE) dir = this->dir;
	// Se obtiene el nombre de la animación a partir del enum
	std::map<std::pair<PlayerAnim, Direction>, std::string>::iterator it;
	it = animList.find(make_pair(anim, dir));
	// Si el iterador alcanca el final de la lista, no está la anim
	if (it == animList.end())
		return "";
	else
		return (*it).second;
};

bool Player::playAnim(PlayerAnim anim, Direction dir)
{
	if (dir == NONE)
		dir = this->dir;
	// Si la animación no existe, seguro que no se puede
	std::string name = getAnimName(anim, dir);
	if (name == "")
		return false;

	// Si la animación no tiene datos, algo va mal
	PlayerAnimData data = getAnimationData(anim, dir);
	if (data.numFrames < 0)
		return false;

	// 1. Comprobación de estado actual: ¿permite manipulación?
	if (state == Animation)
		return false;
	// 2. Almacenar estado, animación y cosas actuales
	savedState = state;
	// 3. Establecer nueva animación
	state = Animation;
	((SpriteMap*) graphic)->playAnim(name, data.animSpeed, false, false);

	return true;
};

// Intenta cambiar al player al estado que sea
bool Player::changeState(PlayerState next, bool forced)
{
	// Si estamos obligados, cambiamos el estado sin más
	if (forced)
		state = next;
	else
	{
		// Si no, comprobamos que se pueda cambiar
		// To be done
		if (state == Damaged && next != Normal && next != Dead)
			return false;
		state = next;
		return true;
	}

	return true;
};

std::string Player::getConfigurationFileName(std::string fname)
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

bool Player::loadAnimations(std::string fname)
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

	// 2. Leer todas las animaciones
	// Stand
	loadAnimation(Stand, UP, "stu", f);
	loadAnimation(Stand, DOWN, "std", f);
	loadAnimation(Stand, LEFT, "stl", f);
	loadAnimation(Stand, RIGHT, "str", f);

	// Walk
	loadAnimation(Walk, UP, "wau", f);
	loadAnimation(Walk, DOWN, "wad", f);
	loadAnimation(Walk, LEFT, "wal", f);
	loadAnimation(Walk, RIGHT, "war", f);

	// Slash
	loadAnimation(Slash, UP, "slu", f);
	loadAnimation(Slash, DOWN, "sld", f);
	loadAnimation(Slash, LEFT, "sll", f);
	loadAnimation(Slash, RIGHT, "slr", f);

	// Thrust
	loadAnimation(Thrust, UP, "thu", f);
	loadAnimation(Thrust, DOWN, "thd", f);
	loadAnimation(Thrust, LEFT, "thl", f);
	loadAnimation(Thrust, RIGHT, "thr", f);

	fclose(f);

	return true;
};

bool Player::loadAnimation(PlayerAnim anim, Direction direction, std::string name, FILE* from)
{
	// Cargar animación indicada de from
	if (from == NULL || name == "")
		return false;

	int numFrames, speed;
	int* frameList;
	PlayerFrameData frameData;
	PlayerAnimData animData;

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
	SpriteMap* gfx = ((SpriteMap*) graphic);
	gfx->addAnim(name, frameList, numFrames, speed, true);

	// Se mappea la anim
	animList.insert(make_pair(make_pair(anim, direction), name));
	// Y se agrega su info
	animDataList.insert(make_pair(make_pair(anim, direction), animData));
	delete frameList;

	return true;
};

Player::PlayerFrameData Player::loadAnimationFrame(FILE* from)
{
	// Se carga un frame de from
	// Se prepara un frame vacío
	PlayerFrameData fd;
	fd.frameId = 0;
	fd.walkMask.offsetX = 0;
	fd.walkMask.offsetY = 0;
	fd.walkMask.width = 0;
	fd.walkMask.height = 0;
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

	// Y por ahora ya
	return fd;
};

Player::PlayerAnimData Player::getAnimationData(PlayerAnim anim, Direction dir)
{
	if (dir == NONE) dir = this->dir;
	// Se obtiene el nombre de la animación a partir del enum
	std::map<std::pair<PlayerAnim, Direction>, PlayerAnimData>::iterator it;
	it = animDataList.find(make_pair(anim, dir));
	// Si el iterador alcanca el final de la lista, no está la anim
	if (it == animDataList.end())
	{
		PlayerAnimData a; a.animSpeed = -1; a.numFrames = -1;
		return a;
	}
	else
		return (*it).second;
};

Player::PlayerState Player::getState()
{
	return state;
};

void Player::onDamage(int damage, short damageType)
{
	if (state != Damaged)
	{
		state = Damaged;
		setTimer(5, 10);
		iDamageable::onDamage(damage, damageType);
	}
	
};

void Player::onTimer(int n)
{
	if (n == 5)
	{
		if (state == Damaged)
			if (!dead)
				state = Normal;
			else state = Dead;
	};
};

void Player::onDeath()
{
	dead = true;
};

void Player::onCollision(CollisionPair other, Entity* e)
{
	/*if (other.a == "solid1")
		onDamage(1, 0x0);*/
};

void Player::toLastPosition()
{
	x = lastX;
	y = lastY;
};

void Player::setLastEnemyDirection(Direction dir)
{
	if (state != Damaged)
		lastEnemyDirection = dir;
};