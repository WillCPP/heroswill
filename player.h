#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <fstream>
#include "entity.h"

using namespace std;

class Player : public Entity
{/*
private:
	int x, y;
	int shadow_x, shadow_y;
	int spawn_x, spawn_y;
	int check_x, check_y;
	bool collide_up, collide_down, collide_left, collide_right;//*/
	
public:
	Player();

	int playerLevel, exp, str, dex, con, intel, wis, cha;
	string m_name;

	void getPlayerName();
	void showPlayerName();
	void setPlayerName();
	void showInfo();
	void setStats();

	void updateShadow();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	string get_m_name() { return m_name; }
	void set_m_name(string n) { m_name = n; return; }
	int getPlayerLevel() { return playerLevel; }
	int getExp() { return exp; }
	int getStr() { return str; }
	int getDex() { return dex; }
	int getCon() { return con; }
	int getIntel() { return intel; }
	int getWis() { return wis; }
	int getCha() { return cha; }
};

#endif