#pragma once

#ifndef __ENEMYTOOl_H__
#define __ENEMYTOOL_H__

#include "Enemy.h"
#include "ComponentAnim.h"

class EnemyTool: public GameEntity
{
private:
	// Carga todas las animaciones de una imagen
	/*	graphicpath: ruta de la imagen
		fname: fichero de configuraci�n de la imagen */
	bool loadAnimations(std::string graphicpath, std::string fname);

	ComponentAnim* compAnim;

protected:

	//------------------------- Tipos auxiliares -----------------------------------------

	struct FrameData
	{
		int frameId;
		int hotspotX, hotspotY;
		int offsetX, offsetY, width, height; // datos de la m�scara
	};

	struct EnemyToolAnimData
	{
		int animSpeed;
		unsigned char numFrames;
		Direction dir;
		std::vector<FrameData> frameData;
	};

	// --------------------------- Atributos --------------------------------------

	int idEnemyTool;		// Identificadr de la herramienta
	int atkSpeed;		// Velocidad a la que ataca (cuanto espera antes de poder volver a acativarse)
	int atkRange;		// Distancia que se desplaza
	int travelSpeed;	// Velocidad a la que se mueve la herramienta
	Enemy* enemy;		// Puntero al enemy
	Direction dir;	// direcci�n en la que nos dirigimos
	std::map<std::string, EnemyToolAnimData> animList;  // mapa que guarda la informaci�n de cada animaci�n

	bool active; // indica si ya estamos activados
	
	// --------------------- M�todos de auxiliares ----------------------------

	// Carga una animaci�n de la herramienta (si es una herramienta animada)
	bool loadAnimation(Direction dir, std::string name, FILE* from);

	// Coge el identificador de un frame del archivo de configuraci�n
	FrameData loadAnimationFrame(FILE* from);

	// Devuelve el nombre del fichero de configuraci�n de una imagen
	std::string getConfigurationFileName(std::string fname);

	// Realiza la animaci�n seleccionada
	bool playAnim(std::string name);

	/* Coloca la herramienta en el sitio indicado teniendo en cuenta el hotspot actual del enemy,
	y el frame actual de la animaci�n */
	void placeTool();

public:

	EnemyTool(int x, int y, Game* game, GameState* world);
	~EnemyTool();

	// inicia la herramienta
	void init(Enemy* e, int idTool, std::string graphicpath);
	
	// Indica si ha acabado la animaci�n de la herramienta
	bool animFinished();

	// acci�n a realizar cuando se active la herramienta
	void activate();

	bool isActive();

	void setAtkSpeed(int sp);
	void setAtkRange(int rg);
	void setTravelSpeed(int ts);

	void onStep();
	void onRender();

	// Har� da�o (o no) y se destruir� en el momento en que colisione con algo
	void onCollision(){};

	// On timer que tenemos por extender GameEntity
	void onTimer(int n);
	
};
#endif