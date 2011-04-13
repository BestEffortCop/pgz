#ifndef HORSES
#define HORSES

#include <time.h>
#include "GenMath.h"

using namespace std;
const int LIFE = 50;
const float COLLRAD = 15;
const int RUN_STEPS = 0;
typedef struct {
	Vector2D pos;
	Vector2D vel;
	int life;
	float wandertheta;
} Horse;

class Horses {
private:
	vector<int> getHorseOrder(int inputSize);
	void recurCall(int& indx, int* subDiv, int& sizCont);
	vector<Horse> reorder(vector<Horse> hors);
	void updateRopes();

public:
	
	vector<GLine> ropes;
	vector<vector<Horse>> auxHList;

	Horses();
	void update();
	void run();
	void applyBehaviour(Horse &h);
	void avoidObstacles(Horse &h, vector<Horse> obstacles);
	vector<Horse> placeHorseLine(GLine l, float d, int p, vector<Horse>& vect);
	void placeHorses(GPolygon p, int padding);
};

#endif