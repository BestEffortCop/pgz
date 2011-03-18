#pragma once
#ifndef __GAMESTATUS_H__
#define __GAMESTATUS_H__

#include <map>
#include <tuple>
#include "HelperTypes.h"

//!Mantiene la persistencia de datos relacionada con el juego
/*!
	Recibirá toda la información de controller y permitirá mantener y actualizar la información sobre el juego
	\sa Controller 
*/
class GameStatus
{
	private:
		int numKeyItems;
		int maxLife;
		std::map<int,std::tr1::tuple<bool,int,int>> tools;	//tabla de herramientas disponibles <idTool,disponible,<idMunición,cantidad>>
		int actualMoney;
		MapId actualScreen;									//Mapa y pantalla del mapa actual <mapId,mapX,mapY>
		std::pair<int,int> lastPos;							//Ultima posición de aparición del player <lastX,lastY>
		int numPlayers;
		int numPidgeons;
		int numHeartPieces;									//puede tomar valores de 0 a maxHeartPieces
		int maxHeartPieces;
		int barterProgress;
		int gameProgress;
	
	public:

		//!Instancia los atributos de GameStatus
		GameStatus();

		//!Instancia e inicializa los atributos de GameStatus
		GameStatus(int numKeyItems, int maxLife, std::map<int,bool,std::pair<int,int>> tools, int actualMoney,
					std::pair<int,std::pair<int,int>> actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPidgeons,
					int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress);
		
		//!Destructora de GameStatus
		~GameStatus();

		//!Inicializa los atributos de GameStatus
		void init(int numKeyItems, int maxLife, std::map<int,bool,std::pair<int,int>> tools, int actualMoney,
					std::pair<int,std::pair<int,int>> actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPidgeons,
					int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress);

		//!Getter de numKeyItems
		/*!
			\return numKeyItems
		*/
		int getNumKeyItems();
		
		//!Setter de numKeyItems
		/*!
			\param numKeyItems nuevo valor para numKeyItems
		*/
		void setNumKeyItems(int numKeyItems);

		//!Getter de maxLife
		/*!
			\return maxLife
		*/
		int getMaxLife();

		//!Setter de maxLife
		/*!
			\param maxLife nuevo valor para maxLife
		*/
		void setMaxLife(int maxLife);

		//!Getter de tools
		/*!
			\return el mapa de tools
		*/
		std::map<int, std::tr1::tuple<bool,int,int>> getTools();
		
		//!Setter de tools
		/*!
			\param tools mapa de tools que queremos añadir
		*/
		void setTools(std::map<int, std::tr1::tuple<bool,int,int>> tools);

		//!Busca un elemento en el mapa de tools y obtiene toda la información relacionada
		/*!
			\param idTool id de la tool sobre la que queremos realizar la bísqueda
			\return std::tr1::tuple<bool,int,int> una tupla con la información de idTool
		*/
		std::tr1::tuple<bool,int,int> getToolInfo(int idTool);

		//!Actualiza la información de una herramienta dada
		/*!
			Los parametros a actualizar o insertar de la herramienta son:
			\param idTool id de la herramienta que queremos actualizar
			\param available indica si la herramienta estará o no disponible para el uso del jugador
			\param idAmmo id de la munición de la herramienta dada
			\param ammoQuantity cantidad de munición disponible para la herramienta
			\return tupla con toda la información de la idTool
		*/
		void setTool(int idTool, bool available, int idAmmo, int ammoQuantity);

		//! Indica si una herramienta dada está o no disponible
		/*!
			\param idTool herramienta sobre la que se realiza la petición
			\return true si se puede usar false sino
		*/
		bool isToolAvailable(int idTool);

		//!Actualiza la información sobre la disponibilidad de una herramienta dada
		/*!
			\param idTool id de la herramienta a actualizar
		*/
		void setToolAvailable(int idTool);

		//!Devuelve el tipo de munición que usa una herramienta
		/*!
			\param idTool identificador de la herramienta a modificar
			\return id de la munición
		*/
		int getToolAmmoId(int idTool);

		//!Devuelve la cantidad de munición disponible para una herramienta dada
		/*!
			\param idTool identificador de la herramienta dada
			\return cantidad de munición disponible
		*/
		int getToolAmmoQuantity(int idTool);

		//!Asigna el tipo de munición de una herramienta dada
		/*!
			\param idTool id de la herramienta a actualizar
			\param idAmmo id del tipo de munición a asignar
		*/
		void setToolAmmo(int idTool, int idAmmo);

		//!Establece la cantidad de munición de una herramienta dada
		/*!
			\param idTool identificador de la herramienta a actualizar
			\param ammoQuantity cantidad de munición que tendrá dicha herramienta
		*/
		void setToolAmmoQuantity(int idTool, int ammoQuantity);

		//! Getter de actualMoney
		/*!
			\return actualMoney
		*/
		int getActualMoney();

		//!Setter de actualMoney
		/*!
			\param actualMoney
		*/
		void setActualMoney(int actualMoney);

		//!Getter de actualScreen
		/*!
			\return actualScreen como un struct definido en HelperTypes
		*/
		MapId getActualScreen();

		//!Setter de actualScreen
		/*!
			\param actualScreen
		*/
		void setActualScreen(MapId acualtScreen);

		std::pair<int,int> getLastPos();
		void setLastPos(std::pair<int,int> lastPos);

		int getNumPlayers();
		void setNumPlayers(int numPlayers);

		int getNumPidgeons();
		void setNumPidgeons(int numPidgeons);

		int getHeartPieces();
		void setHeartPieces(int heartPieces);

		int getMaxHeartPieces();
		int setMaxHeartPieces(int maxHeartPieces);

		int getBarterProgress();
		void setBarterProgress(int barterProgress);

		int getGameProgress();
		void setGameProgress(int gameProgress);
};

#endif