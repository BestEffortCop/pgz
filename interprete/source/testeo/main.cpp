#include "PGZGame.h"

int main()
{
	// Hm... Load config...

	PGZGame* g = new PGZGame();

	while (!g->isFinished())
		g->step();

	delete g;

	return 0;
}
