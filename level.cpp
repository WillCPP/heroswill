#include "level.h"

void Level::loadLevel()
{
	ifstream infile, levelfile;
	levelName = "levels/level" + currentLevelString + ".txt";
	levelfile.open(levelName);

	int j = 0;
	while (!levelfile.eof())
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			levelfile >> map[j][i];
		}
		j++;
	}
	levelfile.close();
	return;
}

void Level::drawLevel()
{
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			cout << map[j][i];
		}
		cout << endl;
	}
	return;
}

string Level::getCurrentLevelString()
{
	return currentLevelString;
}

void Level::setCurrentLevelString(string s)
{
	currentLevelString = s;
	return;
}

void Level::setCurrentLevelInt(int level)
{
	currentLevelInt = level;
	return;
}
