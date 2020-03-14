#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Math.h"

#include "Constants.h"
#include "BlueSky.h"
#include "LevelGoal.h"
#include "NextLevelScreen.h"
#include "NextLevelButton.h"
#include "GameOverScreen.h"
#include "TextSpriteComponent.h"
#include "ButtonComponent.h"
#include <vector>
#include <fstream>
#include "Sound.h"
#include "Music.h"
#include "PlayButton.h"
#include "MainMenuScreen.h"
#include "ReturnToMenuButton.h"
#include "GameScreen.h"

class Game
{
public:
	Game() {}
	~Game() {}

	bool Initialize();

	void Shutdown();

	void PollInput();

	void Update();

	void Render();

	void LoadNextLevelMenu();

	class Mario* GetPlayer() { return mPlayer; }
	void SetPlayerSpawnPoint(Vector2 position);

	void IncrementScore(int amount = 10);

	int GetCurrentLevel() const { return mCurrentLevel; }

	void NextLevel();
	void PlayFirstLevel();
	void ReturnToMainMenu();
	void RetryLevel();

	void OnPlayerDeath();

	SDL_Rect mCamera = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	int GetScore() const { return mScore; }
	int GetHighscore() const { return mHighScore; }


	BlueSky* GetEngine() const { return mEngine; }

	bool IsGameOver() const { return gameOver; }
	bool IsGamePaused() const { return bPaused; }

	class GameScreen* GetCurrentScreen() { return mLevels[mCurrentLevel]; } 
private:
	bool gameOver = false;
	bool bPaused = true;


	void LoadContent();

	class ScoreManager* mScoreManager = nullptr;

	class Actor* bgActor = nullptr;
	class Actor* fgActor = nullptr;

	class Mario* mPlayer = nullptr;
	class Actor* mapActor = nullptr;

	Music* mBGMusic = nullptr;

	class NextLevelScreen* mNextLevelScreen = nullptr;
	class MainMenuScreen* mMainMenu = nullptr;
	class GameOverScreen* mGameOverScreen = nullptr;

	Actor* mScoreText = nullptr;
	class TextSpriteComponent* mScoreTsc = nullptr;

	int mCurrentLevel = 0;

	int mScore = 0;
	int mHighScore = 0;

	BlueSky* mEngine = nullptr;

	GameScreen* mLevels[5];

	void LevelChange(int levelIndex);
};

