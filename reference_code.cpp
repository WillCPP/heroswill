#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

const int P = 112;
const int W = 119;
const int A = 97;
const int S = 115;
const int D = 100;

const string WALL_VERTICAL = "|";
const string WALL_HORIZONTAL = "-";
const string WALL_CORNER = "+";
const string WALL_DIAG_RIGHT = "/";
const string WALL_DIAG_LEFT = "\\";

const int MAP_HEIGHT = 20;
const int MAP_WIDTH = 60;

const int MAX_PLAYER_TOP = 1;
const int MAX_PLAYER_BOTTOM = MAP_HEIGHT - 2;
const int MAX_PLAYER_LEFT = 1;
const int MAX_PLAYER_RIGHT = MAP_WIDTH - 2;
const int PLAYER_WALK_SPEED = 1;

struct Player
{
	int x = 1, y = 1;
	int shadow_x, shadow_y;
	int spawn_x = 1, spawn_y = 1;
	int check_x, check_y;
	string m_name;

	bool collide_up, collide_down, collide_left, collide_right;

	int playerLevel, exp, str, dex, con, intel, wis, cha;
};

struct Level
{
	int numberOfLevels, currentLevelInt;
	string currentLevelString, levelName;
	string map[MAP_HEIGHT][MAP_WIDTH];
};

void getPlayerName(string &);
void showPlayerName(string);
void flushScreen();
void loadLevel(int, string&, string&, string[MAP_HEIGHT][MAP_WIDTH]);
void loadLevelAlt(Level &);
void drawLevel(string[MAP_HEIGHT][MAP_WIDTH]);
void updatePlayerPosistion(Player &, Level &);
void collisionDetection(Player &, Level);
void drawPlayerPosition(Player);
void cursorPosition(int, int);
void startGame(Player &, Level &);
void showInfo(Player, Level);
void saveGame(Player, Level);
void setStats(Player &);

int main()
{
	Player player;
	//Map map;
	Level level;

	startGame(player, level);
	system("pause");
	flushScreen();
	//loadLevel(level.numberOfLevels, level.currentLevelString, level.levelName, level.map);
	loadLevelAlt(level);
	drawLevel(level.map);
	//showInfo(player, level); //moved to game loop
	//cursorPosition(player.x, player.y);
	updatePlayerPosistion(player, level);

	saveGame(player, level);

	system("pause");
	return 0;
}

//sets player name //gets data from file
void getPlayerName(string &name)
{
	string print;
	ifstream infile;
	infile.open("intro.txt");
	while (!infile.eof())
	{
		getline(infile, print);
		cout << print << endl;
	}
	cout << ">> ";
	getline(cin, name);
	return;
}

//shows player name // gets data from file
void showPlayerName(string name)
{
	string print;
	ifstream infile;
	infile.open("begin.txt");

	while (!infile.eof())
	{
		getline(infile, print);
		cout << print << endl;
	}
	cout << name << ", your adventure starts now!" << endl << endl;
	return;
}

//clears the screen
void flushScreen()
{
	system("cls");
	return;
}

//depricated
void loadLevel(int numberOfLevels, string &currentLevelString, string &levelName, string levelMap[MAP_HEIGHT][MAP_WIDTH])
{
	ifstream infile, levelfile;
	infile.open("current_level.txt");
	infile >> currentLevelString;
	infile.close();
	levelName = "levels/level" + currentLevelString + ".txt";
	levelfile.open(levelName);

	int j = 0;
	while (!levelfile.eof())
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			levelfile >> levelMap[j][i];
		}
		j++;
	}
	levelfile.close();
	return;
}

//
void loadLevelAlt(Level &level)
{
	ifstream infile, levelfile;
	//infile.open("current_level.txt");
	//infile >> level.currentLevelString;
	infile.close();
	level.levelName = "levels/level" + level.currentLevelString + ".txt";
	levelfile.open(level.levelName);

	int j = 0;
	while (!levelfile.eof())
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			levelfile >> level.map[j][i];
		}
		j++;
	}
	levelfile.close();
	return;
}

//
void drawLevel(string levelMap[MAP_HEIGHT][MAP_WIDTH])
{
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			cout << levelMap[j][i];
		}
		cout << endl;
	}
	return;
}

//
void updatePlayerPosistion(Player &player, Level &level)
{
	int input;

	player.shadow_x = player.spawn_x;
	player.shadow_y = player.spawn_y;
	showInfo(player, level);
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
			if (player.y != MAX_PLAYER_TOP && !player.collide_up)
			{
				player.shadow_x = player.x;
				player.shadow_y = player.y;
				player.y -= PLAYER_WALK_SPEED;
			}
		}
		else if (input == S)
		{
			if (player.y != MAX_PLAYER_BOTTOM && !player.collide_down)
			{
				player.shadow_x = player.x;
				player.shadow_y = player.y;
				player.y += PLAYER_WALK_SPEED;
			}
		}
		else if (input == A)
		{
			if (player.x != MAX_PLAYER_LEFT && !player.collide_left)
			{
				player.shadow_x = player.x;
				player.shadow_y = player.y;
				player.x -= PLAYER_WALK_SPEED;
			}
		}
		else if (input == D)
		{
			if (player.x != MAX_PLAYER_RIGHT && !player.collide_right)
			{
				player.shadow_x = player.x;
				player.shadow_y = player.y;
				player.x += PLAYER_WALK_SPEED;
			}
		}
		drawPlayerPosition(player);
	} while (input != P);

	return;
}

//
void collisionDetection(Player &player, Level level)
{
	player.collide_up = false;
	player.collide_down = false;
	player.collide_left = false;
	player.collide_right = false;

	if (level.map[player.y - 1][player.x] == WALL_CORNER || level.map[player.y - 1][player.x] == WALL_DIAG_LEFT || level.map[player.y - 1][player.x] == WALL_DIAG_RIGHT || level.map[player.y - 1][player.x] == WALL_HORIZONTAL || level.map[player.y - 1][player.x] == WALL_VERTICAL)
	{
		/*if (level.map[player.y - 1][player.x] == WALL_CORNER)
		{
		cout << "1";
		}
		if (level.map[player.y - 1][player.x] == WALL_DIAG_LEFT)
		{
		cout << "2";
		}
		if (level.map[player.y - 1][player.x] == WALL_DIAG_RIGHT)
		{
		cout << "3";
		}
		if (level.map[player.y - 1][player.x] == WALL_HORIZONTAL)
		{
		cout << "4";
		}
		if (level.map[player.y - 1][player.x] == WALL_VERTICAL)
		{
		cout << "5";
		}*/
		player.collide_up = true;
	}
	if (level.map[player.y + 1][player.x] == WALL_CORNER || level.map[player.y + 1][player.x] == WALL_DIAG_LEFT || level.map[player.y + 1][player.x] == WALL_DIAG_RIGHT || level.map[player.y + 1][player.x] == WALL_HORIZONTAL || level.map[player.y + 1][player.x] == WALL_VERTICAL)
	{
		player.collide_down = true;
	}
	if (level.map[player.y][player.x - 1] == WALL_CORNER || level.map[player.y][player.x - 1] == WALL_DIAG_LEFT || level.map[player.y][player.x - 1] == WALL_DIAG_RIGHT || level.map[player.y][player.x - 1] == WALL_HORIZONTAL || level.map[player.y][player.x - 1] == WALL_VERTICAL)
	{
		player.collide_left = true;
	}
	if (level.map[player.y][player.x + 1] == WALL_CORNER || level.map[player.y][player.x + 1] == WALL_DIAG_LEFT || level.map[player.y][player.x + 1] == WALL_DIAG_RIGHT || level.map[player.y][player.x + 1] == WALL_HORIZONTAL || level.map[player.y][player.x + 1] == WALL_VERTICAL)
	{
		player.collide_right = true;
	}

	return;
}

//
void drawPlayerPosition(Player player)
{
	cursorPosition(player.x, player.y);
	cout << '@';
	cursorPosition(player.shadow_x, player.shadow_y);
	cout << '*';
	return;
}

//
void cursorPosition(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
}

//load game or new game
void startGame(Player &player, Level &level)
{
	string print, input;
	//string::size_type sizeptr;
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
		playerFile >> player.m_name >> level.currentLevelString >> player.playerLevel >> player.exp >> player.str >> player.dex >> player.con >> player.intel >> player.wis >> player.cha;
		level.currentLevelInt = stoi(level.currentLevelString);
		flushScreen();
	}
	else if (input == "2")
	{
		flushScreen();
		getPlayerName(player.m_name);
		flushScreen();
		showPlayerName(player.m_name);
		level.currentLevelString = "0";
		setStats(player);
	}
	playerFile.close();
	infile.close();
	return;
}

//
void showInfo(Player player, Level level)
{
	cout << player.m_name << " Floor: " << level.currentLevelString << " Lvl: " << player.playerLevel << " Str: " << player.str << " Dex: " << player.dex << " Con: " << player.con << " Int: " << player.intel << " Wis: " << player.wis << " Cha: " << player.cha << endl;
	return;
}

//
void saveGame(Player player, Level level)
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
			outfile << player.m_name << " " << level.currentLevelString << " " << player.playerLevel << " " << player.exp << " " << player.str << " " << player.dex << " " << player.con << " " << player.intel << " " << player.wis << " " << player.cha;
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

//
void setStats(Player &player)
{
	player.exp = 0;
	player.str = 0;
	player.dex = 0;
	player.con = 0;
	player.intel = 0;
	player.wis = 0;
	player.cha = 0;
	return;
}