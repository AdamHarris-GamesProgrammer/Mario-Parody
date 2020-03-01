#include "ScoreManager.h"
#include "Game.h"

ScoreManager::ScoreManager(Game* game) {
	mGame = game;
}
int ScoreManager::LoadScore()
{
	int currentLevel = mGame->GetCurrentLevel();
	std::string currentLevelPath = "Assets/Scores/" + std::to_string(currentLevel) + ".txt";

	std::ifstream inFile;
	inFile.open(currentLevelPath);

	char scoreText[8];

	if (inFile.good()) {
		inFile >> mHighscore;
		std::cout << mHighscore << std::endl;
	}
	else
	{
		std::cout << "Cant Open file: " << currentLevelPath << " Creating file instead and setting score to 0" << std::endl;
		mHighscore = 0;
		SaveScore(mHighscore);
	}
	inFile.close();

	return mHighscore;
}

void ScoreManager::SaveScore(int newValue)
{
	int currentLevel = mGame->GetCurrentLevel();
	std::string currentLevelPath = "Assets/Scores/" + std::to_string(currentLevel) + ".txt";

	std::ofstream outFile(currentLevelPath);

	if (outFile) {
		outFile << newValue;
	}
	else
	{
		std::cout << "Cannot Open file: " << currentLevelPath << std::endl;
	}

	outFile.close();
}
