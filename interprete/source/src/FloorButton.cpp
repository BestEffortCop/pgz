#include "FloorButton.h"

FloorButton::FloorButton(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
{
	graphic = new Stamp("data/graphics/cursorM.png", g->getGfxEngine());
	mask = new MaskBox(x, y, 16, 16, "puzzle");
	onceSolved = false;
	onceUnsolved = true;
}
FloorButton::~FloorButton()
{
};


void FloorButton::init(GamePuzzle* puzzle)
{



	GamePuzzleElement::init(puzzle);
}

void FloorButton::onStep()
{
	if (isPuzzleSolved())
		graphic->setColor(Color::Red);
	else
		graphic->setColor(Color::White);

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