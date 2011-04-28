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
		fname: fichero de configuración de la imagen */
	bool loadAnimations(std::string graphicpath, std::string fname);
	// Puntero al ComponentAnim del enemigo que nos usa
	ComponentAnim* compAnim;

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
	int atkSpeed;		// Velocidad a la que ataca (cuanto espera antes de poder volver a acativarse)
	int atkRange;		// Distancia que se desplaza
	int travelSpeed;	// Velocidad a la que se mueve la EnemyTool
	int damage;			// Daño que hace el EnemyTool
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

	// inicia la herramienta
	void init(Enemy* e, int idTool, std::string graphicpath);
	
	// Indica si ha acabado la animación de la herramienta
	bool animFinished();

	// acción a realizar cuando se active la herramienta
	void activate();

	bool isActive();

	void setAtkSpeed(int sp);
	void setAtkRange(int rg);
	void setTravelSpeed(int ts);
	void setDamage(int dmg);

	void onStep();
	void onRender();
	void onTimer(int n);
	void onCollision(CollisionPair pair, Entity* other);
	
};
#endif
