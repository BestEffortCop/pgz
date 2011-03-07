#include "SpriteMap.h"


SpriteMap::SpriteMap(string fname, int nCol, int nRow, GfxEngine* gfxEngine) : Graphic()
{
	list = new map<string,Anim2D*>();
	currentAnim = NULL;
	img = new Image(fname,gfxEngine);
	this->gfxEngine = gfxEngine;
	logger = Logger::Instance();
	currentFramesPerStep = 0;
	currentLoop = false;
	frame = 0;
	lastFrame = 0;
	step = 1;
	this->nCol = nCol;
	this->nRow = nRow;
	finished = false;
}


void SpriteMap::deleteAnimMap()
{
	//Creamos un iterador para el map y lo inicializamos
	map< string, Anim2D* >::iterator it = list->begin();
	Anim2D* tmp;
	
	while (it != list->end())
	{
		//Referenciamos en el temporal la posible animación a borrar
		tmp = it->second;
		it++;
		//Si hay animación asociada en esa posición del map, la borramos
		if (tmp)
			delete tmp;
	}
	delete list;
}


SpriteMap::~SpriteMap() 
{
	//borro las animaciones y la imagen
	deleteAnimMap();
	delete img;
	Logger::DestroyInstance();
}


void SpriteMap::addAnim(string name, vector<int>* frameList, int framesPerStep, bool loop)
{
	//Creo la animación y la añado a la lista de animaciones
	Anim2D* temp = new Anim2D(name, frameList, framesPerStep, loop);
	list->insert(make_pair(name, temp));
}



void SpriteMap::addAnim(string name, int* frameList, int numFrames, int framesPerStep, bool loop)
{
	//Creo un vector para guardar la lista de frames
	vector<int>* temp = new vector<int>(numFrames);
	
	//Añado los frames a la lista
	for (int i = 0; i < numFrames; i++)
		(*temp)[i] = frameList[i];
		
	//Creo la animación y la añado a la lista de animaciones
	Anim2D* aux = new Anim2D(name, temp, framesPerStep, loop);
	list->insert(make_pair(name, aux));
}


void SpriteMap::addAnim(Anim2D* a)
{
	list->insert(make_pair(a->getName(), a));
}


bool SpriteMap::nextFrame() 
{
	//Si se ha alcanzado el número de pasos del juego que hacen falta para cambiar de frame, 
	//reinicio el numero de pasos de juego y aviso de que toca cambiar de frame
	if (step >= currentFramesPerStep) 
	{
		step = 1;
		return true;
	}
	//Si no, aumento el numero de pasos de juego desde el último cambio de frame, y aviso de que 
	//aún no toca cambiar
	else 
	{
		step++;
		return false;
	}
}


void SpriteMap::playAnim(string name)
{
	// Creamos un iterador para map
	map<string, Anim2D*>::iterator it;
	//Pido que busque la animación solicitada
	it = list->find(name);
	if (it == list->end())
		//Si no está hemos acabado
		return;
	else
	{
		//Si no hay animación actual o no es la que me piden, copio la nueva en currentAnim
		if (!(currentAnim && (currentAnim->getName() == name)))
		{
			currentAnim = list->find(name)->second;
			currentFramesPerStep = currentAnim->getFramesPerStep();
			currentLoop = currentAnim->getLoop();
			frame = 0; 
			finished = false;
		}
		//Tanto si he tenido que cambiar  de animación como si no, reseteo los parametros de la 
		//animación en curso porque la reproducción es nueva
	}
}
	


void SpriteMap::playAnim(string name, int framesPerStep, bool loop)
{
	//Llamo a playAnim(name) para que haga la parte de reproducir una nueva animación
	playAnim(name);
	
	//Actualizo los parametros de la animación actual para los framesPerStep y la repetición
	currentFramesPerStep = framesPerStep;
	currentLoop = loop;
}


void SpriteMap::playAnim(string name, float frameRate, bool loop)
{
	//Llamo a playAnim(name) para que haga la parte de reproducir una nueva animación
	playAnim(name);

	//Actualizo los parametros de la animación actual para los framesPerStep y la repetición
	currentFramesPerStep = (int) (currentAnim->getFramesPerStep()/frameRate);
	currentLoop = loop;
}


void SpriteMap::stopAnim()
{
	//Si existe animación actual fija como último frame el acutal
	if (currentAnim)
	{
		lastFrame = currentAnim->getFrameList()->at(frame);
	}
}


void SpriteMap::update()
{
	//Si existe animación, no está finalizada y toca cambiar de frame
	if (currentAnim && !finished && nextFrame())
	{
		//Cambio de frame y compruebo si he llegado al final
		frame++;
		if (frame >= currentAnim->getFrameCount()) 
		{
			//Si he llegado al final compruebo si tiene repetición
			if (!currentLoop) 
			{
				//Si no la tiene marco la animación actual como finalizada, reinicio los steps del 
				//juego desde el último cambio de frame, pongo el último frame usado como lastFrame
				//y indico que número fue el ultimo frame reproducido
				finished = true;
				step = 1;
				lastFrame = currentAnim->getFrameList()->at((currentAnim->getFrameCount())-1);
				frame = currentAnim->getFrameCount()-1;
			}
			//Si tiene repetición reinicio el frame y dejo que siga
			else frame = 0;
		}
	}
}
	

void SpriteMap::render(int x, int y) 
{
	//Calculo el ancho y el alto de cada tile
	int w = img->getWidth() / nCol;
	int h = img->getHeigth() / nRow;
	
	//Si hay animación actual
	if (currentAnim) 
	{
		//Calculo la posición en la imagen del frame actual
		int posnum = currentAnim->getFrameList()->at(frame);
		//La paso a coordenadas cartesianas
		pair<int,int> pos = numToXY(posnum);
		//Renderizo la parte de la imagen que va desde (pos.first*w, pos.second*h), es decir, 
		//la esquina superior izquierda del frame, hasta (pos.first*w + w, pos.second*h +h), 
		//es decir la esquina inferior derecha del frame a dibujar, en la posición (x,y) de la
		//imagen por defecto
		gfxEngine->renderPartExt(img, x+originX, y+originY, pos.first*w, pos.second*h, w, h, *color, alpha, scaleH, scaleV, rotation, NULL, originX, originY);
	}
}


pair<int,int> SpriteMap::numToXY(int num)
{
	return make_pair(num % nCol, num / nCol);
}

int SpriteMap::XYToNum(int x, int y)
{
	return x*nCol+y;
}

void SpriteMap::setImg(Image* img)
{
	this->img = img;
}

Image* SpriteMap::getImg()
{
	return img;
}

string SpriteMap::getCurrentAnim()
{
	//Si existe la animación devuelvo el nombre
	if (currentAnim) 
		return currentAnim->getName(); 
	//Si no, digo que no hay animación en curso
	else 
		return "No hay ninguna animación reproduciendose";
}

bool SpriteMap::animFinished()
{
	return finished;
}



