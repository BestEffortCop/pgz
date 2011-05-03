#include "DamageableBlockade.h"


DamageableBlockade::DamageableBlockade(int x, int y, Game* game, GameState* gameState):Entity(x,y,game,gameState)
{
	dying = false;
}

void DamageableBlockade::init(short typeWeakness, string gfxPath, int xColision, int yColision)
{
	iDamageable::init(1,1,0,typeWeakness);
	loadAnimations(gfxPath);
	this->mask = new MaskBox(x, y, xColision, yColision, "DamageableBlockade");
	this->solid = true;
	((SpriteMap*) graphic)->playAnim("stand");
}

/*/////////////////////////////////////////////////////////////////////////////////////////
El archivo de configuración contiene columnas y filas, velocidad y numero de frames
y luego 4 enteros que serán la animación de parado y otros 4 de la animacion de muerte
/////////////////////////////////////////////////////////////////////////////////////////*/

bool DamageableBlockade::loadAnimations(string fname)
{
	// se busca extensión
    size_t found = fname.find_last_of(".");
        
    //Si la encuentra
    if (found != string::npos){
            //Se descarta 
            fname = fname.substr(0,found);
    }
	
	// Se almacena el nombre de archivo sin extensión
    string fnameConf = fname;

    // carga configuracion y tileSet de los ficheros correspondientes
    //nombreArchivo.png
    fname = fname.append(".png");
    //nombreArchivo.txt
    fnameConf= fnameConf.append(".cfg");
	
	// Carga el archivo de config y lee
	FILE* f = fopen(fnameConf.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Ancho y alto de imagen 
	int ncol = 0, nrow = 0;
	if (fscanf(f, "%d %d", &ncol, &nrow) < 2)
		return false;

	//Una vez tengo ya el ancho y el alto puedo cargar el SpriteMap que será mi grafico
	graphic = new SpriteMap(fname, ncol, nrow, game->getGfxEngine());
	
	// Leo todas las animaciones
	// Stand
	loadAnimation(Stand, "stand", f);

	//Death
	loadAnimation(Death, "death", f);

	//Cierro el archivo y salgo
	fclose(f);

	return true;
};


bool DamageableBlockade::loadAnimation(BlockadeAnim anim, string name, FILE* file)
{
	// Cargar animación indicada de from
	if (file == NULL || name == "")
		return false;

	int numFrames, speed, auxFrame;
	int* frameList;

	// Leemos datos de la animación

	// Speed
	if (fscanf(file, "%d", &speed) < 1)
		return false;

	// Nº frames
	if (fscanf(file, "%d", &numFrames) < 1)
		return false;

	// Se instancia el contenedor de frames
	frameList = new int[numFrames];

	// Se carga cada frame
	for (int i = 0; i < numFrames; i++)
	{
		if (fscanf(file, "%d", &auxFrame) < 1)
			return false;
		frameList[i] = auxFrame;
	}

	// Se añade la animación al graphic con el nombre indicado
	SpriteMap* spMap = ((SpriteMap*) graphic);
	spMap->addAnim(name, frameList, numFrames, speed, true);

	delete frameList;

	return true;
}

void DamageableBlockade::onStep()
{
	if (dying)
		if (((SpriteMap*) graphic)->animFinished())
			instance_destroy();
}

void DamageableBlockade::onDeath()
{
	((SpriteMap*) graphic)->playAnim("death",(float) 1,false);
	dying = true;
}

//esto está temporal, es el arma el que deberia llamar a la onDamage
/*void DamageableBlockade::onCollision(CollisionPair other, Entity* e)
{
	if (other.b == "tool")
	{
		// Si algun arma nos colisiona nos hace daño
		onDamage(1, PHYSICAL);
	}
}*/