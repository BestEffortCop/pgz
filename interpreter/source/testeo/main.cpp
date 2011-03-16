
#include "OneGame.h"
int main()
{
	OneGame* g = new OneGame();

	while (!g->isFinished())
		g->step();

	delete g;

	return 0;
}
