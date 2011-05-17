#pragma once

#ifndef _GEN_ZONE_H_
#define _GEN_ZONE_H_

#include <vector>
#include <queue>

#include "Overworld.h"
#include "GenDungeon.h"
#include "OwScreen.h"
#include "SafeZoneInfo.h"
#define UPDIR 1
#define RIGHTDIR 2 
#define DOWNDIR 3
#define LEFTDIR 4

using namespace std;

// Clase contenedor que delimita una zona del mundo mediante un polígono.
/*
	Con un conjunto de puntos, por afinidad, se determina la forma de la zona sobre se realizará toda la funcionalidad asociada a la clase.
	Esto abarca la posibilidad de colocar zonas seguras, mazmorras y comprobar dadas unas coordenadas enteras de un tile en mapTileMatrix, su pertenencia
	a la zona.
*/

class GenZone {

	protected:
		// Atributos de la clase GenZone
		string zone; //Tipo de la zona (bosque, desierto, etc...)
		short idTileSet;
		short gameDifficulty;  //dificultad del juego

		int zoneNumber; //Número de la zona dentro del overworld(internamente, para nosotros)
		int dungEntranceTile;
		int dungEntranceScreenN;
		short numEnemies;

		GenDungeon * genDungeon; //la fabrica ^^.
		short numDungeon;
		short idTool;
		short ratioDungeon;
		vector<SafeZoneInfo>* safeZones;

		Decorator* decorator;

		// Mini-matriz
		vector<OwScreen*>* screenList;
		Overworld* overworld;
		DBManager* myDB;



		bool isTileInZone(MapTile* tile);

		
		
		
		
	public:
		// Construye un delimitador de zonas mediante un stl::vector indicando el tipo de la misma.
		/*
			shape vector de coordenadas de tile que definen un polígono para una zona del mundo.
			typeId tipo de zona.
		*/
		GenZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies, short difficulty,
			    GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator,DBManager* myDB);

		// Destructora
		virtual ~GenZone();

		/* Permite colocar un mazmorra dentro de la zona de forma pseudo-aleatoria o bien mediante una posición especificada por parámetro.
			Se ha de tomar decisiones sobre la tool y el keyObject que se le proporcionará al generador de mazmorras entre los conjuntos dados.
			Así mismo se determina la dificultad de la mazmorra mediante los parámetros gameDiff y dungNumber en este nivel.
		*/
		virtual void placeDungeon() = 0;

		virtual void placeBlockades() = 0;

		// Por decidir, de primeras coloca la entrada a una zona segura.
		/*
			idZone tipo de zona segura.
			pos posición donde colocar la entrada a la zona segura. Si es NULL se coloca de forma pseudo-aleatoria.
		*/
		virtual void placeSafeZone(int idZone,GPoint* pos=NULL) = 0;

		// Invoca el genScreens de cada OwScreen en nuestra screenList.
		virtual void genScreens() = 0;

		//Creamos bloques grandes de Bloques Geológicos
		virtual void genGeoDetail() = 0;

		//Elige los tiles decorando la zona
		virtual void genDetail() = 0;


		// Permite cambiar el tipo de la zona
		string getZone();

		short getNumEnemies();

		// Comprueba si el tile pos en mapTileMatrix se encuentra en el polígono asociado a la zona y si es así devuelve el MapTile correspondiente.
		/*
			pos coordenadas x e y de un tile en mapTileMatrix.
		*/
		MapTile* inZone(GPoint pos);

		// Devuelve el número de orden de la mazmorra que se encuentra en la zona.
		int getNumDungeon();

		// Establece un nuevo número de orden de la mazmorra de la zona.
		void setNumDungeon(int dunNum);

		// Añade un OwScreen a screenList.
		void addScreen(OwScreen* ows);

		virtual int getTileOfScreen(int& screenNumber) = 0;
		

		int getNumScreens();

		int getDungEntranceTile();
		int getZoneNumber();
};

#endif
