#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <windows.h>
#include "game.h"
#include "level.h"
#include "player.h"

#include "box.h"

using namespace std;

int main()
{
	Game* game = new Game();
	Level* level = new Level();
	Player* player = new Player();
	bool continue_game = true;

	game->startUp(player, level);
	game->flushScreen();
	game->beginGame();
	player->getPlayerName();

	system("pause");
	game->flushScreen();

	level->loadLevel();
	level->drawLevel();

	player->showInfo();
	
	Box box;
	game->cursorPosition(box.getX(), box.getY());
	cout << "#";//*/

	//game->updatePlayerPosition(player, level);
	
	//New game loop
	int input;
	player->updateShadow();
	while (continue_game)
	{
		//update
		input = _getch();
		game->collisionDetection(player, level);
		continue_game = game->manageInput(input, player);
		box.followPlayer(*player);
		//draw
		game->drawPlayerPosition(player);
		box.drawBox();
	}

	game->saveGame(player, level);
	system("pause");
	return 0;
}