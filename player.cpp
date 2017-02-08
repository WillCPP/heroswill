#include "player.h"

using namespace std;

const int PLAYER_WALK_SPEED = 1;

Player::Player()
{
	spawn_x = 1;
	spawn_y = 1;
	x = spawn_x;
	y = spawn_y;
}

void Player::getPlayerName()
{
	cout << m_name << ", your adventure starts now!" << endl << endl;
	return;
}

void Player::showPlayerName()
{
	string print;
	ifstream infile;
	infile.open("begin.txt");

	while (!infile.eof())
	{
		getline(infile, print);
		cout << print << endl;
	}
	infile.close();
	cout << m_name << ", your adventure starts now!" << endl << endl;
	return;
}

void Player::setPlayerName()
{
	getline(cin, m_name);
	return;
}

void Player::showInfo()
{
	cout << m_name << " Lvl: " << playerLevel << " Str: " << str << " Dex: " << dex << " Con: " << con << " Int: " << intel << " Wis: " << wis << " Cha: " << cha << endl;
	return;
}

void Player::setStats()
{
	exp = 0;
	str = 0;
	dex = 0;
	con = 0;
	intel = 0;
	wis = 0;
	cha = 0;
	return;
}

void Player::updateShadow()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
}

void Player::moveUp()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setY(this->getY() - PLAYER_WALK_SPEED);
}
void Player::moveDown()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setY(this->getY() + PLAYER_WALK_SPEED);
}
void Player::moveLeft()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setX(this->getX() - PLAYER_WALK_SPEED);
}
void Player::moveRight()
{
	this->setShadowX(this->getX());
	this->setShadowY(this->getY());
	this->setX(this->getX() + PLAYER_WALK_SPEED);
}