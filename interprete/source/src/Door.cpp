#include "Door.h"


Door::Door(int x, int y, Direction dir, Game* game, GameState* world) : Entity(x, y, game, world)
{
	graphic = new SpriteMap("data/graphics/door.png", 3, 4, game->getGfxEngine());

	// Para que el player reproduzca su animación de empujar
	mask = new MaskBox(x, y, 16, 16, "pushable");

	collidable = true;
	solid = true;
	this->dir = dir;
	closed = true;
	transition = false;

	doorType = NORMAL;

	vector<int>* fopenup = new vector<int>();
	fopenup->push_back(5);
	((SpriteMap*) graphic)->addAnim("open-up",fopenup, 0, false);

	vector<int>* fListdown = new vector<int>();
	fListdown->push_back(2);
	((SpriteMap*) graphic)->addAnim("open-dw",fListdown, 0, false);

	vector<int>* fListright = new vector<int>();
	fListright->push_back(11);
	((SpriteMap*) graphic)->addAnim("open-rg",fListright, 0, false);

	vector<int>* fListleft = new vector<int>();
	fListleft->push_back(8);
	((SpriteMap*) graphic)->addAnim("open-lf",fListleft, 0, false);



	vector<int>* fcloseup = new vector<int>();
	fcloseup->push_back(3);
	((SpriteMap*) graphic)->addAnim("close-up",fcloseup, 0, false);

	vector<int>* fclosedown = new vector<int>();
	fclosedown->push_back(0);
	((SpriteMap*) graphic)->addAnim("close-dw",fclosedown, 0, false);

	vector<int>* fcloseright = new vector<int>();
	fcloseright->push_back(9);
	((SpriteMap*) graphic)->addAnim("close-rg",fcloseright, 0, false);

	vector<int>* fcloseleft = new vector<int>();
	fcloseleft->push_back(6);
	((SpriteMap*) graphic)->addAnim("close-lf",fcloseleft, 0, false);



	vector<int>* frameListup = new vector<int>();
	frameListup->push_back(3);
	frameListup->push_back(4);
	frameListup->push_back(5);
	((SpriteMap*) graphic)->addAnim("opening-up",frameListup, 4, false);

	vector<int>* frameListdown = new vector<int>();
	frameListdown->push_back(0);
	frameListdown->push_back(1);
	frameListup->push_back(2);
	((SpriteMap*) graphic)->addAnim("opening-dw",frameListdown, 4, false);

	vector<int>* frameListright = new vector<int>();
	frameListright->push_back(9);
	frameListright->push_back(10);
	frameListright->push_back(11);
	((SpriteMap*) graphic)->addAnim("opening-rg",frameListright, 4, false);

	vector<int>* frameListleft = new vector<int>();
	frameListleft->push_back(6);
	frameListleft->push_back(7);
	frameListleft->push_back(8);
	((SpriteMap*) graphic)->addAnim("opening-lf",frameListleft, 4, false);



	vector<int>* closingup = new vector<int>();
	closingup->push_back(5);
	closingup->push_back(4);
	closingup->push_back(3);
	((SpriteMap*) graphic)->addAnim("closing-up",closingup, 4, false);

	vector<int>* closingdown = new vector<int>();
	closingdown->push_back(2);
	closingdown->push_back(1);
	closingdown->push_back(0);
	((SpriteMap*) graphic)->addAnim("closing-dw",closingdown, 4, false);

	vector<int>* closingright = new vector<int>();
	closingright->push_back(11);
	closingright->push_back(10);
	closingright->push_back(9);
	((SpriteMap*) graphic)->addAnim("closing-rg",closingright, 4, false);

	vector<int>* closingleft = new vector<int>();
	closingleft->push_back(8);
	closingleft->push_back(7);
	closingleft->push_back(6);
	((SpriteMap*) graphic)->addAnim("closing-lf",closingleft, 4, false);


	if (!closed)
		playAnimation("open");
	else
		playAnimation("close");
}

Door::~Door()
{
}

void Door::playAnimation(std::string s)
{
	switch(dir)
	{
		case UP:
			s.append("-up");
			break;
		case DOWN:
			s.append("-dw");
			break;
		case LEFT:
			s.append("-lf");
			break;
		case RIGHT:
			s.append("-rg");
			break;
	}

	((SpriteMap*) graphic)->playAnim(s);
}

void Door::onStep()
{
	if (transition)
	{
		if (((SpriteMap*) graphic)->animFinished())
		{
			if (closed)
			{
				setCollidable(true);
				solid = true;
				playAnimation("close");
			}
			else
			{
				setCollidable(false);
				solid = false;
				playAnimation("open");
			}
			transition = false;
		}
	}
}

void Door::open()
{
	if (closed)
	{
		closed = false;
		transition = true;
		playAnimation("opening");
	}
}

void Door::close()
{
	if (!closed)
	{
		closed = true;
		transition = true;
		playAnimation("closing");
	}
}

bool Door::isOpen()
{
	return (!closed && !transition);
}

void Door::setDoorType(DoorType doorType)
{
	this->doorType = doorType;
}

Door::DoorType Door::getDoorType()
{
	return doorType;
}