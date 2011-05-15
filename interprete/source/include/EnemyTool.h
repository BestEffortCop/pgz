#pragma once

#ifndef __ENEMYTOOl_H__
#define __ENEMYTOOL_H__

#include "Enemy.h"
#include "ComponentAnim.h"

class Enemy;

class EnemyTool: public GameEntity
{
private:
	// Carga todas las animaciones de una imagen
	/*	graphicpath: ruta de la imagen
		fname: fichero de configuración de la imagen */
	bool loadAnimations(std::string graphicpath, std::string fname);
	int distTravelled;

protected:

	//------------------------- Tipos auxiliares -----------------------------------------

	struct FrameData
	{
		int frameId;
		int hotspotX, hotspotY;
		int offsetX, offsetY, width, height; // datos de la máscara
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
	int idEnemyToolType;	// Identificador para que podamos clasificar en la DB los tipos de EnemyTools
	int atkCoolDown;		// Cuanto espera antes de poder volver a activarse
	int atkRange;		// Distancia que se desplaza
	int atkTravelSpeed;	// Velocidad a la que se mueve la EnemyTool
	int atkDamage;			// Daño que hace el EnemyTool
	Enemy* enemy;		// Puntero al enemy
	Direction dir;	// dirección en la que nos dirigimos
	std::map<std::string, EnemyToolAnimData> animList;  // mapa que guarda la información de cada animación

	bool active; // indica si ya estamos activados
	
	// --------------------- Métodos de auxiliares ----------------------------

	// Carga una animación de la herramienta (si es una herramienta animada)
	bool loadAnimation(Direction dir, std::string name, FILE* from);

	// Coge el identificador de un frame del archivo de configuración
	FrameData loadAnimationFrame(FILE* from);

	// Devuelve el nombre del fichero de configuración de una imagen
	std::string getConfigurationFileName(std::string fname);

	// Realiza la animación seleccionada
	bool playAnim(std::string name);

	/* Coloca la herramienta en el sitio indicado teniendo en cuenta el hotspot actual del enemy,
	y el frame actual de la animación */
	void placeTool();

public:

	EnemyTool(int x, int y, Game* game, GameState* world);
	~EnemyTool();

	// minima distancia con la que es capaz de golpear al jugador
	int mindist;

	// inicia la herramienta
	void init(Enemy* e, int idTool, std::string graphicpath);
	
	// Indica si ha acabado la animación de la herramienta
	bool animFinished();

	// acción a realizar cuando se active la herramienta
	virtual void activate();

	bool isActive();

	void setCoolDown(int cool);
	void setRange(int range);
	void setTravelSpeed(int ts);
	void setDamage(int dmg);

	virtual void onStep();
	virtual void onRender();
	virtual void onTimer(int n);
	virtual void onCollision(CollisionPair pair, Entity* other);
	
};
#endif
