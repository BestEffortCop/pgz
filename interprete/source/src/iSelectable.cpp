#include "iSelectable.h"

iSelectable::iSelectable(int x, int y, int w, int h)
{
	this->menuController = NULL;
	mask = new MaskBox(x, y, w, h, "selectable");
	cursorLocation = NONE;
	cursorH = 8;
	cursorW = 8;
	setCursorPlace(cursorLocation);

	enabled = true;
}

iSelectable::~iSelectable()
{
	delete mask;
}

void iSelectable::setMenuController(GameMenuController* menuController)
{
	this->menuController = menuController;
}

void iSelectable::setDimension(int x, int y, int w, int h)
{
	delete mask;
	mask = new MaskBox(w, y, w, h, "selectable");
	
	setCursorPlace(cursorLocation);
}

void iSelectable::setCursorLocation(Direction dir)
{
	cursorLocation = dir;
	setCursorPlace(dir);
}

void iSelectable::setCursorPlace(Direction dir)
{
	switch (dir)
	{
		case UP:
			cursorPlaceX = mask->x + (mask->width / 2) - (cursorW / 2);
			cursorPlaceY = mask->y - cursorH;
			break;
		case DOWN:
			cursorPlaceX = mask->x + (mask->width / 2) - (cursorW / 2);
			cursorPlaceY = mask->y + mask->height;
			break;
		case LEFT:
			cursorPlaceX = mask->x - cursorW;
			cursorPlaceY = mask->y + (mask->height / 2) - (cursorH / 2);
			break;
		case RIGHT:
			cursorPlaceX = mask->x + mask->width;
			cursorPlaceY = mask->y + (mask->height / 2) - (cursorH / 2);
			break;
		case UPLEFT:
			cursorPlaceX = mask->x - cursorW;
			cursorPlaceY = mask->y - cursorH;
			break;
		case UPRIGHT:
			cursorPlaceX = mask->x + mask->width;
			cursorPlaceY = mask->y - cursorH;
			break;
		case DOWNLEFT:
			cursorPlaceX = mask->x - cursorW;
			cursorPlaceY = mask->y + mask->height;
			break;
		case DOWNRIGHT:
			cursorPlaceX = mask->x + mask->width;
			cursorPlaceY = mask->y + mask->height;
			break;
		case NONE:
			cursorPlaceX = mask->x;
			cursorPlaceY = mask->y;
			break;
	};
}

void iSelectable::setSelected()
{
	menuController->setSelected(this);
}

bool iSelectable::isSelected()
{
	return menuController->selected == this;
}

void iSelectable::onSelected()
{
	menuController->onSelected(this);
}

void iSelectable::onDeselected()
{
	menuController->onDeselected(this);
}

void iSelectable::onBeingDeselected()
{
	menuController->onBeingDeselected(this);
}

void iSelectable::onChosen()
{
	menuController->onChosen(this);
}

void iSelectable::onCancelled()
{
	menuController->onCancelled(this);
}

void iSelectable::onIddle()
{
	menuController->onIddle(this);
}

void iSelectable::onStartPressed()
{
	menuController->onStartPressed(this);
}

void iSelectable::onSelectPressed()
{
	menuController->onSelectPressed(this);
}
