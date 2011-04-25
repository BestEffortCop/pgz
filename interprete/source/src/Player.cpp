#include "Player.h"
#include "PushableTester.h"

// Suponemos que mask y graphic no están inicialmente creados, sino dejaría basura
Player::Player(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world) 
{
	// Creamos la máscara
	mask = new MaskBox(x, y, 12, 8, "player", 2, 14); // offsets están a cero por defecto

	// Cambiamos la configuración por defecto de los flags que nos interesan
	solid = true;
	type = "player";

	lastX = lastY = 0;

	currentInput.xAxis = 0;
	currentInput.yAxis = 0;
	currentInput.buttonA = OFF;
	currentInput.buttonB = OFF;

	inputConfig.joyMode = false;
	inputConfig.gamePad = 0;
	inputConfig.xAxis = 0;
	inputConfig.yAxis = 1;
	inputConfig.joyA = 0;
	inputConfig.joyB = 1;
	
	inputConfig.keyLeft = Input::kLEFT;
	inputConfig.keyRight = Input::kRIGHT;
	inputConfig.keyUp = Input::kUP;
	inputConfig.keyDown = Input::kDOWN;
	inputConfig.keyA = Input::kA;
	inputConfig.keyB = Input::kS;
};

Player::~Player()
{
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
	currentAnim = Stand;
	lastEnemyDirection = NONE;

	dead = false;

	GameEntity::initShadow(GameEntity::sMedium);

	return true;
}

Player::PlayerInputConfig Player::getInputConfig()
{
	return inputConfig;
};

void Player::setInputConfig(Player::PlayerInputConfig config)
{
	inputConfig = config;
};

void Player::parseInput()
{
	// Here be the config and such
	Input* input = game->getInput();

	if (inputConfig.joyMode)
	{
		// Control por gamepad
		currentInput.xAxis = input->joyAxis(inputConfig.gamePad, inputConfig.xAxis);
		currentInput.yAxis = input->joyAxis(inputConfig.gamePad, inputConfig.yAxis);

		if (input->joyPressed(inputConfig.gamePad, inputConfig.joyA))
			currentInput.buttonA = PRESSED;
		else if (input->joyReleased(inputConfig.gamePad, inputConfig.joyA))
			currentInput.buttonA = RELEASED;
		else if (input->joyButton(inputConfig.gamePad, inputConfig.joyA))
			currentInput.buttonA = ON;
		else
			currentInput.buttonA = OFF;

		if (input->joyPressed(inputConfig.gamePad, inputConfig.joyB))
			currentInput.buttonB = PRESSED;
		else if (input->joyReleased(inputConfig.gamePad, inputConfig.joyB))
			currentInput.buttonB = RELEASED;
		else if (input->joyButton(inputConfig.gamePad, inputConfig.joyB))
			currentInput.buttonB = ON;
		else
			currentInput.buttonB = OFF;
	}
	else
	{
		// Control por teclado
		if (input->key(inputConfig.keyLeft)) currentInput.xAxis = -1;
		else if (input->key(inputConfig.keyRight)) currentInput.xAxis = 1;
		else currentInput.xAxis = 0;

		if (input->key(inputConfig.keyUp)) currentInput.yAxis = -1;
		else if (input->key(inputConfig.keyDown)) currentInput.yAxis = 1;
		else currentInput.yAxis = 0;

		if (input->keyPressed(inputConfig.keyA))
			currentInput.buttonA = PRESSED;
		else if (input->keyReleased(inputConfig.keyA))
			currentInput.buttonA = RELEASED;
		else if (input->key(inputConfig.keyA))
			currentInput.buttonA = ON;
		else
			currentInput.buttonA = OFF;

		if (input->keyPressed(inputConfig.keyB))
			currentInput.buttonB = PRESSED;
		else if (input->keyReleased(inputConfig.keyB))
			currentInput.buttonB = RELEASED;
		else if (input->key(inputConfig.keyB))
			currentInput.buttonB = ON;
		else
			currentInput.buttonB = OFF;
	}
};

bool Player::getNewPos(int& xtemp, int& ytemp, int sp)
{
	int move_pixels = sp; // número de píxeles que se mueve el player
	
	if (abs(currentInput.xAxis) > 0.9 && abs(currentInput.yAxis) > 0.9)
		move_pixels = sp-sp/3;

	/*if (currentInput.xAxis > 0.3) xtemp += move_pixels, dir = RIGHT;
	else if (currentInput.xAxis < -0.3) xtemp -= move_pixels, dir = LEFT;
	if (currentInput.yAxis > 0.3) ytemp += move_pixels, dir = DOWN;
	else if (currentInput.yAxis < -0.3) ytemp -= move_pixels, dir = UP;*/
	
	if (abs(currentInput.xAxis) > 0.3)
		xtemp += move_pixels*currentInput.xAxis;
	if (abs(currentInput.yAxis) > 0.3)
		ytemp += move_pixels*currentInput.yAxis;

	if (xtemp < x) dir = LEFT;
	else if (xtemp > x) dir = RIGHT;
	if (ytemp < y) dir = UP;
	else if (ytemp > y) dir = DOWN;

	return ((xtemp != x) || (ytemp != y));
}

void Player::onStep()
{
	int xtemp, ytemp;
	bool moved;

	lastX = x;
	lastY = y;

	if (GameEntity::isPaused())
		return;

	Entity* e;
	iPushable* pushable;
	std::pair<int, int> pushedDistance = make_pair(0, 0);

	switch (state)
	{
		case Normal:
			/* ********************** Normal ************************* */
			xtemp = x;
			ytemp = y;

			// Comprobamos entrada para mover al player
			parseInput();

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

			// Si no está libre el destino, podemos estar empujando
			if (!place_free(xtemp, ytemp))
			{
				currentAction = aPush;
				e = NULL;
				switch (dir)
				{
				case LEFT:
					e = place_meeting(x-mask->width/2, y, "pushable");
					break;
				case RIGHT:
					e = place_meeting(x+mask->width/2, y, "pushable");
					break;
				case UP:
					e = place_meeting(x, y-mask->height/2, "pushable");
					break;
				case DOWN:
					e = place_meeting(x, y+mask->height/2, "pushable");
					break;
				}

				if (e != NULL)
					if (pushable = dynamic_cast<iPushable*>(e))
					{
						pushedDistance = pushable->onPush(e, dir);
						if (dir == LEFT) xtemp -= pushedDistance.first;
						else if (dir == RIGHT) xtemp += pushedDistance.first;
						else if (dir == UP) ytemp -= pushedDistance.second;
						else if (dir == DOWN) ytemp += pushedDistance.second;
					}
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
			currentAnim = Stand;
			break;
		case aWalk:
			((SpriteMap*) graphic)->playAnim(getAnimName(Walk, dir));
			currentAnim = Walk;
			break;
		case aPush:
			((SpriteMap*) graphic)->playAnim(getAnimName(Walk, dir));
			currentAnim = Walk;
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
		graphic->setAlpha(0.7f);
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

bool Player::playAnim(PlayerAnim anim, int speed, Direction dir)
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

	if (speed < 0)
		speed = data.animSpeed;

	// 1. Comprobación de estado actual: ¿permite manipulación?
	if (state == Animation)
		return false;
	// 2. Almacenar estado, animación y cosas actuales
	savedState = state;
	// 3. Establecer nueva animación
	state = Animation;
	((SpriteMap*) graphic)->playAnim(name, speed, false, false);
	currentAnim = anim;

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
		if ((state == Damaged || state == Attack || state == Animation) && (next != Normal && next != Dead))
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
#ifdef _VS2008_
	cfgname.substr(0, cfgname.size()-3);
#endif
#ifdef _VS2010_
	for (int i = 0; i < 3; i++)
		cfgname.pop_back();
#endif
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

	// Se lee el hotspot
	if (fscanf(from, "%d %d", &fd.hotspotX, &fd.hotspotY) < 1)
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

std::pair<int, int> Player::getCurrentHotSpot()
{
	int frame = ((SpriteMap*) graphic)->getCurrentFrame();
	if (frame >= getAnimationData(currentAnim, dir).frameData.size())
		return make_pair(0, 0);
	PlayerFrameData d = getAnimationData(currentAnim, dir).frameData.at(frame);
	return make_pair(d.hotspotX, d.hotspotY);
};

void Player::onRender()
{
	GameEntity::onRender();
	// Hotspot
	//game->getGfxEngine()->renderRectangle(x + getCurrentHotSpot().first, y + getCurrentHotSpot().second, 2, 2, Color::Green);
};

Controller* Player::getController()
{
	return controller;
};

void Player::onCollision(CollisionPair pair, Entity* other)
{
	if (pair.b == "npc")
		toLastPosition();
};