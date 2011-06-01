/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#ifndef _GAMESTATUS_H
#define _GAMESTATUS_H

#include <map>

#include "HelperTypes.h"

//!Mantiene la persistencia de datos relacionada con el juego
//!
//	Recibirá toda la información de controller y permitirá mantener y actualizar la información sobre el juego
//	\sa Controller 
class GameStatus 
{
private:

	int numKeyItems;

	int maxLife;

	//tabla de herramientas disponibles
	std::map<int,ToolInfo> tools;

	int currentMoney;

	//Mapa y pantalla del mapa actual <mapId,mapX,mapY>
	MapLocation currentMapLocation;

	//Ultima posición de aparición del player <lastX,lastY>
	std::pair<int,int> lastPlayerPosition;

	int numPlayers;

	int numPigeons;

	int currentHeartPieces;

	int barterProgress;

	int gameProgress;

	void mapCopy(std::map<int,bool> * m, char id);


public:
	//!Instancia los atributos de GameStatus
	GameStatus();

	//!Destructora de GameStatus
	~GameStatus();

	//!Inicializa los atributos de GameStatus
	void init(int numKeyItems, int maxLife, std::map<int,ToolInfo> tools, int currentMoney, MapLocation currentScreen, std::pair<int,int> lastPos, int numPlayers, int numPigeons);

	//!Getter de numKeyItems
	//!
	//			\return numKeyItems
	int getNumKeyItems();

	//!Setter de numKeyItems
	//!
	//			\param numKeyItems nuevo valor para numKeyItems
	void setNumKeyItems(int numKeyItems);

	//!Getter de maxLife
	//!
	//			\return maxLife
	int getMaxLife();

	//!Setter de maxLife
	//!
	//			\param maxLife nuevo valor para maxLife
	void setMaxLife(int maxLife);

	//!Getter de tools
	//!
	//			\return el mapa de tools
	std::map<int, ToolInfo> getTools();

	//!Setter de tools
	//!
	//			\param tools mapa de tools que queremos añadir
	void setTools(std::map<int, ToolInfo> tools);

	//!Busca un elemento en el mapa de tools y obtiene toda la información relacionada
	//!
	//			\param idTool id de la tool sobre la que queremos realizar la bísqueda
	//			\return std::tr1::tuple<bool,int,int> una tupla con la información de idTool
	ToolInfo getToolInfo(int idTool);

	//!Actualiza la información de una herramienta dada
	//!
	//			Los parametros a actualizar o insertar de la herramienta son:
	//			\param idTool id de la herramienta que queremos actualizar
	//			\param available indica si la herramienta estará o no disponible para el uso del jugador
	//			\param idAmmo id de la munición de la herramienta dada
	//			\param ammoQuantity cantidad de munición disponible para la herramienta
	//			\return tupla con toda la información de la idTool
	void setTool(int idTool, bool available, int idAmmo, int ammoQuantity);

	//! Indica si una herramienta dada está o no disponible
	//!
	//			\param idTool herramienta sobre la que se realiza la petición
	//			\return true si se puede usar false sino
	bool isToolAvailable(int idTool);

	//!Actualiza la información sobre la disponibilidad de una herramienta dada
	//!
	//			\param idTool id de la herramienta a actualizar
	void setToolAvailable(int idTool, bool available);

	//!Devuelve el tipo de munición que usa una herramienta
	//!
	//			\param idTool identificador de la herramienta a modificar
	//			\return id de la munición
	int getToolAmmoId(int idTool);

	//!Devuelve la cantidad de munición disponible para una herramienta dada
	//!
	//			\param idTool identificador de la herramienta dada
	//			\return cantidad de munición disponible
	int getToolAmmoQuantity(int idTool);

	//!Asigna el tipo de munición de una herramienta dada
	//!
	//			\param idTool id de la herramienta a actualizar
	//			\param idAmmo id del tipo de munición a asignar
	void setToolAmmo(int idTool, int idAmmo);

	//!Establece la cantidad de munición de una herramienta dada
	//!
	//			\param idTool identificador de la herramienta a actualizar
	//			\param ammoQuantity cantidad de munición que tendrá dicha herramienta
	void setToolAmmoQuantity(int idTool, int ammoQuantity);

	//! Getter de actualMoney
	//!
	//			\return actualMoney
	int getCurrentMoney();

	//!Setter de actualMoney
	//!
	//			\param actualMoney
	void setCurrentMoney(int actualMoney);

	//!Getter de actualScreen
	//!
	//			\return actualScreen como un struct definido en HelperTypes
	MapLocation getCurrentMapLocation();

	//!Setter de actualScreen
	//!
	//			\param actualScreen
	void setCurrentMapLocation(MapLocation mapLocation);

	//!Getter de lastPos
	//!
	//			\return lastPos
	std::pair<int,int> getLastPlayerPosition();

	//!Setter de lastPos
	//!
	//			\param un par que representa lastPos
	void setLastPlayerPosition(std::pair<int,int> lastPos);

	//!Getter de numPlayers
	int getNumPlayers();

	//!Setter de numPlayers
	//!
	//			\param numPlayers número de jugadores en la partida actual
	void setNumPlayers(int numPlayers);

	//!Getter de numPidgeons
	//!
	//			\return el numero de pidgeons conseguidos
	int getNumPigeons();

	//!Setter de numPidgeons
	//!
	//			\param numPidgeons establece el número de pidgeons conseguidos
	void setNumPigeons(int numPigeons);

	//!Getter de numHeartPieces
	int getCurrentHeartPieces();

	//!Setter de numHeartPieces
	void setCurrentHeartPieces(int heartPieces);

	//!Getter de barterProgress
	int getBarterProgress();

	//!Setter de barterProgress
	void setBarterProgress(int barterProgress);

	//!Getter de gameProgress
	int getGameProgress();

	//!Setter de gameProgress
	void setGameProgress(int gameProgress);

	void save(FILE* f);
	void load(FILE* f);
};

#endif
