#include "NPC.h"

NPC::NPC(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world) {
	mask = new MaskBox(x, y, 12, 8, "npc", 0, 0); 
	solid = true;
	type = "npc";
}

NPC::~NPC() {}

void NPC::init(string graphicpath, int ncol, int nrow) {
	graphic = new SpriteMap(graphicpath, ncol, nrow, game->getGfxEngine());
	ox = x;
	oy = y;
	sp = 2;
	state = move;
	dir = DOWN;
	this->setTimer(0, 60); 

	vector<int>* frames = new vector<int>();
	frames->push_back(0);
	frames->push_back(1);
	frames->push_back(2);
	((SpriteMap*) graphic)->addAnim("up", frames, 3, true);

	frames = new vector<int>();
	frames->push_back(3);
	frames->push_back(4);
	frames->push_back(5);
	((SpriteMap*) graphic)->addAnim("down", frames, 4, true);

	frames = new vector<int>();
	frames->push_back(6);
	frames->push_back(7);
	frames->push_back(8);
	((SpriteMap*) graphic)->addAnim("right", frames, 4, true);

	frames = new vector<int>();
	frames->push_back(9);
	frames->push_back(10);
	frames->push_back(11);
	((SpriteMap*) graphic)->addAnim("left", frames, 4, true);

	frames = new vector<int>();
	frames->push_back(3);
	((SpriteMap*) graphic)->addAnim("idle", frames, 4, true);

	((SpriteMap*) graphic)->playAnim("idle");
}

void NPC::onStep(){
	if (state == move){
		switch (dir){
			case UP:
				if (place_free(x, y - sp)){
					if (ox - x == 16 || oy - y == 16 || ox - x == -16 || oy - y == -16){
						ox = x;
						oy = y;
						state = idle;
						((SpriteMap*) graphic)->playAnim("idle");
					}
					else{
						y -= sp;
						((SpriteMap*) graphic)->playAnim("up");
					}
				}
				else
					moveToContact(x, y - sp);
				break;
			case DOWN:
				if (place_free(x, y + sp)){
					if (ox - x == 16 || oy - y == 16 || ox - x == -16 || oy - y == -16){
						ox = x;
						oy = y;
						state = idle;
						((SpriteMap*) graphic)->playAnim("idle");
					}
					else{
						y += sp;
						((SpriteMap*) graphic)->playAnim("down");
					}
				}
				else
					moveToContact(x, y + sp);
				break;
			case LEFT:
				if (place_free(x - sp,y)){
					if (ox - x == 16 || oy - y == 16 || ox - x == -16 || oy - y == -16){
						ox = x;
						oy = y;
						state = idle;
						((SpriteMap*) graphic)->playAnim("idle");
					}
					else{
						x -= sp;
						((SpriteMap*) graphic)->playAnim("left");
					}
				}
				else
					moveToContact(x - sp, y);
				break;
			case RIGHT:
				if (place_free(x + sp,y)){
					if (ox - x == 16 || oy - y == 16 || ox - x == -16 || oy - y == -16){
						ox = x;
						oy = y;
						state = idle;
						((SpriteMap*) graphic)->playAnim("idle");
					}
					else{
						x += sp;
						((SpriteMap*) graphic)->playAnim("right");
					}
				}
				else
					moveToContact(x + sp, y);
				break;
		}
	}
}

bool NPC::animFinished() {
	return ((SpriteMap*) graphic)->animFinished();
}

void NPC::onTimer(int timer){
	int op = rand() % 2;
	int d;
	switch (timer) {
		case 0: 
			switch (op){
				case 0:
					state = idle;
					break;
				case 1:
					state = move;
					d = rand() % 4;
					switch (d){
						case 0: dir = UP;
							break;
						case 1: dir = DOWN;
							break;
						case 2: dir = LEFT;
							break;
						case 3: dir = RIGHT;
							break;
					}
					break;
			}
			break;
	}
	this->setTimer(0, rand()%60);
}

void NPC::onInteract(Player* p){
	p->Dead;
}
