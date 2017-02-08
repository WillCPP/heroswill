#ifndef LEVEL_H
#define LEVEL_H



#include <string>
#include <fstream>
#include <iostream>

using namespace std;


class Level
{
private:
	const static int MAP_HEIGHT = 20;
	const static int MAP_WIDTH = 60;
	int numberOfLevels, currentLevelInt;
	string levelName;
public:
	string currentLevelString;

	string map[MAP_HEIGHT][MAP_WIDTH];
	void loadLevel();
	void drawLevel();
	string getCurrentLevelString();
	void setCurrentLevelString(string);
	void setCurrentLevelInt(int);
};

#endif