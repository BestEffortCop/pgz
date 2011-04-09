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
		allocar la memoria que indica. Muy util :D 
	_CrtSetBreakAlloc(930);
	_CrtSetBreakAlloc(937);
	_CrtSetBreakAlloc(939);
	_CrtSetBreakAlloc(941);
	_CrtSetBreakAlloc(943);
	_CrtSetBreakAlloc(945);*/

	PGZGame* g = new PGZGame();

	while (!g->isFinished())
		g->step();

	delete g;

	_CrtDumpMemoryLeaks();

	return 0;
}
