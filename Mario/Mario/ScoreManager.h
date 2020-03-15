#pragma once

#include <fstream>
#include <iostream>
#include <string>

class ScoreManager
{
public:
	ScoreManager(class Game* game);

	//Getter/Setter for the highscore
	int GetHighscore()  { return LoadScore(); }
	void SetHighscore(int newValue) { if (newValue > mHighscore) SaveScore(newValue); } //if the newValue is greater than mHighscore then save the newValue

private:
	int mHighscore = 0;

	class Game* mGame;

	//Loads the score
	int LoadScore();
	//saves the score
	void SaveScore(int newValue);
};

