#include "game.h"
#include "player.h"
#include "level.h"

using namespace std;

const int P = 112;
const int W = 119;
const int A = 97;
const int S = 115;
const int D = 100;//*/

const string WALL_VERTICAL = "|";
const string WALL_HORIZONTAL = "-";
const string WALL_CORNER = "+";
const string WALL_DIAG_RIGHT = "/";
const string WALL_DIAG_LEFT = "\\";

const int MAP_HEIGHT = 20;
const int MAP_WIDTH = 60;//*/

const int MAX_PLAYER_TOP = 1;
const int MAX_PLAYER_BOTTOM = MAP_HEIGHT - 2;
const int MAX_PLAYER_LEFT = 1;
const int MAX_PLAYER_RIGHT = MAP_WIDTH - 2;
const int PLAYER_WALK_SPEED = 1;//*/

Game::Game()
{
	
}

void Game::startUp(Player* player, Level* level)
{
	string print, input;
	ifstream infile, playerFile;
	infile.open("startgame.txt");
	while (!infile.eof())
	{
		getline(infile, print);
		cout << print << endl;
	}
	do
	{
		cout << ">> ";
		getline(cin, input);
	} while (input != "1" && input != "2");
	if (input == "1")
	{
		playerFile.open("playerInfo.txt");
		playerFile >> player->m_name >> level->currentLevelString >> player->playerLevel >> player->exp >> player->str >> player->dex >> player->con >> player->intel >> player->wis >> player->cha;
		level->setCurrentLevelInt(stoi(level->currentLevelString));
		flushScreen();
	}
	else if (input == "2")
	{
		flushScreen();
		player->getPlayerName();
		flushScreen();
		player->showPlayerName();
		level->setCurrentLevelString("0");
		player->setStats();
	}
	playerFile.close();
	infile.close();
	return;
}

void Game::beginGame()
{
	string print;
	ifstream infile;
	infile.open("begin.txt");

	while (!infile.eof())
	{
		getline(infile, print);
		cout << print << endl;
	}

	return;
}

void Game::flushScreen()
{
	system("cls");
	return;
}

void Game::collisionDetection(Player* player, Level* level)
{
	player->setCollideUp(false);
	player->setCollideDown(false);
	player->setCollideLeft(false);
	player->setCollideRight(false);

	if (level->map[player->getY() - 1][player->getX()] == WALL_CORNER || 
		level->map[player->getY() - 1][player->getX()] == WALL_DIAG_LEFT ||
		level->map[player->getY() - 1][player->getX()] == WALL_DIAG_RIGHT ||
		level->map[player->getY() - 1][player->getX()] == WALL_HORIZONTAL ||
		level->map[player->getY() - 1][player->getX()] == WALL_VERTICAL)
	{
		player->setCollideUp(true);
	}
	if (level->map[player->getY() + 1][player->getX()] == WALL_CORNER ||
		level->map[player->getY() + 1][player->getX()] == WALL_DIAG_LEFT ||
		level->map[player->getY() + 1][player->getX()] == WALL_DIAG_RIGHT ||
		level->map[player->getY() + 1][player->getX()] == WALL_HORIZONTAL ||
		level->map[player->getY() + 1][player->getX()] == WALL_VERTICAL)
	{
		player->setCollideDown(true);
	}
	if (level->map[player->getY()][player->getX() - 1] == WALL_CORNER ||
		level->map[player->getY()][player->getX() - 1] == WALL_DIAG_LEFT ||
		level->map[player->getY()][player->getX() - 1] == WALL_DIAG_RIGHT ||
		level->map[player->getY()][player->getX() - 1] == WALL_HORIZONTAL ||
		level->map[player->getY()][player->getX() - 1] == WALL_VERTICAL)
	{
		player->setCollideLeft(true);
	}
	if (level->map[player->getY()][player->getX() + 1] == WALL_CORNER ||
		level->map[player->getY()][player->getX() + 1] == WALL_DIAG_LEFT ||
		level->map[player->getY()][player->getX() + 1] == WALL_DIAG_RIGHT ||
		level->map[player->getY()][player->getX() + 1] == WALL_HORIZONTAL ||
		level->map[player->getY()][player->getX() + 1] == WALL_VERTICAL)
	{
		player->setCollideRight(true);
	}

	return;
}

void Game::cursorPosition(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
}

void Game::drawPlayerPosition(Player* player)
{
	cursorPosition(player->getX(), player->getY());
	cout << '@';
	cursorPosition(player->getShadowX(), player->getShadowY());
	cout << '*';
	return;
}

//deprecated
void Game::updatePlayerPosition(Player *player, Level *level)
{
	int input;

	//player->setShadowX(player->getSpawnX());
	//player->setShadowY(player->getSpawnY());
	player->updateShadow();
	//player->showInfo();
	do //main game loop
	{
		input = _getch();
		collisionDetection(player, level);
		if (input == P)
		{
			break;
		}
		else if (input == W)
		{
			if (player->getY() != MAX_PLAYER_TOP && !player->getCollideUp())
			{
				player->setShadowX(player->getX());
				player->setShadowY(player->getY());
				player->setY(player->getY() - PLAYER_WALK_SPEED);
			}
		}
		else if (input == S)
		{
			if (player->getY() != MAX_PLAYER_BOTTOM && !player->getCollideDown())
			{
				player->setShadowX(player->getX());
				player->setShadowY(player->getY());
				player->setY(player->getY() + PLAYER_WALK_SPEED);
			}
		}
		else if (input == A)
		{
			if (player->getX() != MAX_PLAYER_LEFT && !player->getCollideLeft())
			{
				player->setShadowX(player->getX());
				player->setShadowY(player->getY());
				player->setX(player->getX() - PLAYER_WALK_SPEED);
			}
		}
		else if (input == D)
		{
			if (player->getX() != MAX_PLAYER_RIGHT && !player->getCollideRight())
			{
				player->setShadowX(player->getX());
				player->setShadowY(player->getY());
				player->setX(player->getX() + PLAYER_WALK_SPEED);
			}
		}
		drawPlayerPosition(player);
	} while (input != P);

	return;
}

void Game::saveGame(Player *player, Level *level)
{
	char input;
	ofstream outfile;
	flushScreen();
	cout << "Would you like to save your game?[Y or N]" << endl;
	cin >> input;
	do
	{
		if (input == 'y')
		{
			outfile.open("playerInfo.txt");
			outfile << player->get_m_name() 
				<< " " << level->getCurrentLevelString() 
				<< " " << player->getPlayerLevel() 
				<< " " << player->getExp() << " " 
				<< player->getStr() << " " 
				<< player->getDex() << " " 
				<< player->getCon() << " " 
				<< player->getIntel() << " " 
				<< player->getWis() << " " 
				<< player->getCha();
			cout << "Thou adventure has been recorded in the scrolls of eternity." << endl;
		}
		else if (input == 'n')
		{
			cout << "Thou adventure shall not be recorded in the scrolls of eternity." << endl;
		}
		else
		{
			cout << "Error: That is not a valid option." << endl;
		}
	} while (input != 'y' && input != 'n');
	return;
}

//wip
void Game::drawPosition(Entity* b)
{
	cursorPosition(b->getX(), b->getY());
	cout << "#";
	return;
}

//wip
void Game::drawPlayerPosition(Player* player, Entity* b)
{
	cursorPosition(player->getX(), player->getY());
	cout << '@';
	cursorPosition(player->getShadowX(), player->getShadowY());
	cout << '*';
	drawPosition(b);
	return;
}

bool Game::manageInput(int input, Player* player)
{
	if (input == P)
	{
		return false;
	}
	else if (input == W)
	{
		if (player->getY() != MAX_PLAYER_TOP && !player->getCollideUp())
		{
			player->moveUp();
		}
	}
	else if (input == S)
	{
		if (player->getY() != MAX_PLAYER_BOTTOM && !player->getCollideDown())
		{
			player->moveDown();
		}
	}
	else if (input == A)
	{
		if (player->getX() != MAX_PLAYER_LEFT && !player->getCollideLeft())
		{
			player->moveLeft();
		}
	}
	else if (input == D)
	{
		if (player->getX() != MAX_PLAYER_RIGHT && !player->getCollideRight())
		{
			player->moveRight();
		}
	}
	return true;
}