#include "box.h"

const int BOX_SPEED = 1;

Box::Box()
{
	x = 5;
	y = 5;
}

void Box::followPlayer(Player p)
{
	int pX = p.getX(), pY = p.getY();
	int bX = this->getX(), bY = this->getY();
	if (sqrt((pX - bX)*(pX - bX) + (pY - bY)*(pY - bY)) > 3)
	{
		if (pX < bX && pY == bY)
		{
			this->moveLeft();
		}
		else if(pX > bX && pY==bY)
		{
			this->moveRight();
		}

		if (pY < bY && pX == bX)
		{
			this->moveUp();
		}
		else if(pY > bY && pX == bX)
		{
			this->moveDown();
		}

		if (pY < bY && pX < bY)
		{
			this->moveDiagonalUpDownRight();
		}
		else if (pY > bY && pX < bX)
		{
			this->moveDiagonalUpDownLeft();
		}
	}
}

void Box::moveUp()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setY(this->getY() - BOX_SPEED);
}
void Box::moveDown()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setY(this->getY() + BOX_SPEED);
}
void Box::moveLeft()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setX(this->getX() - BOX_SPEED);
}
void Box::moveRight()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setX(this->getX() + BOX_SPEED);
}
void Box::moveDiagonalUpDownRight()
{
	this->setShadowX(this->getX() - 1);
	this->setShadowY(this->getY());
	this->setY(this->getY() - BOX_SPEED);
}
void Box::moveDiagonalUpDownLeft()
{
	this->setShadowX(this->getX() + 1);
	this->setShadowY(this->getY());
	this->setY(this->getY() - BOX_SPEED);
}

void Box::drawBox()
{
	cursorPosition(this->getX(), this->getY());
	cout << '#';
	cursorPosition(this->getShadowX(), this->getShadowY());
	cout << '*';
	return;
}

void Box::cursorPosition(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
}