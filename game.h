#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "player.h"
#include "level.h"

using namespace std;

class Game
{
private:
	
public:
	Game();
	void startUp(Player*, Level*);
	void beginGame();
	void flushScreen();
	void collisionDetection(Player* player, Level* level);
	void cursorPosition(int, int);
	void drawPlayerPosition(Player*);
	void updatePlayerPosition(Player*, Level*);
	void saveGame(Player*, Level*);

	void drawPosition(Entity*);
	void drawPlayerPosition(Player*, Entity*);
	bool manageInput(int, Player*);
};

#endif
