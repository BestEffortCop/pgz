/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __MESSAGECONTROLLER_H__
#define __MESSAGECONTROLLER_H__

#include "MessageDialog.h"
#include "Controller.h"
#include "NPC.h"
#include <vector>

class NPC;
class MessageDialog;

class MessageController {
	private:
		Controller* controller;		/* Puntero a Controller */
		vector<string>* texts;		/* Vector de textos obtenido a partir del archivo que guarda la BDD */
		TileFont* font;				/* Fuente del juego */
		TileSet* background;		/* Fondo de los textos obtenidos a partir de la BDD */
		MessageDialog* m;			/* Bocadillo de texto */
		bool flag;
		NPC* npc;					/* Puntero al NPC que lo ha invocado */
		iInteractable* interact;				/* Puntero al interactable que lo ha lanzado */

		enum MessageType { NONE, DIALOG, ITEM, NORMALMESSAGE };
		MessageType currentType;

		bool getText(string path);

	public:
		MessageController(Controller* c);
		~MessageController();

		void init(string textsPath, string fontPath, string backgroundPath);
		void showMessageDialog(int idText, NPC* npc);
		void showItemMessage(string itemName);
		void showMessage(string message, iInteractable* i = NULL);

		void onStep();
};

#endif