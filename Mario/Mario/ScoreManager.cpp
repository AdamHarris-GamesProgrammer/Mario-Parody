#include "ScoreManager.h"
#include "Game.h"

ScoreManager::ScoreManager(Game* game) {
	mGame = game; //sets mGame
}
int ScoreManager::LoadScore()
{
	//Gets the current level
	int currentLevel = mGame->GetCurrentLevel();
	std::string currentLevelPath = "Assets/Scores/" + std::to_string(currentLevel) + ".txt"; //creates the filepath for the current level file path

	//Opens the file
	std::ifstream inFile;
	inFile.open(currentLevelPath);

	char scoreText[8];

	if (inFile.good()) { //if file exists
		inFile >> mHighscore; //gets the highscore from the file
		std::cout << mHighscore << std::endl;
	}
	else //file does not exist
	{
		std::cout << "Cant Open file: " << currentLevelPath << " Creating file instead and setting score to 0" << std::endl;
		mHighscore = 0;
		SaveScore(mHighscore);
	}
	inFile.close(); //closes file

	return mHighscore; //returns highscore
}

void ScoreManager::SaveScore(int newValue)
{
	//Gets the current level
	int currentLevel = mGame->GetCurrentLevel();
	std::string currentLevelPath = "Assets/Scores/" + std::to_string(currentLevel) + ".txt"; //constucts the filepath for the current level

	//opens the file
	std::ofstream outFile(currentLevelPath);

	
	if (outFile) { //if the file exists
		outFile << newValue; //send the score to the file
	}
	else //if the file does not exist
	{
		std::cout << "Cannot Open file: " << currentLevelPath << std::endl;
	}

	outFile.close(); //closes the file
}
