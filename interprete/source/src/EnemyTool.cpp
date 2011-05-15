#include "EnemyTool.h"

// Inicialización por defecto
EnemyTool::EnemyTool(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world)
{
	enemy = NULL;
	// nos ponemos invisibles por defecto
	game->getGameState()->add(this);
	setVisible(false);
	atkRange = 0;
	// por ejemplo
	mindist = 200;
}

EnemyTool::~EnemyTool()
{
}

void EnemyTool::activate()
{
	// Si no estamos ya activados
	if(!active){

		collidable = true;
		EnemyToolAnimData data;
		std::string name;
		distTravelled = 0;

		// nos activamos y preparamos el timer para desactivarnos
		active = true;
		setTimer(1, atkCoolDown);
		// seteamos la direccion
		dir = enemy->dir;

		// Ejecutamos la animación correspondiente en función de la dirección a la que mira el player
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
		case RIGHT:
			name = "right";
			break;
		}

		enabled = true;
		setVisible(true);
		playAnim(name);									// ejecutamos la animación

		placeTool();	// Colocamos el arma en función de la animación actual
	}
}

void EnemyTool::onStep()
{
	if (active){
		int xtmp = x;
		int ytmp = y;

		// Movimiento de la munición en función de la dirección y de la velocidad
		switch (dir)
		{
		case UP:
			ytmp -= atkTravelSpeed;
			break;
		case DOWN:
			ytmp += atkTravelSpeed;
			break;
		case LEFT:
			xtmp -= atkTravelSpeed;
			break;
		case RIGHT:
			xtmp += atkTravelSpeed;
			break;
		}
		
		// si ya hemos recorrido la distancia maxima nos descativamos
		if (distTravelled >= atkRange && atkRange != 0){
			x = -1;
			y = -1;
			collidable = false;
			active = false;
			setVisible(false);
			enabled = false;
			setTimer(0,0);
		}
		// Actualizamos la distancia recorrida
		else distTravelled += atkTravelSpeed;

		// De momento no hacemos ninguna comprobación
		x = xtmp; y = ytmp;

		// Actualizamos la profundidad del gráfico
		depth = y;
	}
}

void EnemyTool::init(Enemy* e, int idTool, std::string graphicpath)
{
	this->enemy = e;
	this->idEnemyTool = idTool;
	dir = NONE;
	active = false;

	// cargamos las diferentes animaciones de la herramienta
	loadAnimations(graphicpath, getConfigurationFileName(graphicpath));
}

std::string EnemyTool::getConfigurationFileName(string fname)
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

bool EnemyTool::loadAnimation(Direction dir, std::string name, FILE* from)
{
	// Cargar animación indicada de from
	if (from == NULL || name == "")
		return false;

	int numFrames, speed;
	int* frameList;
	EnemyToolAnimData animData;
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

EnemyTool::FrameData EnemyTool::loadAnimationFrame(FILE* from)
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

	if (mindist > fd.height)
		mindist = fd.height;
	if (mindist > fd.width)
		mindist = fd.width;

	// Y por ahora ya
	return fd;
}

bool EnemyTool::playAnim(std::string name)
{
	// Si la animación no existe, algo va mal
	std::map<std::string, EnemyToolAnimData>::iterator it;
	it = animList.find(name);
	if (it == animList.end())
		return false;
	// Si la animación no tiene datos, algo va mal
	EnemyToolAnimData data = (*it).second;
	if (data.numFrames < 0)
		return false;

	// Establecer nueva animación
	if(graphic != NULL) ((SpriteMap*) graphic)->playAnim(name, data.animSpeed, true, false);

	return true;
}

bool EnemyTool::animFinished()
{
	if(graphic != NULL)
		return ((SpriteMap*) graphic)->animFinished();
	else
		return true;
}

static int hEX=0, hEY=0, hTX =0, hTY =0;

void EnemyTool::placeTool()
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
		if(enemy->cAnim != NULL){
			int hotEnemyX, hotEnemyY;
		
			int eframe = ((SpriteMap*) enemy->graphic)->getCurrentFrame();
			if (eframe >= enemy->cAnim->getAnimationData(enemy->currentAnim, dir).frameData.size()){
				hotEnemyX = 0;
				hotEnemyY = 0;
			}
			else 
			{
				ComponentAnim::EnemyFrameData d = enemy->cAnim->getAnimationData(enemy->currentAnim, dir).frameData.at(eframe);
				hotEnemyX = d.hotspotX;
				hotEnemyY = d.hotspotY;
			}

#ifdef _VS2010_
			EnemyToolAnimData animData = animList.at(name); // cogemos la información de la animación actual
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

			// Actualizamos la posición en función del hotspot del enemy y del hotspot del frame actual de la espada
			x = enemy->x + hotEnemyX - fd.hotspotX;
			y = enemy->y + hotEnemyY - (fd.hotspotY); // No se WHYTF tengo que sumarle la altura pero asi es la vida

			// Actualizamos la máscara
			if (mask != NULL) delete mask; // borramos la antigua
			mask = new MaskBox(x, y, fd.width, fd.height, "enemyTool", fd.offsetX, fd.offsetY); // creamos la nueva en la posición actual
			
			hEX = enemy->x + hotEnemyX;
			hEY = enemy->y + hotEnemyY;
			
			// Actualizamos la profundidad del gráfico
			depth = y;
		}
	}
}

bool EnemyTool::loadAnimations(std::string graphicpath, std::string fname)
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

	// creamos el gráfico de la herramienta
	graphic = new SpriteMap(graphicpath, nCols, nRows, game->getGfxEngine());

	// 2. Leer las animaciones
	loadAnimation(UP, "up", f);
	loadAnimation(DOWN, "down", f);
	loadAnimation(LEFT, "left", f);
	loadAnimation(RIGHT, "right", f);

	fclose(f);

	return true;
}

void EnemyTool::onRender()
{
	if (visible)
		GameEntity::onRender();
}

bool EnemyTool::isActive(){
	return active;
}

void EnemyTool::onTimer(int timer)
{
	if (timer == 1){
		x = -1;
		y = -1;
		collidable = false;
		active = false;
		setVisible(false);
		enabled = false;
		}
}

void EnemyTool::onCollision(CollisionPair pair, Entity* other)
{
	if (pair.b == "player"){
		((Player*) other)->setLastEnemyDirection(dir);
		((Player*) other)->onDamage(enemy->strength, 0x1);
	}

	if (pair.b == "coltest")
	{
		this->instance_destroy();
	}
};

void EnemyTool::setCoolDown(int cool)
{
	atkCoolDown = cool;
}

void EnemyTool::setRange(int range)
{
	atkRange = range;
}

void EnemyTool::setTravelSpeed(int ts)
{
	atkTravelSpeed = ts;
}

void EnemyTool::setDamage(int dmg)
{
	atkDamage = dmg;
}