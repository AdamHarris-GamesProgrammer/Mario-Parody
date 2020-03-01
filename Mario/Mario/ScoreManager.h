#pragma once

#include <fstream>
#include <iostream>
#include <string>

class ScoreManager
{
public:
	ScoreManager(class Game* game);

	int GetHighscore()  { return LoadScore(); }
	void SetHighscore(int newValue) { if (newValue > mHighscore) SaveScore(newValue); }

private:
	int mHighscore = 0;

	class Game* mGame;

	int LoadScore();
	void SaveScore(int newValue);
};

