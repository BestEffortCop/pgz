#pragma once

#ifndef __MESSAGECONTROLLER_H__
#define __MESSAGECONTROLLER_H__

#include "MessageDialog.h"
#include "Controller.h"
#include "NPC.h"
#include <vector>

class NPC;

class MessageController {
	private:
		Controller* controller;		/* Puntero a Controller */
		vector<string>* texts;		/* Vector de textos obtenido a partir del archivo que guarda la BDD */
		TileFont* font;				/* Fuente del juego */
		TileSet* background;		/* Fondo de los textos obtenidos a partir de la BDD */
		MessageDialog* m;			/* Bocadillo de texto */
		bool flag;
		NPC* npc;					/* Puntero al NPC que lo ha invocado */

		bool getText(string path);

	public:
		MessageController(Controller* c);
		~MessageController();

		void init(string textsPath, string fontPath, string backgroundPath);
		void showMessageDialog(int idText, NPC* npc);

		void onStep();
};

#endif