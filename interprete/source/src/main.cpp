#include "PGZGame.h"

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

	PGZGame* g = new PGZGame();

	while (!g->isFinished())
		g->step();

	delete g;

	_CrtDumpMemoryLeaks();

	return 0;
}
