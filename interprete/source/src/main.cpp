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

#include "PGZGame.h"
//#include "vld.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//#ifdef _DEBUG
   #ifndef DBG_NEW
     #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
//#endif  // _DEBUG

int main()
{
	// Hm... Load config...
	/* Autobreakpoints para los memblocks sin liberar
		Esto hace que se interrumpa el asunto al
		allocar la memoria que indica. Muy util :D */
	// bloques 142~148 - ??
	// bloques 166~173 - Engine thingies que parece que no se liberan pero sí se hace (creo)
	//_CrtSetBreakAlloc(142); // <- no lo pilla
	//_CrtSetBreakAlloc(2631); // el fondo del menú

	PGZGame* g = new PGZGame();

	while (!g->isFinished())
		g->step();

	delete g;

	//_CrtDumpMemoryLeaks();

	return 0;
}
