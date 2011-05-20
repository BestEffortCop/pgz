#include "FloorButton.h"

FloorButton::FloorButton(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
{
	onceSolved = false;
	onceUnsolved = true;
}
FloorButton::~FloorButton()
{
};


void FloorButton::init(GamePuzzle* puzzle, std::string gfxpath)
{
	graphic = new SpriteMap(gfxpath, 2, 1, game->getGfxEngine());
	mask = new MaskBox(x, y, 16, 16, "puzzle");

	vector<int>* vsolved = new vector<int>();
	vsolved->push_back(1);
	((SpriteMap*) graphic)->addAnim("solved", vsolved, 1, false);

	vector<int>* vunsolved = new vector<int>();
	vunsolved->push_back(0);
	((SpriteMap*) graphic)->addAnim("unsolved", vunsolved, 1, false);

	GamePuzzleElement::init(puzzle);
}

void FloorButton::onStep()
{
	if (isPuzzleSolved())
		((SpriteMap*) graphic)->playAnim("solved");
	else
		((SpriteMap*) graphic)->playAnim("unsolved");

	if (!place_meeting(x, y, "player") && !place_meeting(x, y, "pushable"))
		if (!onceUnsolved)
		{
			onceUnsolved = true;
			onceSolved = false;
			unsolvePuzzle();
		}
};

void FloorButton::onCollision(CollisionPair p, Entity* other)
{
	if ((p.b == "player" || p.b == "pushable") && !onceSolved)
	{
		solvePuzzle();
		onceSolved = true;
		onceUnsolved = false;
	}
}

void FloorButton::onRender()
{/*
	if (visible && enabled)
		game->getGfxEngine()->renderRectangle(x, y, 16, 16, Color::Red, false);*/
	Entity::onRender();
};