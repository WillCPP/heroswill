#ifndef BOX_H
#define BOX_H

#include <string>
#include <conio.h>
#include <Windows.h>
#include "entity.h"
#include "player.h"

class Box : public Entity
{
public:
	Box();
	void followPlayer(Player p);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveDiagonalUpDownRight();
	void moveDiagonalUpDownLeft();

	void drawBox();

	void cursorPosition(int, int);
};

#endif